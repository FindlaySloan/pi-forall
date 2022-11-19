#include <vector>
#include <functional>
#include <thread>
#include <optional>
#include <iostream>
#include <system_error>
#include <map>
#include "LockingCQueue.hpp"
#include "Semaphore.hpp"

//////////////////////////////////////
// GLOBAL STATE AND HELPER FUNCTION //
//////////////////////////////////////

// map of threads
std::map<int, std::thread*> pidsMap;
std::mutex pidMutex;

// map of channels
std::map<int, void*> channelsMap;
std::mutex channelMutex;

// Helper functions for pids
std::thread* getThread(int pid) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(pidMutex);

  // return the information
  return pidsMap[pid];
}

void addThread(int pid, std::thread* t) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(pidMutex);

  // Adding the thread, will never overwrite
  pidsMap[pid] = t;
}

// Helper functions for channels
void* getChannel(int chid) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(channelMutex);

  //  returning the channel
  return channelsMap[chid];
}

template <typename A>
void addChannel(int chid, LockingCQueue<A>* queue) {
  // Aquireing the lock
  std::lock_guard<std::mutex> lock(channelMutex);

  // adding the channel
  channelsMap[chid] = queue;
}

////////////////////////////
// CONCURRENCY PRIMITIVES //
////////////////////////////

// The spawn function, other args should be erased
std::optional<int> spawn(int pid, std::function<void(void)> f) {
  try {
    std::thread* t= new std::thread(f);

    addThread(pid, t);

  } catch (std::system_error) {
    return {};
  }
  return pid;
}

template <typename A>
std::optional<LockingCQueue<A>*> link(int chid) {
  
  LockingCQueue<A>* q = new LockingCQueue<A>();

  addChannel(chid, q);

  return q;
  
}

///////////////////////////////
// PIPELINE HELPER FUNCTIONS //
///////////////////////////////

template <typename A>
void producerWrapper(LockingCQueue<std::optional<A>>* channel, std::vector<A> input) {
  for (auto i : input) {
    channel->enqueue(i);
  }

  channel->enqueue({});
}

template <typename A>
void farmProducerWrapper(const std::vector<LockingCQueue<std::optional<A>>*> channels, std::vector<A> input) {
  int ch = 0;

  for (A i : input) {
    std::cout << "producer sent " << i << " along channel " << ch <<std::endl;
    channels[ch]->enqueue(i);
    // Increment the channel
    ch++;

    if (ch >= channels.size()) {
      std::cout << "reset at " << i << " " << ch << std::endl;
      ch = 0;
    }
  }

  for(LockingCQueue<std::optional<A>>* c : channels) {
    c->enqueue({});
  }
}

template <typename A, typename B>
void workerWrapper(LockingCQueue<std::optional<A>>* in, LockingCQueue<std::optional<B>>* out, std::function<B(A)> f) {
  std::optional<A> input = in->dequeue();

  while(input.has_value()) {
    std::cout << "recieved " << input.value() << std::endl;
    B output = f(input.value());

    out->enqueue(output);
    std::cout << "sent " << input.value() << " along " << out << std::endl;
    input = in->dequeue();
  }

  out->enqueue({});
}

/////////////////////
// CREATE PIPELINE //
/////////////////////
template <typename A, typename B, typename C>
std::vector<C> createPipeline2(
  int producerPid,
  int stage1Pid,
  int stage2Pid,
  int pToS1Chid,
  int s1ToS2Chid,
  int s2toCChid, 
  std::vector<A> input,
  std::function<B(A)> f,
  std::function<C(B)> g
) {

  // Create Channel p -> s1
  std::optional<LockingCQueue<std::optional<A>>*> pToS1Ch = link<std::optional<A>>(pToS1Chid);

  // Create Channel s1 -> s2
  std::optional<LockingCQueue<std::optional<B>>*> s1ToS2Ch = link<std::optional<B>>(s1ToS2Chid);

  // Create Channel s2 -> this
  std::optional<LockingCQueue<std::optional<C>>*> s2ToCCh = link<std::optional<C>>(s2toCChid);

  // NEED TO DO ERROR HANLDING

  // Run producer
  std::optional<int> resPid = spawn(producerPid, [pToS1Ch, input](){producerWrapper(pToS1Ch.value(), input);});

  // Run stage 1
  std::optional<int> resPid1 = spawn(stage1Pid, [pToS1Ch, s1ToS2Ch, f](){workerWrapper(pToS1Ch.value(), s1ToS2Ch.value(), f);});
  
  // Run stage 2
  std::optional<int> resPid2 = spawn(stage2Pid, [s1ToS2Ch, s2ToCCh, g](){workerWrapper(s1ToS2Ch.value(), s2ToCCh.value(), g);});

  // Run consumer, just read off s2ToCCh until empty
  std::vector<C> toReturn;

  std::optional<C> inputt = s2ToCCh.value()->dequeue();

  // Looping until there is an emptyer optional is recieved
  while(inputt.has_value()) {
      // Can run the consumer function
      toReturn.push_back(inputt.value());

      inputt = s2ToCCh.value()->dequeue();
  }

  for (auto i : toReturn) {
    std::cout << i << std::endl;
  }

  return toReturn;

}

template <typename A>
std::optional<std::vector<int>> spawnWorkersFarm(std::vector<int> pids, std::vector<LockingCQueue<std::optional<A>>*> chs, LockingCQueue<std::optional<A>>* consumerChannel, std::function<A(A)> f) {
  std::vector<int> toReturn;

  for(int i = 0; i < pids.size(); i++) {
    std::optional<int> resPid = spawn(pids[i], [i, chs, consumerChannel, f](){workerWrapper(chs[i], consumerChannel, f);});
    if (!resPid.has_value()) {
      return {};
    }

    toReturn.push_back(resPid.value());
  }

  return toReturn;
}

template <typename A>
std::optional<std::vector<LockingCQueue<std::optional<A>>*>> createChannelsFarm(std::vector<int> chids) {
  std::vector<LockingCQueue<std::optional<A>>*> toReturn;

  for (int chid : chids) {
    std::optional<LockingCQueue<std::optional<A>>*> ch = link<std::optional<A>>(chid);

    if (!ch.has_value()) {
      return {};
    }

    toReturn.push_back(ch.value());
  }

  return toReturn;
}

template <typename A>
std::vector<A> createFarm(
  std::vector<int> pids, 
  std::vector<int> chids,
  int numWorkers,
  std::function<A(A)> f,
  std::vector<A> input
) {
  // Create all the channels
  std::vector<LockingCQueue<std::optional<A>>*> chs = createChannelsFarm<A>(chids).value();

  // Getting the consumer channel
  LockingCQueue<std::optional<A>>* consumerChannel = chs[0];

  // Setting the chs to now be the rest of the list
  chs.erase(chs.begin());

  // Getting the producer pid
  int producerPid = pids[0];

  // Getting the workerPids, just rest of pids
  pids.erase(pids.begin());

  // // Spawn the producer pid,
  std::optional<int> resProducerPid = spawn(producerPid, [chs, input](){farmProducerWrapper<A>(chs, input);});


  // // Spawn all the workers
  std::optional<std::vector<int>> resWorkerPids = spawnWorkersFarm<A>(pids, chs, consumerChannel, f);
  

  
  pidsMap[1]->join();
  pidsMap[2]->join();
  pidsMap[3]->join();

  // // Consumer the result
  int numFinished = 0;

  // // The return list
  std::vector<A> toReturn;
  
  // // The ouput
  std::optional<A> output = consumerChannel->dequeue();
  
  while(numFinished < numWorkers) {
    if (!output.has_value()) {
      numFinished++;

      if (numFinished != numWorkers) {
        output = consumerChannel->dequeue();
      }
      continue;
    }

    toReturn.push_back(output.value());
    // std::cout << output.value() << std::endl;
    output = consumerChannel->dequeue();
  }

  
  for (auto i : toReturn) {
    std::cout << i << std::endl;
  }


  std::cout << "size " << toReturn.size() << std::endl;
  return toReturn;
  
  // return {};
}

int fib(int x) {
   if((x==1)||(x==0)) {
      return(x);
   }else {
      return(fib(x-1)+fib(x-2));
   }
}

int main() {
  // std::vector<int> i = createPipeline2<int, int, int>(1, 2, 3, 1, 2, 3, {1, 2, 3, 4, 5}, [](int i){return i+2;}, [](int i){return i+5;});
  std::vector<int> i = createFarm<int>({1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}, 5, fib, {42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42});
  // for (int i = 0; i < 13; i++) {
  //   std::cout << fib(42) << std::endl;
  // }
}

