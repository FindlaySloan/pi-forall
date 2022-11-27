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
  auto _133 = [x]() {
    auto _134 = x;
    if (!_134) {
      auto _135 = (uint64_t)1;
      return _135;
    } else {
      auto y = _134 - 1;
      auto _135 = [x, y]() {
        auto _136 = y;
        if (!_136) {
          auto _137 = (uint64_t)1;
          return _137;
        } else {
          auto z = _136 - 1;
          auto _140 = y;
          auto _138 = fib(_140);
          auto _141 = z;
          auto _139 = fib(_141);
          auto _137 = plus(_138)(_139);
          return _137;
        }
      }();
      return _135;
    }
  }();
  return _133;
};

std::function<uint64_t(uint64_t)> fact = [](auto n) {
  auto _142 = [n]() {
    auto _143 = n;
    if (!_143) {
      auto _144 = (uint64_t)1;
      return _144;
    } else {
      auto m = _143 - 1;
      auto _145 = n;
      auto _147 = m;
      auto _146 = fact(_147);
      auto _144 = mult(_145)(_146);
      return _144;
    }
  }();
  return _142;
};

template <class A>
std::function<std::function<_Vec<A>(_Vec<A>)>(_Vec<A>)> append = [](auto v1) {
  auto _148 = [v1](auto ys) {
    auto _149 = [v1, ys]() {
      auto _150 = v1;
      switch (_150.type) {
        case ConsV: {
          auto _152 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_150.data));
          auto x = _152._1;
          auto xs = _152._2;
          auto _153 = x;
          auto _156 = xs;
          auto _157 = ys;
          auto _154 = append<A>(_156)(_157);
          auto _151 = _Vec<A>::_ConsV(_153, _154);
          return _151;
        }
        case NilV: {
          auto _162 = *(std::static_pointer_cast<_Vec_NilV<A>>(_150.data));
          auto _161 = ys;
          return _161;
        }
      }
    }();
    return _149;
  };
  return _148;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> trans = [](auto pf1) {
  auto _163 = [pf1](auto pf2) {
    auto _165 = pf1;
    auto _164 = _165;
    return _164;
  };
  return _163;
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
  auto _166 = [p]() {
    auto _167 = p;
    return _Void();
  }();
  return _166;
};

std::function<std::function<std::function<_Void(_ElemVec<uint64_t>)>(std::function<_Void(_ElemVec<uint64_t>)>)>(std::function<_Void(_TyEq)>)> neitherHereNorThereVec = [](auto xneqy) {
  auto _168 = [xneqy](auto xninxs) {
    auto _169 = [xneqy, xninxs](auto p) {
      auto _170 = [p, xneqy, xninxs]() {
        auto _171 = p;
        switch (_171.type) {
          case HereV: {
            auto _173 = *(std::static_pointer_cast<_ElemVec_HereV<uint64_t>>(_171.data));
            auto as = _173._1;
            auto _174 = _TyEq::_Refl();
            auto _172 = xneqy(_174);
            return _172;
          }
          case ThereV: {
            auto _176 = *(std::static_pointer_cast<_ElemVec_ThereV<uint64_t>>(_171.data));
            auto as = _176._1;
            auto b = _176._2;
            auto prf = _176._3;
            auto _177 = prf;
            auto _175 = xninxs(_177);
            return _175;
          }
        }
      }();
      return _170;
    };
    return _169;
  };
  return _168;
};

std::function<std::function<_Dec<_ElemVec<uint64_t>>(_Vec<uint64_t>)>(uint64_t)> isElemVec = [](auto x) {
  auto _178 = [x](auto xs) {
    auto _179 = [xs, x]() {
      auto _180 = xs;
      switch (_180.type) {
        case NilV: {
          auto _182 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_180.data));
          auto _183 = xNotInNilV<uint64_t>;
          auto _181 = _Dec<_ElemVec<uint64_t>>::_No(_183);
          return _181;
        }
        case ConsV: {
          auto _188 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_180.data));
          auto y = _188._1;
          auto ys = _188._2;
          auto _187 = [xs, x, y, ys]() {
            auto _190 = x;
            auto _191 = y;
            auto _189 = decEqNat(_190)(_191);
            switch (_189.type) {
              case Yes: {
                auto _193 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_189.data));
                auto pf = _193._1;
                auto _196 = ys;
                auto _195 = _ElemVec<uint64_t>::_HereV(_196);
                auto _194 = _195;
                auto _192 = _Dec<_ElemVec<uint64_t>>::_Yes(_194);
                return _192;
              }
              case No: {
                auto _199 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_189.data));
                auto xneqyPf = _199._1;
                auto _198 = [xs, x, y, ys, xneqyPf]() {
                  auto _201 = x;
                  auto _202 = ys;
                  auto _200 = isElemVec(_201)(_202);
                  switch (_200.type) {
                    case Yes: {
                      auto _205 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_200.data));
                      auto pf = _205._1;
                      auto _207 = ys;
                      auto _208 = x;
                      auto _209 = pf;
                      auto _206 = _ElemVec<uint64_t>::_ThereV(_207, _208, _209);
                      auto _204 = _Dec<_ElemVec<uint64_t>>::_Yes(_206);
                      return _204;
                    }
                    case No: {
                      auto _212 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_200.data));
                      auto xninysPf = _212._1;
                      auto _214 = xneqyPf;
                      auto _215 = xninysPf;
                      auto _213 = neitherHereNorThereVec(_214)(_215);
                      auto _211 = _Dec<_ElemVec<uint64_t>>::_No(_213);
                      return _211;
                    }
                  }
                }();
                return _198;
              }
            }
          }();
          return _187;
        }
      }
    }();
    return _179;
  };
  return _178;
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
  auto _220 = [p]() {
    auto _221 = p;
    return _Void();
  }();
  return _220;
};

template <class A>
std::function<std::function<_Disjoint<A>(_TyEq)>(_List<A>)> lemma_y_empty_disjoint = [](auto a) {
  auto _222 = [a](auto pf) {
    auto _223 = [a, pf]() {
      auto _224 = a;
      switch (_224.type) {
        case Nil: {
          auto _226 = *(std::static_pointer_cast<_List_Nil<A>>(_224.data));
          auto _225 = _Disjoint<A>::_DNil();
          return _225;
        }
        case Cons: {
          auto _228 = *(std::static_pointer_cast<_List_Cons<A>>(_224.data));
          auto x = _228._1;
          auto xs = _228._2;
          auto _229 = x;
          auto _230 = xs;
          auto _233 = xNotInNil<A>;
          auto _231 = _233;
          auto _236 = xs;
          auto _237 = pf;
          auto _232 = lemma_y_empty_disjoint<A>(_236)(_237);
          auto _227 = _Disjoint<A>::_DCons(_229, _230, _231, _232);
          return _227;
        }
      }
    }();
    return _223;
  };
  return _222;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(_Elem<A>)> lemma_x_in_b = [](auto xInB) {
  auto _240 = [xInB](auto pf) {
    auto _241 = [pf, xInB]() {
      auto _242 = pf;
      switch (_242.type) {
        case DCons: {
          auto _244 = *(std::static_pointer_cast<_Disjoint_DCons<A>>(_242.data));
          auto i = _244._1;
          auto is = _244._2;
          auto pfFori = _244._3;
          auto others = _244._4;
          auto _245 = xInB;
          auto _243 = pfFori(_245);
          return _243;
        }
      }
    }();
    return _241;
  };
  return _240;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(std::function<_Void(_Disjoint<A>)>)> lemma_xs_in_b = [](auto pf) {
  auto _246 = [pf](auto p) {
    auto _247 = [p, pf]() {
      auto _248 = p;
      switch (_248.type) {
        case DCons: {
          auto _250 = *(std::static_pointer_cast<_Disjoint_DCons<A>>(_248.data));
          auto i = _250._1;
          auto is = _250._2;
          auto pfFori = _250._3;
          auto others = _250._4;
          auto _251 = others;
          auto _249 = pf(_251);
          return _249;
        }
      }
    }();
    return _247;
  };
  return _246;
};

std::function<std::function<_Dec<_Disjoint<uint64_t>>(_List<uint64_t>)>(_List<uint64_t>)> decDisjointLists = [](auto a) {
  auto _252 = [a](auto b) {
    auto _253 = [a, b]() {
      auto _254 = a;
      switch (_254.type) {
        case Nil: {
          auto _256 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_254.data));
          auto _257 = _Disjoint<uint64_t>::_DNil();
          auto _255 = _Dec<_Disjoint<uint64_t>>::_Yes(_257);
          return _255;
        }
        case Cons: {
          auto _259 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_254.data));
          auto x = _259._1;
          auto xs = _259._2;
          auto _258 = [a, b, xs, x]() {
            auto _260 = b;
            switch (_260.type) {
              case Nil: {
                auto _262 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_260.data));
                auto _264 = a;
                auto _265 = _TyEq::_Refl();
                auto _263 = lemma_y_empty_disjoint<uint64_t>(_264)(_265);
                auto _261 = _Dec<_Disjoint<uint64_t>>::_Yes(_263);
                return _261;
              }
              case Cons: {
                auto _269 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_260.data));
                auto y = _269._1;
                auto ys = _269._2;
                auto _268 = [a, b, xs, x]() {
                  auto _271 = xs;
                  auto _272 = b;
                  auto _270 = decDisjointLists(_271)(_272);
                  switch (_270.type) {
                    case Yes: {
                      auto _274 = *(std::static_pointer_cast<_Dec_Yes<_Disjoint<uint64_t>>>(_270.data));
                      auto pf = _274._1;
                      auto _273 = [a, b, xs, x, pf]() {
                        auto _276 = x;
                        auto _277 = b;
                        auto _275 = isElem(_276)(_277);
                        switch (_275.type) {
                          case Yes: {
                            auto _279 = *(std::static_pointer_cast<_Dec_Yes<_Elem<uint64_t>>>(_275.data));
                            auto elemPf = _279._1;
                            auto _281 = elemPf;
                            auto _280 = lemma_x_in_b<uint64_t>(_281);
                            auto _278 = _Dec<_Disjoint<uint64_t>>::_No(_280);
                            return _278;
                          }
                          case No: {
                            auto _288 = *(std::static_pointer_cast<_Dec_No<_Elem<uint64_t>>>(_275.data));
                            auto p = _288._1;
                            auto _290 = x;
                            auto _291 = xs;
                            auto _292 = p;
                            auto _293 = pf;
                            auto _289 = _Disjoint<uint64_t>::_DCons(_290, _291, _292, _293);
                            auto _287 = _Dec<_Disjoint<uint64_t>>::_Yes(_289);
                            return _287;
                          }
                        }
                      }();
                      return _273;
                    }
                    case No: {
                      auto _295 = *(std::static_pointer_cast<_Dec_No<_Disjoint<uint64_t>>>(_270.data));
                      auto p = _295._1;
                      auto _297 = p;
                      auto _296 = lemma_xs_in_b<uint64_t>(_297);
                      auto _294 = _Dec<_Disjoint<uint64_t>>::_No(_296);
                      return _294;
                    }
                  }
                }();
                return _268;
              }
            }
          }();
          return _258;
        }
      }
    }();
    return _253;
  };
  return _252;
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
  auto _302 = [a](auto pf) {
    auto _303 = [a, pf]() {
      auto _304 = a;
      switch (_304.type) {
        case NilV: {
          auto _306 = *(std::static_pointer_cast<_Vec_NilV<A>>(_304.data));
          auto _305 = _DisjointVec<A>::_DNilV();
          return _305;
        }
        case ConsV: {
          auto _308 = *(std::static_pointer_cast<_Vec_ConsV<A>>(_304.data));
          auto x = _308._1;
          auto xs = _308._2;
          auto _309 = x;
          auto _310 = xs;
          auto _314 = xNotInNilV<A>;
          auto _311 = _314;
          auto _318 = xs;
          auto _319 = pf;
          auto _312 = lemma_y_empty_disjoint_vec<A>(_318)(_319);
          auto _307 = _DisjointVec<A>::_DConsV(_309, _310, _311, _312);
          return _307;
        }
      }
    }();
    return _303;
  };
  return _302;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(_ElemVec<A>)> lemma_x_in_b_vec = [](auto xInB) {
  auto _323 = [xInB](auto pf) {
    auto _324 = [pf, xInB]() {
      auto _325 = pf;
      switch (_325.type) {
        case DConsV: {
          auto _327 = *(std::static_pointer_cast<_DisjointVec_DConsV<A>>(_325.data));
          auto y = _327._1;
          auto ys = _327._2;
          auto pfFory = _327._3;
          auto others = _327._4;
          auto _328 = xInB;
          auto _326 = pfFory(_328);
          return _326;
        }
      }
    }();
    return _324;
  };
  return _323;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(std::function<_Void(_DisjointVec<A>)>)> lemma_xs_in_b_vec = [](auto pf) {
  auto _329 = [pf](auto p) {
    auto _330 = [p, pf]() {
      auto _331 = p;
      switch (_331.type) {
        case DConsV: {
          auto _333 = *(std::static_pointer_cast<_DisjointVec_DConsV<A>>(_331.data));
          auto i = _333._1;
          auto is = _333._2;
          auto pfFori = _333._3;
          auto others = _333._4;
          auto _334 = others;
          auto _332 = pf(_334);
          return _332;
        }
      }
    }();
    return _330;
  };
  return _329;
};

std::function<std::function<_Dec<_DisjointVec<uint64_t>>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decDisjointVecs = [](auto a) {
  auto _335 = [a](auto b) {
    auto _336 = [a, b]() {
      auto _337 = a;
      switch (_337.type) {
        case NilV: {
          auto _339 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_337.data));
          auto _340 = _DisjointVec<uint64_t>::_DNilV();
          auto _338 = _Dec<_DisjointVec<uint64_t>>::_Yes(_340);
          return _338;
        }
        case ConsV: {
          auto _342 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_337.data));
          auto x = _342._1;
          auto xs = _342._2;
          auto _341 = [a, b, xs, x]() {
            auto _343 = b;
            switch (_343.type) {
              case NilV: {
                auto _345 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_343.data));
                auto _347 = a;
                auto _348 = _TyEq::_Refl();
                auto _346 = lemma_y_empty_disjoint_vec<uint64_t>(_347)(_348);
                auto _344 = _Dec<_DisjointVec<uint64_t>>::_Yes(_346);
                return _344;
              }
              case ConsV: {
                auto _353 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_343.data));
                auto y = _353._1;
                auto ys = _353._2;
                auto _352 = [a, b, xs, x]() {
                  auto _355 = xs;
                  auto _356 = b;
                  auto _354 = decDisjointVecs(_355)(_356);
                  switch (_354.type) {
                    case Yes: {
                      auto _360 = *(std::static_pointer_cast<_Dec_Yes<_DisjointVec<uint64_t>>>(_354.data));
                      auto pf = _360._1;
                      auto _359 = [a, b, xs, x, pf]() {
                        auto _362 = x;
                        auto _363 = b;
                        auto _361 = isElemVec(_362)(_363);
                        switch (_361.type) {
                          case Yes: {
                            auto _366 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_361.data));
                            auto elemPf = _366._1;
                            auto _368 = elemPf;
                            auto _367 = lemma_x_in_b_vec<uint64_t>(_368);
                            auto _365 = _Dec<_DisjointVec<uint64_t>>::_No(_367);
                            return _365;
                          }
                          case No: {
                            auto _377 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_361.data));
                            auto p = _377._1;
                            auto _379 = x;
                            auto _380 = xs;
                            auto _381 = p;
                            auto _382 = pf;
                            auto _378 = _DisjointVec<uint64_t>::_DConsV(_379, _380, _381, _382);
                            auto _376 = _Dec<_DisjointVec<uint64_t>>::_Yes(_378);
                            return _376;
                          }
                        }
                      }();
                      return _359;
                    }
                    case No: {
                      auto _385 = *(std::static_pointer_cast<_Dec_No<_DisjointVec<uint64_t>>>(_354.data));
                      auto p = _385._1;
                      auto _387 = p;
                      auto _386 = lemma_xs_in_b_vec<uint64_t>(_387);
                      auto _384 = _Dec<_DisjointVec<uint64_t>>::_No(_386);
                      return _384;
                    }
                  }
                }();
                return _352;
              }
            }
          }();
          return _341;
        }
      }
    }();
    return _336;
  };
  return _335;
};

std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjLem = [](auto prf1) {
  auto _394 = [](auto prf2) {
    auto _397 = prf2;
    auto _396 = f_equal<_Vec<uint64_t>, _Vec<uint64_t>>(_397);
    auto _395 = _396;
    return _395;
  };
  return _394;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjective = [](auto p1) {
  auto _403 = [](auto p2) {
    auto _406 = p2;
    auto _405 = f_equal<_Vec<A>, _Vec<A>>(_406);
    auto _404 = _405;
    return _404;
  };
  return _403;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjectiveTail = [](auto p1) {
  auto _412 = [](auto p2) {
    auto _414 = p2;
    auto _413 = f_equal<_Vec<A>, A>(_414);
    return _413;
  };
  return _412;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(_TyEq)> lemma_x_eq_xs_neq_vec = [](auto prf1) {
  auto _420 = [prf1](auto p) {
    auto _421 = [p, prf1](auto prf2) {
      auto _424 = prf1;
      auto _425 = prf2;
      auto _423 = consVInjective<A>(_424)(_425);
      auto _422 = p(_423);
      return _422;
    };
    return _421;
  };
  return _420;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(_TyEq)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_eq_vec = [](auto p) {
  auto _432 = [p](auto p2) {
    auto _433 = [p, p2](auto p3) {
      auto _436 = p2;
      auto _437 = p3;
      auto _435 = consVInjectiveTail<A>(_436)(_437);
      auto _434 = p(_435);
      return _434;
    };
    return _433;
  };
  return _432;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_neq_vec = [](auto p) {
  auto _444 = [p](auto p2) {
    auto _445 = [p](auto p3) {
      auto _448 = p3;
      auto _447 = f_equal<_Vec<A>, A>(_448);
      auto _446 = p(_447);
      return _446;
    };
    return _445;
  };
  return _444;
};

std::function<std::function<_Dec<_TyEq>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decEqVec = [](auto a) {
  auto _454 = [a](auto b) {
    auto _455 = [a, b]() {
      auto _456 = a;
      switch (_456.type) {
        case NilV: {
          auto _458 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_456.data));
          auto _457 = [a, b]() {
            auto _459 = b;
            switch (_459.type) {
              case NilV: {
                auto _461 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_459.data));
                auto _462 = _TyEq::_Refl();
                auto _460 = _Dec<_TyEq>::_Yes(_462);
                return _460;
              }
            }
          }();
          return _457;
        }
        case ConsV: {
          auto _464 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_456.data));
          auto x = _464._1;
          auto xs = _464._2;
          auto _463 = [a, b, x, xs]() {
            auto _465 = b;
            switch (_465.type) {
              case ConsV: {
                auto _467 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_465.data));
                auto y = _467._1;
                auto ys = _467._2;
                auto _466 = [a, b, x, y, xs, ys]() {
                  auto _469 = x;
                  auto _470 = y;
                  auto _468 = decEqNat(_469)(_470);
                  switch (_468.type) {
                    case Yes: {
                      auto _472 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_468.data));
                      auto xeqy = _472._1;
                      auto _471 = [a, b, x, y, xs, ys, xeqy]() {
                        auto _474 = xs;
                        auto _475 = ys;
                        auto _473 = decEqVec(_474)(_475);
                        switch (_473.type) {
                          case Yes: {
                            auto _478 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_473.data));
                            auto xseqys = _478._1;
                            auto _480 = xeqy;
                            auto _481 = xseqys;
                            auto _479 = consVInjLem(_480)(_481);
                            auto _477 = _Dec<_TyEq>::_Yes(_479);
                            return _477;
                          }
                          case No: {
                            auto _488 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_473.data));
                            auto xsneqys = _488._1;
                            auto _490 = xeqy;
                            auto _491 = xsneqys;
                            auto _489 = lemma_x_eq_xs_neq_vec<uint64_t>(_490)(_491);
                            auto _487 = _Dec<_TyEq>::_No(_489);
                            return _487;
                          }
                        }
                      }();
                      return _471;
                    }
                    case No: {
                      auto _499 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_468.data));
                      auto xneqy = _499._1;
                      auto _498 = [a, b, x, y, xs, ys, xneqy]() {
                        auto _501 = xs;
                        auto _502 = ys;
                        auto _500 = decEqVec(_501)(_502);
                        switch (_500.type) {
                          case Yes: {
                            auto _505 = *(std::static_pointer_cast<_Dec_Yes<_TyEq>>(_500.data));
                            auto xseqys = _505._1;
                            auto _507 = xneqy;
                            auto _508 = xseqys;
                            auto _506 = lemma_x_neq_xs_eq_vec<uint64_t>(_507)(_508);
                            auto _504 = _Dec<_TyEq>::_No(_506);
                            return _504;
                          }
                          case No: {
                            auto _516 = *(std::static_pointer_cast<_Dec_No<_TyEq>>(_500.data));
                            auto xsneqys = _516._1;
                            auto _518 = xneqy;
                            auto _519 = xsneqys;
                            auto _517 = lemma_x_neq_xs_neq_vec<uint64_t>(_518)(_519);
                            auto _515 = _Dec<_TyEq>::_No(_517);
                            return _515;
                          }
                        }
                      }();
                      return _498;
                    }
                  }
                }();
                return _466;
              }
            }
          }();
          return _463;
        }
      }
    }();
    return _455;
  };
  return _454;
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
  auto _526 = [pf](auto p) {
    auto _527 = [p, pf]() {
      auto _528 = p;
      switch (_528.type) {
        case UConsV: {
          auto _530 = *(std::static_pointer_cast<_UniqueVec_UConsV<A>>(_528.data));
          auto x = _530._1;
          auto xs = _530._2;
          auto xNInXs = _530._3;
          auto others = _530._4;
          auto _531 = pf;
          auto _529 = xNInXs(_531);
          return _529;
        }
      }
    }();
    return _527;
  };
  return _526;
};

template <class A>
std::function<std::function<_Void(_UniqueVec<A>)>(std::function<_Void(_UniqueVec<A>)>)> lemma_xs_not_unique = [](auto pf) {
  auto _532 = [pf](auto p) {
    auto _533 = [p, pf]() {
      auto _534 = p;
      switch (_534.type) {
        case UConsV: {
          auto _536 = *(std::static_pointer_cast<_UniqueVec_UConsV<A>>(_534.data));
          auto x = _536._1;
          auto xs = _536._2;
          auto xNInXs = _536._3;
          auto others = _536._4;
          auto _537 = others;
          auto _535 = pf(_537);
          return _535;
        }
      }
    }();
    return _533;
  };
  return _532;
};

std::function<_Dec<_UniqueVec<uint64_t>>(_Vec<uint64_t>)> decUniqueVec = [](auto v) {
  auto _538 = [v]() {
    auto _539 = v;
    switch (_539.type) {
      case NilV: {
        auto _541 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_539.data));
        auto _542 = _UniqueVec<uint64_t>::_UNilV();
        auto _540 = _Dec<_UniqueVec<uint64_t>>::_Yes(_542);
        return _540;
      }
      case ConsV: {
        auto _544 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_539.data));
        auto x = _544._1;
        auto xs = _544._2;
        auto _543 = [v, x, xs]() {
          auto _546 = x;
          auto _547 = xs;
          auto _545 = isElemVec(_546)(_547);
          switch (_545.type) {
            case Yes: {
              auto _550 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_545.data));
              auto xInXs = _550._1;
              auto _552 = xInXs;
              auto _551 = lemma_x_in_xs_not_unique<uint64_t>(_552);
              auto _549 = _Dec<_UniqueVec<uint64_t>>::_No(_551);
              return _549;
            }
            case No: {
              auto _558 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_545.data));
              auto xNInXs = _558._1;
              auto _557 = [v, x, xs, xNInXs]() {
                auto _560 = xs;
                auto _559 = decUniqueVec(_560);
                switch (_559.type) {
                  case Yes: {
                    auto _563 = *(std::static_pointer_cast<_Dec_Yes<_UniqueVec<uint64_t>>>(_559.data));
                    auto xsU = _563._1;
                    auto _565 = x;
                    auto _566 = xs;
                    auto _567 = xNInXs;
                    auto _568 = xsU;
                    auto _564 = _UniqueVec<uint64_t>::_UConsV(_565, _566, _567, _568);
                    auto _562 = _Dec<_UniqueVec<uint64_t>>::_Yes(_564);
                    return _562;
                  }
                  case No: {
                    auto _571 = *(std::static_pointer_cast<_Dec_No<_UniqueVec<uint64_t>>>(_559.data));
                    auto xsNU = _571._1;
                    auto _573 = xsNU;
                    auto _572 = lemma_xs_not_unique<uint64_t>(_573);
                    auto _570 = _Dec<_UniqueVec<uint64_t>>::_No(_572);
                    return _570;
                  }
                }
              }();
              return _557;
            }
          }
        }();
        return _543;
      }
    }
  }();
  return _538;
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
  auto _578 = [pfXNotInb](auto pf) {
    auto _579 = [pf, pfXNotInb]() {
      auto _580 = pf;
      switch (_580.type) {
        case SConsV: {
          auto _582 = *(std::static_pointer_cast<_SubsetVec_SConsV<A>>(_580.data));
          auto a = _582._1;
          auto as = _582._2;
          auto pfFora = _582._3;
          auto others = _582._4;
          auto _583 = pfFora;
          auto _581 = pfXNotInb(_583);
          return _581;
        }
      }
    }();
    return _579;
  };
  return _578;
};

template <class A>
std::function<std::function<_Void(_SubsetVec<A>)>(std::function<_Void(_SubsetVec<A>)>)> lemma_xs_not_subset_b_vec = [](auto xsNotSubsetPf) {
  auto _584 = [xsNotSubsetPf](auto p) {
    auto _585 = [p, xsNotSubsetPf]() {
      auto _586 = p;
      switch (_586.type) {
        case SConsV: {
          auto _588 = *(std::static_pointer_cast<_SubsetVec_SConsV<A>>(_586.data));
          auto a = _588._1;
          auto as = _588._2;
          auto pfFora = _588._3;
          auto others = _588._4;
          auto _589 = others;
          auto _587 = xsNotSubsetPf(_589);
          return _587;
        }
      }
    }();
    return _585;
  };
  return _584;
};

std::function<std::function<_Dec<_SubsetVec<uint64_t>>(_Vec<uint64_t>)>(_Vec<uint64_t>)> decSubsetVecs = [](auto a) {
  auto _590 = [a](auto b) {
    auto _591 = [a, b]() {
      auto _592 = a;
      switch (_592.type) {
        case NilV: {
          auto _594 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_592.data));
          auto _595 = _SubsetVec<uint64_t>::_SNilV1();
          auto _593 = _Dec<_SubsetVec<uint64_t>>::_Yes(_595);
          return _593;
        }
        case ConsV: {
          auto _597 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_592.data));
          auto x = _597._1;
          auto xs = _597._2;
          auto _596 = [a, b, xs, x]() {
            auto _598 = b;
            switch (_598.type) {
              case NilV: {
                auto _600 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_598.data));
                auto _601 = _SubsetVec<uint64_t>::_SNilV2();
                auto _599 = _Dec<_SubsetVec<uint64_t>>::_Yes(_601);
                return _599;
              }
              case ConsV: {
                auto _603 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_598.data));
                auto y = _603._1;
                auto ys = _603._2;
                auto _602 = [a, b, xs, x]() {
                  auto _605 = xs;
                  auto _606 = b;
                  auto _604 = decSubsetVecs(_605)(_606);
                  switch (_604.type) {
                    case Yes: {
                      auto _610 = *(std::static_pointer_cast<_Dec_Yes<_SubsetVec<uint64_t>>>(_604.data));
                      auto pf = _610._1;
                      auto _609 = [a, b, xs, x, pf]() {
                        auto _612 = x;
                        auto _613 = b;
                        auto _611 = isElemVec(_612)(_613);
                        switch (_611.type) {
                          case Yes: {
                            auto _616 = *(std::static_pointer_cast<_Dec_Yes<_ElemVec<uint64_t>>>(_611.data));
                            auto elemPf = _616._1;
                            auto _618 = x;
                            auto _619 = xs;
                            auto _620 = elemPf;
                            auto _621 = pf;
                            auto _617 = _SubsetVec<uint64_t>::_SConsV(_618, _619, _620, _621);
                            auto _615 = _Dec<_SubsetVec<uint64_t>>::_Yes(_617);
                            return _615;
                          }
                          case No: {
                            auto _624 = *(std::static_pointer_cast<_Dec_No<_ElemVec<uint64_t>>>(_611.data));
                            auto p = _624._1;
                            auto _626 = p;
                            auto _625 = lemma_x_not_in_b_vec<uint64_t>(_626);
                            auto _623 = _Dec<_SubsetVec<uint64_t>>::_No(_625);
                            return _623;
                          }
                        }
                      }();
                      return _609;
                    }
                    case No: {
                      auto _635 = *(std::static_pointer_cast<_Dec_No<_SubsetVec<uint64_t>>>(_604.data));
                      auto p = _635._1;
                      auto _637 = p;
                      auto _636 = lemma_xs_not_subset_b_vec<uint64_t>(_637);
                      auto _634 = _Dec<_SubsetVec<uint64_t>>::_No(_636);
                      return _634;
                    }
                  }
                }();
                return _602;
              }
            }
          }();
          return _596;
        }
      }
    }();
    return _591;
  };
  return _590;
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
  auto _646 = a;
  auto _645 = _IO<A>::_MkIO(_646);
  return _645;
};

template <class A, class B>
std::function<std::function<_IO<B>(std::function<_IO<B>(A)>)>(_IO<A>)> bindEq = [](auto a) {
  auto _647 = [a](auto f) {
    auto _648 = [a, f]() {
      auto _649 = a;
      switch (_649.type) {
        case MkIO: {
          auto _651 = *(std::static_pointer_cast<_IO_MkIO<A>>(_649.data));
          auto inner = _651._1;
          auto _652 = inner;
          auto _650 = f(_652);
          return _650;
        }
      }
    }();
    return _648;
  };
  return _647;
};

template <class A, class B>
std::function<std::function<_IO<B>(_IO<B>)>(_IO<A>)> bind = [](auto a) {
  auto _653 = [a](auto b) {
    auto _655 = a;
    auto _656 = [a, b](auto c) {
      auto _659 = b;
      return _659;
    };
    auto _654 = bindEq<A, B>(_655)(_656);
    return _654;
  };
  return _653;
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
  auto _660 = [l]() {
    auto _661 = l;
    switch (_661.type) {
      case Nil: {
        auto _663 = *(std::static_pointer_cast<_List_Nil<_List<char>>>(_661.data));
        auto _664 = _Unit::_unit();
        auto _662 = returnIO<_Unit>(_664);
        return _662;
      }
      case Cons: {
        auto _667 = *(std::static_pointer_cast<_List_Cons<_List<char>>>(_661.data));
        auto x = _667._1;
        auto xs = _667._2;
        auto _672 = x;
        auto _668 = print(_672);
        auto _673 = xs;
        auto _669 = printList(_673);
        auto _666 = bind<_Unit, _Unit>(_668)(_669);
        return _666;
      }
    }
  }();
  return _660;
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
  auto _674 = [id](auto x) {
    auto _675 = [id, x](auto ch) {
      auto _677 = id;
      auto _678 = x;
      auto _679 = ch;
      auto _676 = channelEnqueue<A>(_677)(_678)(_679);
      return _676;
    };
    return _675;
  };
  return _674;
};

template <class A>
std::function<std::function<_IO<_Maybe<A>>(_Channel<A>)>(uint64_t)> receive = [](auto id) {
  auto _681 = [id](auto ch) {
    auto _683 = id;
    auto _684 = ch;
    auto _682 = channelDequeue<A>(_683)(_684);
    return _682;
  };
  return _681;
};

template <class A>
std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(std::function<_Void(_ElemVec<uint64_t>)>)>(_Vec<uint64_t>)>(uint64_t)>
    link = [](auto id) {
      auto _686 = [id](auto idSet) {
        auto _687 = [id, idSet](auto pf) {
          auto _688 = [id, idSet]() {
            auto _690 = id;
            auto _689 = prim_create_channel<A>(_690);
            switch (_689.type) {
              case True: {
                auto _693 = *(std::static_pointer_cast<_Bool_True>(_689.data));
                auto _697 = id;
                auto _701 = id;
                auto _699 = _Channel<A>::_MkChannel(_701);
                auto _704 = id;
                auto _705 = idSet;
                auto _702 = _Vec<uint64_t>::_ConsV(_704, _705);
                auto _707 = _TyEq::_Refl();
                auto _708 = _TyEq::_Refl();
                auto _703 = _Sigma<_TyEq, _TyEq>::_Prod(_707, _708);
                auto _700 = _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>::_Prod(_702, _703);
                auto _698 = _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>::_Prod(_699, _700);
                auto _696 = _Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Prod(_697, _698);
                auto _694 = _Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>::_Just(_696);
                auto _692 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_694);
                return _692;
              }
              case False: {
                auto _710 = *(std::static_pointer_cast<_Bool_False>(_689.data));
                auto _711 = _Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>::_Nothing();
                auto _709 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_711);
                return _709;
              }
            }
          }();
          return _688;
        };
        return _687;
      };
      return _686;
    };

std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(std::function<_Void(_ElemVec<uint64_t>)>)>(_Vec<uint64_t>)>(
    uint64_t)>(uint64_t)>
    spawn = [](auto pid) {
      auto _713 = [pid](auto n) {
        auto _714 = [pid](auto pidSet) {
          auto _715 = [pid, pidSet](auto pf) {
            auto _720 = pid;
            auto _724 = pid;
            auto _725 = pidSet;
            auto _722 = _Vec<uint64_t>::_ConsV(_724, _725);
            auto _727 = _TyEq::_Refl();
            auto _728 = _TyEq::_Refl();
            auto _723 = _Sigma<_TyEq, _TyEq>::_Prod(_727, _728);
            auto _721 = _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>::_Prod(_722, _723);
            auto _719 = _Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>::_Prod(_720, _721);
            auto _717 = _Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>::_Just(_719);
            auto _716 = returnIO<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_717);
            return _716;
          };
          return _715;
        };
        return _714;
      };
      return _713;
    };

std::function<std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_IO<_Unit>)>(_ElemVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(uint64_t)> run =
    [](auto pid) {
      auto _729 = [](auto n) {
        auto _730 = [](auto pidSet) {
          auto _731 = [pidSet](auto pf) {
            auto _732 = [pidSet](auto process) {
              auto _737 = pidSet;
              auto _738 = _TyEq::_Refl();
              auto _736 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_737, _738);
              auto _734 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_736);
              auto _733 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_734);
              return _733;
            };
            return _732;
          };
          return _731;
        };
        return _730;
      };
      return _729;
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
  auto _739 = [id](auto ch) {
    auto _740 = [id, ch](auto list) {
      auto _741 = [list, id, ch]() {
        auto _742 = list;
        switch (_742.type) {
          case Nil: {
            auto _744 = *(std::static_pointer_cast<_List_Nil<A>>(_742.data));
            auto _749 = id;
            auto _750 = _Maybe<A>::_Nothing();
            auto _751 = ch;
            auto _745 = send<A>(_749)(_750)(_751);
            auto _746 = end;
            auto _743 = bind<_Unit, _Unit>(_745)(_746);
            return _743;
          }
          case Cons: {
            auto _754 = *(std::static_pointer_cast<_List_Cons<A>>(_742.data));
            auto x = _754._1;
            auto xs = _754._2;
            auto _759 = id;
            auto _763 = x;
            auto _760 = _Maybe<A>::_Just(_763);
            auto _761 = ch;
            auto _755 = send<A>(_759)(_760)(_761);
            auto _764 = id;
            auto _765 = ch;
            auto _766 = xs;
            auto _756 = producerWrapper<A>(_764)(_765)(_766);
            auto _753 = bind<_Unit, _Unit>(_755)(_756);
            return _753;
          }
        }
      }();
      return _741;
    };
    return _740;
  };
  return _739;
};

template <class A>
std::function<_IO<_Unit>(_Vec<_Sigma<uint64_t, _Channel<A>>>)> propgateTermination = [](auto chs) {
  auto _768 = [chs]() {
    auto _769 = chs;
    switch (_769.type) {
      case NilV: {
        auto _771 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_769.data));
        auto _770 = end;
        return _770;
      }
      case ConsV: {
        auto _773 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_769.data));
        auto ch = _773._1;
        auto restChs = _773._2;
        auto _772 = [chs, ch, restChs]() {
          auto _774 = ch;
          switch (_774.type) {
            case Prod: {
              auto _776 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_774.data));
              auto chid = _776._1;
              auto channel = _776._2;
              auto _781 = chid;
              auto _782 = _Maybe<A>::_Nothing();
              auto _783 = channel;
              auto _777 = send<A>(_781)(_782)(_783);
              auto _785 = restChs;
              auto _778 = propgateTermination<A>(_785);
              auto _775 = bind<_Unit, _Unit>(_777)(_778);
              return _775;
            }
          }
        }();
        return _772;
      }
    }
  }();
  return _768;
};

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_List<A>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)> farmProducerWrapper = [](auto allChs) {
  auto _788 = [allChs](auto chs) {
    auto _789 = [allChs, chs](auto list) {
      auto _790 = [list, allChs, chs]() {
        auto _791 = list;
        switch (_791.type) {
          case Nil: {
            auto _793 = *(std::static_pointer_cast<_List_Nil<A>>(_791.data));
            auto _794 = allChs;
            auto _792 = propgateTermination<A>(_794);
            return _792;
          }
          case Cons: {
            auto _798 = *(std::static_pointer_cast<_List_Cons<A>>(_791.data));
            auto x = _798._1;
            auto xs = _798._2;
            auto _797 = [list, allChs, chs, x, xs]() {
              auto _799 = chs;
              switch (_799.type) {
                case NilV: {
                  auto _801 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_799.data));
                  auto _802 = allChs;
                  auto _803 = allChs;
                  auto _804 = list;
                  auto _800 = farmProducerWrapper<A>(_802)(_803)(_804);
                  return _800;
                }
                case ConsV: {
                  auto _809 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_799.data));
                  auto ch = _809._1;
                  auto restChs = _809._2;
                  auto _808 = [list, allChs, chs, ch, x, restChs, xs]() {
                    auto _810 = ch;
                    switch (_810.type) {
                      case Prod: {
                        auto _812 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_810.data));
                        auto chid = _812._1;
                        auto channel = _812._2;
                        auto _817 = chid;
                        auto _821 = x;
                        auto _818 = _Maybe<A>::_Just(_821);
                        auto _819 = channel;
                        auto _813 = send<A>(_817)(_818)(_819);
                        auto _822 = allChs;
                        auto _823 = restChs;
                        auto _824 = xs;
                        auto _814 = farmProducerWrapper<A>(_822)(_823)(_824);
                        auto _811 = bind<_Unit, _Unit>(_813)(_814);
                        return _811;
                      }
                    }
                  }();
                  return _808;
                }
              }
            }();
            return _797;
          }
        }
      }();
      return _790;
    };
    return _789;
  };
  return _788;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_Channel<A>)>(_Channel<A>)>(uint64_t)>(uint64_t)> workerWrapper = [](auto receiveId) {
  auto _828 = [receiveId](auto sendId) {
    auto _829 = [receiveId, sendId](auto receiveChannel) {
      auto _830 = [receiveId, receiveChannel, sendId](auto sendChannel) {
        auto _831 = [receiveId, receiveChannel, sendId, sendChannel](auto f) {
          auto _837 = receiveId;
          auto _838 = receiveChannel;
          auto _833 = receive<A>(_837)(_838);
          auto _834 = [receiveId, receiveChannel, sendId, sendChannel, f](auto mx) {
            auto _840 = [receiveId, receiveChannel, mx, sendId, sendChannel, f]() {
              auto _841 = mx;
              switch (_841.type) {
                case Nothing: {
                  auto _843 = *(std::static_pointer_cast<_Maybe_Nothing<A>>(_841.data));
                  auto _848 = sendId;
                  auto _849 = _Maybe<A>::_Nothing();
                  auto _850 = sendChannel;
                  auto _844 = send<A>(_848)(_849)(_850);
                  auto _845 = end;
                  auto _842 = bind<_Unit, _Unit>(_844)(_845);
                  return _842;
                }
                case Just: {
                  auto _853 = *(std::static_pointer_cast<_Maybe_Just<A>>(_841.data));
                  auto x = _853._1;
                  auto _858 = sendId;
                  auto _863 = x;
                  auto _862 = f(_863);
                  auto _859 = _Maybe<A>::_Just(_862);
                  auto _860 = sendChannel;
                  auto _854 = send<A>(_858)(_859)(_860);
                  auto _864 = receiveId;
                  auto _865 = sendId;
                  auto _866 = receiveChannel;
                  auto _867 = sendChannel;
                  auto _868 = f;
                  auto _855 = workerWrapper<A>(_864)(_865)(_866)(_867)(_868);
                  auto _852 = bind<_Unit, _Unit>(_854)(_855);
                  return _852;
                }
              }
            }();
            return _840;
          };
          auto _832 = bindEq<_Maybe<A>, _Unit>(_833)(_834);
          return _832;
        };
        return _831;
      };
      return _830;
    };
    return _829;
  };
  return _828;
};

template <class A>
std::function<std::function<std::function<_IO<_List<A>>(uint64_t)>(_Channel<A>)>(uint64_t)> farmConsumerWrapper = [](auto chid) {
  auto _870 = [chid](auto ch) {
    auto _871 = [chid, ch](auto numLeft) {
      auto _872 = [numLeft, chid, ch]() {
        auto _873 = numLeft;
        if (!_873) {
          auto _875 = _List<A>::_Nil();
          auto _874 = returnIO<_List<A>>(_875);
          return _874;
        } else {
          auto n = _873 - 1;
          auto _881 = chid;
          auto _882 = ch;
          auto _877 = receive<A>(_881)(_882);
          auto _878 = [numLeft, chid, ch, n](auto mx) {
            auto _884 = [numLeft, chid, ch, mx, n]() {
              auto _885 = mx;
              switch (_885.type) {
                case Nothing: {
                  auto _887 = *(std::static_pointer_cast<_Maybe_Nothing<A>>(_885.data));
                  auto _888 = chid;
                  auto _889 = ch;
                  auto _890 = n;
                  auto _886 = farmConsumerWrapper<A>(_888)(_889)(_890);
                  return _886;
                }
                case Just: {
                  auto _893 = *(std::static_pointer_cast<_Maybe_Just<A>>(_885.data));
                  auto x = _893._1;
                  auto _898 = chid;
                  auto _899 = ch;
                  auto _900 = numLeft;
                  auto _894 = farmConsumerWrapper<A>(_898)(_899)(_900);
                  auto _895 = [numLeft, chid, ch, mx, n, x](auto res) {
                    auto _905 = x;
                    auto _906 = res;
                    auto _903 = _List<A>::_Cons(_905, _906);
                    auto _902 = returnIO<_List<A>>(_903);
                    return _902;
                  };
                  auto _892 = bindEq<_List<A>, _List<A>>(_894)(_895);
                  return _892;
                }
              }
            }();
            return _884;
          };
          auto _874 = bindEq<_Maybe<A>, _List<A>>(_877)(_878);
          return _874;
        }
      }();
      return _872;
    };
    return _871;
  };
  return _870;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(std::function<A(A)>)>(
    _Sigma<uint64_t, _Channel<A>>)>(_Vec<_Sigma<uint64_t, _Channel<A>>>)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>
    spawnWorkersFarm = [](auto n) {
      auto _907 = [n](auto pidSet) {
        auto _908 = [pidSet, n](auto nDash) {
          auto _909 = [pidSet, n, nDash](auto pids) {
            auto _910 = [pids, pidSet, n, nDash](auto pidPf) {
              auto _911 = [pids, pidSet, pidPf, n, nDash](auto chs) {
                auto _912 = [pids, pidSet, pidPf, chs, n, nDash](auto consumerCh) {
                  auto _913 = [consumerCh, pids, pidSet, pidPf, chs, n, nDash](auto f) {
                    auto _914 = [consumerCh, pids, pidSet, pidPf, chs, f, n, nDash]() {
                      auto _915 = consumerCh;
                      switch (_915.type) {
                        case Prod: {
                          auto _917 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_915.data));
                          auto consumerChid = _917._1;
                          auto consumerChannel = _917._2;
                          auto _916 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash]() {
                            auto _918 = pids;
                            switch (_918.type) {
                              case NilV: {
                                auto _920 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_918.data));
                                auto _924 = pidSet;
                                auto _925 = _TyEq::_Refl();
                                auto _923 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_924, _925);
                                auto _921 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_923);
                                auto _919 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_921);
                                return _919;
                              }
                              case ConsV: {
                                auto _927 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_918.data));
                                auto x = _927._1;
                                auto xs = _927._2;
                                auto _926 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash, xs]() {
                                  auto _928 = pidPf;
                                  switch (_928.type) {
                                    case UConsV: {
                                      auto _930 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_928.data));
                                      auto y = _930._1;
                                      auto ys = _930._2;
                                      auto pf = _930._3;
                                      auto restPf = _930._4;
                                      auto _929 = [consumerCh, pids, pidSet, pidPf, chs, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf]() {
                                        auto _931 = chs;
                                        switch (_931.type) {
                                          case ConsV: {
                                            auto _933 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_931.data));
                                            auto curCh = _933._1;
                                            auto restChs = _933._2;
                                            auto _932 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf, restChs]() {
                                              auto _934 = curCh;
                                              switch (_934.type) {
                                                case Prod: {
                                                  auto _936 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_934.data));
                                                  auto currChid = _936._1;
                                                  auto currChannel = _936._2;
                                                  auto _941 = y;
                                                  auto _942 = ys;
                                                  auto _943 = pf;
                                                  auto _937 = spawnAndRun(_941)(_942)(
                                                      _943)([consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f]() {
                                                    auto _946 = currChid;
                                                    auto _947 = consumerChid;
                                                    auto _948 = currChannel;
                                                    auto _949 = consumerChannel;
                                                    auto _950 = f;
                                                    auto _944 = workerWrapper<A>(_946)(_947)(_948)(_949)(_950);
                                                  });
                                                  auto _938 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, n, nDash, xs, restPf,
                                                               restChs](auto mres) {
                                                    auto _952 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash, xs,
                                                                 restPf, restChs]() {
                                                      auto _953 = mres;
                                                      switch (_953.type) {
                                                        case Nothing: {
                                                          auto _955 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_953.data));
                                                          auto _956 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Nothing();
                                                          auto _954 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_956);
                                                          return _954;
                                                        }
                                                        case Just: {
                                                          auto _959 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_953.data));
                                                          auto res = _959._1;
                                                          auto _964 = n;
                                                          auto _965 = pidSet;
                                                          auto _973 = nDash;
                                                          auto _966 = pred(_973);
                                                          auto _967 = xs;
                                                          auto _968 = restPf;
                                                          auto _969 = restChs;
                                                          auto _970 = consumerCh;
                                                          auto _971 = f;
                                                          auto _960 = spawnWorkersFarm<A>(_964)(_965)(_966)(_967)(_968)(_969)(_970)(_971);
                                                          auto _961 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash,
                                                                       xs, restPf, restChs](auto mress) {
                                                            auto _974 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n,
                                                                         nDash, xs, restPf, restChs, mress]() {
                                                              auto _975 = mress;
                                                              switch (_975.type) {
                                                                case Nothing: {
                                                                  auto _977 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<uint64_t>, _TyEq>>>(_975.data));
                                                                  auto _978 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Nothing();
                                                                  auto _976 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_978);
                                                                  return _976;
                                                                }
                                                                case Just: {
                                                                  auto _981 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<uint64_t>, _TyEq>>>(_975.data));
                                                                  auto res = _981._1;
                                                                  auto _980 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n,
                                                                               nDash, xs, restPf, restChs, mress, res]() {
                                                                    auto _982 = res;
                                                                    switch (_982.type) {
                                                                      case Prod: {
                                                                        auto _984 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_982.data));
                                                                        auto newPidSet = _984._1;
                                                                        auto pfNewPidSetCorrect = _984._2;
                                                                        auto _990 = y;
                                                                        auto _991 = newPidSet;
                                                                        auto _988 = _Vec<uint64_t>::_ConsV(_990, _991);
                                                                        auto _993 = _TyEq::_Refl();
                                                                        auto _989 = _993;
                                                                        auto _987 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_988, _989);
                                                                        auto _985 = _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>::_Just(_987);
                                                                        auto _983 = returnIO<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_985);
                                                                        return _983;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _980;
                                                                }
                                                              }
                                                            }();
                                                            return _974;
                                                          };
                                                          auto _958 = bindEq<_Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>, _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_960)(_961);
                                                          return _958;
                                                        }
                                                      }
                                                    }();
                                                    return _952;
                                                  };
                                                  auto _935 = bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>, _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>>(_937)(_938);
                                                  return _935;
                                                }
                                              }
                                            }();
                                            return _932;
                                          }
                                        }
                                      }();
                                      return _929;
                                    }
                                  }
                                }();
                                return _926;
                              }
                            }
                          }();
                          return _916;
                        }
                      }
                    }();
                    return _914;
                  };
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

template <class A>
std::function<std::function<std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>
    createChannelsFarm = [](auto m) {
      auto _994 = [m](auto chidSet) {
        auto _995 = [chidSet, m](auto mDash) {
          auto _996 = [chidSet, m, mDash](auto chids) {
            auto _997 = [chids, chidSet, m, mDash](auto chidPf) {
              auto _998 = [chids, chidSet, chidPf, m, mDash]() {
                auto _999 = chids;
                switch (_999.type) {
                  case NilV: {
                    auto _1001 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_999.data));
                    auto _1005 = _Vec<_Sigma<uint64_t, _Channel<A>>>::_NilV();
                    auto _1007 = chidSet;
                    auto _1008 = _TyEq::_Refl();
                    auto _1006 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1007, _1008);
                    auto _1004 = _Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1005, _1006);
                    auto _1002 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Just(_1004);
                    auto _1000 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1002);
                    return _1000;
                  }
                  case ConsV: {
                    auto _1010 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_999.data));
                    auto x = _1010._1;
                    auto xs = _1010._2;
                    auto _1009 = [chids, chidSet, chidPf, m, mDash, xs]() {
                      auto _1011 = chidPf;
                      switch (_1011.type) {
                        case UConsV: {
                          auto _1013 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_1011.data));
                          auto y = _1013._1;
                          auto ys = _1013._2;
                          auto pf = _1013._3;
                          auto restPf = _1013._4;
                          auto _1018 = y;
                          auto _1019 = ys;
                          auto _1020 = pf;
                          auto _1014 = link<A>(_1018)(_1019)(_1020);
                          auto _1015 = [chids, chidSet, chidPf, y, ys, pf, m, mDash, xs, restPf](auto mres) {
                            auto _1023 = [chids, chidSet, chidPf, y, ys, pf, mres, m, mDash, xs, restPf]() {
                              auto _1024 = mres;
                              switch (_1024.type) {
                                case Nothing: {
                                  auto _1026 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_1024.data));
                                  auto _1027 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                  auto _1025 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1027);
                                  return _1025;
                                }
                                case Just: {
                                  auto _1030 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>>(_1024.data));
                                  auto res = _1030._1;
                                  auto _1029 = [chids, chidSet, chidPf, y, ys, pf, mres, res, m, mDash, xs, restPf]() {
                                    auto _1031 = res;
                                    switch (_1031.type) {
                                      case Prod: {
                                        auto _1033 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(_1031.data));
                                        auto resChid = _1033._1;
                                        auto rest1 = _1033._2;
                                        auto _1032 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, m, mDash, xs, restPf]() {
                                          auto _1034 = rest1;
                                          switch (_1034.type) {
                                            case Prod: {
                                              auto _1036 = *(std::static_pointer_cast<_Sigma_Prod<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>(_1034.data));
                                              auto ch = _1036._1;
                                              auto rest2 = _1036._2;
                                              auto _1035 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, m, mDash, xs, restPf, ch]() {
                                                auto _1037 = rest2;
                                                switch (_1037.type) {
                                                  case Prod: {
                                                    auto _1039 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>(_1037.data));
                                                    auto newChidSet = _1039._1;
                                                    auto pfs = _1039._2;
                                                    auto _1038 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch]() {
                                                      auto _1040 = pfs;
                                                      switch (_1040.type) {
                                                        case Prod: {
                                                          auto _1042 = *(std::static_pointer_cast<_Sigma_Prod<_TyEq, _TyEq>>(_1040.data));
                                                          auto chidEqResChidPf = _1042._1;
                                                          auto pfNewChidSetCorrect = _1042._2;
                                                          auto _1047 = m;
                                                          auto _1048 = chidSet;
                                                          auto _1053 = mDash;
                                                          auto _1049 = pred(_1053);
                                                          auto _1050 = xs;
                                                          auto _1051 = restPf;
                                                          auto _1043 = createChannelsFarm<A>(_1047)(_1048)(_1049)(_1050)(_1051);
                                                          auto _1044 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch](auto mress) {
                                                            auto _1054 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ch]() {
                                                              auto _1055 = mress;
                                                              switch (_1055.type) {
                                                                case Nothing: {
                                                                  auto _1057 = *(
                                                                      std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1055.data));
                                                                  auto _1058 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Nothing();
                                                                  auto _1056 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1058);
                                                                  return _1056;
                                                                }
                                                                case Just: {
                                                                  auto _1061 =
                                                                      *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1055.data));
                                                                  auto ress = _1061._1;
                                                                  auto _1060 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, ch]() {
                                                                    auto _1062 = ress;
                                                                    switch (_1062.type) {
                                                                      case Prod: {
                                                                        auto _1064 =
                                                                            *(std::static_pointer_cast<_Sigma_Prod<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1062.data));
                                                                        auto chs = _1064._1;
                                                                        auto rest3 = _1064._2;
                                                                        auto _1063 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, rest3, ch,
                                                                                      chs]() {
                                                                          auto _1065 = rest3;
                                                                          switch (_1065.type) {
                                                                            case Prod: {
                                                                              auto _1067 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1065.data));
                                                                              auto returnedChidSet = _1067._1;
                                                                              auto pfReturnedChidSetCorrect = _1067._2;
                                                                              auto _1077 = y;
                                                                              auto _1078 = ch;
                                                                              auto _1076 = _Sigma<uint64_t, _Channel<A>>::_Prod(_1077, _1078);
                                                                              auto _1073 = _1076;
                                                                              auto _1074 = chs;
                                                                              auto _1071 = _Vec<_Sigma<uint64_t, _Channel<A>>>::_ConsV(_1073, _1074);
                                                                              auto _1081 = y;
                                                                              auto _1082 = returnedChidSet;
                                                                              auto _1079 = _Vec<uint64_t>::_ConsV(_1081, _1082);
                                                                              auto _1084 = _TyEq::_Refl();
                                                                              auto _1080 = _1084;
                                                                              auto _1072 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1079, _1080);
                                                                              auto _1070 = _Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1071, _1072);
                                                                              auto _1068 = _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Just(_1070);
                                                                              auto _1066 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1068);
                                                                              return _1066;
                                                                            }
                                                                          }
                                                                        }();
                                                                        return _1063;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _1060;
                                                                }
                                                              }
                                                            }();
                                                            return _1054;
                                                          };
                                                          auto _1041 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>,
                                                                              _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1043)(_1044);
                                                          return _1041;
                                                        }
                                                      }
                                                    }();
                                                    return _1038;
                                                  }
                                                }
                                              }();
                                              return _1035;
                                            }
                                          }
                                        }();
                                        return _1032;
                                      }
                                    }
                                  }();
                                  return _1029;
                                }
                              }
                            }();
                            return _1023;
                          };
                          auto _1012 = bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Channel<A>, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>,
                                              _Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1014)(_1015);
                          return _1012;
                        }
                      }
                    }();
                    return _1009;
                  }
                }
              }();
              return _998;
            };
            return _997;
          };
          return _996;
        };
        return _995;
      };
      return _994;
    };

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_List<A>)>(std::function<A(A)>)>(_TyEq)>(_TyEq)>(
    std::function<_Void(_TyEq)>)>(uint64_t)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(uint64_t)>(_UniqueVec<uint64_t>)>(_Vec<uint64_t>)>(uint64_t)>(_Vec<uint64_t>)>(
    uint64_t)>
    createFarm = [](auto n) {
      auto _1085 = [n](auto pidSet) {
        auto _1086 = [n, pidSet](auto nDash) {
          auto _1087 = [n, pidSet, nDash](auto pids) {
            auto _1088 = [pids, n, pidSet, nDash](auto pidPf) {
              auto _1089 = [pids, pidPf, n, pidSet, nDash](auto m) {
                auto _1090 = [m, pids, pidPf, n, pidSet, nDash](auto chidSet) {
                  auto _1091 = [m, chidSet, pids, pidPf, n, pidSet, nDash](auto mDash) {
                    auto _1092 = [m, chidSet, mDash, pids, pidPf, n, pidSet, nDash](auto chids) {
                      auto _1093 = [m, chidSet, mDash, chids, pids, pidPf, n, pidSet, nDash](auto chidPf) {
                        auto _1094 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash](auto numWorkers) {
                          auto _1095 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfNotZ) {
                            auto _1096 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfPidsNCorrect) {
                              auto _1097 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfChidsMCorrect) {
                                auto _1098 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto f) {
                                  auto _1099 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, f, numWorkers](auto input) {
                                    auto _1105 = m;
                                    auto _1106 = chidSet;
                                    auto _1107 = mDash;
                                    auto _1108 = chids;
                                    auto _1109 = chidPf;
                                    auto _1101 = createChannelsFarm<A>(_1105)(_1106)(_1107)(_1108)(_1109);
                                    auto _1102 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, input, n, pidSet, nDash, f, numWorkers](auto mres1) {
                                      auto _1111 = [m, chidSet, mDash, chids, chidPf, mres1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                        auto _1112 = mres1;
                                        switch (_1112.type) {
                                          case Nothing: {
                                            auto _1114 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1112.data));
                                            auto _1115 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                            auto _1113 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1115);
                                            return _1113;
                                          }
                                          case Just: {
                                            auto _1118 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>>(_1112.data));
                                            auto res1 = _1118._1;
                                            auto _1117 = [m, chidSet, mDash, chids, chidPf, mres1, res1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                              auto _1119 = res1;
                                              switch (_1119.type) {
                                                case Prod: {
                                                  auto _1121 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>(_1119.data));
                                                  auto chs = _1121._1;
                                                  auto chidPfToReturn = _1121._2;
                                                  auto _1120 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, pids, pidPf, input, n, pidSet, nDash, f, numWorkers, chidPfToReturn]() {
                                                    auto _1122 = chs;
                                                    switch (_1122.type) {
                                                      case NilV: {
                                                        auto _1124 = *(std::static_pointer_cast<_Vec_NilV<_Sigma<uint64_t, _Channel<A>>>>(_1122.data));
                                                        auto _1125 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                        auto _1123 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1125);
                                                        return _1123;
                                                      }
                                                      case ConsV: {
                                                        auto _1128 = *(std::static_pointer_cast<_Vec_ConsV<_Sigma<uint64_t, _Channel<A>>>>(_1122.data));
                                                        auto consumerCh = _1128._1;
                                                        auto otherChs = _1128._2;
                                                        auto _1127 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, f, numWorkers,
                                                                      chidPfToReturn]() {
                                                          auto _1129 = consumerCh;
                                                          switch (_1129.type) {
                                                            case Prod: {
                                                              auto _1131 = *(std::static_pointer_cast<_Sigma_Prod<uint64_t, _Channel<A>>>(_1129.data));
                                                              auto consumerChid = _1131._1;
                                                              auto consumerChannel = _1131._2;
                                                              auto _1130 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, f,
                                                                            consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                auto _1132 = pids;
                                                                switch (_1132.type) {
                                                                  case NilV: {
                                                                    auto _1134 = *(std::static_pointer_cast<_Vec_NilV<uint64_t>>(_1132.data));
                                                                    auto _1135 =
                                                                        _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                                    auto _1133 =
                                                                        returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                            _1135);
                                                                    return _1133;
                                                                  }
                                                                  case ConsV: {
                                                                    auto _1138 = *(std::static_pointer_cast<_Vec_ConsV<uint64_t>>(_1132.data));
                                                                    auto x = _1138._1;
                                                                    auto xs = _1138._2;
                                                                    auto _1137 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, otherChs, input, n, pidSet, nDash, xs, f,
                                                                                  consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                      auto _1139 = pidPf;
                                                                      switch (_1139.type) {
                                                                        case UConsV: {
                                                                          auto _1141 = *(std::static_pointer_cast<_UniqueVec_UConsV<uint64_t>>(_1139.data));
                                                                          auto producerPid = _1141._1;
                                                                          auto restPids = _1141._2;
                                                                          auto producerPidPf = _1141._3;
                                                                          auto restPfs = _1141._4;
                                                                          auto _1146 = producerPid;
                                                                          auto _1147 = restPids;
                                                                          auto _1148 = producerPidPf;
                                                                          auto _1142 = spawnAndRun(_1146)(_1147)(_1148)([m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf,
                                                                                                                         producerPid, restPids, producerPidPf, otherChs, input]() {
                                                                            auto _1151 = otherChs;
                                                                            auto _1152 = otherChs;
                                                                            auto _1153 = input;
                                                                            auto _1149 = farmProducerWrapper<A>(_1151)(_1152)(_1153);
                                                                          });
                                                                          auto _1143 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                        producerPidPf, otherChs, input, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel, numWorkers,
                                                                                        chidPfToReturn](auto mres2) {
                                                                            auto _1157 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                          producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel,
                                                                                          numWorkers, chidPfToReturn]() {
                                                                              auto _1158 = mres2;
                                                                              switch (_1158.type) {
                                                                                case Nothing: {
                                                                                  auto _1160 =
                                                                                      *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(
                                                                                          _1158.data));
                                                                                  auto _1161 =
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>::
                                                                                          _Nothing();
                                                                                  auto _1159 = returnIO<
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                      _1161);
                                                                                  return _1159;
                                                                                }
                                                                                case Just: {
                                                                                  auto _1164 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>>(
                                                                                      _1158.data));
                                                                                  auto res2 = _1164._1;
                                                                                  auto _1169 = n;
                                                                                  auto _1170 = pidSet;
                                                                                  auto _1178 = nDash;
                                                                                  auto _1171 = pred(_1178);
                                                                                  auto _1172 = xs;
                                                                                  auto _1173 = restPfs;
                                                                                  auto _1179 = otherChs;
                                                                                  auto _1174 = _1179;
                                                                                  auto _1175 = consumerCh;
                                                                                  auto _1176 = f;
                                                                                  auto _1165 = spawnWorkersFarm<A>(_1169)(_1170)(_1171)(_1172)(_1173)(_1174)(_1175)(_1176);
                                                                                  auto _1166 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, consumerChid, consumerChannel,
                                                                                                numWorkers, chidPfToReturn](auto mres3) {
                                                                                    auto _1180 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                  producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3, consumerChid,
                                                                                                  consumerChannel, numWorkers, chidPfToReturn]() {
                                                                                      auto _1181 = mres3;
                                                                                      switch (_1181.type) {
                                                                                        case Nothing: {
                                                                                          auto _1183 = *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1181.data));
                                                                                          auto _1184 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                       _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Nothing();
                                                                                          auto _1182 = returnIO<_Maybe<_Sigma<
                                                                                              _List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                              _1184);
                                                                                          return _1182;
                                                                                        }
                                                                                        case Just: {
                                                                                          auto _1187 = *(std::static_pointer_cast<_Maybe_Just<_Sigma<_Vec<uint64_t>, _TyEq>>>(_1181.data));
                                                                                          auto workerPidPfs = _1187._1;
                                                                                          auto _1186 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                        restPids, producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3,
                                                                                                        workerPidPfs, consumerChid, consumerChannel, numWorkers, chidPfToReturn]() {
                                                                                            auto _1188 = workerPidPfs;
                                                                                            switch (_1188.type) {
                                                                                              case Prod: {
                                                                                                auto _1190 = *(std::static_pointer_cast<_Sigma_Prod<_Vec<uint64_t>, _TyEq>>(_1188.data));
                                                                                                auto workersPidSet = _1190._1;
                                                                                                auto workerPidSetPf = _1190._2;
                                                                                                auto _1195 = consumerChid;
                                                                                                auto _1196 = consumerChannel;
                                                                                                auto _1197 = numWorkers;
                                                                                                auto _1191 = farmConsumerWrapper<A>(_1195)(_1196)(_1197);
                                                                                                auto _1192 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                              restPids, producerPidPf, otherChs, input, mres2, n, pidSet, nDash, xs, restPfs, f, mres3,
                                                                                                              workerPidPfs, consumerChid, consumerChannel, numWorkers, workersPidSet, workerPidSetPf,
                                                                                                              chidPfToReturn](auto resultantList) {
                                                                                                  auto _1203 = resultantList;
                                                                                                  auto _1207 = numWorkers;
                                                                                                  auto _1208 = f;
                                                                                                  auto _1205 = _Farm<A>::_MkFarm(_1207, _1208);
                                                                                                  auto _1213 = producerPid;
                                                                                                  auto _1214 = workersPidSet;
                                                                                                  auto _1211 = _Vec<uint64_t>::_ConsV(_1213, _1214);
                                                                                                  auto _1216 = _TyEq::_Refl();
                                                                                                  auto _1217 = workerPidSetPf;
                                                                                                  auto _1212 = consVInjLem(_1216)(_1217);
                                                                                                  auto _1209 = _Sigma<_Vec<uint64_t>, _TyEq>::_Prod(_1211, _1212);
                                                                                                  auto _1210 = chidPfToReturn;
                                                                                                  auto _1206 =
                                                                                                      _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>::_Prod(_1209, _1210);
                                                                                                  auto _1204 =
                                                                                                      _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>::_Prod(
                                                                                                          _1205, _1206);
                                                                                                  auto _1202 =
                                                                                                      _Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                               _Sigma<_Vec<uint64_t>, _TyEq>>>>::_Prod(_1203, _1204);
                                                                                                  auto _1200 =
                                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                      _Sigma<_Vec<uint64_t>, _TyEq>>>>>::_Just(_1202);
                                                                                                  auto _1199 =
                                                                                                      returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                               _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                                          _1200);
                                                                                                  return _1199;
                                                                                                };
                                                                                                auto _1189 =
                                                                                                    bindEq<_List<A>, _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>,
                                                                                                                                                                     _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                                        _1191)(_1192);
                                                                                                return _1189;
                                                                                              }
                                                                                            }
                                                                                          }();
                                                                                          return _1186;
                                                                                        }
                                                                                      }
                                                                                    }();
                                                                                    return _1180;
                                                                                  };
                                                                                  auto _1163 = bindEq<
                                                                                      _Maybe<_Sigma<_Vec<uint64_t>, _TyEq>>,
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                      _1165)(_1166);
                                                                                  return _1163;
                                                                                }
                                                                              }
                                                                            }();
                                                                            return _1157;
                                                                          };
                                                                          auto _1140 =
                                                                              bindEq<_Maybe<_Sigma<uint64_t, _Sigma<_Vec<uint64_t>, _Sigma<_TyEq, _TyEq>>>>,
                                                                                     _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(
                                                                                  _1142)(_1143);
                                                                          return _1140;
                                                                        }
                                                                      }
                                                                    }();
                                                                    return _1137;
                                                                  }
                                                                }
                                                              }();
                                                              return _1130;
                                                            }
                                                          }
                                                        }();
                                                        return _1127;
                                                      }
                                                    }
                                                  }();
                                                  return _1120;
                                                }
                                              }
                                            }();
                                            return _1117;
                                          }
                                        }
                                      }();
                                      return _1111;
                                    };
                                    auto _1100 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<uint64_t, _Channel<A>>>, _Sigma<_Vec<uint64_t>, _TyEq>>>,
                                                        _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1101)(_1102);
                                    return _1100;
                                  };
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

std::function<uint64_t(uint64_t)> id = [](auto a) {
  auto _1224 = a;
  auto _1223 = _1224 + 1;
  ;
  return _1223;
};

_IO<_Unit> main3 = []() {
  auto _1231 = natToString;
  auto _1235 = (uint64_t)42;
  auto _1237 = (uint64_t)42;
  auto _1239 = (uint64_t)42;
  auto _1241 = (uint64_t)42;
  auto _1243 = (uint64_t)42;
  auto _1245 = (uint64_t)42;
  auto _1247 = (uint64_t)42;
  auto _1249 = (uint64_t)42;
  auto _1251 = (uint64_t)42;
  auto _1253 = (uint64_t)42;
  auto _1254 = _List<uint64_t>::_Nil();
  auto _1252 = _List<uint64_t>::_Cons(_1253, _1254);
  auto _1250 = _List<uint64_t>::_Cons(_1251, _1252);
  auto _1248 = _List<uint64_t>::_Cons(_1249, _1250);
  auto _1246 = _List<uint64_t>::_Cons(_1247, _1248);
  auto _1244 = _List<uint64_t>::_Cons(_1245, _1246);
  auto _1242 = _List<uint64_t>::_Cons(_1243, _1244);
  auto _1240 = _List<uint64_t>::_Cons(_1241, _1242);
  auto _1238 = _List<uint64_t>::_Cons(_1239, _1240);
  auto _1236 = _List<uint64_t>::_Cons(_1237, _1238);
  auto _1232 = _List<uint64_t>::_Cons(_1235, _1236);
  auto _1230 = map<uint64_t, _List<char>>(_1231)(_1232);
  auto _1226 = printList(_1230);
  auto _1260 = 'O';
  auto _1262 = 'U';
  auto _1264 = 'T';
  auto _1266 = 'P';
  auto _1268 = 'U';
  auto _1270 = 'T';
  auto _1272 = '-';
  auto _1274 = 'T';
  auto _1276 = 'I';
  auto _1278 = 'M';
  auto _1280 = 'E';
  auto _1281 = _List<char>::_Nil();
  auto _1279 = _List<char>::_Cons(_1280, _1281);
  auto _1277 = _List<char>::_Cons(_1278, _1279);
  auto _1275 = _List<char>::_Cons(_1276, _1277);
  auto _1273 = _List<char>::_Cons(_1274, _1275);
  auto _1271 = _List<char>::_Cons(_1272, _1273);
  auto _1269 = _List<char>::_Cons(_1270, _1271);
  auto _1267 = _List<char>::_Cons(_1268, _1269);
  auto _1265 = _List<char>::_Cons(_1266, _1267);
  auto _1263 = _List<char>::_Cons(_1264, _1265);
  auto _1261 = _List<char>::_Cons(_1262, _1263);
  auto _1259 = _List<char>::_Cons(_1260, _1261);
  auto _1255 = print(_1259);
  auto _1256 = []() {
    auto _1290 = (uint64_t)3;
    auto _1293 = (uint64_t)2;
    auto _1296 = (uint64_t)1;
    auto _1297 = _Vec<uint64_t>::_NilV();
    auto _1294 = _Vec<uint64_t>::_ConsV(_1296, _1297);
    auto _1291 = _Vec<uint64_t>::_ConsV(_1293, _1294);
    auto _1285 = _Vec<uint64_t>::_ConsV(_1290, _1291);
    auto _1286 = _Vec<uint64_t>::_NilV();
    auto _1283 = append<uint64_t>(_1285)(_1286);
    auto _1282 = decUniqueVec(_1283);
    switch (_1282.type) {
      case Yes: {
        auto _1300 = *(std::static_pointer_cast<_Dec_Yes<_UniqueVec<uint64_t>>>(_1282.data));
        auto pf1 = _1300._1;
        auto _1305 = (uint64_t)0;
        auto _1306 = _Vec<uint64_t>::_NilV();
        auto _1307 = (uint64_t)3;
        auto _1322 = (uint64_t)3;
        auto _1325 = (uint64_t)2;
        auto _1328 = (uint64_t)1;
        auto _1329 = _Vec<uint64_t>::_NilV();
        auto _1326 = _Vec<uint64_t>::_ConsV(_1328, _1329);
        auto _1323 = _Vec<uint64_t>::_ConsV(_1325, _1326);
        auto _1308 = _Vec<uint64_t>::_ConsV(_1322, _1323);
        auto _1309 = pf1;
        auto _1310 = (uint64_t)0;
        auto _1311 = _Vec<uint64_t>::_NilV();
        auto _1312 = (uint64_t)3;
        auto _1331 = (uint64_t)3;
        auto _1334 = (uint64_t)2;
        auto _1337 = (uint64_t)1;
        auto _1338 = _Vec<uint64_t>::_NilV();
        auto _1335 = _Vec<uint64_t>::_ConsV(_1337, _1338);
        auto _1332 = _Vec<uint64_t>::_ConsV(_1334, _1335);
        auto _1313 = _Vec<uint64_t>::_ConsV(_1331, _1332);
        auto _1314 = pf1;
        auto _1315 = (uint64_t)2;
        auto _1344 = (uint64_t)1;
        auto _1340 = ZnotS(_1344);
        auto _1316 = negEqSym<uint64_t>(_1340);
        auto _1317 = _TyEq::_Refl();
        auto _1318 = _TyEq::_Refl();
        auto _1319 = fib;
        auto _1345 = (uint64_t)42;
        auto _1347 = (uint64_t)42;
        auto _1349 = (uint64_t)42;
        auto _1351 = (uint64_t)42;
        auto _1353 = (uint64_t)42;
        auto _1355 = (uint64_t)42;
        auto _1357 = (uint64_t)42;
        auto _1359 = (uint64_t)42;
        auto _1361 = (uint64_t)42;
        auto _1363 = (uint64_t)42;
        auto _1364 = _List<uint64_t>::_Nil();
        auto _1362 = _List<uint64_t>::_Cons(_1363, _1364);
        auto _1360 = _List<uint64_t>::_Cons(_1361, _1362);
        auto _1358 = _List<uint64_t>::_Cons(_1359, _1360);
        auto _1356 = _List<uint64_t>::_Cons(_1357, _1358);
        auto _1354 = _List<uint64_t>::_Cons(_1355, _1356);
        auto _1352 = _List<uint64_t>::_Cons(_1353, _1354);
        auto _1350 = _List<uint64_t>::_Cons(_1351, _1352);
        auto _1348 = _List<uint64_t>::_Cons(_1349, _1350);
        auto _1346 = _List<uint64_t>::_Cons(_1347, _1348);
        auto _1320 = _List<uint64_t>::_Cons(_1345, _1346);
        auto _1301 = createFarm<uint64_t>(_1305)(_1306)(_1307)(_1308)(_1309)(_1310)(_1311)(_1312)(_1313)(_1314)(_1315)(_1316)(_1317)(_1318)(_1319)(_1320);
        auto _1302 = [pf1](auto mres) {
          auto _1365 = [pf1, mres]() {
            auto _1366 = mres;
            switch (_1366.type) {
              case Nothing: {
                auto _1368 =
                    *(std::static_pointer_cast<_Maybe_Nothing<_Sigma<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1366.data));
                auto _1370 = 'R';
                auto _1372 = 'I';
                auto _1374 = 'P';
                auto _1375 = _List<char>::_Nil();
                auto _1373 = _List<char>::_Cons(_1374, _1375);
                auto _1371 = _List<char>::_Cons(_1372, _1373);
                auto _1369 = _List<char>::_Cons(_1370, _1371);
                auto _1367 = print(_1369);
                return _1367;
              }
              case Just: {
                auto _1377 =
                    *(std::static_pointer_cast<_Maybe_Just<_Sigma<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>>(_1366.data));
                auto r = _1377._1;
                auto _1376 = [pf1, mres, r]() {
                  auto _1378 = r;
                  switch (_1378.type) {
                    case Prod: {
                      auto _1380 = *(std::static_pointer_cast<_Sigma_Prod<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>(_1378.data));
                      auto l = _1380._1;
                      auto rest = _1380._2;
                      auto _1382 = natToString;
                      auto _1383 = l;
                      auto _1381 = map<uint64_t, _List<char>>(_1382)(_1383);
                      auto _1379 = printList(_1381);
                      return _1379;
                    }
                  }
                }();
                return _1376;
              }
            }
          }();
          return _1365;
        };
        auto _1299 = bindEq<_Maybe<_Sigma<_List<uint64_t>, _Sigma<_Farm<uint64_t>, _Sigma<_Sigma<_Vec<uint64_t>, _TyEq>, _Sigma<_Vec<uint64_t>, _TyEq>>>>>, _Unit>(_1301)(_1302);
        return _1299;
      }
    }
  }();
  auto _1227 = bind<_Unit, _Unit>(_1255)(_1256);
  auto _1225 = bind<_Unit, _Unit>(_1226)(_1227);
  return _1225;
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