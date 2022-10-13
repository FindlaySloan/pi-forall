#include <functional>
#include <iostream>
enum _enum_Sigma_type { Prod };
template <class a, class b>
class _Sigma {
 public:
  enum _enum_Sigma_type type;
  void* data;
  static _Sigma<a, b> _Prod(a _1, b _2);
};
template <class a, class b>
class _Sigma_Prod {
 public:
  a _1;
  b _2;
  _Sigma_Prod(a _1, b _2) {
    this->_1 = _1;
    this->_2 = _2;
  };
};
template <class a, class b>
inline _Sigma<a, b> _Sigma<a, b>::_Prod(a _1, b _2) {
  _Sigma_Prod<a, b>* _innerClass = new _Sigma_Prod<a, b>(_1, _2);
  return _Sigma<a, b>{Prod, _innerClass};
};
enum _enum_List_type { Nil, Cons };
template <class c>
class _List {
 public:
  enum _enum_List_type type;
  void* data;
  static _List<c> _Nil();
  static _List<c> _Cons(c _1, _List<c> _2);
};
template <class c>
class _List_Nil {
 public:
  _List_Nil(){};
};
template <class c>
class _List_Cons {
 public:
  c _1;
  _List<c> _2;
  _List_Cons(c _1, _List<c> _2) {
    this->_1 = _1;
    this->_2 = _2;
  };
};
template <class c>
inline _List<c> _List<c>::_Nil() {
  _List_Nil<c>* _innerClass = new _List_Nil<c>();
  return _List<c>{Nil, _innerClass};
};
template <class c>
inline _List<c> _List<c>::_Cons(c _1, _List<c> _2) {
  _List_Cons<c>* _innerClass = new _List_Cons<c>(_1, _2);
  return _List<c>{Cons, _innerClass};
};
enum _enum_Nat_type { Zero, Succ };
class _Nat {
 public:
  enum _enum_Nat_type type;
  void* data;
  static _Nat _Zero();
  static _Nat _Succ(_Nat _1);
};
class _Nat_Zero {
 public:
  _Nat_Zero(){};
};
class _Nat_Succ {
 public:
  _Nat _1;
  _Nat_Succ(_Nat _1) { this->_1 = _1; };
};
inline _Nat _Nat::_Zero() {
  _Nat_Zero* _innerClass = new _Nat_Zero();
  return _Nat{Zero, _innerClass};
};
inline _Nat _Nat::_Succ(_Nat _1) {
  _Nat_Succ* _innerClass = new _Nat_Succ(_1);
  return _Nat{Succ, _innerClass};
};
enum _enum_Channel_type { Chan };
template <class A>
class _Channel {
 public:
  enum _enum_Channel_type type;
  void* data;
  static _Channel<A> _Chan();
};
template <class A>
class _Channel_Chan {
 public:
  _Channel_Chan(){};
};
template <class A>
inline _Channel<A> _Channel<A>::_Chan() {
  _Channel_Chan<A>* _innerClass = new _Channel_Chan<A>();
  return _Channel<A>{Chan, _innerClass};
};
enum _enum_Process_type { Proc };
class _Process {
 public:
  enum _enum_Process_type type;
  void* data;
  static _Process _Proc(std::function<B(A)> _1);
};
class _Process_Proc {
 public:
  std::function<B(A)> _1;
  _Process_Proc(std::function<B(A)> _1) { this->_1 = _1; };
};
inline _Process _Process::_Proc(std::function<B(A)> _1) {
  _Process_Proc* _innerClass = new _Process_Proc(_1);
  return _Process{Proc, _innerClass};
};

int main() {}