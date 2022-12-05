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
  auto _738 = [id](auto ch) {
    auto _739 = [id, ch](auto list) {
      auto _740 = [list, id, ch]() {
        auto _741 = list;
        switch (_741.type) {
          case Nil: {
            auto _743 = *(std::static_pointer_cast<_List_Nil<A>>(_741.data));
            auto _748 = id;
            auto _749 = _Maybe<A>::_Nothing();
            auto _750 = ch;
            auto _744 = send<A>(_748)(_749)(_750);
            auto _745 = end;
            auto _742 = bind<_Unit, _Unit>(_744)(_745);
            return _742;
          }
          case Cons: {
            auto _753 = *(std::static_pointer_cast<_List_Cons<A>>(_741.data));
            auto x = _753._1;
            auto xs = _753._2;
            auto _758 = id;
            auto _762 = x;
            auto _759 = _Maybe<A>::_Just(_762);
            auto _760 = ch;
            auto _754 = send<A>(_758)(_759)(_760);
            auto _763 = id;
            auto _764 = ch;
            auto _765 = xs;
            auto _755 = producerWrapper<A>(_763)(_764)(_765);
            auto _752 = bind<_Unit, _Unit>(_754)(_755);
            return _752;
          }
        }
      }();
      return _740;
    };
    return _739;
  };
  return _738;
};

template <class A>
std::function<_IO<_Unit>(_Vec<_Sigma<uint64_t, _Channel<A>>>)> propgateTermination = [](auto chs) {
  auto _767 = [chs]() {
    auto _768 = chs;
    switch (_768.type) {
      case NilV: {
        auto _770 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_768.data));
        auto _769 = end;
        return _769;
      }
      case ConsV: {
        auto _772 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_768.data));
        auto ch = _772._1;
        auto restChs = _772._2;
        auto _771 = [chs, ch, restChs]() {
          auto _773 = ch;
          switch (_773.type) {
            case Prod: {
              auto _775 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_773.data));
              auto chid = _775._1;
              auto channel = _775._2;
              auto _780 = chid;
              auto _781 = _Maybe<A>::_Nothing();
              auto _782 = channel;
              auto _776 = send<A>(_780)(_781)(_782);
              auto _784 = restChs;
              auto _777 = propgateTermination<A>(_784);
              auto _774 = bind<_Unit, _Unit>(_776)(_777);
              return _774;
            }
          }
        }();
        return _771;
      }
    }
  }();
  return _767;
};

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_List<A>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)> farmProducerWrapper = [](auto allChs) {
  auto _787 = [allChs](auto chs) {
    auto _788 = [allChs, chs](auto list) {
      auto _789 = [list, allChs, chs]() {
        auto _790 = list;
        switch (_790.type) {
          case Nil: {
            auto _792 = *(std::static_pointer_cast<_List_Nil<A>>(_790.data));
            auto _793 = allChs;
            auto _791 = propgateTermination<A>(_793);
            return _791;
          }
          case Cons: {
            auto _797 = *(std::static_pointer_cast<_List_Cons<A>>(_790.data));
            auto x = _797._1;
            auto xs = _797._2;
            auto _796 = [list, allChs, chs, x, xs]() {
              auto _798 = chs;
              switch (_798.type) {
                case NilV: {
                  auto _800 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_798.data));
                  auto _801 = allChs;
                  auto _802 = allChs;
                  auto _803 = list;
                  auto _799 = farmProducerWrapper<A>(_801)(_802)(_803);
                  return _799;
                }
                case ConsV: {
                  auto _808 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_798.data));
                  auto ch = _808._1;
                  auto restChs = _808._2;
                  auto _807 = [list, allChs, chs, ch, x, restChs, xs]() {
                    auto _809 = ch;
                    switch (_809.type) {
                      case Prod: {
                        auto _811 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_809.data));
                        auto chid = _811._1;
                        auto channel = _811._2;
                        auto _816 = chid;
                        auto _820 = x;
                        auto _817 = _Maybe<A>::_Just(_820);
                        auto _818 = channel;
                        auto _812 = send<A>(_816)(_817)(_818);
                        auto _821 = allChs;
                        auto _822 = restChs;
                        auto _823 = xs;
                        auto _813 = farmProducerWrapper<A>(_821)(_822)(_823);
                        auto _810 = bind<_Unit, _Unit>(_812)(_813);
                        return _810;
                      }
                    }
                  }();
                  return _807;
                }
              }
            }();
            return _796;
          }
        }
      }();
      return _789;
    };
    return _788;
  };
  return _787;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_Channel<A>)>(_Channel<A>)>(uint64_t)>(uint64_t)> workerWrapper = [](auto receiveId) {
  auto _827 = [receiveId](auto sendId) {
    auto _828 = [receiveId, sendId](auto receiveChannel) {
      auto _829 = [receiveId, receiveChannel, sendId](auto sendChannel) {
        auto _830 = [receiveId, receiveChannel, sendId, sendChannel](auto f) {
          auto _836 = receiveId;
          auto _837 = receiveChannel;
          auto _832 = receive<A>(_836)(_837);
          auto _833 = [receiveId, receiveChannel, sendId, sendChannel, f](auto mx) {
            auto _839 = [receiveId, receiveChannel, mx, sendId, sendChannel, f]() {
              auto _840 = mx;
              switch (_840.type) {
                case Nothing: {
                  auto _842 = *(std::static_pointer_cast<_Maybe_Nothing<A>>(_840.data));
                  auto _847 = sendId;
                  auto _848 = _Maybe<A>::_Nothing();
                  auto _849 = sendChannel;
                  auto _843 = send<A>(_847)(_848)(_849);
                  auto _844 = end;
                  auto _841 = bind<_Unit, _Unit>(_843)(_844);
                  return _841;
                }
                case Just: {
                  auto _852 = *(std::static_pointer_cast<_Maybe_Just<A>>(_840.data));
                  auto x = _852._1;
                  auto _857 = sendId;
                  auto _862 = x;
                  auto _861 = f(_862);
                  auto _858 = _Maybe<A>::_Just(_861);
                  auto _859 = sendChannel;
                  auto _853 = send<A>(_857)(_858)(_859);
                  auto _863 = receiveId;
                  auto _864 = sendId;
                  auto _865 = receiveChannel;
                  auto _866 = sendChannel;
                  auto _867 = f;
                  auto _854 = workerWrapper<A>(_863)(_864)(_865)(_866)(_867);
                  auto _851 = bind<_Unit, _Unit>(_853)(_854);
                  return _851;
                }
              }
            }();
            return _839;
          };
          auto _831 = bindEq<_Maybe<A>, _Unit>(_832)(_833);
          return _831;
        };
        return _830;
      };
      return _829;
    };
    return _828;
  };
  return _827;
};

template <class A>
std::function<std::function<std::function<_IO<_List<A>>(uint64_t)>(_Channel<A>)>(uint64_t)> farmConsumerWrapper = [](auto chid) {
  auto _869 = [chid](auto ch) {
    auto _870 = [chid, ch](auto numLeft) {
      auto _871 = [numLeft, chid, ch]() {
        auto _872 = numLeft;
        if (!_872) {
          auto _874 = _List<A>::_Nil();
          auto _873 = returnIO<_List<A>>(_874);
          return _873;
        } else {
          auto n = _872 - 1;
          auto _880 = chid;
          auto _881 = ch;
          auto _876 = receive<A>(_880)(_881);
          auto _877 = [numLeft, chid, ch, n](auto mx) {
            auto _883 = [numLeft, chid, ch, mx, n]() {
              auto _884 = mx;
              switch (_884.type) {
                case Nothing: {
                  auto _886 = *(std::static_pointer_cast<_Maybe_Nothing<A>>(_884.data));
                  auto _887 = chid;
                  auto _888 = ch;
                  auto _889 = n;
                  auto _885 = farmConsumerWrapper<A>(_887)(_888)(_889);
                  return _885;
                }
                case Just: {
                  auto _892 = *(std::static_pointer_cast<_Maybe_Just<A>>(_884.data));
                  auto x = _892._1;
                  auto _897 = chid;
                  auto _898 = ch;
                  auto _899 = numLeft;
                  auto _893 = farmConsumerWrapper<A>(_897)(_898)(_899);
                  auto _894 = [numLeft, chid, ch, mx, n, x](auto res) {
                    auto _904 = x;
                    auto _905 = res;
                    auto _902 = _List<A>::_Cons(_904, _905);
                    auto _901 = returnIO<_List<A>>(_902);
                    return _901;
                  };
                  auto _891 = bindEq<_List<A>, _List<A>>(_893)(_894);
                  return _891;
                }
              }
            }();
            return _883;
          };
          auto _873 = bindEq<_Maybe<A>, _List<A>>(_876)(_877);
          return _873;
        }
      }();
      return _871;
    };
    return _870;
  };
  return _869;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(std::function<A(A)>)>(
    _Sigma<uint64_t, _Channel<A>>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>
    spawnWorkersFarm = [](auto n) {
      auto _906 = [n](auto pidSet) {
        auto _907 = [pidSet, n](auto nDash) {
          auto _908 = [pidSet, n, nDash](auto pids) {
            auto _909 = [pids, pidSet, n, nDash](auto pidPf) {
              auto _910 = [pids, pidSet, pidPf, n, nDash](auto chs) {
                auto _911 = [pids, pidSet, pidPf, chs, n, nDash](auto consumerCh) {
                  auto _912 = [consumerCh, pids, pidSet, pidPf, chs, n, nDash](auto f) {
                    auto _913 = [consumerCh, pids, pidSet, pidPf, chs, f, n, nDash]() {
                      auto _914 = consumerCh;
                      switch (_914.type) {
                        case Prod: {
                          auto _916 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_914.data));
                          auto consumerChid = _916._1;
                          auto consumerChannel = _916._2;
                          auto _915 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash]() {
                            auto _917 = pids;
                            switch (_917.type) {
                              case NilV: {
                                auto _919 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_917.data));
                                auto _923 = pidSet;
                                auto _924 = _TyEq::_Refl();
                                auto _922 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_923, _924);
                                auto _920 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_922);
                                auto _918 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_920);
                                return _918;
                              }
                              case ConsV: {
                                auto _926 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_917.data));
                                auto x = _926._1;
                                auto xs = _926._2;
                                auto _925 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash, xs]() {
                                  auto _927 = pidPf;
                                  switch (_927.type) {
                                    case UConsV: {
                                      auto _929 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_927.data));
                                      auto y = _929._1;
                                      auto ys = _929._2;
                                      auto pf = _929._3;
                                      auto restPf = _929._4;
                                      auto _928 = [consumerCh, pids, pidSet, pidPf, chs, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf]() {
                                        auto _930 = chs;
                                        switch (_930.type) {
                                          case ConsV: {
                                            auto _932 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_930.data));
                                            auto curCh = _932._1;
                                            auto restChs = _932._2;
                                            auto _931 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf, restChs]() {
                                              auto _933 = curCh;
                                              switch (_933.type) {
                                                case Prod: {
                                                  auto _935 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_933.data));
                                                  auto currChid = _935._1;
                                                  auto currChannel = _935._2;
                                                  auto _940 = y;
                                                  auto _941 = ys;
                                                  auto _942 = pf;
                                                  auto _936 = spawnAndRun(_940)(_941)(
                                                      _942)([consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f]() {
                                                    auto _945 = currChid;
                                                    auto _946 = consumerChid;
                                                    auto _947 = currChannel;
                                                    auto _948 = consumerChannel;
                                                    auto _949 = f;
                                                    auto _943 = workerWrapper<A>(_945)(_946)(_947)(_948)(_949);
                                                  });
                                                  auto _937 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, n, nDash, xs, restPf,
                                                               restChs](auto mres) {
                                                    auto _951 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash, xs,
                                                                 restPf, restChs]() {
                                                      auto _952 = mres;
                                                      switch (_952.type) {
                                                        case Nothing: {
                                                          auto _954 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_952.data));
                                                          auto _955 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Nothing();
                                                          auto _953 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_955);
                                                          return _953;
                                                        }
                                                        case Just: {
                                                          auto _958 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_952.data));
                                                          auto res = _958._1;
                                                          auto _963 = n;
                                                          auto _964 = pidSet;
                                                          auto _972 = nDash;
                                                          auto _965 = pred(_972);
                                                          auto _966 = xs;
                                                          auto _967 = restPf;
                                                          auto _968 = restChs;
                                                          auto _969 = consumerCh;
                                                          auto _970 = f;
                                                          auto _959 = spawnWorkersFarm<A>(_963)(_964)(_965)(_966)(_967)(_968)(_969)(_970);
                                                          auto _960 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash,
                                                                       xs, restPf, restChs](auto mress) {
                                                            auto _973 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n,
                                                                         nDash, xs, restPf, restChs, mress]() {
                                                              auto _974 = mress;
                                                              switch (_974.type) {
                                                                case Nothing: {
                                                                  auto _976 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<uint64_t>, _TyEq>>>(_974.data));
                                                                  auto _977 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Nothing();
                                                                  auto _975 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_977);
                                                                  return _975;
                                                                }
                                                                case Just: {
                                                                  auto _980 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<uint64_t>, _TyEq>>>(_974.data));
                                                                  auto res = _980._1;
                                                                  auto _979 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n,
                                                                               nDash, xs, restPf, restChs, mress, res]() {
                                                                    auto _981 = res;
                                                                    switch (_981.type) {
                                                                      case Prod: {
                                                                        auto _983 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_981.data));
                                                                        auto newPidSet = _983._1;
                                                                        auto pfNewPidSetCorrect = _983._2;
                                                                        auto _989 = y;
                                                                        auto _990 = newPidSet;
                                                                        auto _987 = _Vec<uint64_t>::_ConsV(_989, _990);
                                                                        auto _992 = _TyEq::_Refl();
                                                                        auto _988 = _992;
                                                                        auto _986 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_987, _988);
                                                                        auto _984 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_986);
                                                                        auto _982 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_984);
                                                                        return _982;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _979;
                                                                }
                                                              }
                                                            }();
                                                            return _973;
                                                          };
                                                          auto _957 = bindEq<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>, _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_959)(_960);
                                                          return _957;
                                                        }
                                                      }
                                                    }();
                                                    return _951;
                                                  };
                                                  auto _934 = bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>, _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_936)(_937);
                                                  return _934;
                                                }
                                              }
                                            }();
                                            return _931;
                                          }
                                        }
                                      }();
                                      return _928;
                                    }
                                  }
                                }();
                                return _925;
                              }
                            }
                          }();
                          return _915;
                        }
                      }
                    }();
                    return _913;
                  };
                  return _912;
                };
                return _911;
              };
              return _910;
            };
            return _909;
          };
          return _908;
        };
        return _907;
      };
      return _906;
    };

template <class A>
std::function<std::function<std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>
    createChannelsFarm = [](auto m) {
      auto _993 = [m](auto chidSet) {
        auto _994 = [chidSet, m](auto mDash) {
          auto _995 = [chidSet, m, mDash](auto chids) {
            auto _996 = [chids, chidSet, m, mDash](auto chidPf) {
              auto _997 = [chids, chidSet, chidPf, m, mDash]() {
                auto _998 = chids;
                switch (_998.type) {
                  case NilV: {
                    auto _1000 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_998.data));
                    auto _1004 = _Vec<_Sigma<uint64_t, _Channel<A>>>::_NilV();
                    auto _1006 = chidSet;
                    auto _1007 = _TyEq::_Refl();
                    auto _1005 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1006, _1007);
                    auto _1003 = _Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1004, _1005);
                    auto _1001 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Just(_1003);
                    auto _999 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1001);
                    return _999;
                  }
                  case ConsV: {
                    auto _1009 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_998.data));
                    auto x = _1009._1;
                    auto xs = _1009._2;
                    auto _1008 = [chids, chidSet, chidPf, m, mDash, xs]() {
                      auto _1010 = chidPf;
                      switch (_1010.type) {
                        case UConsV: {
                          auto _1012 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_1010.data));
                          auto y = _1012._1;
                          auto ys = _1012._2;
                          auto pf = _1012._3;
                          auto restPf = _1012._4;
                          auto _1017 = y;
                          auto _1018 = ys;
                          auto _1019 = pf;
                          auto _1013 = link<A>(_1017)(_1018)(_1019);
                          auto _1014 = [chids, chidSet, chidPf, y, ys, pf, m, mDash, xs, restPf](auto mres) {
                            auto _1022 = [chids, chidSet, chidPf, y, ys, pf, mres, m, mDash, xs, restPf]() {
                              auto _1023 = mres;
                              switch (_1023.type) {
                                case Nothing: {
                                  auto _1025 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_1023.data));
                                  auto _1026 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                  auto _1024 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1026);
                                  return _1024;
                                }
                                case Just: {
                                  auto _1029 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_1023.data));
                                  auto res = _1029._1;
                                  auto _1028 = [chids, chidSet, chidPf, y, ys, pf, mres, res, m, mDash, xs, restPf]() {
                                    auto _1030 = res;
                                    switch (_1030.type) {
                                      case Prod: {
                                        auto _1032 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_1030.data));
                                        auto resChid = _1032._1;
                                        auto rest1 = _1032._2;
                                        auto _1031 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, m, mDash, xs, restPf]() {
                                          auto _1033 = rest1;
                                          switch (_1033.type) {
                                            case Prod: {
                                              auto _1035 = *(std::static_pointer_cast<_Sigma_Prod<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>(_1033.data));
                                              auto ch = _1035._1;
                                              auto rest2 = _1035._2;
                                              auto _1034 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, m, mDash, xs, restPf, ch]() {
                                                auto _1036 = rest2;
                                                switch (_1036.type) {
                                                  case Prod: {
                                                    auto _1038 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>(_1036.data));
                                                    auto newChidSet = _1038._1;
                                                    auto pfs = _1038._2;
                                                    auto _1037 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch]() {
                                                      auto _1039 = pfs;
                                                      switch (_1039.type) {
                                                        case Prod: {
                                                          auto _1041 = *(std::static_pointer_cast<_Sigma_Prod<_TyEq, _TyEq>>(_1039.data));
                                                          auto chidEqResChidPf = _1041._1;
                                                          auto pfNewChidSetCorrect = _1041._2;
                                                          auto _1046 = m;
                                                          auto _1047 = chidSet;
                                                          auto _1052 = mDash;
                                                          auto _1048 = pred(_1052);
                                                          auto _1049 = xs;
                                                          auto _1050 = restPf;
                                                          auto _1042 = createChannelsFarm<A>(_1046)(_1047)(_1048)(_1049)(_1050);
                                                          auto _1043 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch](auto mress) {
                                                            auto _1053 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ch]() {
                                                              auto _1054 = mress;
                                                              switch (_1054.type) {
                                                                case Nothing: {
                                                                  auto _1056 = *(
                                                                      std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1054.data));
                                                                  auto _1057 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                                                  auto _1055 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1057);
                                                                  return _1055;
                                                                }
                                                                case Just: {
                                                                  auto _1060 =
                                                                      *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1054.data));
                                                                  auto ress = _1060._1;
                                                                  auto _1059 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, ch]() {
                                                                    auto _1061 = ress;
                                                                    switch (_1061.type) {
                                                                      case Prod: {
                                                                        auto _1063 =
                                                                            *(std::static_pointer_cast<_Sigma_Prod<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1061.data));
                                                                        auto chs = _1063._1;
                                                                        auto rest3 = _1063._2;
                                                                        auto _1062 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, rest3, ch,
                                                                                      chs]() {
                                                                          auto _1064 = rest3;
                                                                          switch (_1064.type) {
                                                                            case Prod: {
                                                                              auto _1066 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1064.data));
                                                                              auto returnedChidSet = _1066._1;
                                                                              auto pfReturnedChidSetCorrect = _1066._2;
                                                                              auto _1076 = y;
                                                                              auto _1077 = ch;
                                                                              auto _1075 = _Sigma<uint64_t, _Channel<A>>::_Prod(_1076, _1077);
                                                                              auto _1072 = _1075;
                                                                              auto _1073 = chs;
                                                                              auto _1070 = _Vec<_Sigma<uint64_t, _Channel<A>>>::_ConsV(_1072, _1073);
                                                                              auto _1080 = y;
                                                                              auto _1081 = returnedChidSet;
                                                                              auto _1078 = _Vec<uint64_t>::_ConsV(_1080, _1081);
                                                                              auto _1083 = _TyEq::_Refl();
                                                                              auto _1079 = _1083;
                                                                              auto _1071 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1078, _1079);
                                                                              auto _1069 = _Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1070, _1071);
                                                                              auto _1067 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Just(_1069);
                                                                              auto _1065 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1067);
                                                                              return _1065;
                                                                            }
                                                                          }
                                                                        }();
                                                                        return _1062;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _1059;
                                                                }
                                                              }
                                                            }();
                                                            return _1053;
                                                          };
                                                          auto _1040 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>,
                                                                              _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1042)(_1043);
                                                          return _1040;
                                                        }
                                                      }
                                                    }();
                                                    return _1037;
                                                  }
                                                }
                                              }();
                                              return _1034;
                                            }
                                          }
                                        }();
                                        return _1031;
                                      }
                                    }
                                  }();
                                  return _1028;
                                }
                              }
                            }();
                            return _1022;
                          };
                          auto _1011 = bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>,
                                              _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1013)(_1014);
                          return _1011;
                        }
                      }
                    }();
                    return _1008;
                  }
                }
              }();
              return _997;
            };
            return _996;
          };
          return _995;
        };
        return _994;
      };
      return _993;
    };

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_List<A>)>(std::function<A(A)>)>(_TyEq)>(_TyEq)>(
    std::function<_Void(_TyEq)>)>(uint64_t)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(
    uint64_t)>
    createFarm = [](auto n) {
      auto _1084 = [n](auto pidSet) {
        auto _1085 = [n, pidSet](auto nDash) {
          auto _1086 = [n, pidSet, nDash](auto pids) {
            auto _1087 = [pids, n, pidSet, nDash](auto pidPf) {
              auto _1088 = [pids, pidPf, n, pidSet, nDash](auto m) {
                auto _1089 = [m, pids, pidPf, n, pidSet, nDash](auto chidSet) {
                  auto _1090 = [m, chidSet, pids, pidPf, n, pidSet, nDash](auto mDash) {
                    auto _1091 = [m, chidSet, mDash, pids, pidPf, n, pidSet, nDash](auto chids) {
                      auto _1092 = [m, chidSet, mDash, chids, pids, pidPf, n, pidSet, nDash](auto chidPf) {
                        auto _1093 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash](auto numWorkers) {
                          auto _1094 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfNotZ) {
                            auto _1095 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfPidsNCorrect) {
                              auto _1096 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfChidsMCorrect) {
                                auto _1097 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto f) {
                                  auto _1098 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, f, numWorkers](auto input) {
                                    auto _1104 = m;
                                    auto _1105 = chidSet;
                                    auto _1106 = mDash;
                                    auto _1107 = chids;
                                    auto _1108 = chidPf;
                                    auto _1100 = createChannelsFarm<A>(_1104)(_1105)(_1106)(_1107)(_1108);
                                    auto _1101 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, input, n, pidSet, nDash, f, numWorkers](auto mres1) {
                                      auto _1110 = [m, chidSet, mDash, chids, chidPf, mres1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                        auto _1111 = mres1;
                                        switch (_1111.type) {
                                          case Nothing: {
                                            auto _1113 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1111.data));
                                            auto _1114 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                            auto _1112 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1114);
                                            return _1112;
                                          }
                                          case Just: {
                                            auto _1117 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1111.data));
                                            auto res1 = _1117._1;
                                            auto _1116 = [m, chidSet, mDash, chids, chidPf, mres1, res1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                              auto _1118 = res1;
                                              switch (_1118.type) {
                                                case Prod: {
                                                  auto _1120 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1118.data));
                                                  auto chs = _1120._1;
                                                  auto chidPfToReturn = _1120._2;
                                                  auto _1119 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, pids, pidPf, input, n, pidSet, nDash, f, numWorkers, chidPfToReturn]() {
                                                    auto _1121 = chs;
                                                    switch (_1121.type) {
                                                      case NilV: {
                                                        auto _1123 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_1121.data));
                                                        auto _1124 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                        auto _1122 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1124);
                                                        return _1122;
                                                      }
                                                      case ConsV: {
                                                        auto _1127 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_1121.data));
                                                        auto consumerCh = _1127._1;
                                                        auto otherChs = _1127._2;
                                                        auto _1126 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, f, numWorkers,
                                                                      chidPfToReturn]() {
                                                          auto _1128 = consumerCh;
                                                          switch (_1128.type) {
                                                            case Prod: {
                                                              auto _1130 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_1128.data));
                                                              auto consumerChid = _1130._1;
                                                              auto consumerChannel = _1130._2;
                                                              auto _1129 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, f,
                                                                            consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                auto _1131 = pids;
                                                                switch (_1131.type) {
                                                                  case NilV: {
                                                                    auto _1133 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_1131.data));
                                                                    auto _1134 =
                                                                        _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                                    auto _1132 =
                                                                        returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                            _1134);
                                                                    return _1132;
                                                                  }
                                                                  case ConsV: {
                                                                    auto _1137 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_1131.data));
                                                                    auto x = _1137._1;
                                                                    auto xs = _1137._2;
                                                                    auto _1136 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, xs, f,
                                                                                  consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                      auto _1138 = pidPf;
                                                                      switch (_1138.type) {
                                                                        case UConsV: {
                                                                          auto _1140 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_1138.data));
                                                                          auto producerPid = _1140._1;
                                                                          auto restPids = _1140._2;
                                                                          auto producerPidPf = _1140._3;
                                                                          auto restPfs = _1140._4;
                                                                          auto _1145 = producerPid;
                                                                          auto _1146 = restPids;
                                                                          auto _1147 = producerPidPf;
                                                                          auto _1141 = spawnAndRun(_1145)(_1146)(_1147)([m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf,
                                                                                                                         producerPid, restPids, producerPidPf, otherChs, input]() {
                                                                            auto _1150 = otherChs;
                                                                            auto _1151 = otherChs;
                                                                            auto _1152 = input;
                                                                            auto _1148 = farmProducerWrapper<A>(_1150)(_1151)(_1152);
                                                                          });
                                                                          auto _1142 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                        producerPidPf, otherChs, input, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel, numWorkers,
                                                                                        chidPfToReturn](auto mres2) {
                                                                            auto _1156 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                          producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel,
                                                                                          numWorkers, chidPfToReturn]() {
                                                                              auto _1157 = mres2;
                                                                              switch (_1157.type) {
                                                                                case Nothing: {
                                                                                  auto _1159 =
                                                                                      *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(
                                                                                          _1157.data));
                                                                                  auto _1160 =
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::
                                                                                          _Nothing();
                                                                                  auto _1158 = returnIO<
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                      _1160);
                                                                                  return _1158;
                                                                                }
                                                                                case Just: {
                                                                                  auto _1163 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(
                                                                                      _1157.data));
                                                                                  auto res2 = _1163._1;
                                                                                  auto _1168 = n;
                                                                                  auto _1169 = pidSet;
                                                                                  auto _1177 = nDash;
                                                                                  auto _1170 = pred(_1177);
                                                                                  auto _1171 = xs;
                                                                                  auto _1172 = restPfs;
                                                                                  auto _1178 = otherChs;
                                                                                  auto _1173 = _1178;
                                                                                  auto _1174 = consumerCh;
                                                                                  auto _1175 = f;
                                                                                  auto _1164 = spawnWorkersFarm<A>(_1168)(_1169)(_1170)(_1171)(_1172)(_1173)(_1174)(_1175);
                                                                                  auto _1165 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel,
                                                                                                numWorkers, chidPfToReturn](auto mres3) {
                                                                                    auto _1179 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                  producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3, consumerChid,
                                                                                                  consumerChannel, numWorkers, chidPfToReturn]() {
                                                                                      auto _1180 = mres3;
                                                                                      switch (_1180.type) {
                                                                                        case Nothing: {
                                                                                          auto _1182 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1180.data));
                                                                                          auto _1183 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                       _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                                                          auto _1181 = returnIO<_Maybe<_Sigma<
                                                                                              _List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                              _1183);
                                                                                          return _1181;
                                                                                        }
                                                                                        case Just: {
                                                                                          auto _1186 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1180.data));
                                                                                          auto workerPidPfs = _1186._1;
                                                                                          auto _1185 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                        restPids, producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3,
                                                                                                        workerPidPfs, consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                                            auto _1187 = workerPidPfs;
                                                                                            switch (_1187.type) {
                                                                                              case Prod: {
                                                                                                auto _1189 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1187.data));
                                                                                                auto workersPidSet = _1189._1;
                                                                                                auto workerPidSetPf = _1189._2;
                                                                                                auto _1194 = consumerChid;
                                                                                                auto _1195 = consumerChannel;
                                                                                                auto _1196 = numWorkers;
                                                                                                auto _1190 = farmConsumerWrapper<A>(_1194)(_1195)(_1196);
                                                                                                auto _1191 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                              restPids, producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3,
                                                                                                              workerPidPfs, consumerChid, consumerChannel, numWorkers, workersPidSet, workerPidSetPf,
                                                                                                              chidPfToReturn](auto resultantList) {
                                                                                                  auto _1202 = resultantList;
                                                                                                  auto _1206 = numWorkers;
                                                                                                  auto _1207 = f;
                                                                                                  auto _1204 = _Farm<A>::_MkFarm(_1206, _1207);
                                                                                                  auto _1212 = producerPid;
                                                                                                  auto _1213 = workersPidSet;
                                                                                                  auto _1210 = _Vec<uint64_t>::_ConsV(_1212, _1213);
                                                                                                  auto _1215 = _TyEq::_Refl();
                                                                                                  auto _1216 = workerPidSetPf;
                                                                                                  auto _1211 = consVInjLem(_1215)(_1216);
                                                                                                  auto _1208 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1210, _1211);
                                                                                                  auto _1209 = chidPfToReturn;
                                                                                                  auto _1205 =
                                                                                                      _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1208, _1209);
                                                                                                  auto _1203 =
                                                                                                      _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Prod(
                                                                                                          _1204, _1205);
                                                                                                  auto _1201 =
                                                                                                      _Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                               _Sigma<_Vec<uint64_t>, _TyEq>>>>::_Prod(_1202, _1203);
                                                                                                  auto _1199 =
                                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                      _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Just(_1201);
                                                                                                  auto _1198 =
                                                                                                      returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                               _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                                          _1199);
                                                                                                  return _1198;
                                                                                                };
                                                                                                auto _1188 =
                                                                                                    bindEq<_List<A>, _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                                     _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                                        _1190)(_1191);
                                                                                                return _1188;
                                                                                              }
                                                                                            }
                                                                                          }();
                                                                                          return _1185;
                                                                                        }
                                                                                      }
                                                                                    }();
                                                                                    return _1179;
                                                                                  };
                                                                                  auto _1162 = bindEq<
                                                                                      _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>,
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                      _1164)(_1165);
                                                                                  return _1162;
                                                                                }
                                                                              }
                                                                            }();
                                                                            return _1156;
                                                                          };
                                                                          auto _1139 =
                                                                              bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>,
                                                                                     _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                  _1141)(_1142);
                                                                          return _1139;
                                                                        }
                                                                      }
                                                                    }();
                                                                    return _1136;
                                                                  }
                                                                }
                                                              }();
                                                              return _1129;
                                                            }
                                                          }
                                                        }();
                                                        return _1126;
                                                      }
                                                    }
                                                  }();
                                                  return _1119;
                                                }
                                              }
                                            }();
                                            return _1116;
                                          }
                                        }
                                      }();
                                      return _1110;
                                    };
                                    auto _1099 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>,
                                                        _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1100)(_1101);
                                    return _1099;
                                  };
                                  return _1098;
                                };
                                return _1097;
                              };
                              return _1096;
                            };
                            return _1095;
                          };
                          return _1094;
                        };
                        return _1093;
                      };
                      return _1092;
                    };
                    return _1091;
                  };
                  return _1090;
                };
                return _1089;
              };
              return _1088;
            };
            return _1087;
          };
          return _1086;
        };
        return _1085;
      };
      return _1084;
    };

std::function<uint64_t(uint64_t)> id = [](auto a) {
  auto _1223 = a;
  auto _1222 = _1223 + 1;
  ;
  return _1222;
};

template <class A>
std::function<_IO<_Unit>(A)> runInIO = [](auto f) {
  auto _1225 = _Unit::_unit();
  auto _1224 = returnIO<_Unit>(_1225);
  return _1224;
};

template <class A>
std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_List<A>)> baseRun = [](auto inList) {
  auto _1227 = [inList](auto func) {
    auto _1233 = (uint64_t)0;
    auto _1229 = getTime(_1233);
    auto _1230 = [func, inList](auto startTime1) {
      auto _1240 = startTime1;
      auto _1239 = natToString(_1240);
      auto _1235 = print(_1239);
      auto _1247 = func;
      auto _1248 = inList;
      auto _1245 = map<A, A>(_1247)(_1248);
      auto _1241 = runInIO<_List<A>>(_1245);
      auto _1255 = (uint64_t)0;
      auto _1251 = getTime(_1255);
      auto _1252 = [startTime1, func, inList](auto endTime1) {
        auto _1262 = endTime1;
        auto _1261 = natToString(_1262);
        auto _1257 = print(_1261);
        auto _1258 = end;
        auto _1256 = bind<_Unit, _Unit>(_1257)(_1258);
        return _1256;
      };
      auto _1242 = bindEq<uint64_t, _Unit>(_1251)(_1252);
      auto _1236 = bind<_Unit, _Unit>(_1241)(_1242);
      auto _1234 = bind<_Unit, _Unit>(_1235)(_1236);
      return _1234;
    };
    auto _1228 = bindEq<uint64_t, _Unit>(_1229)(_1230);
    return _1228;
  };
  return _1227;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<
    _IO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>(
    uint64_t)>(std::function<A(A)>)>(_List<A>)>
    runFarm = [](auto inList) {
      auto _1263 = [inList](auto func) {
        auto _1264 = [func, inList](auto numWorkers) {
          auto _1265 = [numWorkers, func, inList](auto n) {
            auto _1266 = [numWorkers, n, func, inList](auto pidSet) {
              auto _1267 = [pidSet, numWorkers, n, func, inList](auto x) {
                auto _1268 = [pidSet, numWorkers, x, n, func, inList](auto pidsToAdd) {
                  auto _1269 = [pidsToAdd, pidSet, numWorkers, x, n, func, inList](auto m) {
                    auto _1270 = [pidsToAdd, pidSet, numWorkers, x, n, m, func, inList](auto chidSet) {
                      auto _1271 = [pidsToAdd, pidSet, chidSet, numWorkers, x, n, m, func, inList](auto y) {
                        auto _1272 = [pidsToAdd, pidSet, chidSet, numWorkers, x, y, n, m, func, inList](auto chidsToAdd) {
                          auto _1273 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, n, m, func, inList]() {
                            auto _1277 = pidsToAdd;
                            auto _1278 = pidSet;
                            auto _1275 = append<uint64_t>(_1277)(_1278);
                            auto _1274 = decUniqueVec(_1275);
                            switch (_1274.type) {
                              case Yes: {
                                auto _1283 = *(std::static_pointer_cast<_Dec_Yes<_UniqueVec<uint64_t>>>(_1274.data));
                                auto pidsProof = _1283._1;
                                auto _1282 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, n, pidsProof, m, func, inList]() {
                                  auto _1287 = chidsToAdd;
                                  auto _1288 = chidSet;
                                  auto _1285 = append<uint64_t>(_1287)(_1288);
                                  auto _1284 = decUniqueVec(_1285);
                                  switch (_1284.type) {
                                    case Yes: {
                                      auto _1293 = *(std::static_pointer_cast<_Dec_Yes<_UniqueVec<uint64_t>>>(_1284.data));
                                      auto chidsProof = _1293._1;
                                      auto _1292 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, n, pidsProof, m, chidsProof, func, inList]() {
                                        auto _1295 = numWorkers;
                                        auto _1296 = (uint64_t)0;
                                        auto _1294 = decEqNat(_1295)(_1296);
                                        switch (_1294.type) {
                                          case No: {
                                            auto _1298 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_1294.data));
                                            auto numWneq0 = _1298._1;
                                            auto _1297 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, n, pidsProof, m, chidsProof, numWneq0, func, inList]() {
                                              auto _1300 = x;
                                              auto _1302 = numWorkers;
                                              auto _1301 = _1302 + 1;
                                              ;
                                              auto _1299 = decEqNat(_1300)(_1301);
                                              switch (_1299.type) {
                                                case Yes: {
                                                  auto _1304 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_1299.data));
                                                  auto xProof = _1304._1;
                                                  auto _1303 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, n, pidsProof, m, chidsProof, numWneq0, xProof, func, inList]() {
                                                    auto _1306 = y;
                                                    auto _1308 = numWorkers;
                                                    auto _1307 = _1308 + 1;
                                                    ;
                                                    auto _1305 = decEqNat(_1306)(_1307);
                                                    switch (_1305.type) {
                                                      case Yes: {
                                                        auto _1310 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_1305.data));
                                                        auto yProof = _1310._1;
                                                        auto _1315 = (uint64_t)0;
                                                        auto _1311 = getTime(_1315);
                                                        auto _1312 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, n, pidsProof, m, chidsProof, numWneq0, xProof, yProof, func,
                                                                      inList](auto startTime) {
                                                          auto _1322 = startTime;
                                                          auto _1321 = natToString(_1322);
                                                          auto _1317 = print(_1321);
                                                          auto _1327 = n;
                                                          auto _1328 = pidSet;
                                                          auto _1329 = x;
                                                          auto _1330 = pidsToAdd;
                                                          auto _1331 = pidsProof;
                                                          auto _1332 = m;
                                                          auto _1333 = chidSet;
                                                          auto _1334 = y;
                                                          auto _1335 = chidsToAdd;
                                                          auto _1336 = chidsProof;
                                                          auto _1337 = numWorkers;
                                                          auto _1338 = numWneq0;
                                                          auto _1339 = xProof;
                                                          auto _1340 = yProof;
                                                          auto _1341 = func;
                                                          auto _1342 = inList;
                                                          auto _1323 = createFarm<A>(_1327)(_1328)(_1329)(_1330)(_1331)(_1332)(_1333)(_1334)(_1335)(_1336)(_1337)(_1338)(_1339)(_1340)(_1341)(_1342);
                                                          auto _1324 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, startTime, n, pidsProof, m, chidsProof, numWneq0, xProof, yProof,
                                                                        func, inList](auto mresult) {
                                                            auto _1344 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, startTime, n, pidsProof, m, chidsProof, numWneq0, xProof, yProof,
                                                                          func, inList, mresult]() {
                                                              auto _1345 = mresult;
                                                              switch (_1345.type) {
                                                                case Just: {
                                                                  auto _1347 = *(std::static_pointer_cast<
                                                                                 _Maybe_Just<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                      _1345.data));
                                                                  auto result = _1347._1;
                                                                  auto _1346 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, startTime, n, pidsProof, m, chidsProof, numWneq0, xProof,
                                                                                yProof, func, inList, mresult, result]() {
                                                                    auto _1348 = result;
                                                                    switch (_1348.type) {
                                                                      case Prod: {
                                                                        auto _1350 = *(std::static_pointer_cast<
                                                                                       _Sigma_Prod<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>(
                                                                            _1348.data));
                                                                        auto output = _1350._1;
                                                                        auto rest1 = _1350._2;
                                                                        auto _1349 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, startTime, n, pidsProof, m, chidsProof, numWneq0,
                                                                                      xProof, yProof, func, inList, mresult, result, rest1]() {
                                                                          auto _1351 = rest1;
                                                                          switch (_1351.type) {
                                                                            case Prod: {
                                                                              auto _1353 = *(
                                                                                  std::static_pointer_cast<_Sigma_Prod<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(
                                                                                      _1351.data));
                                                                              auto farmObject = _1353._1;
                                                                              auto toReturn = _1353._2;
                                                                              auto _1358 = (uint64_t)0;
                                                                              auto _1354 = getTime(_1358);
                                                                              auto _1355 = [pidsToAdd, pidSet, chidsToAdd, chidSet, numWorkers, x, y, startTime, n, pidsProof, m, chidsProof, numWneq0,
                                                                                            xProof, yProof, func, inList, mresult, result, rest1, toReturn](auto endTime) {
                                                                                auto _1365 = endTime;
                                                                                auto _1364 = natToString(_1365);
                                                                                auto _1360 = print(_1364);
                                                                                auto _1368 = toReturn;
                                                                                auto _1366 = _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Just(_1368);
                                                                                auto _1361 = returnIO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1366);
                                                                                auto _1359 = bind<_Unit, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1360)(_1361);
                                                                                return _1359;
                                                                              };
                                                                              auto _1352 = bindEq<uint64_t, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1354)(_1355);
                                                                              return _1352;
                                                                            }
                                                                          }
                                                                        }();
                                                                        return _1349;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _1346;
                                                                }
                                                                case Nothing: {
                                                                  auto _1370 =
                                                                      *(std::static_pointer_cast<
                                                                          _Maybe_Nothing<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                          _1345.data));
                                                                  auto _1371 = _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                                                  auto _1369 = returnIO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1371);
                                                                  return _1369;
                                                                }
                                                              }
                                                            }();
                                                            return _1344;
                                                          };
                                                          auto _1318 = bindEq<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>,
                                                                              _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1323)(_1324);
                                                          auto _1316 = bind<_Unit, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1317)(_1318);
                                                          return _1316;
                                                        };
                                                        auto _1309 = bindEq<uint64_t, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1311)(_1312);
                                                        return _1309;
                                                      }
                                                      case No: {
                                                        auto _1374 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_1305.data));
                                                        auto xYProof = _1374._1;
                                                        auto _1380 = 'E';
                                                        auto _1382 = 'r';
                                                        auto _1384 = 'r';
                                                        auto _1386 = 'o';
                                                        auto _1388 = 'r';
                                                        auto _1389 = _List<char>::_Nil();
                                                        auto _1387 = _List<char>::_Cons(_1388, _1389);
                                                        auto _1385 = _List<char>::_Cons(_1386, _1387);
                                                        auto _1383 = _List<char>::_Cons(_1384, _1385);
                                                        auto _1381 = _List<char>::_Cons(_1382, _1383);
                                                        auto _1379 = _List<char>::_Cons(_1380, _1381);
                                                        auto _1375 = print(_1379);
                                                        auto _1390 = _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                                        auto _1376 = returnIO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1390);
                                                        auto _1373 = bind<_Unit, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1375)(_1376);
                                                        return _1373;
                                                      }
                                                    }
                                                  }();
                                                  return _1303;
                                                }
                                                case No: {
                                                  auto _1393 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_1299.data));
                                                  auto cXProof = _1393._1;
                                                  auto _1399 = 'E';
                                                  auto _1401 = 'r';
                                                  auto _1403 = 'r';
                                                  auto _1405 = 'o';
                                                  auto _1407 = 'r';
                                                  auto _1408 = _List<char>::_Nil();
                                                  auto _1406 = _List<char>::_Cons(_1407, _1408);
                                                  auto _1404 = _List<char>::_Cons(_1405, _1406);
                                                  auto _1402 = _List<char>::_Cons(_1403, _1404);
                                                  auto _1400 = _List<char>::_Cons(_1401, _1402);
                                                  auto _1398 = _List<char>::_Cons(_1399, _1400);
                                                  auto _1394 = print(_1398);
                                                  auto _1409 = _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                                  auto _1395 = returnIO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1409);
                                                  auto _1392 = bind<_Unit, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1394)(_1395);
                                                  return _1392;
                                                }
                                              }
                                            }();
                                            return _1297;
                                          }
                                          case Yes: {
                                            auto _1412 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_1294.data));
                                            auto numWeq0 = _1412._1;
                                            auto _1418 = 'E';
                                            auto _1420 = 'r';
                                            auto _1422 = 'r';
                                            auto _1424 = 'o';
                                            auto _1426 = 'r';
                                            auto _1427 = _List<char>::_Nil();
                                            auto _1425 = _List<char>::_Cons(_1426, _1427);
                                            auto _1423 = _List<char>::_Cons(_1424, _1425);
                                            auto _1421 = _List<char>::_Cons(_1422, _1423);
                                            auto _1419 = _List<char>::_Cons(_1420, _1421);
                                            auto _1417 = _List<char>::_Cons(_1418, _1419);
                                            auto _1413 = print(_1417);
                                            auto _1428 = _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                            auto _1414 = returnIO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1428);
                                            auto _1411 = bind<_Unit, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1413)(_1414);
                                            return _1411;
                                          }
                                        }
                                      }();
                                      return _1292;
                                    }
                                    case No: {
                                      auto _1431 = *(std::static_pointer_cast<_Dec_No<_UniqueVec<uint64_t>>>(_1284.data));
                                      auto cChidsProof = _1431._1;
                                      auto _1437 = 'E';
                                      auto _1439 = 'r';
                                      auto _1441 = 'r';
                                      auto _1443 = 'o';
                                      auto _1445 = 'r';
                                      auto _1446 = _List<char>::_Nil();
                                      auto _1444 = _List<char>::_Cons(_1445, _1446);
                                      auto _1442 = _List<char>::_Cons(_1443, _1444);
                                      auto _1440 = _List<char>::_Cons(_1441, _1442);
                                      auto _1438 = _List<char>::_Cons(_1439, _1440);
                                      auto _1436 = _List<char>::_Cons(_1437, _1438);
                                      auto _1432 = print(_1436);
                                      auto _1447 = _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                      auto _1433 = returnIO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1447);
                                      auto _1430 = bind<_Unit, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1432)(_1433);
                                      return _1430;
                                    }
                                  }
                                }();
                                return _1282;
                              }
                              case No: {
                                auto _1450 = *(std::static_pointer_cast<_Dec_No<_UniqueVec<uint64_t>>>(_1274.data));
                                auto cPidsProof = _1450._1;
                                auto _1456 = 'E';
                                auto _1458 = 'r';
                                auto _1460 = 'r';
                                auto _1462 = 'o';
                                auto _1464 = 'r';
                                auto _1465 = _List<char>::_Nil();
                                auto _1463 = _List<char>::_Cons(_1464, _1465);
                                auto _1461 = _List<char>::_Cons(_1462, _1463);
                                auto _1459 = _List<char>::_Cons(_1460, _1461);
                                auto _1457 = _List<char>::_Cons(_1458, _1459);
                                auto _1455 = _List<char>::_Cons(_1456, _1457);
                                auto _1451 = print(_1455);
                                auto _1466 = _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                auto _1452 = returnIO<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1466);
                                auto _1449 = bind<_Unit, _Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1451)(_1452);
                                return _1449;
                              }
                            }
                          }();
                          return _1273;
                        };
                        return _1272;
                      };
                      return _1271;
                    };
                    return _1270;
                  };
                  return _1269;
                };
                return _1268;
              };
              return _1267;
            };
            return _1266;
          };
          return _1265;
        };
        return _1264;
      };
      return _1263;
    };

template <class A>
std::function<std::function<std::function<std::function<_IO<_Unit>(_Vec<uint64_t>)>(_Vec<uint64_t>)>(std::function<A(A)>)>(_List<A>)> sixCoreTest2 = [](auto inList) {
  auto _1468 = [inList](auto func) {
    auto _1469 = [inList, func](auto pidSet) {
      auto _1470 = [inList, func, pidSet](auto chidSet) {
        auto _1476 = inList;
        auto _1477 = func;
        auto _1478 = (uint64_t)4;
        auto _1479 = (uint64_t)7;
        auto _1480 = pidSet;
        auto _1481 = (uint64_t)5;
        auto _1488 = (uint64_t)12;
        auto _1491 = (uint64_t)11;
        auto _1494 = (uint64_t)10;
        auto _1497 = (uint64_t)9;
        auto _1500 = (uint64_t)8;
        auto _1501 = _Vec<uint64_t>::_NilV();
        auto _1498 = _Vec<uint64_t>::_ConsV(_1500, _1501);
        auto _1495 = _Vec<uint64_t>::_ConsV(_1497, _1498);
        auto _1492 = _Vec<uint64_t>::_ConsV(_1494, _1495);
        auto _1489 = _Vec<uint64_t>::_ConsV(_1491, _1492);
        auto _1482 = _Vec<uint64_t>::_ConsV(_1488, _1489);
        auto _1483 = (uint64_t)7;
        auto _1484 = chidSet;
        auto _1485 = (uint64_t)5;
        auto _1503 = (uint64_t)12;
        auto _1506 = (uint64_t)11;
        auto _1509 = (uint64_t)10;
        auto _1512 = (uint64_t)9;
        auto _1515 = (uint64_t)8;
        auto _1516 = _Vec<uint64_t>::_NilV();
        auto _1513 = _Vec<uint64_t>::_ConsV(_1515, _1516);
        auto _1510 = _Vec<uint64_t>::_ConsV(_1512, _1513);
        auto _1507 = _Vec<uint64_t>::_ConsV(_1509, _1510);
        auto _1504 = _Vec<uint64_t>::_ConsV(_1506, _1507);
        auto _1486 = _Vec<uint64_t>::_ConsV(_1503, _1504);
        auto _1472 = runFarm<A>(_1476)(_1477)(_1478)(_1479)(_1480)(_1481)(_1482)(_1483)(_1484)(_1485)(_1486);
        auto _1473 = [inList, func, pidSet, chidSet](auto mresult3) {
          auto _1518 = [inList, func, pidSet, chidSet, mresult3]() {
            auto _1519 = mresult3;
            switch (_1519.type) {
              case Just: {
                auto _1521 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1519.data));
                auto result3 = _1521._1;
                auto _1520 = [inList, func, pidSet, chidSet, mresult3, result3]() {
                  auto _1522 = result3;
                  switch (_1522.type) {
                    case Prod: {
                      auto _1524 = *(std::static_pointer_cast<_Sigma_Prod<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1522.data));
                      auto pidStuff3 = _1524._1;
                      auto chidStuff3 = _1524._2;
                      auto _1523 = [inList, func, pidSet, chidSet, mresult3, result3, pidStuff3, chidStuff3]() {
                        auto _1525 = pidStuff3;
                        switch (_1525.type) {
                          case Prod: {
                            auto _1527 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1525.data));
                            auto pidSet3 = _1527._1;
                            auto pidSet3Pf = _1527._2;
                            auto _1526 = [inList, func, pidSet, chidSet, mresult3, result3, pidStuff3, chidStuff3, pidSet3]() {
                              auto _1528 = chidStuff3;
                              switch (_1528.type) {
                                case Prod: {
                                  auto _1530 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1528.data));
                                  auto chidSet3 = _1530._1;
                                  auto chidSet3Pf = _1530._2;
                                  auto _1535 = inList;
                                  auto _1536 = func;
                                  auto _1537 = (uint64_t)5;
                                  auto _1538 = (uint64_t)12;
                                  auto _1539 = pidSet3;
                                  auto _1540 = (uint64_t)6;
                                  auto _1547 = (uint64_t)18;
                                  auto _1550 = (uint64_t)17;
                                  auto _1553 = (uint64_t)16;
                                  auto _1556 = (uint64_t)15;
                                  auto _1559 = (uint64_t)14;
                                  auto _1562 = (uint64_t)13;
                                  auto _1563 = _Vec<uint64_t>::_NilV();
                                  auto _1560 = _Vec<uint64_t>::_ConsV(_1562, _1563);
                                  auto _1557 = _Vec<uint64_t>::_ConsV(_1559, _1560);
                                  auto _1554 = _Vec<uint64_t>::_ConsV(_1556, _1557);
                                  auto _1551 = _Vec<uint64_t>::_ConsV(_1553, _1554);
                                  auto _1548 = _Vec<uint64_t>::_ConsV(_1550, _1551);
                                  auto _1541 = _Vec<uint64_t>::_ConsV(_1547, _1548);
                                  auto _1542 = (uint64_t)12;
                                  auto _1543 = chidSet3;
                                  auto _1544 = (uint64_t)6;
                                  auto _1565 = (uint64_t)18;
                                  auto _1568 = (uint64_t)17;
                                  auto _1571 = (uint64_t)16;
                                  auto _1574 = (uint64_t)15;
                                  auto _1577 = (uint64_t)14;
                                  auto _1580 = (uint64_t)13;
                                  auto _1581 = _Vec<uint64_t>::_NilV();
                                  auto _1578 = _Vec<uint64_t>::_ConsV(_1580, _1581);
                                  auto _1575 = _Vec<uint64_t>::_ConsV(_1577, _1578);
                                  auto _1572 = _Vec<uint64_t>::_ConsV(_1574, _1575);
                                  auto _1569 = _Vec<uint64_t>::_ConsV(_1571, _1572);
                                  auto _1566 = _Vec<uint64_t>::_ConsV(_1568, _1569);
                                  auto _1545 = _Vec<uint64_t>::_ConsV(_1565, _1566);
                                  auto _1531 = runFarm<A>(_1535)(_1536)(_1537)(_1538)(_1539)(_1540)(_1541)(_1542)(_1543)(_1544)(_1545);
                                  auto _1532 = [inList, func, pidSet, chidSet, mresult3, result3, pidStuff3, chidStuff3, pidSet3, chidSet3](auto mresult4) {
                                    auto _1583 = [inList, func, pidSet, chidSet, mresult3, result3, pidStuff3, chidStuff3, pidSet3, chidSet3, mresult4]() {
                                      auto _1584 = mresult4;
                                      switch (_1584.type) {
                                        case Just: {
                                          auto _1586 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1584.data));
                                          auto result4 = _1586._1;
                                          auto _1585 = [inList, func, pidSet, chidSet, mresult3, result3, pidStuff3, chidStuff3, pidSet3, chidSet3, mresult4, result4]() {
                                            auto _1587 = result4;
                                            switch (_1587.type) {
                                              case Prod: {
                                                auto _1589 = *(std::static_pointer_cast<_Sigma_Prod<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1587.data));
                                                auto pidStuff4 = _1589._1;
                                                auto chidStuff4 = _1589._2;
                                                auto _1588 = [inList, func, pidSet, chidSet, mresult3, result3, pidStuff3, chidStuff3, pidSet3, chidSet3, mresult4, result4, pidStuff4, chidStuff4]() {
                                                  auto _1590 = pidStuff4;
                                                  switch (_1590.type) {
                                                    case Prod: {
                                                      auto _1592 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1590.data));
                                                      auto pidSet4 = _1592._1;
                                                      auto pidSet4Pf = _1592._2;
                                                      auto _1591 = [inList, func, pidSet, chidSet, mresult3, result3, pidStuff3, chidStuff3, pidSet3, chidSet3, mresult4, result4, pidStuff4,
                                                                    chidStuff4, pidSet4]() {
                                                        auto _1593 = chidStuff4;
                                                        switch (_1593.type) {
                                                          case Prod: {
                                                            auto _1595 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1593.data));
                                                            auto chidSet4 = _1595._1;
                                                            auto chidSet4Pf = _1595._2;
                                                            auto _1600 = inList;
                                                            auto _1601 = func;
                                                            auto _1602 = (uint64_t)6;
                                                            auto _1603 = (uint64_t)18;
                                                            auto _1604 = pidSet4;
                                                            auto _1605 = (uint64_t)7;
                                                            auto _1612 = (uint64_t)25;
                                                            auto _1615 = (uint64_t)24;
                                                            auto _1618 = (uint64_t)23;
                                                            auto _1621 = (uint64_t)22;
                                                            auto _1624 = (uint64_t)21;
                                                            auto _1627 = (uint64_t)20;
                                                            auto _1630 = (uint64_t)19;
                                                            auto _1631 = _Vec<uint64_t>::_NilV();
                                                            auto _1628 = _Vec<uint64_t>::_ConsV(_1630, _1631);
                                                            auto _1625 = _Vec<uint64_t>::_ConsV(_1627, _1628);
                                                            auto _1622 = _Vec<uint64_t>::_ConsV(_1624, _1625);
                                                            auto _1619 = _Vec<uint64_t>::_ConsV(_1621, _1622);
                                                            auto _1616 = _Vec<uint64_t>::_ConsV(_1618, _1619);
                                                            auto _1613 = _Vec<uint64_t>::_ConsV(_1615, _1616);
                                                            auto _1606 = _Vec<uint64_t>::_ConsV(_1612, _1613);
                                                            auto _1607 = (uint64_t)18;
                                                            auto _1608 = chidSet4;
                                                            auto _1609 = (uint64_t)7;
                                                            auto _1633 = (uint64_t)25;
                                                            auto _1636 = (uint64_t)24;
                                                            auto _1639 = (uint64_t)23;
                                                            auto _1642 = (uint64_t)22;
                                                            auto _1645 = (uint64_t)21;
                                                            auto _1648 = (uint64_t)20;
                                                            auto _1651 = (uint64_t)19;
                                                            auto _1652 = _Vec<uint64_t>::_NilV();
                                                            auto _1649 = _Vec<uint64_t>::_ConsV(_1651, _1652);
                                                            auto _1646 = _Vec<uint64_t>::_ConsV(_1648, _1649);
                                                            auto _1643 = _Vec<uint64_t>::_ConsV(_1645, _1646);
                                                            auto _1640 = _Vec<uint64_t>::_ConsV(_1642, _1643);
                                                            auto _1637 = _Vec<uint64_t>::_ConsV(_1639, _1640);
                                                            auto _1634 = _Vec<uint64_t>::_ConsV(_1636, _1637);
                                                            auto _1610 = _Vec<uint64_t>::_ConsV(_1633, _1634);
                                                            auto _1596 = runFarm<A>(_1600)(_1601)(_1602)(_1603)(_1604)(_1605)(_1606)(_1607)(_1608)(_1609)(_1610);
                                                            auto _1597 = end;
                                                            auto _1594 = bind<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>, _Unit>(_1596)(_1597);
                                                            return _1594;
                                                          }
                                                        }
                                                      }();
                                                      return _1591;
                                                    }
                                                  }
                                                }();
                                                return _1588;
                                              }
                                            }
                                          }();
                                          return _1585;
                                        }
                                        case Nothing: {
                                          auto _1655 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1584.data));
                                          auto _1654 = end;
                                          return _1654;
                                        }
                                      }
                                    }();
                                    return _1583;
                                  };
                                  auto _1529 = bindEq<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>, _Unit>(_1531)(_1532);
                                  return _1529;
                                }
                              }
                            }();
                            return _1526;
                          }
                        }
                      }();
                      return _1523;
                    }
                  }
                }();
                return _1520;
              }
              case Nothing: {
                auto _1657 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1519.data));
                auto _1656 = end;
                return _1656;
              }
            }
          }();
          return _1518;
        };
        auto _1471 = bindEq<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>, _Unit>(_1472)(_1473);
        return _1471;
      };
      return _1470;
    };
    return _1469;
  };
  return _1468;
};

template <class A>
std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_List<A>)> sixCoreTest = [](auto inList) {
  auto _1658 = [inList](auto func) {
    auto _1664 = inList;
    auto _1665 = func;
    auto _1660 = baseRun<A>(_1664)(_1665);
    auto _1671 = inList;
    auto _1672 = func;
    auto _1673 = (uint64_t)2;
    auto _1674 = (uint64_t)0;
    auto _1675 = _Vec<uint64_t>::_NilV();
    auto _1676 = (uint64_t)3;
    auto _1683 = (uint64_t)3;
    auto _1686 = (uint64_t)2;
    auto _1689 = (uint64_t)1;
    auto _1690 = _Vec<uint64_t>::_NilV();
    auto _1687 = _Vec<uint64_t>::_ConsV(_1689, _1690);
    auto _1684 = _Vec<uint64_t>::_ConsV(_1686, _1687);
    auto _1677 = _Vec<uint64_t>::_ConsV(_1683, _1684);
    auto _1678 = (uint64_t)0;
    auto _1679 = _Vec<uint64_t>::_NilV();
    auto _1680 = (uint64_t)3;
    auto _1692 = (uint64_t)3;
    auto _1695 = (uint64_t)2;
    auto _1698 = (uint64_t)1;
    auto _1699 = _Vec<uint64_t>::_NilV();
    auto _1696 = _Vec<uint64_t>::_ConsV(_1698, _1699);
    auto _1693 = _Vec<uint64_t>::_ConsV(_1695, _1696);
    auto _1681 = _Vec<uint64_t>::_ConsV(_1692, _1693);
    auto _1667 = runFarm<A>(_1671)(_1672)(_1673)(_1674)(_1675)(_1676)(_1677)(_1678)(_1679)(_1680)(_1681);
    auto _1668 = [inList, func](auto mResult1) {
      auto _1701 = [inList, func, mResult1]() {
        auto _1702 = mResult1;
        switch (_1702.type) {
          case Just: {
            auto _1704 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1702.data));
            auto result1 = _1704._1;
            auto _1703 = [inList, func, mResult1, result1]() {
              auto _1705 = result1;
              switch (_1705.type) {
                case Prod: {
                  auto _1707 = *(std::static_pointer_cast<_Sigma_Prod<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1705.data));
                  auto pidStuff1 = _1707._1;
                  auto chidStuff1 = _1707._2;
                  auto _1706 = [inList, func, mResult1, result1, pidStuff1, chidStuff1]() {
                    auto _1708 = pidStuff1;
                    switch (_1708.type) {
                      case Prod: {
                        auto _1710 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1708.data));
                        auto pidSet1 = _1710._1;
                        auto pidSet1Pf = _1710._2;
                        auto _1709 = [inList, func, mResult1, result1, pidStuff1, chidStuff1, pidSet1]() {
                          auto _1711 = chidStuff1;
                          switch (_1711.type) {
                            case Prod: {
                              auto _1713 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1711.data));
                              auto chidSet1 = _1713._1;
                              auto chidSet1Pf = _1713._2;
                              auto _1718 = inList;
                              auto _1719 = func;
                              auto _1720 = (uint64_t)3;
                              auto _1721 = (uint64_t)3;
                              auto _1722 = pidSet1;
                              auto _1723 = (uint64_t)4;
                              auto _1730 = (uint64_t)7;
                              auto _1733 = (uint64_t)6;
                              auto _1736 = (uint64_t)5;
                              auto _1739 = (uint64_t)4;
                              auto _1740 = _Vec<uint64_t>::_NilV();
                              auto _1737 = _Vec<uint64_t>::_ConsV(_1739, _1740);
                              auto _1734 = _Vec<uint64_t>::_ConsV(_1736, _1737);
                              auto _1731 = _Vec<uint64_t>::_ConsV(_1733, _1734);
                              auto _1724 = _Vec<uint64_t>::_ConsV(_1730, _1731);
                              auto _1725 = (uint64_t)3;
                              auto _1726 = chidSet1;
                              auto _1727 = (uint64_t)4;
                              auto _1742 = (uint64_t)7;
                              auto _1745 = (uint64_t)6;
                              auto _1748 = (uint64_t)5;
                              auto _1751 = (uint64_t)4;
                              auto _1752 = _Vec<uint64_t>::_NilV();
                              auto _1749 = _Vec<uint64_t>::_ConsV(_1751, _1752);
                              auto _1746 = _Vec<uint64_t>::_ConsV(_1748, _1749);
                              auto _1743 = _Vec<uint64_t>::_ConsV(_1745, _1746);
                              auto _1728 = _Vec<uint64_t>::_ConsV(_1742, _1743);
                              auto _1714 = runFarm<A>(_1718)(_1719)(_1720)(_1721)(_1722)(_1723)(_1724)(_1725)(_1726)(_1727)(_1728);
                              auto _1715 = [inList, func, mResult1, result1, pidStuff1, chidStuff1, pidSet1, chidSet1](auto mResult2) {
                                auto _1754 = [inList, func, mResult1, result1, pidStuff1, chidStuff1, pidSet1, chidSet1, mResult2]() {
                                  auto _1755 = mResult2;
                                  switch (_1755.type) {
                                    case Just: {
                                      auto _1757 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1755.data));
                                      auto result2 = _1757._1;
                                      auto _1756 = [inList, func, mResult1, result1, pidStuff1, chidStuff1, pidSet1, chidSet1, mResult2, result2]() {
                                        auto _1758 = result2;
                                        switch (_1758.type) {
                                          case Prod: {
                                            auto _1760 = *(std::static_pointer_cast<_Sigma_Prod<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1758.data));
                                            auto pidStuff2 = _1760._1;
                                            auto chidStuff2 = _1760._2;
                                            auto _1759 = [inList, func, mResult1, result1, pidStuff1, chidStuff1, pidSet1, chidSet1, mResult2, result2, pidStuff2, chidStuff2]() {
                                              auto _1761 = pidStuff2;
                                              switch (_1761.type) {
                                                case Prod: {
                                                  auto _1763 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1761.data));
                                                  auto pidSet2 = _1763._1;
                                                  auto pidSet2Pf = _1763._2;
                                                  auto _1762 = [inList, func, mResult1, result1, pidStuff1, chidStuff1, pidSet1, chidSet1, mResult2, result2, pidStuff2, chidStuff2, pidSet2]() {
                                                    auto _1764 = chidStuff2;
                                                    switch (_1764.type) {
                                                      case Prod: {
                                                        auto _1766 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1764.data));
                                                        auto chidSet2 = _1766._1;
                                                        auto chidSet2Pf = _1766._2;
                                                        auto _1767 = inList;
                                                        auto _1768 = func;
                                                        auto _1769 = pidSet2;
                                                        auto _1770 = chidSet2;
                                                        auto _1765 = sixCoreTest2<A>(_1767)(_1768)(_1769)(_1770);
                                                        return _1765;
                                                      }
                                                    }
                                                  }();
                                                  return _1762;
                                                }
                                              }
                                            }();
                                            return _1759;
                                          }
                                        }
                                      }();
                                      return _1756;
                                    }
                                    case Nothing: {
                                      auto _1773 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1755.data));
                                      auto _1772 = end;
                                      return _1772;
                                    }
                                  }
                                }();
                                return _1754;
                              };
                              auto _1712 = bindEq<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>, _Unit>(_1714)(_1715);
                              return _1712;
                            }
                          }
                        }();
                        return _1709;
                      }
                    }
                  }();
                  return _1706;
                }
              }
            }();
            return _1703;
          }
          case Nothing: {
            auto _1775 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1702.data));
            auto _1774 = end;
            return _1774;
          }
        }
      }();
      return _1701;
    };
    auto _1661 = bindEq<_Maybe<_Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>, _Unit>(_1667)(_1668);
    auto _1659 = bind<_Unit, _Unit>(_1660)(_1661);
    return _1659;
  };
  return _1658;
};

_IO<_Unit> mainFunc = []() {
  auto _1780 = (uint64_t)42;
  auto _1782 = (uint64_t)42;
  auto _1784 = (uint64_t)42;
  auto _1786 = (uint64_t)42;
  auto _1788 = (uint64_t)42;
  auto _1790 = (uint64_t)42;
  auto _1792 = (uint64_t)42;
  auto _1794 = (uint64_t)42;
  auto _1796 = (uint64_t)42;
  auto _1798 = (uint64_t)42;
  auto _1800 = (uint64_t)42;
  auto _1802 = (uint64_t)42;
  auto _1804 = (uint64_t)42;
  auto _1806 = (uint64_t)42;
  auto _1808 = (uint64_t)42;
  auto _1810 = (uint64_t)42;
  auto _1812 = (uint64_t)42;
  auto _1814 = (uint64_t)42;
  auto _1816 = (uint64_t)42;
  auto _1818 = (uint64_t)42;
  auto _1820 = (uint64_t)42;
  auto _1822 = (uint64_t)42;
  auto _1824 = (uint64_t)42;
  auto _1826 = (uint64_t)42;
  auto _1828 = (uint64_t)42;
  auto _1830 = (uint64_t)42;
  auto _1832 = (uint64_t)42;
  auto _1834 = (uint64_t)42;
  auto _1836 = (uint64_t)42;
  auto _1838 = (uint64_t)42;
  auto _1840 = (uint64_t)42;
  auto _1842 = (uint64_t)42;
  auto _1844 = (uint64_t)42;
  auto _1846 = (uint64_t)42;
  auto _1848 = (uint64_t)42;
  auto _1850 = (uint64_t)42;
  auto _1852 = (uint64_t)42;
  auto _1854 = (uint64_t)42;
  auto _1856 = (uint64_t)42;
  auto _1858 = (uint64_t)42;
  auto _1860 = (uint64_t)42;
  auto _1862 = (uint64_t)42;
  auto _1864 = (uint64_t)42;
  auto _1866 = (uint64_t)42;
  auto _1868 = (uint64_t)42;
  auto _1870 = (uint64_t)42;
  auto _1872 = (uint64_t)42;
  auto _1874 = (uint64_t)42;
  auto _1876 = (uint64_t)42;
  auto _1878 = (uint64_t)42;
  auto _1880 = (uint64_t)42;
  auto _1882 = (uint64_t)42;
  auto _1884 = (uint64_t)42;
  auto _1886 = (uint64_t)42;
  auto _1888 = (uint64_t)42;
  auto _1890 = (uint64_t)42;
  auto _1892 = (uint64_t)42;
  auto _1894 = (uint64_t)42;
  auto _1896 = (uint64_t)42;
  auto _1898 = (uint64_t)42;
  auto _1899 = _List<uint64_t>::_Nil();
  auto _1897 = _List<uint64_t>::_Cons(_1898, _1899);
  auto _1895 = _List<uint64_t>::_Cons(_1896, _1897);
  auto _1893 = _List<uint64_t>::_Cons(_1894, _1895);
  auto _1891 = _List<uint64_t>::_Cons(_1892, _1893);
  auto _1889 = _List<uint64_t>::_Cons(_1890, _1891);
  auto _1887 = _List<uint64_t>::_Cons(_1888, _1889);
  auto _1885 = _List<uint64_t>::_Cons(_1886, _1887);
  auto _1883 = _List<uint64_t>::_Cons(_1884, _1885);
  auto _1881 = _List<uint64_t>::_Cons(_1882, _1883);
  auto _1879 = _List<uint64_t>::_Cons(_1880, _1881);
  auto _1877 = _List<uint64_t>::_Cons(_1878, _1879);
  auto _1875 = _List<uint64_t>::_Cons(_1876, _1877);
  auto _1873 = _List<uint64_t>::_Cons(_1874, _1875);
  auto _1871 = _List<uint64_t>::_Cons(_1872, _1873);
  auto _1869 = _List<uint64_t>::_Cons(_1870, _1871);
  auto _1867 = _List<uint64_t>::_Cons(_1868, _1869);
  auto _1865 = _List<uint64_t>::_Cons(_1866, _1867);
  auto _1863 = _List<uint64_t>::_Cons(_1864, _1865);
  auto _1861 = _List<uint64_t>::_Cons(_1862, _1863);
  auto _1859 = _List<uint64_t>::_Cons(_1860, _1861);
  auto _1857 = _List<uint64_t>::_Cons(_1858, _1859);
  auto _1855 = _List<uint64_t>::_Cons(_1856, _1857);
  auto _1853 = _List<uint64_t>::_Cons(_1854, _1855);
  auto _1851 = _List<uint64_t>::_Cons(_1852, _1853);
  auto _1849 = _List<uint64_t>::_Cons(_1850, _1851);
  auto _1847 = _List<uint64_t>::_Cons(_1848, _1849);
  auto _1845 = _List<uint64_t>::_Cons(_1846, _1847);
  auto _1843 = _List<uint64_t>::_Cons(_1844, _1845);
  auto _1841 = _List<uint64_t>::_Cons(_1842, _1843);
  auto _1839 = _List<uint64_t>::_Cons(_1840, _1841);
  auto _1837 = _List<uint64_t>::_Cons(_1838, _1839);
  auto _1835 = _List<uint64_t>::_Cons(_1836, _1837);
  auto _1833 = _List<uint64_t>::_Cons(_1834, _1835);
  auto _1831 = _List<uint64_t>::_Cons(_1832, _1833);
  auto _1829 = _List<uint64_t>::_Cons(_1830, _1831);
  auto _1827 = _List<uint64_t>::_Cons(_1828, _1829);
  auto _1825 = _List<uint64_t>::_Cons(_1826, _1827);
  auto _1823 = _List<uint64_t>::_Cons(_1824, _1825);
  auto _1821 = _List<uint64_t>::_Cons(_1822, _1823);
  auto _1819 = _List<uint64_t>::_Cons(_1820, _1821);
  auto _1817 = _List<uint64_t>::_Cons(_1818, _1819);
  auto _1815 = _List<uint64_t>::_Cons(_1816, _1817);
  auto _1813 = _List<uint64_t>::_Cons(_1814, _1815);
  auto _1811 = _List<uint64_t>::_Cons(_1812, _1813);
  auto _1809 = _List<uint64_t>::_Cons(_1810, _1811);
  auto _1807 = _List<uint64_t>::_Cons(_1808, _1809);
  auto _1805 = _List<uint64_t>::_Cons(_1806, _1807);
  auto _1803 = _List<uint64_t>::_Cons(_1804, _1805);
  auto _1801 = _List<uint64_t>::_Cons(_1802, _1803);
  auto _1799 = _List<uint64_t>::_Cons(_1800, _1801);
  auto _1797 = _List<uint64_t>::_Cons(_1798, _1799);
  auto _1795 = _List<uint64_t>::_Cons(_1796, _1797);
  auto _1793 = _List<uint64_t>::_Cons(_1794, _1795);
  auto _1791 = _List<uint64_t>::_Cons(_1792, _1793);
  auto _1789 = _List<uint64_t>::_Cons(_1790, _1791);
  auto _1787 = _List<uint64_t>::_Cons(_1788, _1789);
  auto _1785 = _List<uint64_t>::_Cons(_1786, _1787);
  auto _1783 = _List<uint64_t>::_Cons(_1784, _1785);
  auto _1781 = _List<uint64_t>::_Cons(_1782, _1783);
  auto _1777 = _List<uint64_t>::_Cons(_1780, _1781);
  auto _1778 = fib;
  auto _1776 = sixCoreTest<uint64_t>(_1777)(_1778);
  return _1776;
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