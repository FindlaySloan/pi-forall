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
std::map<int, std::thread*> pids;
std::mutex pidMutex;

// map of channels
std::map<int, void*> channels;
std::mutex channelMutex;

// Helper functions for pids
std::thread* getThread(int pid) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(pidMutex);

  // return the information
  return pids[pid];
}

void addThread(int pid, std::thread* t) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(pidMutex);

  // Adding the thread, will never overwrite
  pids[pid] = t;
}

// Helper functions for channels
void* getChannel(int chid) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(channelMutex);

  //  returning the channel
  return channels[chid];
}

template <typename A>
void addChannel(int chid, LockingCQueue<A>* queue) {
  // Aquireing the lock
  std::lock_guard<std::mutex> lock(channelMutex);

  // adding the channel
  channels[chid] = queue;
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

template <typename A, typename B>
void workerWrapper(LockingCQueue<std::optional<A>>* in, LockingCQueue<std::optional<B>>* out, std::function<B(A)> f) {
  std::optional<A> input = in->dequeue();

  while(input.has_value()) {
    B output = f(input.value());

    out->enqueue(output);

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

int main() {
  std::vector<int> i = createPipeline2<int, int, int>(1, 2, 3, 1, 2, 3, {1, 2, 3, 4, 5}, [](int i){return i+2;}, [](int i){return i+5;});
}