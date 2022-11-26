#include <vector>
#include <functional>
#include <thread>
#include <optional>
#include <iostream>
#include <memory>
#include <system_error>
#include <map>
#include <string>
#include "LockingCQueue.hpp"
#include "Semaphore.hpp"

// Forward declares
template <typename A>
class _Maybe;
std::thread* getThread(int pid);
void addThread(int pid, std::thread* t);
void* getChannel(int chid);
template <typename A>
void addChannel(int chid, LockingCQueue<_Maybe<A>>* queue);

// map of threads
std::map<int, std::thread*> pidsMap;
std::mutex pidMutex;

// map of channels
std::map<int, void*> channelsMap;
std::mutex channelMutex;

enum _enum_Nat_type { Zero, Succ };
class _Nat_Zero;
class _Nat_Succ;
class _Nat {
 public:
  enum _enum_Nat_type type;
  void* data;
  static _Nat _Zero();
  static _Nat _Succ(_Nat _1);
  _Nat(_enum_Nat_type t, void* d) {
    type = t;
    data = d;
  }
  _Nat(const _Nat& other);
  _Nat() = default;
};
class _Nat_Zero {
 public:
  _Nat_Zero(){};
  _Nat_Zero(const _Nat_Zero& other) {}
};
class _Nat_Succ {
 public:
  _Nat _1;
  _Nat_Succ(_Nat _1) { this->_1 = _1; };
  _Nat_Succ(const _Nat_Succ& other) { this->_1 = other._1; }
};
inline _Nat _Nat::_Zero() {
  _Nat_Zero* _innerClass = new _Nat_Zero();
  return _Nat(Zero, _innerClass);
};
inline _Nat _Nat::_Succ(_Nat _1) {
  _Nat_Succ* _innerClass = new _Nat_Succ(_1);
  return _Nat(Succ, _innerClass);
};
_Nat::_Nat(const _Nat& other) {
  type = other.type;
  switch (other.type) {
    case Zero: {
      auto d = *(_Nat_Zero*)other.data;
      auto ret = new _Nat_Zero(d);
      data = ret;
      break;
    }
    case Succ: {
      auto d = *(_Nat_Succ*)other.data;
      auto ret = new _Nat_Succ(d);
      data = ret;
      break;
    }
  }
}
std::function<int(_Nat)> intFromNat = [](_Nat n) {
    if (n.type == Zero) {
        return 0;
    } else {
        return 1 + intFromNat((*(_Nat_Succ*)n.data)._1);
    }
};

// List



// Void 
enum _enum_Void_type {};
class _Void {
 public:
  enum _enum_Void_type type;
  void* data;
};


// TyEq

class _TyEq { 
    public: 
        static _TyEq _Refl();
};

inline _TyEq _TyEq::_Refl() {
    return _TyEq{};
}