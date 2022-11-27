#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <system_error>
#include <thread>
#include <vector>

#include "LockingCQueue.hpp"
#include "Semaphore.hpp"

// Forward declares
template <typename A>
class _Maybe;
std::thread* getThread(uint64_t pid);
void addThread(uint64_t pid, std::thread* t);
void* getChannel(uint64_t chid);
template <typename A>
void addChannel(uint64_t chid, LockingCQueue<_Maybe<A>>* queue);

// map of threads
std::map<uint64_t, std::thread*> pidsMap;
std::mutex pidMutex;

// map of channels
std::map<uint64_t, void*> channelsMap;
std::mutex channelMutex;

// enum _enum_Nat_type { Zero, Succ };
// class _Nat_Zero;
// class _Nat_Succ;
// class _Nat {
//  public:
//   enum _enum_Nat_type type;
//   std::shared_ptr<void> data;
//   static _Nat _Zero();
//   static _Nat _Succ(_Nat _1);
//   _Nat(_enum_Nat_type t, std::shared_ptr<void> d) {
//     type = t;
//     data = d;
//   }
//   _Nat(const _Nat& other);
//   _Nat() = default;
// };
// class _Nat_Zero {
//  public:
//   _Nat_Zero(){};
//   _Nat_Zero(const _Nat_Zero* other) {}
// };
// class _Nat_Succ {
//  public:
//   _Nat _1;
//   _Nat_Succ(_Nat _1) { this->_1 = _1; };
//   _Nat_Succ(const _Nat_Succ* other) { this->_1 = other->_1; }
// };
// inline _Nat _Nat::_Zero() {
//   return _Nat(Zero, std::static_pointer_cast<void>(std::make_shared<_Nat_Zero>()));
// };
// inline _Nat _Nat::_Succ(_Nat _1) {
//   return _Nat(Succ, std::static_pointer_cast<void>(std::make_shared<_Nat_Succ>(_1)));
// };
// _Nat::_Nat(const _Nat& other) {
//   type = other.type;
//   data = other.data;
// }
// std::function<uint64_t(_Nat)> intFromNat = [](_Nat n) {
//     if (n.type == Zero) {
//         return 0;
//     } else {
//         return (uint64_t)1 + intFromNat((*(std::static_pointer_cast<_Nat_Succ>(n.data)))._1);
//     }
// };

// List

// Void
enum _enum_Void_type {};
class _Void {
 public:
  enum _enum_Void_type type;
  std::shared_ptr<void> data;
};

// TyEq

class _TyEq {
 public:
  static _TyEq _Refl();
};

inline _TyEq _TyEq::_Refl() { return _TyEq{}; }
enum _enum_Sigma_type { Prod };
template <class a, class b>
class _Sigma_Prod;
template <class a, class b>
class _Sigma {
 public:
  enum _enum_Sigma_type type;
  std::shared_ptr<void> data;
  static _Sigma<a, b> _Prod(a _1, b _2);
  _Sigma<a, b>(_enum_Sigma_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Sigma<a, b>(const _Sigma<a, b>& other);
  _Sigma<a, b>() = default;
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
  _Sigma_Prod(const _Sigma_Prod* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
  }
};
template <class a, class b>
inline _Sigma<a, b> _Sigma<a, b>::_Prod(a _1, b _2) {
  return _Sigma<a, b>(Prod, std::make_shared<_Sigma_Prod<a, b>>(_1, _2));
};
template <class a, class b>
_Sigma<a, b>::_Sigma(const _Sigma<a, b>& other) {
  type = other.type;
  data = other.data;
}
enum _enum_Unit_type { unit };
class _Unit_unit;
class _Unit {
 public:
  enum _enum_Unit_type type;
  std::shared_ptr<void> data;
  static _Unit _unit();
  _Unit(_enum_Unit_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Unit(const _Unit& other);
  _Unit() = default;
};
class _Unit_unit {
 public:
  _Unit_unit(){};
  _Unit_unit(const _Unit_unit* other) {}
};
inline _Unit _Unit::_unit() { return _Unit(unit, std::make_shared<_Unit_unit>()); };
_Unit::_Unit(const _Unit& other) {
  type = other.type;
  data = other.data;
}
enum _enum_Bool_type { False, True };
class _Bool_False;
class _Bool_True;
class _Bool {
 public:
  enum _enum_Bool_type type;
  std::shared_ptr<void> data;
  static _Bool _False();
  static _Bool _True();
  _Bool(_enum_Bool_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Bool(const _Bool& other);
  _Bool() = default;
};
class _Bool_False {
 public:
  _Bool_False(){};
  _Bool_False(const _Bool_False* other) {}
};
class _Bool_True {
 public:
  _Bool_True(){};
  _Bool_True(const _Bool_True* other) {}
};
inline _Bool _Bool::_False() { return _Bool(False, std::make_shared<_Bool_False>()); };
inline _Bool _Bool::_True() { return _Bool(True, std::make_shared<_Bool_True>()); };
_Bool::_Bool(const _Bool& other) {
  type = other.type;
  data = other.data;
}
enum _enum_List_type { Nil, Cons };
template <class c>
class _List_Nil;
template <class c>
class _List_Cons;
template <class c>
class _List {
 public:
  enum _enum_List_type type;
  std::shared_ptr<void> data;
  static _List<c> _Nil();
  static _List<c> _Cons(c _1, _List<c> _2);
  _List<c>(_enum_List_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _List<c>(const _List<c>& other);
  _List<c>() = default;
};
template <class c>
class _List_Nil {
 public:
  _List_Nil(){};
  _List_Nil(const _List_Nil* other) {}
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
  _List_Cons(const _List_Cons* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
  }
};
template <class c>
inline _List<c> _List<c>::_Nil() {
  return _List<c>(Nil, std::make_shared<_List_Nil<c>>());
};
template <class c>
inline _List<c> _List<c>::_Cons(c _1, _List<c> _2) {
  return _List<c>(Cons, std::make_shared<_List_Cons<c>>(_1, _2));
};
template <class c>
_List<c>::_List(const _List<c>& other) {
  type = other.type;
  data = other.data;
}
enum _enum_Maybe_type { Nothing, Just };
template <class A>
class _Maybe_Nothing;
template <class A>
class _Maybe_Just;
template <class A>
class _Maybe {
 public:
  enum _enum_Maybe_type type;
  std::shared_ptr<void> data;
  static _Maybe<A> _Nothing();
  static _Maybe<A> _Just(A _1);
  _Maybe<A>(_enum_Maybe_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Maybe<A>(const _Maybe<A>& other);
  _Maybe<A>() = default;
};
template <class A>
class _Maybe_Nothing {
 public:
  _Maybe_Nothing(){};
  _Maybe_Nothing(const _Maybe_Nothing* other) {}
};
template <class A>
class _Maybe_Just {
 public:
  A _1;
  _Maybe_Just(A _1) { this->_1 = _1; };
  _Maybe_Just(const _Maybe_Just* other) { this->_1 = other->_1; }
};
template <class A>
inline _Maybe<A> _Maybe<A>::_Nothing() {
  return _Maybe<A>(Nothing, std::make_shared<_Maybe_Nothing<A>>());
};
template <class A>
inline _Maybe<A> _Maybe<A>::_Just(A _1) {
  return _Maybe<A>(Just, std::make_shared<_Maybe_Just<A>>(_1));
};
template <class A>
_Maybe<A>::_Maybe(const _Maybe<A>& other) {
  type = other.type;
  data = other.data;
}
enum _enum_Vec_type { NilV, ConsV };
template <class A>
class _Vec_NilV;
template <class A>
class _Vec_ConsV;
template <class A>
class _Vec {
 public:
  enum _enum_Vec_type type;
  std::shared_ptr<void> data;
  static _Vec<A> _NilV();
  static _Vec<A> _ConsV(A _1, _Vec<A> _2);
  _Vec<A>(_enum_Vec_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Vec<A>(const _Vec<A>& other);
  _Vec<A>() = default;
};
template <class A>
class _Vec_NilV {
 public:
  _Vec_NilV(){};
  _Vec_NilV(const _Vec_NilV* other) {}
};
template <class A>
class _Vec_ConsV {
 public:
  A _1;
  _Vec<A> _2;
  _Vec_ConsV(A _1, _Vec<A> _2) {
    this->_1 = _1;
    this->_2 = _2;
  };
  _Vec_ConsV(const _Vec_ConsV* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
  }
};
template <class A>
inline _Vec<A> _Vec<A>::_NilV() {
  return _Vec<A>(NilV, std::make_shared<_Vec_NilV<A>>());
};
template <class A>
inline _Vec<A> _Vec<A>::_ConsV(A _1, _Vec<A> _2) {
  return _Vec<A>(ConsV, std::make_shared<_Vec_ConsV<A>>(_1, _2));
};
template <class A>
_Vec<A>::_Vec(const _Vec<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<A(_Vec<A>)> head = [](auto x) {
  auto _1 = [x]() {
    auto _2 = x;
    switch (_2.type) {
      case ConsV: {
        auto _4 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_2.data));
        auto y = _4._1;
        auto ys = _4._2;
        auto _3 = y;
        return _3;
      }
    }
  }();
  return _1;
};

template <class A>
std::function<_Vec<A>(_Vec<A>)> tail = [](auto x) {
  auto _5 = [x]() {
    auto _6 = x;
    switch (_6.type) {
      case ConsV: {
        auto _8 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_6.data));
        auto y = _8._1;
        auto ys = _8._2;
        auto _7 = ys;
        return _7;
      }
    }
  }();
  return _5;
};

std::function<_List<char>(uint64_t)> natToString = [](auto n) {
  std::string stringVersion = std::to_string(n);
  std::function<_List<char>(std::string)> toList = [&toList](std::string s) {
    if (s.empty()) {
      return _List<char>::_Nil();
    }
    return _List<char>::_Cons(s.at(0), toList(std::string(s).erase(0, 1)));
  };
  return toList(stringVersion);
};

template <class a, class b>
std::function<std::function<_List<b>(_List<a>)>(std::function<b(a)>)> map = [](auto f) {
  auto _9 = [f](auto xs) {
    auto _10 = [xs, f]() {
      auto _11 = xs;
      switch (_11.type) {
        case Nil: {
          auto _13 = *(std::static_pointer_cast<_List_Nil<a>>(_11.data));
          auto _12 = _List<b>::_Nil();
          return _12;
        }
        case Cons: {
          auto _15 = *(std::static_pointer_cast<_List_Cons<a>>(_11.data));
          auto y = _15._1;
          auto ys = _15._2;
          auto _18 = y;
          auto _16 = f(_18);
          auto _19 = f;
          auto _20 = ys;
          auto _17 = map<a, b>(_19)(_20);
          auto _14 = _List<b>::_Cons(_16, _17);
          return _14;
        }
      }
    }();
    return _10;
  };
  return _9;
};
enum _enum_Dec_type { Yes, No };
template <class prop>
class _Dec_Yes;
template <class prop>
class _Dec_No;
template <class prop>
class _Dec {
 public:
  enum _enum_Dec_type type;
  std::shared_ptr<void> data;
  static _Dec<prop> _Yes(prop _1);
  static _Dec<prop> _No(std::function<_Void(prop)> _1);
  _Dec<prop>(_enum_Dec_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Dec<prop>(const _Dec<prop>& other);
  _Dec<prop>() = default;
};
template <class prop>
class _Dec_Yes {
 public:
  prop _1;
  _Dec_Yes(prop _1) { this->_1 = _1; };
  _Dec_Yes(const _Dec_Yes* other) { this->_1 = other->_1; }
};
template <class prop>
class _Dec_No {
 public:
  std::function<_Void(prop)> _1;
  _Dec_No(std::function<_Void(prop)> _1) { this->_1 = _1; };
  _Dec_No(const _Dec_No* other) { this->_1 = other->_1; }
};
template <class prop>
inline _Dec<prop> _Dec<prop>::_Yes(prop _1) {
  return _Dec<prop>(Yes, std::make_shared<_Dec_Yes<prop>>(_1));
};
template <class prop>
inline _Dec<prop> _Dec<prop>::_No(std::function<_Void(prop)> _1) {
  return _Dec<prop>(No, std::make_shared<_Dec_No<prop>>(_1));
};
template <class prop>
_Dec<prop>::_Dec(const _Dec<prop>& other) {
  type = other.type;
  data = other.data;
}

template <class A, class B>
std::function<_TyEq(_TyEq)> f_equal = [](auto pf) {
  auto _24 = _TyEq::_Refl();
  auto _23 = _24;
  return _23;
};

std::function<std::function<_Void(_TyEq)>(uint64_t)> ZnotS = [](auto n) {
  auto _25 = [](auto r) {
    auto _26 = _Void();
    return _26;
  };
  return _25;
};

template <class A>
std::function<_TyEq(_TyEq)> sym = [](auto pf) {
  auto _28 = _TyEq::_Refl();
  auto _27 = _28;
  return _27;
};

template <class t>
std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)> negEqSym = [](auto p) {
  auto _29 = [p](auto h) {
    auto _32 = h;
    auto _31 = sym<t>(_32);
    auto _30 = p(_31);
    return _30;
  };
  return _29;
};

std::function<uint64_t(uint64_t)> pred = [](auto n) {
  auto _36 = [n]() {
    auto _37 = n;
    if (!_37) {
      auto _38 = (uint64_t)0;
      return _38;
    } else {
      auto m = _37 - 1;
      auto _38 = m;
      return _38;
    }
  }();
  return _36;
};

std::function<_TyEq(_TyEq)> succInjective = [](auto p) {
  auto _40 = p;
  auto _39 = f_equal<uint64_t, uint64_t>(_40);
  return _39;
};

std::function<std::function<_Dec<_TyEq>(uint64_t)>(uint64_t)> decEqNat = [](auto a) {
  auto _46 = [a](auto b) {
    auto _47 = [a, b]() {
      auto _48 = a;
      if (!_48) {
        auto _49 = [a, b]() {
          auto _50 = b;
          if (!_50) {
            auto _52 = _TyEq::_Refl();
            auto _51 = _Dec<_TyEq>::_Yes(_52);
            return _51;
          } else {
            auto n = _50 - 1;
            auto _54 = n;
            auto _53 = ZnotS(_54);
            auto _51 = _Dec<_TyEq>::_No(_53);
            return _51;
          }
        }();
        return _49;
      } else {
        auto n = _48 - 1;
        auto _49 = [a, b, n]() {
          auto _55 = b;
          if (!_55) {
            auto _62 = n;
            auto _58 = ZnotS(_62);
            auto _57 = negEqSym<uint64_t>(_58);
            auto _56 = _Dec<_TyEq>::_No(_57);
            return _56;
          } else {
            auto m = _55 - 1;
            auto _56 = [a, b, n, m]() {
              auto _64 = n;
              auto _65 = m;
              auto _63 = decEqNat(_64)(_65);
              switch (_63.type) {
                case Yes: {
                  auto _67 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_63.data));
                  auto p = _67._1;
                  auto _69 = p;
                  auto _68 = f_equal<uint64_t, uint64_t>(_69);
                  auto _66 = _Dec<_TyEq>::_Yes(_68);
                  return _66;
                }
                case No: {
                  auto _76 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_63.data));
                  auto p = _76._1;
                  auto _77 = [a, b, n, m, p](auto h) {
                    auto _80 = h;
                    auto _79 = succInjective(_80);
                    auto _78 = p(_79);
                    return _78;
                  };
                  auto _75 = _Dec<_TyEq>::_No(_77);
                  return _75;
                }
              }
            }();
            return _56;
          }
        }();
        return _49;
      }
    }();
    return _47;
  };
  return _46;
};
enum _enum_Elem_type { Here, There };
template <class a>
class _Elem_Here;
template <class a>
class _Elem_There;
template <class a>
class _Elem {
 public:
  enum _enum_Elem_type type;
  std::shared_ptr<void> data;
  static _Elem<a> _Here(a _1, _List<a> _2);
  static _Elem<a> _There(a _1, a _2, _List<a> _3, _Elem<a> _4);
  _Elem<a>(_enum_Elem_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Elem<a>(const _Elem<a>& other);
  _Elem<a>() = default;
};
template <class a>
class _Elem_Here {
 public:
  a _1;
  _List<a> _2;
  _Elem_Here(a _1, _List<a> _2) {
    this->_1 = _1;
    this->_2 = _2;
  };
  _Elem_Here(const _Elem_Here* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
  }
};
template <class a>
class _Elem_There {
 public:
  a _1;
  a _2;
  _List<a> _3;
  _Elem<a> _4;
  _Elem_There(a _1, a _2, _List<a> _3, _Elem<a> _4) {
    this->_1 = _1;
    this->_2 = _2;
    this->_3 = _3;
    this->_4 = _4;
  };
  _Elem_There(const _Elem_There* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
    this->_3 = other->_3;
    this->_4 = other->_4;
  }
};
template <class a>
inline _Elem<a> _Elem<a>::_Here(a _1, _List<a> _2) {
  return _Elem<a>(Here, std::make_shared<_Elem_Here<a>>(_1, _2));
};
template <class a>
inline _Elem<a> _Elem<a>::_There(a _1, a _2, _List<a> _3, _Elem<a> _4) {
  return _Elem<a>(There, std::make_shared<_Elem_There<a>>(_1, _2, _3, _4));
};
template <class a>
_Elem<a>::_Elem(const _Elem<a>& other) {
  type = other.type;
  data = other.data;
}

std::function<std::function<std::function<_Void(_Elem<uint64_t>)>(std::function<_Void(_Elem<uint64_t>)>)>(std::function<_Void(_TyEq)>)> neitherHereNorThere = [](auto xneqy) {
  auto _83 = [xneqy](auto xninxs) {
    auto _84 = [xneqy, xninxs](auto p) {
      auto _85 = [p, xneqy, xninxs]() {
        auto _86 = p;
        switch (_86.type) {
          case Here: {
            auto _88 = *(std::static_pointer_cast<_Elem_Here<uint64_t>>(_86.data));
            auto a = _88._1;
            auto as = _88._2;
            auto _89 = _TyEq::_Refl();
            auto _87 = xneqy(_89);
            return _87;
          }
          case There: {
            auto _91 = *(std::static_pointer_cast<_Elem_There<uint64_t>>(_86.data));
            auto b = _91._1;
            auto a = _91._2;
            auto as = _91._3;
            auto prf = _91._4;
            auto _92 = prf;
            auto _90 = xninxs(_92);
            return _90;
          }
        }
      }();
      return _85;
    };
    return _84;
  };
  return _83;
};

std::function<_Void(_Elem<uint64_t>)> falseElem1 = [](auto p) {
  auto _93 = [p]() {
    auto _94 = p;
    return _Void();
  }();
  return _93;
};

std::function<std::function<_Dec<_Elem<uint64_t>>(_List<uint64_t>)>(uint64_t)> isElem = [](auto x) {
  auto _95 = [x](auto xss) {
    auto _96 = [xss, x]() {
      auto _97 = xss;
      switch (_97.type) {
        case Nil: {
          auto _99 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_97.data));
          auto _100 = falseElem1;
          auto _98 = _Dec<_Elem<uint64_t>>::_No(_100);
          return _98;
        }
        case Cons: {
          auto _103 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_97.data));
          auto y = _103._1;
          auto xs = _103._2;
          auto _102 = [xss, x, y, xs]() {
            auto _105 = x;
            auto _106 = y;
            auto _104 = decEqNat(_105)(_106);
            switch (_104.type) {
              case Yes: {
                auto _108 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_104.data));
                auto p = _108._1;
                auto _111 = x;
                auto _112 = xs;
                auto _110 = _Elem<uint64_t>::_Here(_111, _112);
                auto _109 = _110;
                auto _107 = _Dec<_Elem<uint64_t>>::_Yes(_109);
                return _107;
              }
              case No: {
                auto _114 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_104.data));
                auto xneqy = _114._1;
                auto _113 = [xss, x, y, xs, xneqy]() {
                  auto _116 = x;
                  auto _117 = xs;
                  auto _115 = isElem(_116)(_117);
                  switch (_115.type) {
                    case Yes: {
                      auto _119 = *(std::static_pointer_cast<_Dec_Yes<_Elem<uint64_t>>>(_115.data));
                      auto xinxs = _119._1;
                      auto _121 = y;
                      auto _122 = x;
                      auto _123 = xs;
                      auto _124 = xinxs;
                      auto _120 = _Elem<uint64_t>::_There(_121, _122, _123, _124);
                      auto _118 = _Dec<_Elem<uint64_t>>::_Yes(_120);
                      return _118;
                    }
                    case No: {
                      auto _126 = *(std::static_pointer_cast<_Dec_No<_Elem<uint64_t>>>(_115.data));
                      auto xninxs = _126._1;
                      auto _128 = xneqy;
                      auto _129 = xninxs;
                      auto _127 = neitherHereNorThere(_128)(_129);
                      auto _125 = _Dec<_Elem<uint64_t>>::_No(_127);
                      return _125;
                    }
                  }
                }();
                return _113;
              }
            }
          }();
          return _102;
        }
      }
    }();
    return _96;
  };
  return _95;
};

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> plus = [](auto n) {
  auto _133 = [n](auto m) {
    
    return n+m;
  };
  return _133;
};

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> mult = [](auto n) {
  auto _140 = [n](auto m) {
    
    return n*m;
  };
  return _140;
};

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> minus = [](auto n) {
  auto _148 = [n](auto m) {
    auto _149 = [n, m]() {
      auto _150 = n;
      if (!_150) {
        auto _151 = (uint64_t)0;
        return _151;
      } else {
        auto p = _150 - 1;
        auto _151 = [n, m, p]() {
          auto _152 = m;
          if (!_152) {
            auto _153 = n;
            return _153;
          } else {
            auto mpred = _152 - 1;
            auto _154 = p;
            auto _155 = mpred;
            auto _153 = minus(_154)(_155);
            return _153;
          }
        }();
        return _151;
      }
    }();
    return _149;
  };
  return _148;
};

std::function<uint64_t(uint64_t)> fib = [](auto x) {
  auto _156 = [x]() {
    auto _157 = x;
    if (!_157) {
      auto _158 = (uint64_t)1;
      return _158;
    } else {
      auto y = _157 - 1;
      auto _158 = [x, y]() {
        auto _159 = y;
        if (!_159) {
          auto _160 = (uint64_t)1;
          return _160;
        } else {
          auto z = _159 - 1;
          auto _163 = y;
          auto _161 = fib(_163);
          auto _164 = z;
          auto _162 = fib(_164);
          auto _160 = plus(_161)(_162);
          return _160;
        }
      }();
      return _158;
    }
  }();
  return _156;
};

std::function<uint64_t(uint64_t)> fact = [](auto n) {
  auto _165 = [n]() {
    auto _166 = n;
    if (!_166) {
      auto _167 = (uint64_t)1;
      return _167;
    } else {
      auto m = _166 - 1;
      auto _168 = n;
      auto _170 = m;
      auto _169 = fact(_170);
      auto _167 = mult(_168)(_169);
      return _167;
    }
  }();
  return _165;
};

template <class A>
std::function<std::function<_Vec<A>(_Vec<A>)>(_Vec<A>)> append = [](auto v1) {
  auto _171 = [v1](auto ys) {
    auto _172 = [v1, ys]() {
      auto _173 = v1;
      switch (_173.type) {
        case ConsV: {
          auto _175 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_173.data));
          auto x = _175._1;
          auto xs = _175._2;
          auto _176 = x;
          auto _179 = xs;
          auto _180 = ys;
          auto _177 = append<A>(_179)(_180);
          auto _174 = _Vec<A>::_ConsV(_176, _177);
          return _174;
        }
        case NilV: {
          auto _185 = *(std::static_pointer_cast<_Vec_NilV<A>>(_173.data));
          auto _184 = ys;
          return _184;
        }
      }
    }();
    return _172;
  };
  return _171;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> trans = [](auto pf1) {
  auto _186 = [pf1](auto pf2) {
    auto _188 = pf1;
    auto _187 = _188;
    return _187;
  };
  return _186;
};
enum _enum_ElemVec_type { HereV, ThereV };
template <class A>
class _ElemVec_HereV;
template <class A>
class _ElemVec_ThereV;
template <class A>
class _ElemVec {
 public:
  enum _enum_ElemVec_type type;
  std::shared_ptr<void> data;
  static _ElemVec<A> _HereV(_Vec<A> _1);
  static _ElemVec<A> _ThereV(_Vec<A> _1, A _2, _ElemVec<A> _3);
  _ElemVec<A>(_enum_ElemVec_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _ElemVec<A>(const _ElemVec<A>& other);
  _ElemVec<A>() = default;
};
template <class A>
class _ElemVec_HereV {
 public:
  _Vec<A> _1;
  _ElemVec_HereV(_Vec<A> _1) { this->_1 = _1; };
  _ElemVec_HereV(const _ElemVec_HereV* other) { this->_1 = other->_1; }
};
template <class A>
class _ElemVec_ThereV {
 public:
  _Vec<A> _1;
  A _2;
  _ElemVec<A> _3;
  _ElemVec_ThereV(_Vec<A> _1, A _2, _ElemVec<A> _3) {
    this->_1 = _1;
    this->_2 = _2;
    this->_3 = _3;
  };
  _ElemVec_ThereV(const _ElemVec_ThereV* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
    this->_3 = other->_3;
  }
};
template <class A>
inline _ElemVec<A> _ElemVec<A>::_HereV(_Vec<A> _1) {
  return _ElemVec<A>(HereV, std::make_shared<_ElemVec_HereV<A>>(_1));
};
template <class A>
inline _ElemVec<A> _ElemVec<A>::_ThereV(_Vec<A> _1, A _2, _ElemVec<A> _3) {
  return _ElemVec<A>(ThereV, std::make_shared<_ElemVec_ThereV<A>>(_1, _2, _3));
};
template <class A>
_ElemVec<A>::_ElemVec(const _ElemVec<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<_Void(_ElemVec<A>)> xNotInNilV = [](auto p) {
  auto _189 = [p]() {
    auto _190 = p;
    return _Void();
  }();
  return _189;
};

std::function<std::function<std::function<_Void(_ElemVec<uint64_t>)>(std::function<_Void(_ElemVec<uint64_t>)>)>(std::function<_Void(_TyEq)>)> neitherHereNorThereVec = [](auto xneqy) {
  auto _191 = [xneqy](auto xninxs) {
    auto _192 = [xneqy, xninxs](auto p) {
      auto _193 = [p, xneqy, xninxs]() {
        auto _194 = p;
        switch (_194.type) {
          case HereV: {
            auto _196 = *(std::static_pointer_cast<_ElemVec_HereV<uint64_t>>(_194.data));
            auto as = _196._1;
            auto _197 = _TyEq::_Refl();
            auto _195 = xneqy(_197);
            return _195;
          }
          case ThereV: {
            auto _199 = *(std::static_pointer_cast<_ElemVec_ThereV<uint64_t>>(_194.data));
            auto as = _199._1;
            auto b = _199._2;
            auto prf = _199._3;
            auto _200 = prf;
            auto _198 = xninxs(_200);
            return _198;
          }
        }
      }();
      return _193;
    };
    return _192;
  };
  return _191;
};

std::function<std::function<_Dec<_ElemVec<uint64_t>>(_Vec<uint64_t>)>(uint64_t)> isElemVec = [](auto x) {
  auto _201 = [x](auto xs) {
    auto _202 = [xs, x]() {
      auto _203 = xs;
      switch (_203.type) {
        case NilV: {
          auto _205 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_203.data));
          auto _206 = xNotInNilV<uint64_t>;
          auto _204 = _Dec<_ElemVec<uint64_t>>::_No(_206);
          return _204;
        }
        case ConsV: {
          auto _211 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_203.data));
          auto y = _211._1;
          auto ys = _211._2;
          auto _210 = [xs, x, y, ys]() {
            auto _213 = x;
            auto _214 = y;
            auto _212 = decEqNat(_213)(_214);
            switch (_212.type) {
              case Yes: {
                auto _216 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_212.data));
                auto pf = _216._1;
                auto _219 = ys;
                auto _218 = _ElemVec<uint64_t>::_HereV(_219);
                auto _217 = _218;
                auto _215 = _Dec<_ElemVec<uint64_t>>::_Yes(_217);
                return _215;
              }
              case No: {
                auto _222 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_212.data));
                auto xneqyPf = _222._1;
                auto _221 = [xs, x, y, ys, xneqyPf]() {
                  auto _224 = x;
                  auto _225 = ys;
                  auto _223 = isElemVec(_224)(_225);
                  switch (_223.type) {
                    case Yes: {
                      auto _228 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_223.data));
                      auto pf = _228._1;
                      auto _230 = ys;
                      auto _231 = x;
                      auto _232 = pf;
                      auto _229 = _ElemVec<uint64_t>::_ThereV(_230, _231, _232);
                      auto _227 = _Dec<_ElemVec<uint64_t>>::_Yes(_229);
                      return _227;
                    }
                    case No: {
                      auto _235 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_223.data));
                      auto xninysPf = _235._1;
                      auto _237 = xneqyPf;
                      auto _238 = xninysPf;
                      auto _236 = neitherHereNorThereVec(_237)(_238);
                      auto _234 = _Dec<_ElemVec<uint64_t>>::_No(_236);
                      return _234;
                    }
                  }
                }();
                return _221;
              }
            }
          }();
          return _210;
        }
      }
    }();
    return _202;
  };
  return _201;
};
enum _enum_Disjoint_type { DNil, DCons };
template <class A>
class _Disjoint_DNil;
template <class A>
class _Disjoint_DCons;
template <class A>
class _Disjoint {
 public:
  enum _enum_Disjoint_type type;
  std::shared_ptr<void> data;
  static _Disjoint<A> _DNil();
  static _Disjoint<A> _DCons(A _1, _List<A> _2, std::function<_Void(_Elem<A>)> _3, _Disjoint<A> _4);
  _Disjoint<A>(_enum_Disjoint_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Disjoint<A>(const _Disjoint<A>& other);
  _Disjoint<A>() = default;
};
template <class A>
class _Disjoint_DNil {
 public:
  _Disjoint_DNil(){};
  _Disjoint_DNil(const _Disjoint_DNil* other) {}
};
template <class A>
class _Disjoint_DCons {
 public:
  A _1;
  _List<A> _2;
  std::function<_Void(_Elem<A>)> _3;
  _Disjoint<A> _4;
  _Disjoint_DCons(A _1, _List<A> _2, std::function<_Void(_Elem<A>)> _3, _Disjoint<A> _4) {
    this->_1 = _1;
    this->_2 = _2;
    this->_3 = _3;
    this->_4 = _4;
  };
  _Disjoint_DCons(const _Disjoint_DCons* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
    this->_3 = other->_3;
    this->_4 = other->_4;
  }
};
template <class A>
inline _Disjoint<A> _Disjoint<A>::_DNil() {
  return _Disjoint<A>(DNil, std::make_shared<_Disjoint_DNil<A>>());
};
template <class A>
inline _Disjoint<A> _Disjoint<A>::_DCons(A _1, _List<A> _2, std::function<_Void(_Elem<A>)> _3, _Disjoint<A> _4) {
  return _Disjoint<A>(DCons, std::make_shared<_Disjoint_DCons<A>>(_1, _2, _3, _4));
};
template <class A>
_Disjoint<A>::_Disjoint(const _Disjoint<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<_Void(_Elem<A>)> xNotInNil = [](auto p) {
  auto _243 = [p]() {
    auto _244 = p;
    return _Void();
  }();
  return _243;
};

template <class A>
std::function<std::function<_Disjoint<A>(_TyEq)>(_List<A>)> lemma_y_empty_disjoint = [](auto a) {
  auto _245 = [a](auto pf) {
    auto _246 = [a, pf]() {
      auto _247 = a;
      switch (_247.type) {
        case Nil: {
          auto _249 = *(std::static_pointer_cast<_List_Nil<A>>(_247.data));
          auto _248 = _Disjoint<A>::_DNil();
          return _248;
        }
        case Cons: {
          auto _251 = *(std::static_pointer_cast<_List_Cons<A>>(_247.data));
          auto x = _251._1;
          auto xs = _251._2;
          auto _252 = x;
          auto _253 = xs;
          auto _256 = xNotInNil<A>;
          auto _254 = _256;
          auto _259 = xs;
          auto _260 = pf;
          auto _255 = lemma_y_empty_disjoint<A>(_259)(_260);
          auto _250 = _Disjoint<A>::_DCons(_252, _253, _254, _255);
          return _250;
        }
      }
    }();
    return _246;
  };
  return _245;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(_Elem<A>)> lemma_x_in_b = [](auto xInB) {
  auto _263 = [xInB](auto pf) {
    auto _264 = [pf, xInB]() {
      auto _265 = pf;
      switch (_265.type) {
        case DCons: {
          auto _267 = *(std::static_pointer_cast<_Disjoint_DCons<A>>(_265.data));
          auto i = _267._1;
          auto is = _267._2;
          auto pfFori = _267._3;
          auto others = _267._4;
          auto _268 = xInB;
          auto _266 = pfFori(_268);
          return _266;
        }
      }
    }();
    return _264;
  };
  return _263;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(std::function<_Void(_Disjoint<A>)>)> lemma_xs_in_b = [](auto pf) {
  auto _269 = [pf](auto p) {
    auto _270 = [p, pf]() {
      auto _271 = p;
      switch (_271.type) {
        case DCons: {
          auto _273 = *(std::static_pointer_cast<_Disjoint_DCons<A>>(_271.data));
          auto i = _273._1;
          auto is = _273._2;
          auto pfFori = _273._3;
          auto others = _273._4;
          auto _274 = others;
          auto _272 = pf(_274);
          return _272;
        }
      }
    }();
    return _270;
  };
  return _269;
};

std::function<std::function<_Dec<_Disjoint<uint64_t>>(_List<uint64_t>)>(_List<uint64_t>)> decDisjointLists = [](auto a) {
  auto _275 = [a](auto b) {
    auto _276 = [a, b]() {
      auto _277 = a;
      switch (_277.type) {
        case Nil: {
          auto _279 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_277.data));
          auto _280 = _Disjoint<uint64_t>::_DNil();
          auto _278 = _Dec<_Disjoint<uint64_t>>::_Yes(_280);
          return _278;
        }
        case Cons: {
          auto _282 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_277.data));
          auto x = _282._1;
          auto xs = _282._2;
          auto _281 = [a, b, xs, x]() {
            auto _283 = b;
            switch (_283.type) {
              case Nil: {
                auto _285 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_283.data));
                auto _287 = a;
                auto _288 = _TyEq::_Refl();
                auto _286 = lemma_y_empty_disjoint<uint64_t>(_287)(_288);
                auto _284 = _Dec<_Disjoint<uint64_t>>::_Yes(_286);
                return _284;
              }
              case Cons: {
                auto _292 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_283.data));
                auto y = _292._1;
                auto ys = _292._2;
                auto _291 = [a, b, xs, x]() {
                  auto _294 = xs;
                  auto _295 = b;
                  auto _293 = decDisjointLists(_294)(_295);
                  switch (_293.type) {
                    case Yes: {
                      auto _297 = *(std::static_pointer_cast<_Dec_Yes<_Disjoint<uint64_t>>>(_293.data));
                      auto pf = _297._1;
                      auto _296 = [a, b, xs, x, pf]() {
                        auto _299 = x;
                        auto _300 = b;
                        auto _298 = isElem(_299)(_300);
                        switch (_298.type) {
                          case Yes: {
                            auto _302 = *(std::static_pointer_cast<_Dec_Yes<_Elem<uint64_t>>>(_298.data));
                            auto elemPf = _302._1;
                            auto _304 = elemPf;
                            auto _303 = lemma_x_in_b<uint64_t>(_304);
                            auto _301 = _Dec<_Disjoint<uint64_t>>::_No(_303);
                            return _301;
                          }
                          case No: {
                            auto _311 = *(std::static_pointer_cast<_Dec_No<_Elem<uint64_t>>>(_298.data));
                            auto p = _311._1;
                            auto _313 = x;
                            auto _314 = xs;
                            auto _315 = p;
                            auto _316 = pf;
                            auto _312 = _Disjoint<uint64_t>::_DCons(_313, _314, _315, _316);
                            auto _310 = _Dec<_Disjoint<uint64_t>>::_Yes(_312);
                            return _310;
                          }
                        }
                      }();
                      return _296;
                    }
                    case No: {
                      auto _318 = *(std::static_pointer_cast<_Dec_No<_Disjoint<uint64_t>>>(_293.data));
                      auto p = _318._1;
                      auto _320 = p;
                      auto _319 = lemma_xs_in_b<uint64_t>(_320);
                      auto _317 = _Dec<_Disjoint<uint64_t>>::_No(_319);
                      return _317;
                    }
                  }
                }();
                return _291;
              }
            }
          }();
          return _281;
        }
      }
    }();
    return _276;
  };
  return _275;
};
enum _enum_DisjointVec_type { DNilV, DConsV };
template <class A>
class _DisjointVec_DNilV;
template <class A>
class _DisjointVec_DConsV;
template <class A>
class _DisjointVec {
 public:
  enum _enum_DisjointVec_type type;
  std::shared_ptr<void> data;
  static _DisjointVec<A> _DNilV();
  static _DisjointVec<A> _DConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _DisjointVec<A> _4);
  _DisjointVec<A>(_enum_DisjointVec_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _DisjointVec<A>(const _DisjointVec<A>& other);
  _DisjointVec<A>() = default;
};
template <class A>
class _DisjointVec_DNilV {
 public:
  _DisjointVec_DNilV(){};
  _DisjointVec_DNilV(const _DisjointVec_DNilV* other) {}
};
template <class A>
class _DisjointVec_DConsV {
 public:
  A _1;
  _Vec<A> _2;
  std::function<_Void(_ElemVec<A>)> _3;
  _DisjointVec<A> _4;
  _DisjointVec_DConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _DisjointVec<A> _4) {
    this->_1 = _1;
    this->_2 = _2;
    this->_3 = _3;
    this->_4 = _4;
  };
  _DisjointVec_DConsV(const _DisjointVec_DConsV* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
    this->_3 = other->_3;
    this->_4 = other->_4;
  }
};
template <class A>
inline _DisjointVec<A> _DisjointVec<A>::_DNilV() {
  return _DisjointVec<A>(DNilV, std::make_shared<_DisjointVec_DNilV<A>>());
};
template <class A>
inline _DisjointVec<A> _DisjointVec<A>::_DConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _DisjointVec<A> _4) {
  return _DisjointVec<A>(DConsV, std::make_shared<_DisjointVec_DConsV<A>>(_1, _2, _3, _4));
};
template <class A>
_DisjointVec<A>::_DisjointVec(const _DisjointVec<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<std::function<_DisjointVec<A>(_TyEq)>(_Vec<A>)> lemma_y_empty_disjoint_vec = [](auto a) {
  auto _325 = [a](auto pf) {
    auto _326 = [a, pf]() {
      auto _327 = a;
      switch (_327.type) {
        case NilV: {
          auto _329 = *(std::static_pointer_cast<_Vec_NilV<A>>(_327.data));
          auto _328 = _DisjointVec<A>::_DNilV();
          return _328;
        }
        case ConsV: {
          auto _331 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_327.data));
          auto x = _331._1;
          auto xs = _331._2;
          auto _332 = x;
          auto _333 = xs;
          auto _337 = xNotInNilV<A>;
          auto _334 = _337;
          auto _341 = xs;
          auto _342 = pf;
          auto _335 = lemma_y_empty_disjoint_vec<A>(_341)(_342);
          auto _330 = _DisjointVec<A>::_DConsV(_332, _333, _334, _335);
          return _330;
        }
      }
    }();
    return _326;
  };
  return _325;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(_ElemVec<A>)> lemma_x_in_b_vec = [](auto xInB) {
  auto _346 = [xInB](auto pf) {
    auto _347 = [pf, xInB]() {
      auto _348 = pf;
      switch (_348.type) {
        case DConsV: {
          auto _350 = *(std::static_pointer_cast<_DisjointVec_DConsV<A>>(_348.data));
          auto y = _350._1;
          auto ys = _350._2;
          auto pfFory = _350._3;
          auto others = _350._4;
          auto _351 = xInB;
          auto _349 = pfFory(_351);
          return _349;
        }
      }
    }();
    return _347;
  };
  return _346;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(std::function<_Void(_DisjointVec<A>)>)> lemma_xs_in_b_vec = [](auto pf) {
  auto _352 = [pf](auto p) {
    auto _353 = [p, pf]() {
      auto _354 = p;
      switch (_354.type) {
        case DConsV: {
          auto _356 = *(std::static_pointer_cast<_DisjointVec_DConsV<A>>(_354.data));
          auto i = _356._1;
          auto is = _356._2;
          auto pfFori = _356._3;
          auto others = _356._4;
          auto _357 = others;
          auto _355 = pf(_357);
          return _355;
        }
      }
    }();
    return _353;
  };
  return _352;
};

std::function<std::function<_Dec<_DisjointVec<uint64_t>>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decDisjointVecs = [](auto a) {
  auto _358 = [a](auto b) {
    auto _359 = [a, b]() {
      auto _360 = a;
      switch (_360.type) {
        case NilV: {
          auto _362 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_360.data));
          auto _363 = _DisjointVec<uint64_t>::_DNilV();
          auto _361 = _Dec<_DisjointVec<uint64_t>>::_Yes(_363);
          return _361;
        }
        case ConsV: {
          auto _365 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_360.data));
          auto x = _365._1;
          auto xs = _365._2;
          auto _364 = [a, b, xs, x]() {
            auto _366 = b;
            switch (_366.type) {
              case NilV: {
                auto _368 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_366.data));
                auto _370 = a;
                auto _371 = _TyEq::_Refl();
                auto _369 = lemma_y_empty_disjoint_vec<uint64_t>(_370)(_371);
                auto _367 = _Dec<_DisjointVec<uint64_t>>::_Yes(_369);
                return _367;
              }
              case ConsV: {
                auto _376 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_366.data));
                auto y = _376._1;
                auto ys = _376._2;
                auto _375 = [a, b, xs, x]() {
                  auto _378 = xs;
                  auto _379 = b;
                  auto _377 = decDisjointVecs(_378)(_379);
                  switch (_377.type) {
                    case Yes: {
                      auto _383 = *(std::static_pointer_cast<_Dec_Yes<_DisjointVec<uint64_t>>>(_377.data));
                      auto pf = _383._1;
                      auto _382 = [a, b, xs, x, pf]() {
                        auto _385 = x;
                        auto _386 = b;
                        auto _384 = isElemVec(_385)(_386);
                        switch (_384.type) {
                          case Yes: {
                            auto _389 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_384.data));
                            auto elemPf = _389._1;
                            auto _391 = elemPf;
                            auto _390 = lemma_x_in_b_vec<uint64_t>(_391);
                            auto _388 = _Dec<_DisjointVec<uint64_t>>::_No(_390);
                            return _388;
                          }
                          case No: {
                            auto _400 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_384.data));
                            auto p = _400._1;
                            auto _402 = x;
                            auto _403 = xs;
                            auto _404 = p;
                            auto _405 = pf;
                            auto _401 = _DisjointVec<uint64_t>::_DConsV(_402, _403, _404, _405);
                            auto _399 = _Dec<_DisjointVec<uint64_t>>::_Yes(_401);
                            return _399;
                          }
                        }
                      }();
                      return _382;
                    }
                    case No: {
                      auto _408 = *(std::static_pointer_cast<_Dec_No<_DisjointVec<uint64_t>>>(_377.data));
                      auto p = _408._1;
                      auto _410 = p;
                      auto _409 = lemma_xs_in_b_vec<uint64_t>(_410);
                      auto _407 = _Dec<_DisjointVec<uint64_t>>::_No(_409);
                      return _407;
                    }
                  }
                }();
                return _375;
              }
            }
          }();
          return _364;
        }
      }
    }();
    return _359;
  };
  return _358;
};

std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjLem = [](auto prf1) {
  auto _417 = [](auto prf2) {
    auto _420 = prf2;
    auto _419 = f_equal<_Vec<uint64_t>, _Vec<uint64_t>>(_420);
    auto _418 = _419;
    return _418;
  };
  return _417;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjective = [](auto p1) {
  auto _426 = [](auto p2) {
    auto _429 = p2;
    auto _428 = f_equal<_Vec<A>, _Vec<A>>(_429);
    auto _427 = _428;
    return _427;
  };
  return _426;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjectiveTail = [](auto p1) {
  auto _435 = [](auto p2) {
    auto _437 = p2;
    auto _436 = f_equal<_Vec<A>, A>(_437);
    return _436;
  };
  return _435;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(_TyEq)> lemma_x_eq_xs_neq_vec = [](auto prf1) {
  auto _443 = [prf1](auto p) {
    auto _444 = [p, prf1](auto prf2) {
      auto _447 = prf1;
      auto _448 = prf2;
      auto _446 = consVInjective<A>(_447)(_448);
      auto _445 = p(_446);
      return _445;
    };
    return _444;
  };
  return _443;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(_TyEq)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_eq_vec = [](auto p) {
  auto _455 = [p](auto p2) {
    auto _456 = [p, p2](auto p3) {
      auto _459 = p2;
      auto _460 = p3;
      auto _458 = consVInjectiveTail<A>(_459)(_460);
      auto _457 = p(_458);
      return _457;
    };
    return _456;
  };
  return _455;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_neq_vec = [](auto p) {
  auto _467 = [p](auto p2) {
    auto _468 = [p](auto p3) {
      auto _471 = p3;
      auto _470 = f_equal<_Vec<A>, A>(_471);
      auto _469 = p(_470);
      return _469;
    };
    return _468;
  };
  return _467;
};

std::function<std::function<_Dec<_TyEq>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decEqVec = [](auto a) {
  auto _477 = [a](auto b) {
    auto _478 = [a, b]() {
      auto _479 = a;
      switch (_479.type) {
        case NilV: {
          auto _481 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_479.data));
          auto _480 = [a, b]() {
            auto _482 = b;
            switch (_482.type) {
              case NilV: {
                auto _484 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_482.data));
                auto _485 = _TyEq::_Refl();
                auto _483 = _Dec<_TyEq>::_Yes(_485);
                return _483;
              }
            }
          }();
          return _480;
        }
        case ConsV: {
          auto _487 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_479.data));
          auto x = _487._1;
          auto xs = _487._2;
          auto _486 = [a, b, x, xs]() {
            auto _488 = b;
            switch (_488.type) {
              case ConsV: {
                auto _490 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_488.data));
                auto y = _490._1;
                auto ys = _490._2;
                auto _489 = [a, b, x, y, xs, ys]() {
                  auto _492 = x;
                  auto _493 = y;
                  auto _491 = decEqNat(_492)(_493);
                  switch (_491.type) {
                    case Yes: {
                      auto _495 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_491.data));
                      auto xeqy = _495._1;
                      auto _494 = [a, b, x, y, xs, ys, xeqy]() {
                        auto _497 = xs;
                        auto _498 = ys;
                        auto _496 = decEqVec(_497)(_498);
                        switch (_496.type) {
                          case Yes: {
                            auto _501 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_496.data));
                            auto xseqys = _501._1;
                            auto _503 = xeqy;
                            auto _504 = xseqys;
                            auto _502 = consVInjLem(_503)(_504);
                            auto _500 = _Dec<_TyEq>::_Yes(_502);
                            return _500;
                          }
                          case No: {
                            auto _511 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_496.data));
                            auto xsneqys = _511._1;
                            auto _513 = xeqy;
                            auto _514 = xsneqys;
                            auto _512 = lemma_x_eq_xs_neq_vec<uint64_t>(_513)(_514);
                            auto _510 = _Dec<_TyEq>::_No(_512);
                            return _510;
                          }
                        }
                      }();
                      return _494;
                    }
                    case No: {
                      auto _522 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_491.data));
                      auto xneqy = _522._1;
                      auto _521 = [a, b, x, y, xs, ys, xneqy]() {
                        auto _524 = xs;
                        auto _525 = ys;
                        auto _523 = decEqVec(_524)(_525);
                        switch (_523.type) {
                          case Yes: {
                            auto _528 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_523.data));
                            auto xseqys = _528._1;
                            auto _530 = xneqy;
                            auto _531 = xseqys;
                            auto _529 = lemma_x_neq_xs_eq_vec<uint64_t>(_530)(_531);
                            auto _527 = _Dec<_TyEq>::_No(_529);
                            return _527;
                          }
                          case No: {
                            auto _539 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_523.data));
                            auto xsneqys = _539._1;
                            auto _541 = xneqy;
                            auto _542 = xsneqys;
                            auto _540 = lemma_x_neq_xs_neq_vec<uint64_t>(_541)(_542);
                            auto _538 = _Dec<_TyEq>::_No(_540);
                            return _538;
                          }
                        }
                      }();
                      return _521;
                    }
                  }
                }();
                return _489;
              }
            }
          }();
          return _486;
        }
      }
    }();
    return _478;
  };
  return _477;
};
enum _enum_UniqueVec_type { UNilV, UConsV };
template <class A>
class _UniqueVec_UNilV;
template <class A>
class _UniqueVec_UConsV;
template <class A>
class _UniqueVec {
 public:
  enum _enum_UniqueVec_type type;
  std::shared_ptr<void> data;
  static _UniqueVec<A> _UNilV();
  static _UniqueVec<A> _UConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _UniqueVec<A> _4);
  _UniqueVec<A>(_enum_UniqueVec_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _UniqueVec<A>(const _UniqueVec<A>& other);
  _UniqueVec<A>() = default;
};
template <class A>
class _UniqueVec_UNilV {
 public:
  _UniqueVec_UNilV(){};
  _UniqueVec_UNilV(const _UniqueVec_UNilV* other) {}
};
template <class A>
class _UniqueVec_UConsV {
 public:
  A _1;
  _Vec<A> _2;
  std::function<_Void(_ElemVec<A>)> _3;
  _UniqueVec<A> _4;
  _UniqueVec_UConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _UniqueVec<A> _4) {
    this->_1 = _1;
    this->_2 = _2;
    this->_3 = _3;
    this->_4 = _4;
  };
  _UniqueVec_UConsV(const _UniqueVec_UConsV* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
    this->_3 = other->_3;
    this->_4 = other->_4;
  }
};
template <class A>
inline _UniqueVec<A> _UniqueVec<A>::_UNilV() {
  return _UniqueVec<A>(UNilV, std::make_shared<_UniqueVec_UNilV<A>>());
};
template <class A>
inline _UniqueVec<A> _UniqueVec<A>::_UConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _UniqueVec<A> _4) {
  return _UniqueVec<A>(UConsV, std::make_shared<_UniqueVec_UConsV<A>>(_1, _2, _3, _4));
};
template <class A>
_UniqueVec<A>::_UniqueVec(const _UniqueVec<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<std::function<_Void(_UniqueVec<A>)>(_ElemVec<A>)> lemma_x_in_xs_not_unique = [](auto pf) {
  auto _549 = [pf](auto p) {
    auto _550 = [p, pf]() {
      auto _551 = p;
      switch (_551.type) {
        case UConsV: {
          auto _553 = *(std::static_pointer_cast<_UniqueVec_UConsV<A>>(_551.data));
          auto x = _553._1;
          auto xs = _553._2;
          auto xNInXs = _553._3;
          auto others = _553._4;
          auto _554 = pf;
          auto _552 = xNInXs(_554);
          return _552;
        }
      }
    }();
    return _550;
  };
  return _549;
};

template <class A>
std::function<std::function<_Void(_UniqueVec<A>)>(std::function<_Void(_UniqueVec<A>)>)> lemma_xs_not_unique = [](auto pf) {
  auto _555 = [pf](auto p) {
    auto _556 = [p, pf]() {
      auto _557 = p;
      switch (_557.type) {
        case UConsV: {
          auto _559 = *(std::static_pointer_cast<_UniqueVec_UConsV<A>>(_557.data));
          auto x = _559._1;
          auto xs = _559._2;
          auto xNInXs = _559._3;
          auto others = _559._4;
          auto _560 = others;
          auto _558 = pf(_560);
          return _558;
        }
      }
    }();
    return _556;
  };
  return _555;
};

std::function<_Dec<_UniqueVec<uint64_t>>(_Vec<uint64_t>)> decUniqueVec = [](auto v) {
  auto _561 = [v]() {
    auto _562 = v;
    switch (_562.type) {
      case NilV: {
        auto _564 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_562.data));
        auto _565 = _UniqueVec<uint64_t>::_UNilV();
        auto _563 = _Dec<_UniqueVec<uint64_t>>::_Yes(_565);
        return _563;
      }
      case ConsV: {
        auto _567 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_562.data));
        auto x = _567._1;
        auto xs = _567._2;
        auto _566 = [v, x, xs]() {
          auto _569 = x;
          auto _570 = xs;
          auto _568 = isElemVec(_569)(_570);
          switch (_568.type) {
            case Yes: {
              auto _573 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_568.data));
              auto xInXs = _573._1;
              auto _575 = xInXs;
              auto _574 = lemma_x_in_xs_not_unique<uint64_t>(_575);
              auto _572 = _Dec<_UniqueVec<uint64_t>>::_No(_574);
              return _572;
            }
            case No: {
              auto _581 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_568.data));
              auto xNInXs = _581._1;
              auto _580 = [v, x, xs, xNInXs]() {
                auto _583 = xs;
                auto _582 = decUniqueVec(_583);
                switch (_582.type) {
                  case Yes: {
                    auto _586 = *(std::static_pointer_cast<_Dec_Yes<_UniqueVec<uint64_t>>>(_582.data));
                    auto xsU = _586._1;
                    auto _588 = x;
                    auto _589 = xs;
                    auto _590 = xNInXs;
                    auto _591 = xsU;
                    auto _587 = _UniqueVec<uint64_t>::_UConsV(_588, _589, _590, _591);
                    auto _585 = _Dec<_UniqueVec<uint64_t>>::_Yes(_587);
                    return _585;
                  }
                  case No: {
                    auto _594 = *(std::static_pointer_cast<_Dec_No<_UniqueVec<uint64_t>>>(_582.data));
                    auto xsNU = _594._1;
                    auto _596 = xsNU;
                    auto _595 = lemma_xs_not_unique<uint64_t>(_596);
                    auto _593 = _Dec<_UniqueVec<uint64_t>>::_No(_595);
                    return _593;
                  }
                }
              }();
              return _580;
            }
          }
        }();
        return _566;
      }
    }
  }();
  return _561;
};
enum _enum_SubsetVec_type { SNilV1, SNilV2, SConsV };
template <class A>
class _SubsetVec_SNilV1;
template <class A>
class _SubsetVec_SNilV2;
template <class A>
class _SubsetVec_SConsV;
template <class A>
class _SubsetVec {
 public:
  enum _enum_SubsetVec_type type;
  std::shared_ptr<void> data;
  static _SubsetVec<A> _SNilV1();
  static _SubsetVec<A> _SNilV2();
  static _SubsetVec<A> _SConsV(A _1, _Vec<A> _2, _ElemVec<A> _3, _SubsetVec<A> _4);
  _SubsetVec<A>(_enum_SubsetVec_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _SubsetVec<A>(const _SubsetVec<A>& other);
  _SubsetVec<A>() = default;
};
template <class A>
class _SubsetVec_SNilV1 {
 public:
  _SubsetVec_SNilV1(){};
  _SubsetVec_SNilV1(const _SubsetVec_SNilV1* other) {}
};
template <class A>
class _SubsetVec_SNilV2 {
 public:
  _SubsetVec_SNilV2(){};
  _SubsetVec_SNilV2(const _SubsetVec_SNilV2* other) {}
};
template <class A>
class _SubsetVec_SConsV {
 public:
  A _1;
  _Vec<A> _2;
  _ElemVec<A> _3;
  _SubsetVec<A> _4;
  _SubsetVec_SConsV(A _1, _Vec<A> _2, _ElemVec<A> _3, _SubsetVec<A> _4) {
    this->_1 = _1;
    this->_2 = _2;
    this->_3 = _3;
    this->_4 = _4;
  };
  _SubsetVec_SConsV(const _SubsetVec_SConsV* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
    this->_3 = other->_3;
    this->_4 = other->_4;
  }
};
template <class A>
inline _SubsetVec<A> _SubsetVec<A>::_SNilV1() {
  return _SubsetVec<A>(SNilV1, std::make_shared<_SubsetVec_SNilV1<A>>());
};
template <class A>
inline _SubsetVec<A> _SubsetVec<A>::_SNilV2() {
  return _SubsetVec<A>(SNilV2, std::make_shared<_SubsetVec_SNilV2<A>>());
};
template <class A>
inline _SubsetVec<A> _SubsetVec<A>::_SConsV(A _1, _Vec<A> _2, _ElemVec<A> _3, _SubsetVec<A> _4) {
  return _SubsetVec<A>(SConsV, std::make_shared<_SubsetVec_SConsV<A>>(_1, _2, _3, _4));
};
template <class A>
_SubsetVec<A>::_SubsetVec(const _SubsetVec<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<std::function<_Void(_SubsetVec<A>)>(std::function<_Void(_ElemVec<A>)>)> lemma_x_not_in_b_vec = [](auto pfXNotInb) {
  auto _601 = [pfXNotInb](auto pf) {
    auto _602 = [pf, pfXNotInb]() {
      auto _603 = pf;
      switch (_603.type) {
        case SConsV: {
          auto _605 = *(std::static_pointer_cast<_SubsetVec_SConsV<A>>(_603.data));
          auto a = _605._1;
          auto as = _605._2;
          auto pfFora = _605._3;
          auto others = _605._4;
          auto _606 = pfFora;
          auto _604 = pfXNotInb(_606);
          return _604;
        }
      }
    }();
    return _602;
  };
  return _601;
};

template <class A>
std::function<std::function<_Void(_SubsetVec<A>)>(std::function<_Void(_SubsetVec<A>)>)> lemma_xs_not_subset_b_vec = [](auto xsNotSubsetPf) {
  auto _607 = [xsNotSubsetPf](auto p) {
    auto _608 = [p, xsNotSubsetPf]() {
      auto _609 = p;
      switch (_609.type) {
        case SConsV: {
          auto _611 = *(std::static_pointer_cast<_SubsetVec_SConsV<A>>(_609.data));
          auto a = _611._1;
          auto as = _611._2;
          auto pfFora = _611._3;
          auto others = _611._4;
          auto _612 = others;
          auto _610 = xsNotSubsetPf(_612);
          return _610;
        }
      }
    }();
    return _608;
  };
  return _607;
};

std::function<std::function<_Dec<_SubsetVec<uint64_t>>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decSubsetVecs = [](auto a) {
  auto _613 = [a](auto b) {
    auto _614 = [a, b]() {
      auto _615 = a;
      switch (_615.type) {
        case NilV: {
          auto _617 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_615.data));
          auto _618 = _SubsetVec<uint64_t>::_SNilV1();
          auto _616 = _Dec<_SubsetVec<uint64_t>>::_Yes(_618);
          return _616;
        }
        case ConsV: {
          auto _620 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_615.data));
          auto x = _620._1;
          auto xs = _620._2;
          auto _619 = [a, b, xs, x]() {
            auto _621 = b;
            switch (_621.type) {
              case NilV: {
                auto _623 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_621.data));
                auto _624 = _SubsetVec<uint64_t>::_SNilV2();
                auto _622 = _Dec<_SubsetVec<uint64_t>>::_Yes(_624);
                return _622;
              }
              case ConsV: {
                auto _626 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_621.data));
                auto y = _626._1;
                auto ys = _626._2;
                auto _625 = [a, b, xs, x]() {
                  auto _628 = xs;
                  auto _629 = b;
                  auto _627 = decSubsetVecs(_628)(_629);
                  switch (_627.type) {
                    case Yes: {
                      auto _633 = *(std::static_pointer_cast<_Dec_Yes<_SubsetVec<uint64_t>>>(_627.data));
                      auto pf = _633._1;
                      auto _632 = [a, b, xs, x, pf]() {
                        auto _635 = x;
                        auto _636 = b;
                        auto _634 = isElemVec(_635)(_636);
                        switch (_634.type) {
                          case Yes: {
                            auto _639 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_634.data));
                            auto elemPf = _639._1;
                            auto _641 = x;
                            auto _642 = xs;
                            auto _643 = elemPf;
                            auto _644 = pf;
                            auto _640 = _SubsetVec<uint64_t>::_SConsV(_641, _642, _643, _644);
                            auto _638 = _Dec<_SubsetVec<uint64_t>>::_Yes(_640);
                            return _638;
                          }
                          case No: {
                            auto _647 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_634.data));
                            auto p = _647._1;
                            auto _649 = p;
                            auto _648 = lemma_x_not_in_b_vec<uint64_t>(_649);
                            auto _646 = _Dec<_SubsetVec<uint64_t>>::_No(_648);
                            return _646;
                          }
                        }
                      }();
                      return _632;
                    }
                    case No: {
                      auto _658 = *(std::static_pointer_cast<_Dec_No<_SubsetVec<uint64_t>>>(_627.data));
                      auto p = _658._1;
                      auto _660 = p;
                      auto _659 = lemma_xs_not_subset_b_vec<uint64_t>(_660);
                      auto _657 = _Dec<_SubsetVec<uint64_t>>::_No(_659);
                      return _657;
                    }
                  }
                }();
                return _625;
              }
            }
          }();
          return _619;
        }
      }
    }();
    return _614;
  };
  return _613;
};
enum _enum_IO_type { MkIO };
template <class A>
class _IO_MkIO;
template <class A>
class _IO {
 public:
  enum _enum_IO_type type;
  std::shared_ptr<void> data;
  static _IO<A> _MkIO(A _1);
  _IO<A>(_enum_IO_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _IO<A>(const _IO<A>& other);
  _IO<A>() = default;
};
template <class A>
class _IO_MkIO {
 public:
  A _1;
  _IO_MkIO(A _1) { this->_1 = _1; };
  _IO_MkIO(const _IO_MkIO* other) { this->_1 = other->_1; }
};
template <class A>
inline _IO<A> _IO<A>::_MkIO(A _1) {
  return _IO<A>(MkIO, std::make_shared<_IO_MkIO<A>>(_1));
};
template <class A>
_IO<A>::_IO(const _IO<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<_IO<A>(A)> returnIO = [](auto a) {
  auto _669 = a;
  auto _668 = _IO<A>::_MkIO(_669);
  return _668;
};

template <class A, class B>
std::function<std::function<_IO<B>(std::function<_IO<B>(A)>)>(_IO<A>)> bindEq = [](auto a) {
  auto _670 = [a](auto f) {
    auto _671 = [a, f]() {
      auto _672 = a;
      switch (_672.type) {
        case MkIO: {
          auto _674 = *(std::static_pointer_cast<_IO_MkIO<A>>(_672.data));
          auto inner = _674._1;
          auto _675 = inner;
          auto _673 = f(_675);
          return _673;
        }
      }
    }();
    return _671;
  };
  return _670;
};

template <class A, class B>
std::function<std::function<_IO<B>(_IO<B>)>(_IO<A>)> bind = [](auto a) {
  auto _676 = [a](auto b) {
    auto _678 = a;
    auto _679 = [a, b](auto c) {
      auto _682 = b;
      return _682;
    };
    auto _677 = bindEq<A, B>(_678)(_679);
    return _677;
  };
  return _676;
};

std::function<_IO<_Unit>(_List<char>)> print = [](auto l) {
  auto _653 = [l]() {
    auto _654 = l;
    switch (_654.type) {
      case Nil: {
        std::cout << "\n" << std::flush;
        return returnIO<_Unit>(_Unit::_unit());
      }
      case Cons: {
        auto _660 = *(std::static_pointer_cast<_List_Cons<char>>(_654.data));
        auto c = _660._1;
        auto cs = _660._2;
        std::cout << c;
        return print(cs);
      }
    }
  }();
  return _653;
};

std::function<_IO<_Unit>(_List<_List<char>>)> printList = [](auto l) {
  auto _683 = [l]() {
    auto _684 = l;
    switch (_684.type) {
      case Nil: {
        auto _686 = *(std::static_pointer_cast<_List_Nil<_List<char>>>(_684.data));
        auto _687 = _Unit::_unit();
        auto _685 = returnIO<_Unit>(_687);
        return _685;
      }
      case Cons: {
        auto _690 = *(std::static_pointer_cast<_List_Cons<_List<char>>>(_684.data));
        auto x = _690._1;
        auto xs = _690._2;
        auto _695 = x;
        auto _691 = print(_695);
        auto _696 = xs;
        auto _692 = printList(_696);
        auto _689 = bind<_Unit, _Unit>(_691)(_692);
        return _689;
      }
    }
  }();
  return _683;
};
enum _enum_Channel_type { MkChannel };
template <class A>
class _Channel_MkChannel;
template <class A>
class _Channel {
 public:
  enum _enum_Channel_type type;
  std::shared_ptr<void> data;
  static _Channel<A> _MkChannel(uint64_t _1);
  _Channel<A>(_enum_Channel_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Channel<A>(const _Channel<A>& other);
  _Channel<A>() = default;
};
template <class A>
class _Channel_MkChannel {
 public:
  uint64_t _1;
  _Channel_MkChannel(uint64_t _1) { this->_1 = _1; };
  _Channel_MkChannel(const _Channel_MkChannel* other) { this->_1 = other->_1; }
};
template <class A>
inline _Channel<A> _Channel<A>::_MkChannel(uint64_t _1) {
  return _Channel<A>(MkChannel, std::make_shared<_Channel_MkChannel<A>>(_1));
};
template <class A>
_Channel<A>::_Channel(const _Channel<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<_Bool(uint64_t)> prim_create_channel = [](auto id) {
  LockingCQueue<_Maybe<A>>* q = new LockingCQueue<_Maybe<A>>();
  addChannel(id, q);
  return _Bool::_True();
};

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_Channel<A>)>(_Maybe<A>)>(uint64_t)> channelEnqueue = [](auto id) {
  auto _629 = [id](auto x) {
    auto _630 = [id, x](auto ch) {
      LockingCQueue<_Maybe<A>>* queue = (LockingCQueue<_Maybe<A>>*)getChannel(id);
      queue->enqueue(x);
      auto _632 = _Unit::_unit();
      auto _631 = returnIO<_Unit>(_632);
      return _631;
    };
    return _630;
  };
  return _629;
};
;

template <class A>
std::function<std::function<_IO<_Maybe<A>>(_Channel<A>)>(uint64_t)> channelDequeue = [](auto id) {
  auto _630 = [id](auto ch) {
    LockingCQueue<_Maybe<A>>* queue = (LockingCQueue<_Maybe<A>>*)getChannel(id);
    auto result = queue->dequeue();
    auto _631 = returnIO<_Maybe<A>>(result);
    return _631;
  };
  return _630;
};
;

_IO<_Unit> end = []() {
  auto _631 = _Unit::_unit();
  auto _630 = returnIO<_Unit>(_631);
  return _630;
}();

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_Channel<A>)>(_Maybe<A>)>(uint64_t)> send = [](auto id) {
  auto _697 = [id](auto x) {
    auto _698 = [id, x](auto ch) {
      auto _700 = id;
      auto _701 = x;
      auto _702 = ch;
      auto _699 = channelEnqueue<A>(_700)(_701)(_702);
      return _699;
    };
    return _698;
  };
  return _697;
};

template <class A>
std::function<std::function<_IO<_Maybe<A>>(_Channel<A>)>(uint64_t)> receive = [](auto id) {
  auto _704 = [id](auto ch) {
    auto _706 = id;
    auto _707 = ch;
    auto _705 = channelDequeue<A>(_706)(_707);
    return _705;
  };
  return _704;
};

template <class A>
std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(std::function<_Void(_ElemVec<uint64_t>)>)>(_Vec<uint64_t>)>(uint64_t)>
    link = [](auto id) {
      auto _709 = [id](auto idSet) {
        auto _710 = [id, idSet](auto pf) {
          auto _711 = [id, idSet]() {
            auto _713 = id;
            auto _712 = prim_create_channel<A>(_713);
            switch (_712.type) {
              case True: {
                auto _716 = *(std::static_pointer_cast<_Bool_True>(_712.data));
                auto _720 = id;
                auto _724 = id;
                auto _722 = _Channel<A>::_MkChannel(_724);
                auto _727 = id;
                auto _728 = idSet;
                auto _725 = _Vec<uint64_t>::_ConsV(_727, _728);
                auto _730 = _TyEq::_Refl();
                auto _731 = _TyEq::_Refl();
                auto _726 = _Sigma<_TyEq, _TyEq>::_Prod(_730, _731);
                auto _723 = _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>::_Prod(_725, _726);
                auto _721 = _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>::_Prod(_722, _723);
                auto _719 = _Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Prod(_720, _721);
                auto _717 = _Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>::_Just(_719);
                auto _715 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_717);
                return _715;
              }
              case False: {
                auto _733 = *(std::static_pointer_cast<_Bool_False>(_712.data));
                auto _734 = _Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>::_Nothing();
                auto _732 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_734);
                return _732;
              }
            }
          }();
          return _711;
        };
        return _710;
      };
      return _709;
    };

std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(std::function<_Void(_ElemVec<uint64_t>)>)>(_Vec<uint64_t>)>(
    uint64_t)>(uint64_t)>
    spawn = [](auto pid) {
      auto _736 = [pid](auto n) {
        auto _737 = [pid](auto pidSet) {
          auto _738 = [pid, pidSet](auto pf) {
            auto _743 = pid;
            auto _747 = pid;
            auto _748 = pidSet;
            auto _745 = _Vec<uint64_t>::_ConsV(_747, _748);
            auto _750 = _TyEq::_Refl();
            auto _751 = _TyEq::_Refl();
            auto _746 = _Sigma<_TyEq, _TyEq>::_Prod(_750, _751);
            auto _744 = _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>::_Prod(_745, _746);
            auto _742 = _Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>::_Prod(_743, _744);
            auto _740 = _Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Just(_742);
            auto _739 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_740);
            return _739;
          };
          return _738;
        };
        return _737;
      };
      return _736;
    };

std::function<std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_IO<_Unit>)>(_ElemVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(uint64_t)> run =
    [](auto pid) {
      auto _752 = [](auto n) {
        auto _753 = [](auto pidSet) {
          auto _754 = [pidSet](auto pf) {
            auto _755 = [pidSet](auto process) {
              auto _760 = pidSet;
              auto _761 = _TyEq::_Refl();
              auto _759 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_760, _761);
              auto _757 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_759);
              auto _756 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_757);
              return _756;
            };
            return _755;
          };
          return _754;
        };
        return _753;
      };
      return _752;
    };

std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(std::function<void(void)>)>(
    std::function<_Void(_ElemVec<uint64_t>)>)>(_Vec<uint64_t>)>(uint64_t)>
    spawnAndRun = [](auto pid) {
      auto _719 = [pid](auto pidSet) {
        auto _720 = [pid, pidSet](auto pf) {
          auto _721 = [pid, pidSet](auto proc) {  // Spawning the thread
            try {
              std::thread* t = new std::thread([proc]() { proc(); });
              addThread(pid, t);
            } catch (std::system_error) {
              return returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Nothing());
            }
            auto _726 = pid;
            auto _730 = pid;
            auto _731 = pidSet;
            auto _728 = _Vec<uint64_t>::_ConsV(_730, _731);
            auto _733 = _TyEq::_Refl();
            auto _734 = _TyEq::_Refl();
            auto _729 = _Sigma<_TyEq, _TyEq>::_Prod(_733, _734);
            auto _727 = _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>::_Prod(_728, _729);
            auto _725 = _Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>::_Prod(_726, _727);
            auto _723 = _Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Just(_725);
            auto _722 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_723);
            return _722;
          };
          return _721;
        };
        return _720;
      };
      return _719;
    };
enum _enum_Farm_type { MkFarm };
template <class A>
class _Farm_MkFarm;
template <class A>
class _Farm {
 public:
  enum _enum_Farm_type type;
  std::shared_ptr<void> data;
  static _Farm<A> _MkFarm(uint64_t _1, std::function<A(A)> _2);
  _Farm<A>(_enum_Farm_type t, std::shared_ptr<void> d) {
    type = t;
    data = d;
  }
  _Farm<A>(const _Farm<A>& other);
  _Farm<A>() = default;
};
template <class A>
class _Farm_MkFarm {
 public:
  uint64_t _1;
  std::function<A(A)> _2;
  _Farm_MkFarm(uint64_t _1, std::function<A(A)> _2) {
    this->_1 = _1;
    this->_2 = _2;
  };
  _Farm_MkFarm(const _Farm_MkFarm* other) {
    this->_1 = other->_1;
    this->_2 = other->_2;
  }
};
template <class A>
inline _Farm<A> _Farm<A>::_MkFarm(uint64_t _1, std::function<A(A)> _2) {
  return _Farm<A>(MkFarm, std::make_shared<_Farm_MkFarm<A>>(_1, _2));
};
template <class A>
_Farm<A>::_Farm(const _Farm<A>& other) {
  type = other.type;
  data = other.data;
}

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_List<A>)>(_Channel<A>)>(uint64_t)> producerWrapper = [](auto id) {
  auto _762 = [id](auto ch) {
    auto _763 = [id, ch](auto list) {
      auto _764 = [list, id, ch]() {
        auto _765 = list;
        switch (_765.type) {
          case Nil: {
            auto _767 = *(std::static_pointer_cast<_List_Nil<A>>(_765.data));
            auto _772 = id;
            auto _773 = _Maybe<A>::_Nothing();
            auto _774 = ch;
            auto _768 = send<A>(_772)(_773)(_774);
            auto _769 = end;
            auto _766 = bind<_Unit, _Unit>(_768)(_769);
            return _766;
          }
          case Cons: {
            auto _777 = *(std::static_pointer_cast<_List_Cons<A>>(_765.data));
            auto x = _777._1;
            auto xs = _777._2;
            auto _782 = id;
            auto _786 = x;
            auto _783 = _Maybe<A>::_Just(_786);
            auto _784 = ch;
            auto _778 = send<A>(_782)(_783)(_784);
            auto _787 = id;
            auto _788 = ch;
            auto _789 = xs;
            auto _779 = producerWrapper<A>(_787)(_788)(_789);
            auto _776 = bind<_Unit, _Unit>(_778)(_779);
            return _776;
          }
        }
      }();
      return _764;
    };
    return _763;
  };
  return _762;
};

template <class A>
std::function<_IO<_Unit>(_Vec<_Sigma<uint64_t, _Channel<A>>>)> propgateTermination = [](auto chs) {
  auto _791 = [chs]() {
    auto _792 = chs;
    switch (_792.type) {
      case NilV: {
        auto _794 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_792.data));
        auto _793 = end;
        return _793;
      }
      case ConsV: {
        auto _796 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_792.data));
        auto ch = _796._1;
        auto restChs = _796._2;
        auto _795 = [chs, ch, restChs]() {
          auto _797 = ch;
          switch (_797.type) {
            case Prod: {
              auto _799 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_797.data));
              auto chid = _799._1;
              auto channel = _799._2;
              auto _804 = chid;
              auto _805 = _Maybe<A>::_Nothing();
              auto _806 = channel;
              auto _800 = send<A>(_804)(_805)(_806);
              auto _808 = restChs;
              auto _801 = propgateTermination<A>(_808);
              auto _798 = bind<_Unit, _Unit>(_800)(_801);
              return _798;
            }
          }
        }();
        return _795;
      }
    }
  }();
  return _791;
};

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_List<A>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)> farmProducerWrapper = [](auto allChs) {
  auto _811 = [allChs](auto chs) {
    auto _812 = [allChs, chs](auto list) {
      auto _813 = [list, allChs, chs]() {
        auto _814 = list;
        switch (_814.type) {
          case Nil: {
            auto _816 = *(std::static_pointer_cast<_List_Nil<A>>(_814.data));
            auto _817 = allChs;
            auto _815 = propgateTermination<A>(_817);
            return _815;
          }
          case Cons: {
            auto _821 = *(std::static_pointer_cast<_List_Cons<A>>(_814.data));
            auto x = _821._1;
            auto xs = _821._2;
            auto _820 = [list, allChs, chs, x, xs]() {
              auto _822 = chs;
              switch (_822.type) {
                case NilV: {
                  auto _824 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_822.data));
                  auto _825 = allChs;
                  auto _826 = allChs;
                  auto _827 = list;
                  auto _823 = farmProducerWrapper<A>(_825)(_826)(_827);
                  return _823;
                }
                case ConsV: {
                  auto _832 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_822.data));
                  auto ch = _832._1;
                  auto restChs = _832._2;
                  auto _831 = [list, allChs, chs, ch, x, restChs, xs]() {
                    auto _833 = ch;
                    switch (_833.type) {
                      case Prod: {
                        auto _835 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_833.data));
                        auto chid = _835._1;
                        auto channel = _835._2;
                        auto _840 = chid;
                        auto _844 = x;
                        auto _841 = _Maybe<A>::_Just(_844);
                        auto _842 = channel;
                        auto _836 = send<A>(_840)(_841)(_842);
                        auto _845 = allChs;
                        auto _846 = restChs;
                        auto _847 = xs;
                        auto _837 = farmProducerWrapper<A>(_845)(_846)(_847);
                        auto _834 = bind<_Unit, _Unit>(_836)(_837);
                        return _834;
                      }
                    }
                  }();
                  return _831;
                }
              }
            }();
            return _820;
          }
        }
      }();
      return _813;
    };
    return _812;
  };
  return _811;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_Channel<A>)>(_Channel<A>)>(uint64_t)>(uint64_t)> workerWrapper = [](auto receiveId) {
  auto _851 = [receiveId](auto sendId) {
    auto _852 = [receiveId, sendId](auto receiveChannel) {
      auto _853 = [receiveId, receiveChannel, sendId](auto sendChannel) {
        auto _854 = [receiveId, receiveChannel, sendId, sendChannel](auto f) {
          auto _860 = receiveId;
          auto _861 = receiveChannel;
          auto _856 = receive<A>(_860)(_861);
          auto _857 = [receiveId, receiveChannel, sendId, sendChannel, f](auto mx) {
            auto _863 = [receiveId, receiveChannel, mx, sendId, sendChannel, f]() {
              auto _864 = mx;
              switch (_864.type) {
                case Nothing: {
                  auto _866 = *(std::static_pointer_cast<_Maybe_Nothing<A>>(_864.data));
                  auto _871 = sendId;
                  auto _872 = _Maybe<A>::_Nothing();
                  auto _873 = sendChannel;
                  auto _867 = send<A>(_871)(_872)(_873);
                  auto _868 = end;
                  auto _865 = bind<_Unit, _Unit>(_867)(_868);
                  return _865;
                }
                case Just: {
                  auto _876 = *(std::static_pointer_cast<_Maybe_Just<A>>(_864.data));
                  auto x = _876._1;
                  auto _881 = sendId;
                  auto _886 = x;
                  auto _885 = f(_886);
                  auto _882 = _Maybe<A>::_Just(_885);
                  auto _883 = sendChannel;
                  auto _877 = send<A>(_881)(_882)(_883);
                  auto _887 = receiveId;
                  auto _888 = sendId;
                  auto _889 = receiveChannel;
                  auto _890 = sendChannel;
                  auto _891 = f;
                  auto _878 = workerWrapper<A>(_887)(_888)(_889)(_890)(_891);
                  auto _875 = bind<_Unit, _Unit>(_877)(_878);
                  return _875;
                }
              }
            }();
            return _863;
          };
          auto _855 = bindEq<_Maybe<A>, _Unit>(_856)(_857);
          return _855;
        };
        return _854;
      };
      return _853;
    };
    return _852;
  };
  return _851;
};

template <class A>
std::function<std::function<std::function<_IO<_List<A>>(uint64_t)>(_Channel<A>)>(uint64_t)> farmConsumerWrapper = [](auto chid) {
  auto _893 = [chid](auto ch) {
    auto _894 = [chid, ch](auto numLeft) {
      auto _895 = [numLeft, chid, ch]() {
        auto _896 = numLeft;
        if (!_896) {
          auto _898 = _List<A>::_Nil();
          auto _897 = returnIO<_List<A>>(_898);
          return _897;
        } else {
          auto n = _896 - 1;
          auto _904 = chid;
          auto _905 = ch;
          auto _900 = receive<A>(_904)(_905);
          auto _901 = [numLeft, chid, ch, n](auto mx) {
            auto _907 = [numLeft, chid, ch, mx, n]() {
              auto _908 = mx;
              switch (_908.type) {
                case Nothing: {
                  auto _910 = *(std::static_pointer_cast<_Maybe_Nothing<A>>(_908.data));
                  auto _911 = chid;
                  auto _912 = ch;
                  auto _913 = n;
                  auto _909 = farmConsumerWrapper<A>(_911)(_912)(_913);
                  return _909;
                }
                case Just: {
                  auto _916 = *(std::static_pointer_cast<_Maybe_Just<A>>(_908.data));
                  auto x = _916._1;
                  auto _921 = chid;
                  auto _922 = ch;
                  auto _923 = numLeft;
                  auto _917 = farmConsumerWrapper<A>(_921)(_922)(_923);
                  auto _918 = [numLeft, chid, ch, mx, n, x](auto res) {
                    auto _928 = x;
                    auto _929 = res;
                    auto _926 = _List<A>::_Cons(_928, _929);
                    auto _925 = returnIO<_List<A>>(_926);
                    return _925;
                  };
                  auto _915 = bindEq<_List<A>, _List<A>>(_917)(_918);
                  return _915;
                }
              }
            }();
            return _907;
          };
          auto _897 = bindEq<_Maybe<A>, _List<A>>(_900)(_901);
          return _897;
        }
      }();
      return _895;
    };
    return _894;
  };
  return _893;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(std::function<A(A)>)>(
    _Sigma<uint64_t, _Channel<A>>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>
    spawnWorkersFarm = [](auto n) {
      auto _930 = [n](auto pidSet) {
        auto _931 = [pidSet, n](auto nDash) {
          auto _932 = [pidSet, n, nDash](auto pids) {
            auto _933 = [pids, pidSet, n, nDash](auto pidPf) {
              auto _934 = [pids, pidSet, pidPf, n, nDash](auto chs) {
                auto _935 = [pids, pidSet, pidPf, chs, n, nDash](auto consumerCh) {
                  auto _936 = [consumerCh, pids, pidSet, pidPf, chs, n, nDash](auto f) {
                    auto _937 = [consumerCh, pids, pidSet, pidPf, chs, f, n, nDash]() {
                      auto _938 = consumerCh;
                      switch (_938.type) {
                        case Prod: {
                          auto _940 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_938.data));
                          auto consumerChid = _940._1;
                          auto consumerChannel = _940._2;
                          auto _939 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash]() {
                            auto _941 = pids;
                            switch (_941.type) {
                              case NilV: {
                                auto _943 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_941.data));
                                auto _947 = pidSet;
                                auto _948 = _TyEq::_Refl();
                                auto _946 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_947, _948);
                                auto _944 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_946);
                                auto _942 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_944);
                                return _942;
                              }
                              case ConsV: {
                                auto _950 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_941.data));
                                auto x = _950._1;
                                auto xs = _950._2;
                                auto _949 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash, xs]() {
                                  auto _951 = pidPf;
                                  switch (_951.type) {
                                    case UConsV: {
                                      auto _953 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_951.data));
                                      auto y = _953._1;
                                      auto ys = _953._2;
                                      auto pf = _953._3;
                                      auto restPf = _953._4;
                                      auto _952 = [consumerCh, pids, pidSet, pidPf, chs, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf]() {
                                        auto _954 = chs;
                                        switch (_954.type) {
                                          case ConsV: {
                                            auto _956 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_954.data));
                                            auto curCh = _956._1;
                                            auto restChs = _956._2;
                                            auto _955 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf, restChs]() {
                                              auto _957 = curCh;
                                              switch (_957.type) {
                                                case Prod: {
                                                  auto _959 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_957.data));
                                                  auto currChid = _959._1;
                                                  auto currChannel = _959._2;
                                                  auto _964 = y;
                                                  auto _965 = ys;
                                                  auto _966 = pf;
                                                  auto _960 = spawnAndRun(_964)(_965)(
                                                      _966)([consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f]() {
                                                    auto _969 = currChid;
                                                    auto _970 = consumerChid;
                                                    auto _971 = currChannel;
                                                    auto _972 = consumerChannel;
                                                    auto _973 = f;
                                                    auto _967 = workerWrapper<A>(_969)(_970)(_971)(_972)(_973);
                                                  });
                                                  auto _961 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, n, nDash, xs, restPf,
                                                               restChs](auto mres) {
                                                    auto _975 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash, xs,
                                                                 restPf, restChs]() {
                                                      auto _976 = mres;
                                                      switch (_976.type) {
                                                        case Nothing: {
                                                          auto _978 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_976.data));
                                                          auto _979 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Nothing();
                                                          auto _977 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_979);
                                                          return _977;
                                                        }
                                                        case Just: {
                                                          auto _982 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_976.data));
                                                          auto res = _982._1;
                                                          auto _987 = n;
                                                          auto _988 = pidSet;
                                                          auto _996 = nDash;
                                                          auto _989 = pred(_996);
                                                          auto _990 = xs;
                                                          auto _991 = restPf;
                                                          auto _992 = restChs;
                                                          auto _993 = consumerCh;
                                                          auto _994 = f;
                                                          auto _983 = spawnWorkersFarm<A>(_987)(_988)(_989)(_990)(_991)(_992)(_993)(_994);
                                                          auto _984 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash,
                                                                       xs, restPf, restChs](auto mress) {
                                                            auto _997 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n,
                                                                         nDash, xs, restPf, restChs, mress]() {
                                                              auto _998 = mress;
                                                              switch (_998.type) {
                                                                case Nothing: {
                                                                  auto _1000 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<uint64_t>, _TyEq>>>(_998.data));
                                                                  auto _1001 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Nothing();
                                                                  auto _999 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1001);
                                                                  return _999;
                                                                }
                                                                case Just: {
                                                                  auto _1004 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<uint64_t>, _TyEq>>>(_998.data));
                                                                  auto res = _1004._1;
                                                                  auto _1003 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres,
                                                                                n, nDash, xs, restPf, restChs, mress, res]() {
                                                                    auto _1005 = res;
                                                                    switch (_1005.type) {
                                                                      case Prod: {
                                                                        auto _1007 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1005.data));
                                                                        auto newPidSet = _1007._1;
                                                                        auto pfNewPidSetCorrect = _1007._2;
                                                                        auto _1013 = y;
                                                                        auto _1014 = newPidSet;
                                                                        auto _1011 = _Vec<uint64_t>::_ConsV(_1013, _1014);
                                                                        auto _1016 = _TyEq::_Refl();
                                                                        auto _1012 = _1016;
                                                                        auto _1010 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1011, _1012);
                                                                        auto _1008 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_1010);
                                                                        auto _1006 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1008);
                                                                        return _1006;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _1003;
                                                                }
                                                              }
                                                            }();
                                                            return _997;
                                                          };
                                                          auto _981 = bindEq<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>, _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_983)(_984);
                                                          return _981;
                                                        }
                                                      }
                                                    }();
                                                    return _975;
                                                  };
                                                  auto _958 = bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>, _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_960)(_961);
                                                  return _958;
                                                }
                                              }
                                            }();
                                            return _955;
                                          }
                                        }
                                      }();
                                      return _952;
                                    }
                                  }
                                }();
                                return _949;
                              }
                            }
                          }();
                          return _939;
                        }
                      }
                    }();
                    return _937;
                  };
                  return _936;
                };
                return _935;
              };
              return _934;
            };
            return _933;
          };
          return _932;
        };
        return _931;
      };
      return _930;
    };

template <class A>
std::function<std::function<std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>
    createChannelsFarm = [](auto m) {
      auto _1017 = [m](auto chidSet) {
        auto _1018 = [chidSet, m](auto mDash) {
          auto _1019 = [chidSet, m, mDash](auto chids) {
            auto _1020 = [chids, chidSet, m, mDash](auto chidPf) {
              auto _1021 = [chids, chidSet, chidPf, m, mDash]() {
                auto _1022 = chids;
                switch (_1022.type) {
                  case NilV: {
                    auto _1024 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_1022.data));
                    auto _1028 = _Vec<_Sigma<uint64_t, _Channel<A>>>::_NilV();
                    auto _1030 = chidSet;
                    auto _1031 = _TyEq::_Refl();
                    auto _1029 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1030, _1031);
                    auto _1027 = _Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1028, _1029);
                    auto _1025 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Just(_1027);
                    auto _1023 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1025);
                    return _1023;
                  }
                  case ConsV: {
                    auto _1033 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_1022.data));
                    auto x = _1033._1;
                    auto xs = _1033._2;
                    auto _1032 = [chids, chidSet, chidPf, m, mDash, xs]() {
                      auto _1034 = chidPf;
                      switch (_1034.type) {
                        case UConsV: {
                          auto _1036 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_1034.data));
                          auto y = _1036._1;
                          auto ys = _1036._2;
                          auto pf = _1036._3;
                          auto restPf = _1036._4;
                          auto _1041 = y;
                          auto _1042 = ys;
                          auto _1043 = pf;
                          auto _1037 = link<A>(_1041)(_1042)(_1043);
                          auto _1038 = [chids, chidSet, chidPf, y, ys, pf, m, mDash, xs, restPf](auto mres) {
                            auto _1046 = [chids, chidSet, chidPf, y, ys, pf, mres, m, mDash, xs, restPf]() {
                              auto _1047 = mres;
                              switch (_1047.type) {
                                case Nothing: {
                                  auto _1049 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_1047.data));
                                  auto _1050 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                  auto _1048 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1050);
                                  return _1048;
                                }
                                case Just: {
                                  auto _1053 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_1047.data));
                                  auto res = _1053._1;
                                  auto _1052 = [chids, chidSet, chidPf, y, ys, pf, mres, res, m, mDash, xs, restPf]() {
                                    auto _1054 = res;
                                    switch (_1054.type) {
                                      case Prod: {
                                        auto _1056 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_1054.data));
                                        auto resChid = _1056._1;
                                        auto rest1 = _1056._2;
                                        auto _1055 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, m, mDash, xs, restPf]() {
                                          auto _1057 = rest1;
                                          switch (_1057.type) {
                                            case Prod: {
                                              auto _1059 = *(std::static_pointer_cast<_Sigma_Prod<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>(_1057.data));
                                              auto ch = _1059._1;
                                              auto rest2 = _1059._2;
                                              auto _1058 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, m, mDash, xs, restPf, ch]() {
                                                auto _1060 = rest2;
                                                switch (_1060.type) {
                                                  case Prod: {
                                                    auto _1062 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>(_1060.data));
                                                    auto newChidSet = _1062._1;
                                                    auto pfs = _1062._2;
                                                    auto _1061 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch]() {
                                                      auto _1063 = pfs;
                                                      switch (_1063.type) {
                                                        case Prod: {
                                                          auto _1065 = *(std::static_pointer_cast<_Sigma_Prod<_TyEq, _TyEq>>(_1063.data));
                                                          auto chidEqResChidPf = _1065._1;
                                                          auto pfNewChidSetCorrect = _1065._2;
                                                          auto _1070 = m;
                                                          auto _1071 = chidSet;
                                                          auto _1076 = mDash;
                                                          auto _1072 = pred(_1076);
                                                          auto _1073 = xs;
                                                          auto _1074 = restPf;
                                                          auto _1066 = createChannelsFarm<A>(_1070)(_1071)(_1072)(_1073)(_1074);
                                                          auto _1067 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch](auto mress) {
                                                            auto _1077 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ch]() {
                                                              auto _1078 = mress;
                                                              switch (_1078.type) {
                                                                case Nothing: {
                                                                  auto _1080 = *(
                                                                      std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1078.data));
                                                                  auto _1081 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                                                  auto _1079 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1081);
                                                                  return _1079;
                                                                }
                                                                case Just: {
                                                                  auto _1084 =
                                                                      *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1078.data));
                                                                  auto ress = _1084._1;
                                                                  auto _1083 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, ch]() {
                                                                    auto _1085 = ress;
                                                                    switch (_1085.type) {
                                                                      case Prod: {
                                                                        auto _1087 =
                                                                            *(std::static_pointer_cast<_Sigma_Prod<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1085.data));
                                                                        auto chs = _1087._1;
                                                                        auto rest3 = _1087._2;
                                                                        auto _1086 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, rest3, ch,
                                                                                      chs]() {
                                                                          auto _1088 = rest3;
                                                                          switch (_1088.type) {
                                                                            case Prod: {
                                                                              auto _1090 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1088.data));
                                                                              auto returnedChidSet = _1090._1;
                                                                              auto pfReturnedChidSetCorrect = _1090._2;
                                                                              auto _1100 = y;
                                                                              auto _1101 = ch;
                                                                              auto _1099 = _Sigma<uint64_t, _Channel<A>>::_Prod(_1100, _1101);
                                                                              auto _1096 = _1099;
                                                                              auto _1097 = chs;
                                                                              auto _1094 = _Vec<_Sigma<uint64_t, _Channel<A>>>::_ConsV(_1096, _1097);
                                                                              auto _1104 = y;
                                                                              auto _1105 = returnedChidSet;
                                                                              auto _1102 = _Vec<uint64_t>::_ConsV(_1104, _1105);
                                                                              auto _1107 = _TyEq::_Refl();
                                                                              auto _1103 = _1107;
                                                                              auto _1095 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1102, _1103);
                                                                              auto _1093 = _Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1094, _1095);
                                                                              auto _1091 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Just(_1093);
                                                                              auto _1089 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1091);
                                                                              return _1089;
                                                                            }
                                                                          }
                                                                        }();
                                                                        return _1086;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _1083;
                                                                }
                                                              }
                                                            }();
                                                            return _1077;
                                                          };
                                                          auto _1064 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>,
                                                                              _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1066)(_1067);
                                                          return _1064;
                                                        }
                                                      }
                                                    }();
                                                    return _1061;
                                                  }
                                                }
                                              }();
                                              return _1058;
                                            }
                                          }
                                        }();
                                        return _1055;
                                      }
                                    }
                                  }();
                                  return _1052;
                                }
                              }
                            }();
                            return _1046;
                          };
                          auto _1035 = bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>,
                                              _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1037)(_1038);
                          return _1035;
                        }
                      }
                    }();
                    return _1032;
                  }
                }
              }();
              return _1021;
            };
            return _1020;
          };
          return _1019;
        };
        return _1018;
      };
      return _1017;
    };

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_List<A>)>(std::function<A(A)>)>(_TyEq)>(_TyEq)>(
    std::function<_Void(_TyEq)>)>(uint64_t)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(
    uint64_t)>
    createFarm = [](auto n) {
      auto _1108 = [n](auto pidSet) {
        auto _1109 = [n, pidSet](auto nDash) {
          auto _1110 = [n, pidSet, nDash](auto pids) {
            auto _1111 = [pids, n, pidSet, nDash](auto pidPf) {
              auto _1112 = [pids, pidPf, n, pidSet, nDash](auto m) {
                auto _1113 = [m, pids, pidPf, n, pidSet, nDash](auto chidSet) {
                  auto _1114 = [m, chidSet, pids, pidPf, n, pidSet, nDash](auto mDash) {
                    auto _1115 = [m, chidSet, mDash, pids, pidPf, n, pidSet, nDash](auto chids) {
                      auto _1116 = [m, chidSet, mDash, chids, pids, pidPf, n, pidSet, nDash](auto chidPf) {
                        auto _1117 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash](auto numWorkers) {
                          auto _1118 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfNotZ) {
                            auto _1119 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfPidsNCorrect) {
                              auto _1120 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfChidsMCorrect) {
                                auto _1121 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto f) {
                                  auto _1122 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, f, numWorkers](auto input) {
                                    auto _1128 = m;
                                    auto _1129 = chidSet;
                                    auto _1130 = mDash;
                                    auto _1131 = chids;
                                    auto _1132 = chidPf;
                                    auto _1124 = createChannelsFarm<A>(_1128)(_1129)(_1130)(_1131)(_1132);
                                    auto _1125 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, input, n, pidSet, nDash, f, numWorkers](auto mres1) {
                                      auto _1134 = [m, chidSet, mDash, chids, chidPf, mres1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                        auto _1135 = mres1;
                                        switch (_1135.type) {
                                          case Nothing: {
                                            auto _1137 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1135.data));
                                            auto _1138 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                            auto _1136 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1138);
                                            return _1136;
                                          }
                                          case Just: {
                                            auto _1141 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1135.data));
                                            auto res1 = _1141._1;
                                            auto _1140 = [m, chidSet, mDash, chids, chidPf, mres1, res1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                              auto _1142 = res1;
                                              switch (_1142.type) {
                                                case Prod: {
                                                  auto _1144 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1142.data));
                                                  auto chs = _1144._1;
                                                  auto chidPfToReturn = _1144._2;
                                                  auto _1143 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, pids, pidPf, input, n, pidSet, nDash, f, numWorkers, chidPfToReturn]() {
                                                    auto _1145 = chs;
                                                    switch (_1145.type) {
                                                      case NilV: {
                                                        auto _1147 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_1145.data));
                                                        auto _1148 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                        auto _1146 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1148);
                                                        return _1146;
                                                      }
                                                      case ConsV: {
                                                        auto _1151 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_1145.data));
                                                        auto consumerCh = _1151._1;
                                                        auto otherChs = _1151._2;
                                                        auto _1150 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, f, numWorkers,
                                                                      chidPfToReturn]() {
                                                          auto _1152 = consumerCh;
                                                          switch (_1152.type) {
                                                            case Prod: {
                                                              auto _1154 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_1152.data));
                                                              auto consumerChid = _1154._1;
                                                              auto consumerChannel = _1154._2;
                                                              auto _1153 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, f,
                                                                            consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                auto _1155 = pids;
                                                                switch (_1155.type) {
                                                                  case NilV: {
                                                                    auto _1157 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_1155.data));
                                                                    auto _1158 =
                                                                        _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                                    auto _1156 =
                                                                        returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                            _1158);
                                                                    return _1156;
                                                                  }
                                                                  case ConsV: {
                                                                    auto _1161 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_1155.data));
                                                                    auto x = _1161._1;
                                                                    auto xs = _1161._2;
                                                                    auto _1160 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, xs, f,
                                                                                  consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                      auto _1162 = pidPf;
                                                                      switch (_1162.type) {
                                                                        case UConsV: {
                                                                          auto _1164 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_1162.data));
                                                                          auto producerPid = _1164._1;
                                                                          auto restPids = _1164._2;
                                                                          auto producerPidPf = _1164._3;
                                                                          auto restPfs = _1164._4;
                                                                          auto _1169 = producerPid;
                                                                          auto _1170 = restPids;
                                                                          auto _1171 = producerPidPf;
                                                                          auto _1165 = spawnAndRun(_1169)(_1170)(_1171)([m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf,
                                                                                                                         producerPid, restPids, producerPidPf, otherChs, input]() {
                                                                            auto _1174 = otherChs;
                                                                            auto _1175 = otherChs;
                                                                            auto _1176 = input;
                                                                            auto _1172 = farmProducerWrapper<A>(_1174)(_1175)(_1176);
                                                                          });
                                                                          auto _1166 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                        producerPidPf, otherChs, input, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel, numWorkers,
                                                                                        chidPfToReturn](auto mres2) {
                                                                            auto _1180 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                          producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel,
                                                                                          numWorkers, chidPfToReturn]() {
                                                                              auto _1181 = mres2;
                                                                              switch (_1181.type) {
                                                                                case Nothing: {
                                                                                  auto _1183 =
                                                                                      *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(
                                                                                          _1181.data));
                                                                                  auto _1184 =
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::
                                                                                          _Nothing();
                                                                                  auto _1182 = returnIO<
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                      _1184);
                                                                                  return _1182;
                                                                                }
                                                                                case Just: {
                                                                                  auto _1187 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(
                                                                                      _1181.data));
                                                                                  auto res2 = _1187._1;
                                                                                  auto _1192 = n;
                                                                                  auto _1193 = pidSet;
                                                                                  auto _1201 = nDash;
                                                                                  auto _1194 = pred(_1201);
                                                                                  auto _1195 = xs;
                                                                                  auto _1196 = restPfs;
                                                                                  auto _1202 = otherChs;
                                                                                  auto _1197 = _1202;
                                                                                  auto _1198 = consumerCh;
                                                                                  auto _1199 = f;
                                                                                  auto _1188 = spawnWorkersFarm<A>(_1192)(_1193)(_1194)(_1195)(_1196)(_1197)(_1198)(_1199);
                                                                                  auto _1189 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel,
                                                                                                numWorkers, chidPfToReturn](auto mres3) {
                                                                                    auto _1203 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                  producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3, consumerChid,
                                                                                                  consumerChannel, numWorkers, chidPfToReturn]() {
                                                                                      auto _1204 = mres3;
                                                                                      switch (_1204.type) {
                                                                                        case Nothing: {
                                                                                          auto _1206 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1204.data));
                                                                                          auto _1207 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                       _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                                                          auto _1205 = returnIO<_Maybe<_Sigma<
                                                                                              _List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                              _1207);
                                                                                          return _1205;
                                                                                        }
                                                                                        case Just: {
                                                                                          auto _1210 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1204.data));
                                                                                          auto workerPidPfs = _1210._1;
                                                                                          auto _1209 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                        restPids, producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3,
                                                                                                        workerPidPfs, consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                                            auto _1211 = workerPidPfs;
                                                                                            switch (_1211.type) {
                                                                                              case Prod: {
                                                                                                auto _1213 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1211.data));
                                                                                                auto workersPidSet = _1213._1;
                                                                                                auto workerPidSetPf = _1213._2;
                                                                                                auto _1218 = consumerChid;
                                                                                                auto _1219 = consumerChannel;
                                                                                                auto _1220 = numWorkers;
                                                                                                auto _1214 = farmConsumerWrapper<A>(_1218)(_1219)(_1220);
                                                                                                auto _1215 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                              restPids, producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3,
                                                                                                              workerPidPfs, consumerChid, consumerChannel, numWorkers, workersPidSet, workerPidSetPf,
                                                                                                              chidPfToReturn](auto resultantList) {
                                                                                                  auto _1226 = resultantList;
                                                                                                  auto _1230 = numWorkers;
                                                                                                  auto _1231 = f;
                                                                                                  auto _1228 = _Farm<A>::_MkFarm(_1230, _1231);
                                                                                                  auto _1236 = producerPid;
                                                                                                  auto _1237 = workersPidSet;
                                                                                                  auto _1234 = _Vec<uint64_t>::_ConsV(_1236, _1237);
                                                                                                  auto _1239 = _TyEq::_Refl();
                                                                                                  auto _1240 = workerPidSetPf;
                                                                                                  auto _1235 = consVInjLem(_1239)(_1240);
                                                                                                  auto _1232 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1234, _1235);
                                                                                                  auto _1233 = chidPfToReturn;
                                                                                                  auto _1229 =
                                                                                                      _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1232, _1233);
                                                                                                  auto _1227 =
                                                                                                      _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Prod(
                                                                                                          _1228, _1229);
                                                                                                  auto _1225 =
                                                                                                      _Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                               _Sigma<_Vec<uint64_t>, _TyEq>>>>::_Prod(_1226, _1227);
                                                                                                  auto _1223 =
                                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                      _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Just(_1225);
                                                                                                  auto _1222 =
                                                                                                      returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                               _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                                          _1223);
                                                                                                  return _1222;
                                                                                                };
                                                                                                auto _1212 =
                                                                                                    bindEq<_List<A>, _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                                     _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                                        _1214)(_1215);
                                                                                                return _1212;
                                                                                              }
                                                                                            }
                                                                                          }();
                                                                                          return _1209;
                                                                                        }
                                                                                      }
                                                                                    }();
                                                                                    return _1203;
                                                                                  };
                                                                                  auto _1186 = bindEq<
                                                                                      _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>,
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                      _1188)(_1189);
                                                                                  return _1186;
                                                                                }
                                                                              }
                                                                            }();
                                                                            return _1180;
                                                                          };
                                                                          auto _1163 =
                                                                              bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>,
                                                                                     _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                  _1165)(_1166);
                                                                          return _1163;
                                                                        }
                                                                      }
                                                                    }();
                                                                    return _1160;
                                                                  }
                                                                }
                                                              }();
                                                              return _1153;
                                                            }
                                                          }
                                                        }();
                                                        return _1150;
                                                      }
                                                    }
                                                  }();
                                                  return _1143;
                                                }
                                              }
                                            }();
                                            return _1140;
                                          }
                                        }
                                      }();
                                      return _1134;
                                    };
                                    auto _1123 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>,
                                                        _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1124)(_1125);
                                    return _1123;
                                  };
                                  return _1122;
                                };
                                return _1121;
                              };
                              return _1120;
                            };
                            return _1119;
                          };
                          return _1118;
                        };
                        return _1117;
                      };
                      return _1116;
                    };
                    return _1115;
                  };
                  return _1114;
                };
                return _1113;
              };
              return _1112;
            };
            return _1111;
          };
          return _1110;
        };
        return _1109;
      };
      return _1108;
    };

std::function<uint64_t(uint64_t)> id = [](auto a) {
  auto _1247 = a;
  auto _1246 = _1247 + 1;
  ;
  return _1246;
};

_IO<_Unit> main3 = []() {
  auto _1254 = natToString;
  auto _1258 = (uint64_t)42;
  auto _1260 = (uint64_t)42;
  auto _1262 = (uint64_t)42;
  auto _1264 = (uint64_t)42;
  auto _1266 = (uint64_t)42;
  auto _1268 = (uint64_t)42;
  auto _1270 = (uint64_t)42;
  auto _1272 = (uint64_t)42;
  auto _1274 = (uint64_t)42;
  auto _1276 = (uint64_t)42;
  auto _1277 = _List<uint64_t>::_Nil();
  auto _1275 = _List<uint64_t>::_Cons(_1276, _1277);
  auto _1273 = _List<uint64_t>::_Cons(_1274, _1275);
  auto _1271 = _List<uint64_t>::_Cons(_1272, _1273);
  auto _1269 = _List<uint64_t>::_Cons(_1270, _1271);
  auto _1267 = _List<uint64_t>::_Cons(_1268, _1269);
  auto _1265 = _List<uint64_t>::_Cons(_1266, _1267);
  auto _1263 = _List<uint64_t>::_Cons(_1264, _1265);
  auto _1261 = _List<uint64_t>::_Cons(_1262, _1263);
  auto _1259 = _List<uint64_t>::_Cons(_1260, _1261);
  auto _1255 = _List<uint64_t>::_Cons(_1258, _1259);
  auto _1253 = map<uint64_t, _List<char>>(_1254)(_1255);
  auto _1249 = printList(_1253);
  auto _1283 = 'O';
  auto _1285 = 'U';
  auto _1287 = 'T';
  auto _1289 = 'P';
  auto _1291 = 'U';
  auto _1293 = 'T';
  auto _1295 = '-';
  auto _1297 = 'T';
  auto _1299 = 'I';
  auto _1301 = 'M';
  auto _1303 = 'E';
  auto _1304 = _List<char>::_Nil();
  auto _1302 = _List<char>::_Cons(_1303, _1304);
  auto _1300 = _List<char>::_Cons(_1301, _1302);
  auto _1298 = _List<char>::_Cons(_1299, _1300);
  auto _1296 = _List<char>::_Cons(_1297, _1298);
  auto _1294 = _List<char>::_Cons(_1295, _1296);
  auto _1292 = _List<char>::_Cons(_1293, _1294);
  auto _1290 = _List<char>::_Cons(_1291, _1292);
  auto _1288 = _List<char>::_Cons(_1289, _1290);
  auto _1286 = _List<char>::_Cons(_1287, _1288);
  auto _1284 = _List<char>::_Cons(_1285, _1286);
  auto _1282 = _List<char>::_Cons(_1283, _1284);
  auto _1278 = print(_1282);
  auto _1279 = []() {
    auto _1313 = (uint64_t)3;
    auto _1316 = (uint64_t)2;
    auto _1319 = (uint64_t)1;
    auto _1320 = _Vec<uint64_t>::_NilV();
    auto _1317 = _Vec<uint64_t>::_ConsV(_1319, _1320);
    auto _1314 = _Vec<uint64_t>::_ConsV(_1316, _1317);
    auto _1308 = _Vec<uint64_t>::_ConsV(_1313, _1314);
    auto _1309 = _Vec<uint64_t>::_NilV();
    auto _1306 = append<uint64_t>(_1308)(_1309);
    auto _1305 = decUniqueVec(_1306);
    switch (_1305.type) {
      case Yes: {
        auto _1323 = *(std::static_pointer_cast<_Dec_Yes<_UniqueVec<uint64_t>>>(_1305.data));
        auto pf1 = _1323._1;
        auto _1328 = (uint64_t)0;
        auto _1329 = _Vec<uint64_t>::_NilV();
        auto _1330 = (uint64_t)3;
        auto _1345 = (uint64_t)3;
        auto _1348 = (uint64_t)2;
        auto _1351 = (uint64_t)1;
        auto _1352 = _Vec<uint64_t>::_NilV();
        auto _1349 = _Vec<uint64_t>::_ConsV(_1351, _1352);
        auto _1346 = _Vec<uint64_t>::_ConsV(_1348, _1349);
        auto _1331 = _Vec<uint64_t>::_ConsV(_1345, _1346);
        auto _1332 = pf1;
        auto _1333 = (uint64_t)0;
        auto _1334 = _Vec<uint64_t>::_NilV();
        auto _1335 = (uint64_t)3;
        auto _1354 = (uint64_t)3;
        auto _1357 = (uint64_t)2;
        auto _1360 = (uint64_t)1;
        auto _1361 = _Vec<uint64_t>::_NilV();
        auto _1358 = _Vec<uint64_t>::_ConsV(_1360, _1361);
        auto _1355 = _Vec<uint64_t>::_ConsV(_1357, _1358);
        auto _1336 = _Vec<uint64_t>::_ConsV(_1354, _1355);
        auto _1337 = pf1;
        auto _1338 = (uint64_t)2;
        auto _1367 = (uint64_t)1;
        auto _1363 = ZnotS(_1367);
        auto _1339 = negEqSym<uint64_t>(_1363);
        auto _1340 = _TyEq::_Refl();
        auto _1341 = _TyEq::_Refl();
        auto _1342 = fib;
        auto _1368 = (uint64_t)42;
        auto _1370 = (uint64_t)42;
        auto _1372 = (uint64_t)42;
        auto _1374 = (uint64_t)42;
        auto _1376 = (uint64_t)42;
        auto _1378 = (uint64_t)42;
        auto _1380 = (uint64_t)42;
        auto _1382 = (uint64_t)42;
        auto _1384 = (uint64_t)42;
        auto _1386 = (uint64_t)42;
        auto _1387 = _List<uint64_t>::_Nil();
        auto _1385 = _List<uint64_t>::_Cons(_1386, _1387);
        auto _1383 = _List<uint64_t>::_Cons(_1384, _1385);
        auto _1381 = _List<uint64_t>::_Cons(_1382, _1383);
        auto _1379 = _List<uint64_t>::_Cons(_1380, _1381);
        auto _1377 = _List<uint64_t>::_Cons(_1378, _1379);
        auto _1375 = _List<uint64_t>::_Cons(_1376, _1377);
        auto _1373 = _List<uint64_t>::_Cons(_1374, _1375);
        auto _1371 = _List<uint64_t>::_Cons(_1372, _1373);
        auto _1369 = _List<uint64_t>::_Cons(_1370, _1371);
        auto _1343 = _List<uint64_t>::_Cons(_1368, _1369);
        auto _1324 = createFarm<uint64_t>(_1328)(_1329)(_1330)(_1331)(_1332)(_1333)(_1334)(_1335)(_1336)(_1337)(_1338)(_1339)(_1340)(_1341)(_1342)(_1343);
        auto _1325 = [pf1](auto mres) {
          auto _1388 = [pf1, mres]() {
            auto _1389 = mres;
            switch (_1389.type) {
              case Nothing: {
                auto _1391 =
                    *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1389.data));
                auto _1393 = 'R';
                auto _1395 = 'I';
                auto _1397 = 'P';
                auto _1398 = _List<char>::_Nil();
                auto _1396 = _List<char>::_Cons(_1397, _1398);
                auto _1394 = _List<char>::_Cons(_1395, _1396);
                auto _1392 = _List<char>::_Cons(_1393, _1394);
                auto _1390 = print(_1392);
                return _1390;
              }
              case Just: {
                auto _1400 =
                    *(std::static_pointer_cast<_Maybe_Just<_Sigma<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1389.data));
                auto r = _1400._1;
                auto _1399 = [pf1, mres, r]() {
                  auto _1401 = r;
                  switch (_1401.type) {
                    case Prod: {
                      auto _1403 = *(std::static_pointer_cast<_Sigma_Prod<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>(_1401.data));
                      auto l = _1403._1;
                      auto rest = _1403._2;
                      auto _1405 = natToString;
                      auto _1406 = l;
                      auto _1404 = map<uint64_t, _List<char>>(_1405)(_1406);
                      auto _1402 = printList(_1404);
                      return _1402;
                    }
                  }
                }();
                return _1399;
              }
            }
          }();
          return _1388;
        };
        auto _1322 = bindEq<_Maybe<_Sigma<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>, _Unit>(_1324)(_1325);
        return _1322;
      }
    }
  }();
  auto _1250 = bind<_Unit, _Unit>(_1278)(_1279);
  auto _1248 = bind<_Unit, _Unit>(_1249)(_1250);
  return _1248;
}();
//////////////////////////////////////
// GLOBAL STATE AND HELPER FUNCTION //
//////////////////////////////////////

// Helper functions for pids
std::thread* getThread(uint64_t pid) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(pidMutex);

  // return the information
  return pidsMap[pid];
}

void addThread(uint64_t pid, std::thread* t) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(pidMutex);

  // Adding the thread, will never overwrite
  pidsMap[pid] = t;
}

// Helper functions for channels
void* getChannel(uint64_t chid) {
  // Aquiring the lock
  std::lock_guard<std::mutex> lock(channelMutex);

  //  returning the channel
  return channelsMap[chid];
}

template <typename A>
void addChannel(uint64_t chid, LockingCQueue<_Maybe<A>>* queue) {
  // Aquireing the lock
  std::lock_guard<std::mutex> lock(channelMutex);

  // adding the channel
  channelsMap[chid] = queue;
}

int main() {}