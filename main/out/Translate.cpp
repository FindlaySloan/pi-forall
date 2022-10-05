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
  static _Nat _Succ(int _1);
};
class _Nat_Zero {
 public:
  _Nat_Zero(){};
};
class _Nat_Succ {
 public:
  int _1;
  _Nat_Succ(int _1) { this->_1 = _1; };
};
inline _Nat _Nat::_Zero() {
  _Nat_Zero* _innerClass = new _Nat_Zero();
  return _Nat{Zero, _innerClass};
};
inline _Nat _Nat::_Succ(int _1) {
  _Nat_Succ* _innerClass = new _Nat_Succ(_1);
  return _Nat{Succ, _innerClass};
};
extern std::function<char(_List<char>)> head;
std::function<char(_List<char>)> head = [](auto a) {
  auto _1 = [a]() {
    auto _2 = a;
    switch (_2.type) {
      case Nil: {
        auto _4 = *(_List_Nil<char>*)_2.data;
        auto _3 = '1';
        return _3;
      }
      case Cons: {
        auto _6 = *(_List_Cons<char>*)_2.data;
        auto x = _6._1;
        auto xs = _6._2;
        auto _5 = x;
        return _5;
      }
    }
  }();
  return _1;
};
extern char m;
char m = []() {
  auto _9 = 'a';
  auto _11 = 'b';
  auto _12 = _List<char>::_Nil();
  auto _10 = _List<char>::_Cons(_11, _12);
  auto _8 = _List<char>::_Cons(_9, _10);
  auto _7 = head(_8);
  return _7;
}();
extern std::function<_List<char>(char)> a;
std::function<_List<char>(char)> a = [](auto a) {
  auto _14 = 'a';
  auto _16 = 'b';
  auto _18 = 'c';
  auto _19 = _List<char>::_Nil();
  auto _17 = _List<char>::_Cons(_18, _19);
  auto _15 = _List<char>::_Cons(_16, _17);
  auto _13 = _List<char>::_Cons(_14, _15);
  return _13;
};
enum _enum_Maybe_type { Nothing, Just };
template <class A>
class _Maybe {
 public:
  enum _enum_Maybe_type type;
  void* data;
  static _Maybe<A> _Nothing();
  static _Maybe<A> _Just(A _1);
};
template <class A>
class _Maybe_Nothing {
 public:
  _Maybe_Nothing(){};
};
template <class A>
class _Maybe_Just {
 public:
  A _1;
  _Maybe_Just(A _1) { this->_1 = _1; };
};
template <class A>
inline _Maybe<A> _Maybe<A>::_Nothing() {
  _Maybe_Nothing<A>* _innerClass = new _Maybe_Nothing<A>();
  return _Maybe<A>{Nothing, _innerClass};
};
template <class A>
inline _Maybe<A> _Maybe<A>::_Just(A _1) {
  _Maybe_Just<A>* _innerClass = new _Maybe_Just<A>(_1);
  return _Maybe<A>{Just, _innerClass};
};
extern std::function<bool(_Maybe<_Maybe<char>>)> f;
std::function<bool(_Maybe<_Maybe<char>>)> f = [](auto b) {
  auto _20 = [b]() {
    auto _21 = b;
    switch (_21.type) {
      case Nothing: {
        auto _23 = *(_Maybe_Nothing<_Maybe<char>>*)_21.data;
        auto _22 = false;
        return _22;
      }
      case Just: {
        auto _25 = *(_Maybe_Just<_Maybe<char>>*)_21.data;
        auto n = _25._1;
        auto _24 = true;
        return _24;
      }
    }
  }();
  return _20;
};
extern std::function<bool(char)> g;
std::function<bool(char)> g = [](auto b) {
  auto _27 = _Maybe<_Maybe<char>>::_Nothing();
  auto _26 = f(_27);
  return _26;
};
enum _enum_Nati_type { Zeroi, Succi };
class _Nati {
 public:
  enum _enum_Nati_type type;
  void* data;
  static _Nati _Zeroi();
  static _Nati _Succi(_Nati _1);
};
class _Nati_Zeroi {
 public:
  _Nati_Zeroi(){};
};
class _Nati_Succi {
 public:
  _Nati _1;
  _Nati_Succi(_Nati _1) { this->_1 = _1; };
};
inline _Nati _Nati::_Zeroi() {
  _Nati_Zeroi* _innerClass = new _Nati_Zeroi();
  return _Nati{Zeroi, _innerClass};
};
inline _Nati _Nati::_Succi(_Nati _1) {
  _Nati_Succi* _innerClass = new _Nati_Succi(_1);
  return _Nati{Succi, _innerClass};
};
extern std::function<char(_Nati)> show;
std::function<char(_Nati)> show = [](auto s) {
  auto _28 = [s]() {
    auto _29 = s;
    switch (_29.type) {
      case Zeroi: {
        auto _31 = *(_Nati_Zeroi*)_29.data;
        auto _30 = '0';
        return _30;
      }
      case Succi: {
        auto _33 = *(_Nati_Succi*)_29.data;
        auto n = _33._1;
        auto _32 = '1';
        return _32;
      }
    }
  }();
  return _28;
};
extern std::function<char(_Nati)> pred;
std::function<char(_Nati)> pred = [](auto n) {
  auto _34 = [n]() {
    auto _35 = n;
    switch (_35.type) {
      case Zeroi: {
        auto _37 = *(_Nati_Zeroi*)_35.data;
        auto _38 = _Nati::_Zeroi();
        auto _36 = show(_38);
        return _36;
      }
      case Succi: {
        auto _40 = *(_Nati_Succi*)_35.data;
        auto nn = _40._1;
        auto _41 = nn;
        auto _39 = show(_41);
        return _39;
      }
    }
  }();
  return _34;
};

int main() {
  std::cout << m << std::endl;

  return 0;
}