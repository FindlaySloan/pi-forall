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

std::function<_Void(_Elem<uint64_t>)> xNotElemOfNil = [](auto p) {
  auto _93 = [p]() {
    auto _94 = p;
    return _Void();
  }();
  return _93;
};

std::function<std::function<_Dec<_Elem<uint64_t>>(_List<uint64_t>)>(uint64_t)> isElem = [](auto x) {
  auto _95 = [x](auto xs) {
    auto _96 = [xs, x]() {
      auto _97 = xs;
      switch (_97.type) {
        case Nil: {
          auto _99 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_97.data));
          auto _100 = xNotElemOfNil;
          auto _98 = _Dec<_Elem<uint64_t>>::_No(_100);
          return _98;
        }
        case Cons: {
          auto _103 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_97.data));
          auto y = _103._1;
          auto ys = _103._2;
          auto _102 = [xs, x, y, ys]() {
            auto _105 = x;
            auto _106 = y;
            auto _104 = decEqNat(_105)(_106);
            switch (_104.type) {
              case Yes: {
                auto _108 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_104.data));
                auto p = _108._1;
                auto _110 = y;
                auto _111 = ys;
                auto _109 = _Elem<uint64_t>::_Here(_110, _111);
                auto _107 = _Dec<_Elem<uint64_t>>::_Yes(_109);
                return _107;
              }
              case No: {
                auto _113 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_104.data));
                auto xneqy = _113._1;
                auto _112 = [xs, x, y, ys, xneqy]() {
                  auto _115 = x;
                  auto _116 = ys;
                  auto _114 = isElem(_115)(_116);
                  switch (_114.type) {
                    case Yes: {
                      auto _118 = *(std::static_pointer_cast<_Dec_Yes<_Elem<uint64_t>>>(_114.data));
                      auto xinys = _118._1;
                      auto _120 = y;
                      auto _121 = x;
                      auto _122 = ys;
                      auto _123 = xinys;
                      auto _119 = _Elem<uint64_t>::_There(_120, _121, _122, _123);
                      auto _117 = _Dec<_Elem<uint64_t>>::_Yes(_119);
                      return _117;
                    }
                    case No: {
                      auto _125 = *(std::static_pointer_cast<_Dec_No<_Elem<uint64_t>>>(_114.data));
                      auto xninys = _125._1;
                      auto _127 = xneqy;
                      auto _128 = xninys;
                      auto _126 = neitherHereNorThere(_127)(_128);
                      auto _124 = _Dec<_Elem<uint64_t>>::_No(_126);
                      return _124;
                    }
                  }
                }();
                return _112;
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
  auto _133 = [n](auto m) { return n + m; };
  return _133;
};
;

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> mult = [](auto n) {
  auto _133 = [n](auto m) { return n * m; };
  return _133;
};
;

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> minus = [](auto n) {
  auto _133 = [n](auto m) { return n - m; };
  return _133;
};
;

std::function<uint64_t(uint64_t)> fib = [](auto x) {
  auto _132 = [x]() {
    auto _133 = x;
    if (!_133) {
      auto _134 = (uint64_t)1;
      return _134;
    } else {
      auto y = _133 - 1;
      auto _134 = [x, y]() {
        auto _135 = y;
        if (!_135) {
          auto _136 = (uint64_t)1;
          return _136;
        } else {
          auto z = _135 - 1;
          auto _139 = y;
          auto _137 = fib(_139);
          auto _140 = z;
          auto _138 = fib(_140);
          auto _136 = plus(_137)(_138);
          return _136;
        }
      }();
      return _134;
    }
  }();
  return _132;
};

std::function<uint64_t(uint64_t)> fact = [](auto n) {
  auto _141 = [n]() {
    auto _142 = n;
    if (!_142) {
      auto _143 = (uint64_t)1;
      return _143;
    } else {
      auto m = _142 - 1;
      auto _144 = n;
      auto _146 = m;
      auto _145 = fact(_146);
      auto _143 = mult(_144)(_145);
      return _143;
    }
  }();
  return _141;
};

template <class A>
std::function<std::function<_Vec<A>(_Vec<A>)>(_Vec<A>)> append = [](auto v1) {
  auto _147 = [v1](auto ys) {
    auto _148 = [v1, ys]() {
      auto _149 = v1;
      switch (_149.type) {
        case ConsV: {
          auto _151 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_149.data));
          auto x = _151._1;
          auto xs = _151._2;
          auto _152 = x;
          auto _155 = xs;
          auto _156 = ys;
          auto _153 = append<A>(_155)(_156);
          auto _150 = _Vec<A>::_ConsV(_152, _153);
          return _150;
        }
        case NilV: {
          auto _161 = *(std::static_pointer_cast<_Vec_NilV<A>>(_149.data));
          auto _160 = ys;
          return _160;
        }
      }
    }();
    return _148;
  };
  return _147;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> trans = [](auto pf1) {
  auto _162 = [pf1](auto pf2) {
    auto _164 = pf1;
    auto _163 = _164;
    return _163;
  };
  return _162;
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
  auto _165 = [p]() {
    auto _166 = p;
    return _Void();
  }();
  return _165;
};

std::function<std::function<std::function<_Void(_ElemVec<uint64_t>)>(std::function<_Void(_ElemVec<uint64_t>)>)>(std::function<_Void(_TyEq)>)> neitherHereNorThereVec = [](auto xneqy) {
  auto _167 = [xneqy](auto xninxs) {
    auto _168 = [xneqy, xninxs](auto p) {
      auto _169 = [p, xneqy, xninxs]() {
        auto _170 = p;
        switch (_170.type) {
          case HereV: {
            auto _172 = *(std::static_pointer_cast<_ElemVec_HereV<uint64_t>>(_170.data));
            auto as = _172._1;
            auto _173 = _TyEq::_Refl();
            auto _171 = xneqy(_173);
            return _171;
          }
          case ThereV: {
            auto _175 = *(std::static_pointer_cast<_ElemVec_ThereV<uint64_t>>(_170.data));
            auto as = _175._1;
            auto b = _175._2;
            auto prf = _175._3;
            auto _176 = prf;
            auto _174 = xninxs(_176);
            return _174;
          }
        }
      }();
      return _169;
    };
    return _168;
  };
  return _167;
};

std::function<std::function<_Dec<_ElemVec<uint64_t>>(_Vec<uint64_t>)>(uint64_t)> isElemVec = [](auto x) {
  auto _177 = [x](auto xs) {
    auto _178 = [xs, x]() {
      auto _179 = xs;
      switch (_179.type) {
        case NilV: {
          auto _181 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_179.data));
          auto _182 = xNotInNilV<uint64_t>;
          auto _180 = _Dec<_ElemVec<uint64_t>>::_No(_182);
          return _180;
        }
        case ConsV: {
          auto _187 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_179.data));
          auto y = _187._1;
          auto ys = _187._2;
          auto _186 = [xs, x, y, ys]() {
            auto _189 = x;
            auto _190 = y;
            auto _188 = decEqNat(_189)(_190);
            switch (_188.type) {
              case Yes: {
                auto _192 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_188.data));
                auto pf = _192._1;
                auto _195 = ys;
                auto _194 = _ElemVec<uint64_t>::_HereV(_195);
                auto _193 = _194;
                auto _191 = _Dec<_ElemVec<uint64_t>>::_Yes(_193);
                return _191;
              }
              case No: {
                auto _198 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_188.data));
                auto xneqyPf = _198._1;
                auto _197 = [xs, x, y, ys, xneqyPf]() {
                  auto _200 = x;
                  auto _201 = ys;
                  auto _199 = isElemVec(_200)(_201);
                  switch (_199.type) {
                    case Yes: {
                      auto _204 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_199.data));
                      auto pf = _204._1;
                      auto _206 = ys;
                      auto _207 = x;
                      auto _208 = pf;
                      auto _205 = _ElemVec<uint64_t>::_ThereV(_206, _207, _208);
                      auto _203 = _Dec<_ElemVec<uint64_t>>::_Yes(_205);
                      return _203;
                    }
                    case No: {
                      auto _211 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_199.data));
                      auto xninysPf = _211._1;
                      auto _213 = xneqyPf;
                      auto _214 = xninysPf;
                      auto _212 = neitherHereNorThereVec(_213)(_214);
                      auto _210 = _Dec<_ElemVec<uint64_t>>::_No(_212);
                      return _210;
                    }
                  }
                }();
                return _197;
              }
            }
          }();
          return _186;
        }
      }
    }();
    return _178;
  };
  return _177;
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
  auto _219 = [p]() {
    auto _220 = p;
    return _Void();
  }();
  return _219;
};

template <class A>
std::function<std::function<_Disjoint<A>(_TyEq)>(_List<A>)> lemma_y_empty_disjoint = [](auto a) {
  auto _221 = [a](auto pf) {
    auto _222 = [a, pf]() {
      auto _223 = a;
      switch (_223.type) {
        case Nil: {
          auto _225 = *(std::static_pointer_cast<_List_Nil<A>>(_223.data));
          auto _224 = _Disjoint<A>::_DNil();
          return _224;
        }
        case Cons: {
          auto _227 = *(std::static_pointer_cast<_List_Cons<A>>(_223.data));
          auto x = _227._1;
          auto xs = _227._2;
          auto _228 = x;
          auto _229 = xs;
          auto _232 = xNotInNil<A>;
          auto _230 = _232;
          auto _235 = xs;
          auto _236 = pf;
          auto _231 = lemma_y_empty_disjoint<A>(_235)(_236);
          auto _226 = _Disjoint<A>::_DCons(_228, _229, _230, _231);
          return _226;
        }
      }
    }();
    return _222;
  };
  return _221;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(_Elem<A>)> lemma_x_in_b = [](auto xInB) {
  auto _239 = [xInB](auto pf) {
    auto _240 = [pf, xInB]() {
      auto _241 = pf;
      switch (_241.type) {
        case DCons: {
          auto _243 = *(std::static_pointer_cast<_Disjoint_DCons<A>>(_241.data));
          auto i = _243._1;
          auto is = _243._2;
          auto pfFori = _243._3;
          auto others = _243._4;
          auto _244 = xInB;
          auto _242 = pfFori(_244);
          return _242;
        }
      }
    }();
    return _240;
  };
  return _239;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(std::function<_Void(_Disjoint<A>)>)> lemma_xs_in_b = [](auto pf) {
  auto _245 = [pf](auto p) {
    auto _246 = [p, pf]() {
      auto _247 = p;
      switch (_247.type) {
        case DCons: {
          auto _249 = *(std::static_pointer_cast<_Disjoint_DCons<A>>(_247.data));
          auto i = _249._1;
          auto is = _249._2;
          auto pfFori = _249._3;
          auto others = _249._4;
          auto _250 = others;
          auto _248 = pf(_250);
          return _248;
        }
      }
    }();
    return _246;
  };
  return _245;
};

std::function<std::function<_Dec<_Disjoint<uint64_t>>(_List<uint64_t>)>(_List<uint64_t>)> decDisjointLists = [](auto a) {
  auto _251 = [a](auto b) {
    auto _252 = [a, b]() {
      auto _253 = a;
      switch (_253.type) {
        case Nil: {
          auto _255 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_253.data));
          auto _256 = _Disjoint<uint64_t>::_DNil();
          auto _254 = _Dec<_Disjoint<uint64_t>>::_Yes(_256);
          return _254;
        }
        case Cons: {
          auto _258 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_253.data));
          auto x = _258._1;
          auto xs = _258._2;
          auto _257 = [a, b, xs, x]() {
            auto _259 = b;
            switch (_259.type) {
              case Nil: {
                auto _261 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_259.data));
                auto _263 = a;
                auto _264 = _TyEq::_Refl();
                auto _262 = lemma_y_empty_disjoint<uint64_t>(_263)(_264);
                auto _260 = _Dec<_Disjoint<uint64_t>>::_Yes(_262);
                return _260;
              }
              case Cons: {
                auto _268 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_259.data));
                auto y = _268._1;
                auto ys = _268._2;
                auto _267 = [a, b, xs, x]() {
                  auto _270 = xs;
                  auto _271 = b;
                  auto _269 = decDisjointLists(_270)(_271);
                  switch (_269.type) {
                    case Yes: {
                      auto _273 = *(std::static_pointer_cast<_Dec_Yes<_Disjoint<uint64_t>>>(_269.data));
                      auto pf = _273._1;
                      auto _272 = [a, b, xs, x, pf]() {
                        auto _275 = x;
                        auto _276 = b;
                        auto _274 = isElem(_275)(_276);
                        switch (_274.type) {
                          case Yes: {
                            auto _278 = *(std::static_pointer_cast<_Dec_Yes<_Elem<uint64_t>>>(_274.data));
                            auto elemPf = _278._1;
                            auto _280 = elemPf;
                            auto _279 = lemma_x_in_b<uint64_t>(_280);
                            auto _277 = _Dec<_Disjoint<uint64_t>>::_No(_279);
                            return _277;
                          }
                          case No: {
                            auto _287 = *(std::static_pointer_cast<_Dec_No<_Elem<uint64_t>>>(_274.data));
                            auto p = _287._1;
                            auto _289 = x;
                            auto _290 = xs;
                            auto _291 = p;
                            auto _292 = pf;
                            auto _288 = _Disjoint<uint64_t>::_DCons(_289, _290, _291, _292);
                            auto _286 = _Dec<_Disjoint<uint64_t>>::_Yes(_288);
                            return _286;
                          }
                        }
                      }();
                      return _272;
                    }
                    case No: {
                      auto _294 = *(std::static_pointer_cast<_Dec_No<_Disjoint<uint64_t>>>(_269.data));
                      auto p = _294._1;
                      auto _296 = p;
                      auto _295 = lemma_xs_in_b<uint64_t>(_296);
                      auto _293 = _Dec<_Disjoint<uint64_t>>::_No(_295);
                      return _293;
                    }
                  }
                }();
                return _267;
              }
            }
          }();
          return _257;
        }
      }
    }();
    return _252;
  };
  return _251;
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
  auto _301 = [a](auto pf) {
    auto _302 = [a, pf]() {
      auto _303 = a;
      switch (_303.type) {
        case NilV: {
          auto _305 = *(std::static_pointer_cast<_Vec_NilV<A>>(_303.data));
          auto _304 = _DisjointVec<A>::_DNilV();
          return _304;
        }
        case ConsV: {
          auto _307 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_303.data));
          auto x = _307._1;
          auto xs = _307._2;
          auto _308 = x;
          auto _309 = xs;
          auto _313 = xNotInNilV<A>;
          auto _310 = _313;
          auto _317 = xs;
          auto _318 = pf;
          auto _311 = lemma_y_empty_disjoint_vec<A>(_317)(_318);
          auto _306 = _DisjointVec<A>::_DConsV(_308, _309, _310, _311);
          return _306;
        }
      }
    }();
    return _302;
  };
  return _301;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(_ElemVec<A>)> lemma_x_in_b_vec = [](auto xInB) {
  auto _322 = [xInB](auto pf) {
    auto _323 = [pf, xInB]() {
      auto _324 = pf;
      switch (_324.type) {
        case DConsV: {
          auto _326 = *(std::static_pointer_cast<_DisjointVec_DConsV<A>>(_324.data));
          auto y = _326._1;
          auto ys = _326._2;
          auto pfFory = _326._3;
          auto others = _326._4;
          auto _327 = xInB;
          auto _325 = pfFory(_327);
          return _325;
        }
      }
    }();
    return _323;
  };
  return _322;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(std::function<_Void(_DisjointVec<A>)>)> lemma_xs_in_b_vec = [](auto pf) {
  auto _328 = [pf](auto p) {
    auto _329 = [p, pf]() {
      auto _330 = p;
      switch (_330.type) {
        case DConsV: {
          auto _332 = *(std::static_pointer_cast<_DisjointVec_DConsV<A>>(_330.data));
          auto i = _332._1;
          auto is = _332._2;
          auto pfFori = _332._3;
          auto others = _332._4;
          auto _333 = others;
          auto _331 = pf(_333);
          return _331;
        }
      }
    }();
    return _329;
  };
  return _328;
};

std::function<std::function<_Dec<_DisjointVec<uint64_t>>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decDisjointVecs = [](auto a) {
  auto _334 = [a](auto b) {
    auto _335 = [a, b]() {
      auto _336 = a;
      switch (_336.type) {
        case NilV: {
          auto _338 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_336.data));
          auto _339 = _DisjointVec<uint64_t>::_DNilV();
          auto _337 = _Dec<_DisjointVec<uint64_t>>::_Yes(_339);
          return _337;
        }
        case ConsV: {
          auto _341 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_336.data));
          auto x = _341._1;
          auto xs = _341._2;
          auto _340 = [a, b, xs, x]() {
            auto _342 = b;
            switch (_342.type) {
              case NilV: {
                auto _344 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_342.data));
                auto _346 = a;
                auto _347 = _TyEq::_Refl();
                auto _345 = lemma_y_empty_disjoint_vec<uint64_t>(_346)(_347);
                auto _343 = _Dec<_DisjointVec<uint64_t>>::_Yes(_345);
                return _343;
              }
              case ConsV: {
                auto _352 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_342.data));
                auto y = _352._1;
                auto ys = _352._2;
                auto _351 = [a, b, xs, x]() {
                  auto _354 = xs;
                  auto _355 = b;
                  auto _353 = decDisjointVecs(_354)(_355);
                  switch (_353.type) {
                    case Yes: {
                      auto _359 = *(std::static_pointer_cast<_Dec_Yes<_DisjointVec<uint64_t>>>(_353.data));
                      auto pf = _359._1;
                      auto _358 = [a, b, xs, x, pf]() {
                        auto _361 = x;
                        auto _362 = b;
                        auto _360 = isElemVec(_361)(_362);
                        switch (_360.type) {
                          case Yes: {
                            auto _365 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_360.data));
                            auto elemPf = _365._1;
                            auto _367 = elemPf;
                            auto _366 = lemma_x_in_b_vec<uint64_t>(_367);
                            auto _364 = _Dec<_DisjointVec<uint64_t>>::_No(_366);
                            return _364;
                          }
                          case No: {
                            auto _376 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_360.data));
                            auto p = _376._1;
                            auto _378 = x;
                            auto _379 = xs;
                            auto _380 = p;
                            auto _381 = pf;
                            auto _377 = _DisjointVec<uint64_t>::_DConsV(_378, _379, _380, _381);
                            auto _375 = _Dec<_DisjointVec<uint64_t>>::_Yes(_377);
                            return _375;
                          }
                        }
                      }();
                      return _358;
                    }
                    case No: {
                      auto _384 = *(std::static_pointer_cast<_Dec_No<_DisjointVec<uint64_t>>>(_353.data));
                      auto p = _384._1;
                      auto _386 = p;
                      auto _385 = lemma_xs_in_b_vec<uint64_t>(_386);
                      auto _383 = _Dec<_DisjointVec<uint64_t>>::_No(_385);
                      return _383;
                    }
                  }
                }();
                return _351;
              }
            }
          }();
          return _340;
        }
      }
    }();
    return _335;
  };
  return _334;
};

std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjLem = [](auto prf1) {
  auto _393 = [](auto prf2) {
    auto _396 = prf2;
    auto _395 = f_equal<_Vec<uint64_t>, _Vec<uint64_t>>(_396);
    auto _394 = _395;
    return _394;
  };
  return _393;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjective = [](auto p1) {
  auto _402 = [](auto p2) {
    auto _405 = p2;
    auto _404 = f_equal<_Vec<A>, _Vec<A>>(_405);
    auto _403 = _404;
    return _403;
  };
  return _402;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjectiveTail = [](auto p1) {
  auto _411 = [](auto p2) {
    auto _413 = p2;
    auto _412 = f_equal<_Vec<A>, A>(_413);
    return _412;
  };
  return _411;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(_TyEq)> lemma_x_eq_xs_neq_vec = [](auto prf1) {
  auto _419 = [prf1](auto p) {
    auto _420 = [p, prf1](auto prf2) {
      auto _423 = prf1;
      auto _424 = prf2;
      auto _422 = consVInjective<A>(_423)(_424);
      auto _421 = p(_422);
      return _421;
    };
    return _420;
  };
  return _419;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(_TyEq)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_eq_vec = [](auto p) {
  auto _431 = [p](auto p2) {
    auto _432 = [p, p2](auto p3) {
      auto _435 = p2;
      auto _436 = p3;
      auto _434 = consVInjectiveTail<A>(_435)(_436);
      auto _433 = p(_434);
      return _433;
    };
    return _432;
  };
  return _431;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_neq_vec = [](auto p) {
  auto _443 = [p](auto p2) {
    auto _444 = [p](auto p3) {
      auto _447 = p3;
      auto _446 = f_equal<_Vec<A>, A>(_447);
      auto _445 = p(_446);
      return _445;
    };
    return _444;
  };
  return _443;
};

std::function<std::function<_Dec<_TyEq>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decEqVec = [](auto a) {
  auto _453 = [a](auto b) {
    auto _454 = [a, b]() {
      auto _455 = a;
      switch (_455.type) {
        case NilV: {
          auto _457 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_455.data));
          auto _456 = [a, b]() {
            auto _458 = b;
            switch (_458.type) {
              case NilV: {
                auto _460 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_458.data));
                auto _461 = _TyEq::_Refl();
                auto _459 = _Dec<_TyEq>::_Yes(_461);
                return _459;
              }
            }
          }();
          return _456;
        }
        case ConsV: {
          auto _463 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_455.data));
          auto x = _463._1;
          auto xs = _463._2;
          auto _462 = [a, b, x, xs]() {
            auto _464 = b;
            switch (_464.type) {
              case ConsV: {
                auto _466 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_464.data));
                auto y = _466._1;
                auto ys = _466._2;
                auto _465 = [a, b, x, y, xs, ys]() {
                  auto _468 = x;
                  auto _469 = y;
                  auto _467 = decEqNat(_468)(_469);
                  switch (_467.type) {
                    case Yes: {
                      auto _471 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_467.data));
                      auto xeqy = _471._1;
                      auto _470 = [a, b, x, y, xs, ys, xeqy]() {
                        auto _473 = xs;
                        auto _474 = ys;
                        auto _472 = decEqVec(_473)(_474);
                        switch (_472.type) {
                          case Yes: {
                            auto _477 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_472.data));
                            auto xseqys = _477._1;
                            auto _479 = xeqy;
                            auto _480 = xseqys;
                            auto _478 = consVInjLem(_479)(_480);
                            auto _476 = _Dec<_TyEq>::_Yes(_478);
                            return _476;
                          }
                          case No: {
                            auto _487 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_472.data));
                            auto xsneqys = _487._1;
                            auto _489 = xeqy;
                            auto _490 = xsneqys;
                            auto _488 = lemma_x_eq_xs_neq_vec<uint64_t>(_489)(_490);
                            auto _486 = _Dec<_TyEq>::_No(_488);
                            return _486;
                          }
                        }
                      }();
                      return _470;
                    }
                    case No: {
                      auto _498 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_467.data));
                      auto xneqy = _498._1;
                      auto _497 = [a, b, x, y, xs, ys, xneqy]() {
                        auto _500 = xs;
                        auto _501 = ys;
                        auto _499 = decEqVec(_500)(_501);
                        switch (_499.type) {
                          case Yes: {
                            auto _504 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_499.data));
                            auto xseqys = _504._1;
                            auto _506 = xneqy;
                            auto _507 = xseqys;
                            auto _505 = lemma_x_neq_xs_eq_vec<uint64_t>(_506)(_507);
                            auto _503 = _Dec<_TyEq>::_No(_505);
                            return _503;
                          }
                          case No: {
                            auto _515 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_499.data));
                            auto xsneqys = _515._1;
                            auto _517 = xneqy;
                            auto _518 = xsneqys;
                            auto _516 = lemma_x_neq_xs_neq_vec<uint64_t>(_517)(_518);
                            auto _514 = _Dec<_TyEq>::_No(_516);
                            return _514;
                          }
                        }
                      }();
                      return _497;
                    }
                  }
                }();
                return _465;
              }
            }
          }();
          return _462;
        }
      }
    }();
    return _454;
  };
  return _453;
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
  auto _525 = [pf](auto p) {
    auto _526 = [p, pf]() {
      auto _527 = p;
      switch (_527.type) {
        case UConsV: {
          auto _529 = *(std::static_pointer_cast<_UniqueVec_UConsV<A>>(_527.data));
          auto x = _529._1;
          auto xs = _529._2;
          auto xNInXs = _529._3;
          auto others = _529._4;
          auto _530 = pf;
          auto _528 = xNInXs(_530);
          return _528;
        }
      }
    }();
    return _526;
  };
  return _525;
};

template <class A>
std::function<std::function<_Void(_UniqueVec<A>)>(std::function<_Void(_UniqueVec<A>)>)> lemma_xs_not_unique = [](auto pf) {
  auto _531 = [pf](auto p) {
    auto _532 = [p, pf]() {
      auto _533 = p;
      switch (_533.type) {
        case UConsV: {
          auto _535 = *(std::static_pointer_cast<_UniqueVec_UConsV<A>>(_533.data));
          auto x = _535._1;
          auto xs = _535._2;
          auto xNInXs = _535._3;
          auto others = _535._4;
          auto _536 = others;
          auto _534 = pf(_536);
          return _534;
        }
      }
    }();
    return _532;
  };
  return _531;
};

std::function<_Dec<_UniqueVec<uint64_t>>(_Vec<uint64_t>)> decUniqueVec = [](auto v) {
  auto _537 = [v]() {
    auto _538 = v;
    switch (_538.type) {
      case NilV: {
        auto _540 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_538.data));
        auto _541 = _UniqueVec<uint64_t>::_UNilV();
        auto _539 = _Dec<_UniqueVec<uint64_t>>::_Yes(_541);
        return _539;
      }
      case ConsV: {
        auto _543 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_538.data));
        auto x = _543._1;
        auto xs = _543._2;
        auto _542 = [v, x, xs]() {
          auto _545 = x;
          auto _546 = xs;
          auto _544 = isElemVec(_545)(_546);
          switch (_544.type) {
            case Yes: {
              auto _549 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_544.data));
              auto xInXs = _549._1;
              auto _551 = xInXs;
              auto _550 = lemma_x_in_xs_not_unique<uint64_t>(_551);
              auto _548 = _Dec<_UniqueVec<uint64_t>>::_No(_550);
              return _548;
            }
            case No: {
              auto _557 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_544.data));
              auto xNInXs = _557._1;
              auto _556 = [v, x, xs, xNInXs]() {
                auto _559 = xs;
                auto _558 = decUniqueVec(_559);
                switch (_558.type) {
                  case Yes: {
                    auto _562 = *(std::static_pointer_cast<_Dec_Yes<_UniqueVec<uint64_t>>>(_558.data));
                    auto xsU = _562._1;
                    auto _564 = x;
                    auto _565 = xs;
                    auto _566 = xNInXs;
                    auto _567 = xsU;
                    auto _563 = _UniqueVec<uint64_t>::_UConsV(_564, _565, _566, _567);
                    auto _561 = _Dec<_UniqueVec<uint64_t>>::_Yes(_563);
                    return _561;
                  }
                  case No: {
                    auto _570 = *(std::static_pointer_cast<_Dec_No<_UniqueVec<uint64_t>>>(_558.data));
                    auto xsNU = _570._1;
                    auto _572 = xsNU;
                    auto _571 = lemma_xs_not_unique<uint64_t>(_572);
                    auto _569 = _Dec<_UniqueVec<uint64_t>>::_No(_571);
                    return _569;
                  }
                }
              }();
              return _556;
            }
          }
        }();
        return _542;
      }
    }
  }();
  return _537;
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
  auto _577 = [pfXNotInb](auto pf) {
    auto _578 = [pf, pfXNotInb]() {
      auto _579 = pf;
      switch (_579.type) {
        case SConsV: {
          auto _581 = *(std::static_pointer_cast<_SubsetVec_SConsV<A>>(_579.data));
          auto a = _581._1;
          auto as = _581._2;
          auto pfFora = _581._3;
          auto others = _581._4;
          auto _582 = pfFora;
          auto _580 = pfXNotInb(_582);
          return _580;
        }
      }
    }();
    return _578;
  };
  return _577;
};

template <class A>
std::function<std::function<_Void(_SubsetVec<A>)>(std::function<_Void(_SubsetVec<A>)>)> lemma_xs_not_subset_b_vec = [](auto xsNotSubsetPf) {
  auto _583 = [xsNotSubsetPf](auto p) {
    auto _584 = [p, xsNotSubsetPf]() {
      auto _585 = p;
      switch (_585.type) {
        case SConsV: {
          auto _587 = *(std::static_pointer_cast<_SubsetVec_SConsV<A>>(_585.data));
          auto a = _587._1;
          auto as = _587._2;
          auto pfFora = _587._3;
          auto others = _587._4;
          auto _588 = others;
          auto _586 = xsNotSubsetPf(_588);
          return _586;
        }
      }
    }();
    return _584;
  };
  return _583;
};

std::function<std::function<_Dec<_SubsetVec<uint64_t>>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decSubsetVecs = [](auto a) {
  auto _589 = [a](auto b) {
    auto _590 = [a, b]() {
      auto _591 = a;
      switch (_591.type) {
        case NilV: {
          auto _593 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_591.data));
          auto _594 = _SubsetVec<uint64_t>::_SNilV1();
          auto _592 = _Dec<_SubsetVec<uint64_t>>::_Yes(_594);
          return _592;
        }
        case ConsV: {
          auto _596 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_591.data));
          auto x = _596._1;
          auto xs = _596._2;
          auto _595 = [a, b, xs, x]() {
            auto _597 = b;
            switch (_597.type) {
              case NilV: {
                auto _599 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_597.data));
                auto _600 = _SubsetVec<uint64_t>::_SNilV2();
                auto _598 = _Dec<_SubsetVec<uint64_t>>::_Yes(_600);
                return _598;
              }
              case ConsV: {
                auto _602 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_597.data));
                auto y = _602._1;
                auto ys = _602._2;
                auto _601 = [a, b, xs, x]() {
                  auto _604 = xs;
                  auto _605 = b;
                  auto _603 = decSubsetVecs(_604)(_605);
                  switch (_603.type) {
                    case Yes: {
                      auto _609 = *(std::static_pointer_cast<_Dec_Yes<_SubsetVec<uint64_t>>>(_603.data));
                      auto pf = _609._1;
                      auto _608 = [a, b, xs, x, pf]() {
                        auto _611 = x;
                        auto _612 = b;
                        auto _610 = isElemVec(_611)(_612);
                        switch (_610.type) {
                          case Yes: {
                            auto _615 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_610.data));
                            auto elemPf = _615._1;
                            auto _617 = x;
                            auto _618 = xs;
                            auto _619 = elemPf;
                            auto _620 = pf;
                            auto _616 = _SubsetVec<uint64_t>::_SConsV(_617, _618, _619, _620);
                            auto _614 = _Dec<_SubsetVec<uint64_t>>::_Yes(_616);
                            return _614;
                          }
                          case No: {
                            auto _623 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_610.data));
                            auto p = _623._1;
                            auto _625 = p;
                            auto _624 = lemma_x_not_in_b_vec<uint64_t>(_625);
                            auto _622 = _Dec<_SubsetVec<uint64_t>>::_No(_624);
                            return _622;
                          }
                        }
                      }();
                      return _608;
                    }
                    case No: {
                      auto _634 = *(std::static_pointer_cast<_Dec_No<_SubsetVec<uint64_t>>>(_603.data));
                      auto p = _634._1;
                      auto _636 = p;
                      auto _635 = lemma_xs_not_subset_b_vec<uint64_t>(_636);
                      auto _633 = _Dec<_SubsetVec<uint64_t>>::_No(_635);
                      return _633;
                    }
                  }
                }();
                return _601;
              }
            }
          }();
          return _595;
        }
      }
    }();
    return _590;
  };
  return _589;
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
  auto _645 = a;
  auto _644 = _IO<A>::_MkIO(_645);
  return _644;
};

template <class A, class B>
std::function<std::function<_IO<B>(std::function<_IO<B>(A)>)>(_IO<A>)> bindEq = [](auto a) {
  auto _646 = [a](auto f) {
    auto _647 = [a, f]() {
      auto _648 = a;
      switch (_648.type) {
        case MkIO: {
          auto _650 = *(std::static_pointer_cast<_IO_MkIO<A>>(_648.data));
          auto inner = _650._1;
          auto _651 = inner;
          auto _649 = f(_651);
          return _649;
        }
      }
    }();
    return _647;
  };
  return _646;
};

template <class A, class B>
std::function<std::function<_IO<B>(_IO<B>)>(_IO<A>)> bind = [](auto a) {
  auto _652 = [a](auto b) {
    auto _654 = a;
    auto _655 = [a, b](auto c) {
      auto _658 = b;
      return _658;
    };
    auto _653 = bindEq<A, B>(_654)(_655);
    return _653;
  };
  return _652;
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
  auto _659 = [l]() {
    auto _660 = l;
    switch (_660.type) {
      case Nil: {
        auto _662 = *(std::static_pointer_cast<_List_Nil<_List<char>>>(_660.data));
        auto _663 = _Unit::_unit();
        auto _661 = returnIO<_Unit>(_663);
        return _661;
      }
      case Cons: {
        auto _666 = *(std::static_pointer_cast<_List_Cons<_List<char>>>(_660.data));
        auto x = _666._1;
        auto xs = _666._2;
        auto _671 = x;
        auto _667 = print(_671);
        auto _672 = xs;
        auto _668 = printList(_672);
        auto _665 = bind<_Unit, _Unit>(_667)(_668);
        return _665;
      }
    }
  }();
  return _659;
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
  auto _673 = [id](auto x) {
    auto _674 = [id, x](auto ch) {
      auto _676 = id;
      auto _677 = x;
      auto _678 = ch;
      auto _675 = channelEnqueue<A>(_676)(_677)(_678);
      return _675;
    };
    return _674;
  };
  return _673;
};

template <class A>
std::function<std::function<_IO<_Maybe<A>>(_Channel<A>)>(uint64_t)> receive = [](auto id) {
  auto _680 = [id](auto ch) {
    auto _682 = id;
    auto _683 = ch;
    auto _681 = channelDequeue<A>(_682)(_683);
    return _681;
  };
  return _680;
};

template <class A>
std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(std::function<_Void(_ElemVec<uint64_t>)>)>(_Vec<uint64_t>)>(uint64_t)>
    link = [](auto id) {
      auto _685 = [id](auto idSet) {
        auto _686 = [id, idSet](auto pf) {
          auto _687 = [id, idSet]() {
            auto _689 = id;
            auto _688 = prim_create_channel<A>(_689);
            switch (_688.type) {
              case True: {
                auto _692 = *(std::static_pointer_cast<_Bool_True>(_688.data));
                auto _696 = id;
                auto _700 = id;
                auto _698 = _Channel<A>::_MkChannel(_700);
                auto _703 = id;
                auto _704 = idSet;
                auto _701 = _Vec<uint64_t>::_ConsV(_703, _704);
                auto _706 = _TyEq::_Refl();
                auto _707 = _TyEq::_Refl();
                auto _702 = _Sigma<_TyEq, _TyEq>::_Prod(_706, _707);
                auto _699 = _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>::_Prod(_701, _702);
                auto _697 = _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>::_Prod(_698, _699);
                auto _695 = _Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Prod(_696, _697);
                auto _693 = _Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>::_Just(_695);
                auto _691 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_693);
                return _691;
              }
              case False: {
                auto _709 = *(std::static_pointer_cast<_Bool_False>(_688.data));
                auto _710 = _Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>::_Nothing();
                auto _708 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_710);
                return _708;
              }
            }
          }();
          return _687;
        };
        return _686;
      };
      return _685;
    };

std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(std::function<_Void(_ElemVec<uint64_t>)>)>(_Vec<uint64_t>)>(
    uint64_t)>(uint64_t)>
    spawn = [](auto pid) {
      auto _712 = [pid](auto n) {
        auto _713 = [pid](auto pidSet) {
          auto _714 = [pid, pidSet](auto pf) {
            auto _719 = pid;
            auto _723 = pid;
            auto _724 = pidSet;
            auto _721 = _Vec<uint64_t>::_ConsV(_723, _724);
            auto _726 = _TyEq::_Refl();
            auto _727 = _TyEq::_Refl();
            auto _722 = _Sigma<_TyEq, _TyEq>::_Prod(_726, _727);
            auto _720 = _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>::_Prod(_721, _722);
            auto _718 = _Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>::_Prod(_719, _720);
            auto _716 = _Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Just(_718);
            auto _715 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_716);
            return _715;
          };
          return _714;
        };
        return _713;
      };
      return _712;
    };

std::function<std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_IO<_Unit>)>(_ElemVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(uint64_t)> run =
    [](auto pid) {
      auto _728 = [](auto n) {
        auto _729 = [](auto pidSet) {
          auto _730 = [pidSet](auto pf) {
            auto _731 = [pidSet](auto process) {
              auto _736 = pidSet;
              auto _737 = _TyEq::_Refl();
              auto _735 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_736, _737);
              auto _733 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_735);
              auto _732 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_733);
              return _732;
            };
            return _731;
          };
          return _730;
        };
        return _729;
      };
      return _728;
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

std::function<_IO<uint64_t>(uint64_t)> getTime = [](auto i) {
  return returnIO<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
};

template <class A, class B>
std::function<std::function<_Vec<B>(_Vec<A>)>(std::function<B(A)>)> mapV = [](auto f) {
  auto _738 = [f](auto v) {
    auto _739 = [v, f]() {
      auto _740 = v;
      switch (_740.type) {
        case NilV: {
          auto _742 = *(std::static_pointer_cast<_Vec_NilV<A>>(_740.data));
          auto _741 = _Vec<B>::_NilV();
          return _741;
        }
        case ConsV: {
          auto _744 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_740.data));
          auto x = _744._1;
          auto xs = _744._2;
          auto _748 = x;
          auto _745 = f(_748);
          auto _749 = f;
          auto _750 = xs;
          auto _746 = mapV<A, B>(_749)(_750);
          auto _743 = _Vec<B>::_ConsV(_745, _746);
          return _743;
        }
      }
    }();
    return _739;
  };
  return _738;
};

template <class A>
std::function<A(_Vec<A>)> headV = [](auto x) {
  auto _754 = [x]() {
    auto _755 = x;
    switch (_755.type) {
      case ConsV: {
        auto _757 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_755.data));
        auto y = _757._1;
        auto ys = _757._2;
        auto _756 = y;
        return _756;
      }
    }
  }();
  return _754;
};

template <class A>
std::function<_Vec<A>(_Vec<A>)> tailV = [](auto x) {
  auto _758 = [x]() {
    auto _759 = x;
    switch (_759.type) {
      case ConsV: {
        auto _761 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_759.data));
        auto y = _761._1;
        auto ys = _761._2;
        auto _760 = ys;
        return _760;
      }
    }
  }();
  return _758;
};

template <class A>
std::function<_List<A>(_Vec<A>)> vecToList = [](auto v) {
  auto _762 = [v]() {
    auto _763 = v;
    switch (_763.type) {
      case NilV: {
        auto _765 = *(std::static_pointer_cast<_Vec_NilV<A>>(_763.data));
        auto _764 = _List<A>::_Nil();
        return _764;
      }
      case ConsV: {
        auto _767 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_763.data));
        auto y = _767._1;
        auto ys = _767._2;
        auto _768 = y;
        auto _770 = ys;
        auto _769 = vecToList<A>(_770);
        auto _766 = _List<A>::_Cons(_768, _769);
        return _766;
      }
    }
  }();
  return _762;
};

std::function<_Vec<_Vec<uint64_t>>(_Vec<_Vec<uint64_t>>)> transpose = [](auto m) {
  auto _773 = [m]() {
    auto _774 = m;
    switch (_774.type) {
      case NilV: {
        auto _776 = *(std::static_pointer_cast<_Vec_NilV<_Vec<uint64_t>>>(_774.data));
        auto _775 = _Vec<_Vec<uint64_t>>::_NilV();
        return _775;
      }
      case ConsV: {
        auto _778 = *(std::static_pointer_cast<_Vec_ConsV<_Vec<uint64_t>>>(_774.data));
        auto y = _778._1;
        auto _779 = _778._2;
        auto _777 = [m, y]() {
          auto _780 = y;
          switch (_780.type) {
            case NilV: {
              auto _782 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_780.data));
              auto _781 = _Vec<_Vec<uint64_t>>::_NilV();
              return _781;
            }
            case ConsV: {
              auto _784 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_780.data));
              auto _785 = _784._1;
              auto _786 = _784._2;
              auto _790 = headV<uint64_t>;
              auto _791 = m;
              auto _787 = mapV<_Vec<uint64_t>, uint64_t>(_790)(_791);
              auto _800 = tailV<uint64_t>;
              auto _801 = m;
              auto _797 = mapV<_Vec<uint64_t>, _Vec<uint64_t>>(_800)(_801);
              auto _788 = transpose(_797);
              auto _783 = _Vec<_Vec<uint64_t>>::_ConsV(_787, _788);
              return _783;
            }
          }
        }();
        return _777;
      }
    }
  }();
  return _773;
};

_IO<_Unit> mainFunc = []() {
  auto _807 = []() {
    auto _815 = (uint64_t)1;
    auto _818 = (uint64_t)2;
    auto _819 = _Vec<uint64_t>::_NilV();
    auto _816 = _Vec<uint64_t>::_ConsV(_818, _819);
    auto _812 = _Vec<uint64_t>::_ConsV(_815, _816);
    auto _824 = (uint64_t)3;
    auto _827 = (uint64_t)4;
    auto _828 = _Vec<uint64_t>::_NilV();
    auto _825 = _Vec<uint64_t>::_ConsV(_827, _828);
    auto _821 = _Vec<uint64_t>::_ConsV(_824, _825);
    auto _822 = _Vec<_Vec<uint64_t>>::_NilV();
    auto _813 = _Vec<_Vec<uint64_t>>::_ConsV(_821, _822);
    auto _809 = _Vec<_Vec<uint64_t>>::_ConsV(_812, _813);
    auto _808 = transpose(_809);
    switch (_808.type) {
      case ConsV: {
        auto _831 = *(std::static_pointer_cast<_Vec_ConsV<_Vec<uint64_t>>>(_808.data));
        auto x = _831._1;
        auto xs = _831._2;
        auto _830 = [xs, x]() {
          auto _832 = xs;
          switch (_832.type) {
            case ConsV: {
              auto _834 = *(std::static_pointer_cast<_Vec_ConsV<_Vec<uint64_t>>>(_832.data));
              auto y = _834._1;
              auto ys = _834._2;
              auto _840 = natToString;
              auto _844 = x;
              auto _841 = vecToList<uint64_t>(_844);
              auto _839 = map<uint64_t, _List<char>>(_840)(_841);
              auto _835 = printList(_839);
              auto _836 = end;
              auto _833 = bind<_Unit, _Unit>(_835)(_836);
              return _833;
            }
          }
        }();
        return _830;
      }
    }
  }();
  return _807;
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