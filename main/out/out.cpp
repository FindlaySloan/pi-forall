#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <system_error>
#include <thread>
#include <vector>

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
std::function<int(_Nat)> intFromNat = [](_Nat n) {
  if (n.type == Zero) {
    return 0;
  } else {
    return 1 + intFromNat((*(_Nat_Succ*)n.data)._1);
  }
};

// TyEq

class _TyEq {
 public:
  static _TyEq _Refl();
};

inline _TyEq _TyEq::_Refl() { return _TyEq{}; }
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
enum _enum_Unit_type { unit };
class _Unit {
 public:
  enum _enum_Unit_type type;
  void* data;
  static _Unit _unit();
};
class _Unit_unit {
 public:
  _Unit_unit(){};
};
inline _Unit _Unit::_unit() {
  _Unit_unit* _innerClass = new _Unit_unit();
  return _Unit{unit, _innerClass};
};
enum _enum_Bool_type { False, True };
class _Bool {
 public:
  enum _enum_Bool_type type;
  void* data;
  static _Bool _False();
  static _Bool _True();
};
class _Bool_False {
 public:
  _Bool_False(){};
};
class _Bool_True {
 public:
  _Bool_True(){};
};
inline _Bool _Bool::_False() {
  _Bool_False* _innerClass = new _Bool_False();
  return _Bool{False, _innerClass};
};
inline _Bool _Bool::_True() {
  _Bool_True* _innerClass = new _Bool_True();
  return _Bool{True, _innerClass};
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
enum _enum_Vec_type { NilV, ConsV };
template <class A>
class _Vec {
 public:
  enum _enum_Vec_type type;
  void* data;
  static _Vec<A> _NilV();
  static _Vec<A> _ConsV(A _1, _Vec<A> _2);
};
template <class A>
class _Vec_NilV {
 public:
  _Vec_NilV(){};
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
};
template <class A>
inline _Vec<A> _Vec<A>::_NilV() {
  _Vec_NilV<A>* _innerClass = new _Vec_NilV<A>();
  return _Vec<A>{NilV, _innerClass};
};
template <class A>
inline _Vec<A> _Vec<A>::_ConsV(A _1, _Vec<A> _2) {
  _Vec_ConsV<A>* _innerClass = new _Vec_ConsV<A>(_1, _2);
  return _Vec<A>{ConsV, _innerClass};
};

template <class A>
std::function<A(_Vec<A>)> head = [](auto x) {
  auto _1 = [x]() {
    auto _2 = x;
    switch (_2.type) {
      case ConsV: {
        auto _4 = *(_Vec_ConsV<A>*)_2.data;
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
        auto _8 = *(_Vec_ConsV<A>*)_6.data;
        auto y = _8._1;
        auto ys = _8._2;
        auto _7 = ys;
        return _7;
      }
    }
  }();
  return _5;
};
enum _enum_Void_type {};
class _Void {
 public:
  enum _enum_Void_type type;
  void* data;
};
enum _enum_Dec_type { Yes, No };
template <class prop>
class _Dec {
 public:
  enum _enum_Dec_type type;
  void* data;
  static _Dec<prop> _Yes(prop _1);
  static _Dec<prop> _No(std::function<_Void(prop)> _1);
};
template <class prop>
class _Dec_Yes {
 public:
  prop _1;
  _Dec_Yes(prop _1) { this->_1 = _1; };
};
template <class prop>
class _Dec_No {
 public:
  std::function<_Void(prop)> _1;
  _Dec_No(std::function<_Void(prop)> _1) { this->_1 = _1; };
};
template <class prop>
inline _Dec<prop> _Dec<prop>::_Yes(prop _1) {
  _Dec_Yes<prop>* _innerClass = new _Dec_Yes<prop>(_1);
  return _Dec<prop>{Yes, _innerClass};
};
template <class prop>
inline _Dec<prop> _Dec<prop>::_No(std::function<_Void(prop)> _1) {
  _Dec_No<prop>* _innerClass = new _Dec_No<prop>(_1);
  return _Dec<prop>{No, _innerClass};
};

template <class A, class B>
std::function<_TyEq(_TyEq)> f_equal = [](auto pf) {
  auto _10 = _TyEq::_Refl();
  auto _9 = _10;
  return _9;
};

std::function<std::function<_Void(_TyEq)>(_Nat)> ZnotS = [](auto n) {
  auto _11 = [](auto r) {
    auto _12 = _Void();
    return _12;
  };
  return _11;
};

template <class A>
std::function<_TyEq(_TyEq)> sym = [](auto pf) {
  auto _14 = _TyEq::_Refl();
  auto _13 = _14;
  return _13;
};

template <class t>
std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)> negEqSym = [](auto p) {
  auto _15 = [p](auto h) {
    auto _18 = h;
    auto _17 = sym<t>(_18);
    auto _16 = p(_17);
    return _16;
  };
  return _15;
};

std::function<_Nat(_Nat)> pred = [](auto n) {
  auto _22 = [n]() {
    auto _23 = n;
    switch (_23.type) {
      case Zero: {
        auto _25 = *(_Nat_Zero*)_23.data;
        auto _24 = _Nat::_Zero();
        return _24;
      }
      case Succ: {
        auto _27 = *(_Nat_Succ*)_23.data;
        auto m = _27._1;
        auto _26 = m;
        return _26;
      }
    }
  }();
  return _22;
};

std::function<_TyEq(_TyEq)> succInjective = [](auto p) {
  auto _29 = p;
  auto _28 = f_equal<_Nat, _Nat>(_29);
  return _28;
};

std::function<std::function<_Dec<_TyEq>(_Nat)>(_Nat)> decEqNat = [](auto a) {
  auto _35 = [a](auto b) {
    auto _36 = [a, b]() {
      auto _37 = a;
      switch (_37.type) {
        case Zero: {
          auto _39 = *(_Nat_Zero*)_37.data;
          auto _38 = [a, b]() {
            auto _40 = b;
            switch (_40.type) {
              case Zero: {
                auto _42 = *(_Nat_Zero*)_40.data;
                auto _43 = _TyEq::_Refl();
                auto _41 = _Dec<_TyEq>::_Yes(_43);
                return _41;
              }
              case Succ: {
                auto _45 = *(_Nat_Succ*)_40.data;
                auto n = _45._1;
                auto _47 = n;
                auto _46 = ZnotS(_47);
                auto _44 = _Dec<_TyEq>::_No(_46);
                return _44;
              }
            }
          }();
          return _38;
        }
        case Succ: {
          auto _49 = *(_Nat_Succ*)_37.data;
          auto n = _49._1;
          auto _48 = [a, b, n]() {
            auto _50 = b;
            switch (_50.type) {
              case Zero: {
                auto _52 = *(_Nat_Zero*)_50.data;
                auto _58 = n;
                auto _54 = ZnotS(_58);
                auto _53 = negEqSym<_Nat>(_54);
                auto _51 = _Dec<_TyEq>::_No(_53);
                return _51;
              }
              case Succ: {
                auto _60 = *(_Nat_Succ*)_50.data;
                auto m = _60._1;
                auto _59 = [a, b, n, m]() {
                  auto _62 = n;
                  auto _63 = m;
                  auto _61 = decEqNat(_62)(_63);
                  switch (_61.type) {
                    case Yes: {
                      auto _65 = *(_Dec_Yes<_TyEq>*)_61.data;
                      auto p = _65._1;
                      auto _67 = p;
                      auto _66 = f_equal<_Nat, _Nat>(_67);
                      auto _64 = _Dec<_TyEq>::_Yes(_66);
                      return _64;
                    }
                    case No: {
                      auto _74 = *(_Dec_No<_TyEq>*)_61.data;
                      auto p = _74._1;
                      auto _75 = [a, b, n, m, p](auto h) {
                        auto _78 = h;
                        auto _77 = succInjective(_78);
                        auto _76 = p(_77);
                        return _76;
                      };
                      auto _73 = _Dec<_TyEq>::_No(_75);
                      return _73;
                    }
                  }
                }();
                return _59;
              }
            }
          }();
          return _48;
        }
      }
    }();
    return _36;
  };
  return _35;
};
enum _enum_Elem_type { Here, There };
template <class a>
class _Elem {
 public:
  enum _enum_Elem_type type;
  void* data;
  static _Elem<a> _Here(a _1, _List<a> _2);
  static _Elem<a> _There(a _1, a _2, _List<a> _3, _Elem<a> _4);
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
};
template <class a>
inline _Elem<a> _Elem<a>::_Here(a _1, _List<a> _2) {
  _Elem_Here<a>* _innerClass = new _Elem_Here<a>(_1, _2);
  return _Elem<a>{Here, _innerClass};
};
template <class a>
inline _Elem<a> _Elem<a>::_There(a _1, a _2, _List<a> _3, _Elem<a> _4) {
  _Elem_There<a>* _innerClass = new _Elem_There<a>(_1, _2, _3, _4);
  return _Elem<a>{There, _innerClass};
};

std::function<std::function<std::function<_Void(_Elem<_Nat>)>(std::function<_Void(_Elem<_Nat>)>)>(std::function<_Void(_TyEq)>)> neitherHereNorThere = [](auto xneqy) {
  auto _81 = [xneqy](auto xninxs) {
    auto _82 = [xneqy, xninxs](auto p) {
      auto _83 = [p, xneqy, xninxs]() {
        auto _84 = p;
        switch (_84.type) {
          case Here: {
            auto _86 = *(_Elem_Here<_Nat>*)_84.data;
            auto a = _86._1;
            auto as = _86._2;
            auto _87 = _TyEq::_Refl();
            auto _85 = xneqy(_87);
            return _85;
          }
          case There: {
            auto _89 = *(_Elem_There<_Nat>*)_84.data;
            auto b = _89._1;
            auto a = _89._2;
            auto as = _89._3;
            auto prf = _89._4;
            auto _90 = prf;
            auto _88 = xninxs(_90);
            return _88;
          }
        }
      }();
      return _83;
    };
    return _82;
  };
  return _81;
};

std::function<_Void(_Elem<_Nat>)> falseElem1 = [](auto p) {
  auto _91 = [p]() {
    auto _92 = p;
    return _Void();
  }();
  return _91;
};

std::function<std::function<_Dec<_Elem<_Nat>>(_List<_Nat>)>(_Nat)> isElem = [](auto x) {
  auto _93 = [x](auto xss) {
    auto _94 = [xss, x]() {
      auto _95 = xss;
      switch (_95.type) {
        case Nil: {
          auto _97 = *(_List_Nil<_Nat>*)_95.data;
          auto _98 = falseElem1;
          auto _96 = _Dec<_Elem<_Nat>>::_No(_98);
          return _96;
        }
        case Cons: {
          auto _101 = *(_List_Cons<_Nat>*)_95.data;
          auto y = _101._1;
          auto xs = _101._2;
          auto _100 = [xss, x, y, xs]() {
            auto _103 = x;
            auto _104 = y;
            auto _102 = decEqNat(_103)(_104);
            switch (_102.type) {
              case Yes: {
                auto _106 = *(_Dec_Yes<_TyEq>*)_102.data;
                auto p = _106._1;
                auto _109 = x;
                auto _110 = xs;
                auto _108 = _Elem<_Nat>::_Here(_109, _110);
                auto _107 = _108;
                auto _105 = _Dec<_Elem<_Nat>>::_Yes(_107);
                return _105;
              }
              case No: {
                auto _112 = *(_Dec_No<_TyEq>*)_102.data;
                auto xneqy = _112._1;
                auto _111 = [xss, x, y, xs, xneqy]() {
                  auto _114 = x;
                  auto _115 = xs;
                  auto _113 = isElem(_114)(_115);
                  switch (_113.type) {
                    case Yes: {
                      auto _117 = *(_Dec_Yes<_Elem<_Nat>>*)_113.data;
                      auto xinxs = _117._1;
                      auto _119 = y;
                      auto _120 = x;
                      auto _121 = xs;
                      auto _122 = xinxs;
                      auto _118 = _Elem<_Nat>::_There(_119, _120, _121, _122);
                      auto _116 = _Dec<_Elem<_Nat>>::_Yes(_118);
                      return _116;
                    }
                    case No: {
                      auto _124 = *(_Dec_No<_Elem<_Nat>>*)_113.data;
                      auto xninxs = _124._1;
                      auto _126 = xneqy;
                      auto _127 = xninxs;
                      auto _125 = neitherHereNorThere(_126)(_127);
                      auto _123 = _Dec<_Elem<_Nat>>::_No(_125);
                      return _123;
                    }
                  }
                }();
                return _111;
              }
            }
          }();
          return _100;
        }
      }
    }();
    return _94;
  };
  return _93;
};

std::function<std::function<_Nat(_Nat)>(_Nat)> plus = [](auto n) {
  auto _131 = [n](auto m) {
    auto _132 = [n, m]() {
      auto _133 = n;
      switch (_133.type) {
        case Zero: {
          auto _135 = *(_Nat_Zero*)_133.data;
          auto _134 = m;
          return _134;
        }
        case Succ: {
          auto _137 = *(_Nat_Succ*)_133.data;
          auto pred = _137._1;
          auto _139 = pred;
          auto _140 = m;
          auto _138 = plus(_139)(_140);
          auto _136 = _Nat::_Succ(_138);
          return _136;
        }
      }
    }();
    return _132;
  };
  return _131;
};

template <class A>
std::function<std::function<_Vec<A>(_Vec<A>)>(_Vec<A>)> append = [](auto v1) {
  auto _141 = [v1](auto ys) {
    auto _142 = [v1, ys]() {
      auto _143 = v1;
      switch (_143.type) {
        case ConsV: {
          auto _145 = *(_Vec_ConsV<A>*)_143.data;
          auto x = _145._1;
          auto xs = _145._2;
          auto _146 = x;
          auto _149 = xs;
          auto _150 = ys;
          auto _147 = append<A>(_149)(_150);
          auto _144 = _Vec<A>::_ConsV(_146, _147);
          return _144;
        }
        case NilV: {
          auto _155 = *(_Vec_NilV<A>*)_143.data;
          auto _154 = ys;
          return _154;
        }
      }
    }();
    return _142;
  };
  return _141;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> trans = [](auto pf1) {
  auto _156 = [pf1](auto pf2) {
    auto _158 = pf1;
    auto _157 = _158;
    return _157;
  };
  return _156;
};
enum _enum_ElemVec_type { HereV, ThereV };
template <class A>
class _ElemVec {
 public:
  enum _enum_ElemVec_type type;
  void* data;
  static _ElemVec<A> _HereV(_Vec<A> _1);
  static _ElemVec<A> _ThereV(_Vec<A> _1, A _2, _ElemVec<A> _3);
};
template <class A>
class _ElemVec_HereV {
 public:
  _Vec<A> _1;
  _ElemVec_HereV(_Vec<A> _1) { this->_1 = _1; };
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
};
template <class A>
inline _ElemVec<A> _ElemVec<A>::_HereV(_Vec<A> _1) {
  _ElemVec_HereV<A>* _innerClass = new _ElemVec_HereV<A>(_1);
  return _ElemVec<A>{HereV, _innerClass};
};
template <class A>
inline _ElemVec<A> _ElemVec<A>::_ThereV(_Vec<A> _1, A _2, _ElemVec<A> _3) {
  _ElemVec_ThereV<A>* _innerClass = new _ElemVec_ThereV<A>(_1, _2, _3);
  return _ElemVec<A>{ThereV, _innerClass};
};

template <class A>
std::function<_Void(_ElemVec<A>)> xNotInNilV = [](auto p) {
  auto _159 = [p]() {
    auto _160 = p;
    return _Void();
  }();
  return _159;
};

std::function<std::function<std::function<_Void(_ElemVec<_Nat>)>(std::function<_Void(_ElemVec<_Nat>)>)>(std::function<_Void(_TyEq)>)> neitherHereNorThereVec = [](auto xneqy) {
  auto _161 = [xneqy](auto xninxs) {
    auto _162 = [xneqy, xninxs](auto p) {
      auto _163 = [p, xneqy, xninxs]() {
        auto _164 = p;
        switch (_164.type) {
          case HereV: {
            auto _166 = *(_ElemVec_HereV<_Nat>*)_164.data;
            auto as = _166._1;
            auto _167 = _TyEq::_Refl();
            auto _165 = xneqy(_167);
            return _165;
          }
          case ThereV: {
            auto _169 = *(_ElemVec_ThereV<_Nat>*)_164.data;
            auto as = _169._1;
            auto b = _169._2;
            auto prf = _169._3;
            auto _170 = prf;
            auto _168 = xninxs(_170);
            return _168;
          }
        }
      }();
      return _163;
    };
    return _162;
  };
  return _161;
};

std::function<std::function<_Dec<_ElemVec<_Nat>>(_Vec<_Nat>)>(_Nat)> isElemVec = [](auto x) {
  auto _171 = [x](auto xs) {
    auto _172 = [xs, x]() {
      auto _173 = xs;
      switch (_173.type) {
        case NilV: {
          auto _175 = *(_Vec_NilV<_Nat>*)_173.data;
          auto _176 = xNotInNilV<_Nat>;
          auto _174 = _Dec<_ElemVec<_Nat>>::_No(_176);
          return _174;
        }
        case ConsV: {
          auto _181 = *(_Vec_ConsV<_Nat>*)_173.data;
          auto y = _181._1;
          auto ys = _181._2;
          auto _180 = [xs, x, y, ys]() {
            auto _183 = x;
            auto _184 = y;
            auto _182 = decEqNat(_183)(_184);
            switch (_182.type) {
              case Yes: {
                auto _186 = *(_Dec_Yes<_TyEq>*)_182.data;
                auto pf = _186._1;
                auto _189 = ys;
                auto _188 = _ElemVec<_Nat>::_HereV(_189);
                auto _187 = _188;
                auto _185 = _Dec<_ElemVec<_Nat>>::_Yes(_187);
                return _185;
              }
              case No: {
                auto _192 = *(_Dec_No<_TyEq>*)_182.data;
                auto xneqyPf = _192._1;
                auto _191 = [xs, x, y, ys, xneqyPf]() {
                  auto _194 = x;
                  auto _195 = ys;
                  auto _193 = isElemVec(_194)(_195);
                  switch (_193.type) {
                    case Yes: {
                      auto _198 = *(_Dec_Yes<_ElemVec<_Nat>>*)_193.data;
                      auto pf = _198._1;
                      auto _200 = ys;
                      auto _201 = x;
                      auto _202 = pf;
                      auto _199 = _ElemVec<_Nat>::_ThereV(_200, _201, _202);
                      auto _197 = _Dec<_ElemVec<_Nat>>::_Yes(_199);
                      return _197;
                    }
                    case No: {
                      auto _205 = *(_Dec_No<_ElemVec<_Nat>>*)_193.data;
                      auto xninysPf = _205._1;
                      auto _207 = xneqyPf;
                      auto _208 = xninysPf;
                      auto _206 = neitherHereNorThereVec(_207)(_208);
                      auto _204 = _Dec<_ElemVec<_Nat>>::_No(_206);
                      return _204;
                    }
                  }
                }();
                return _191;
              }
            }
          }();
          return _180;
        }
      }
    }();
    return _172;
  };
  return _171;
};
enum _enum_Disjoint_type { DNil, DCons };
template <class A>
class _Disjoint {
 public:
  enum _enum_Disjoint_type type;
  void* data;
  static _Disjoint<A> _DNil();
  static _Disjoint<A> _DCons(A _1, _List<A> _2, std::function<_Void(_Elem<A>)> _3, _Disjoint<A> _4);
};
template <class A>
class _Disjoint_DNil {
 public:
  _Disjoint_DNil(){};
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
};
template <class A>
inline _Disjoint<A> _Disjoint<A>::_DNil() {
  _Disjoint_DNil<A>* _innerClass = new _Disjoint_DNil<A>();
  return _Disjoint<A>{DNil, _innerClass};
};
template <class A>
inline _Disjoint<A> _Disjoint<A>::_DCons(A _1, _List<A> _2, std::function<_Void(_Elem<A>)> _3, _Disjoint<A> _4) {
  _Disjoint_DCons<A>* _innerClass = new _Disjoint_DCons<A>(_1, _2, _3, _4);
  return _Disjoint<A>{DCons, _innerClass};
};

template <class A>
std::function<_Void(_Elem<A>)> xNotInNil = [](auto p) {
  auto _213 = [p]() {
    auto _214 = p;
    return _Void();
  }();
  return _213;
};

template <class A>
std::function<std::function<_Disjoint<A>(_TyEq)>(_List<A>)> lemma_y_empty_disjoint = [](auto a) {
  auto _215 = [a](auto pf) {
    auto _216 = [a, pf]() {
      auto _217 = a;
      switch (_217.type) {
        case Nil: {
          auto _219 = *(_List_Nil<A>*)_217.data;
          auto _218 = _Disjoint<A>::_DNil();
          return _218;
        }
        case Cons: {
          auto _221 = *(_List_Cons<A>*)_217.data;
          auto x = _221._1;
          auto xs = _221._2;
          auto _222 = x;
          auto _223 = xs;
          auto _226 = xNotInNil<A>;
          auto _224 = _226;
          auto _229 = xs;
          auto _230 = pf;
          auto _225 = lemma_y_empty_disjoint<A>(_229)(_230);
          auto _220 = _Disjoint<A>::_DCons(_222, _223, _224, _225);
          return _220;
        }
      }
    }();
    return _216;
  };
  return _215;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(_Elem<A>)> lemma_x_in_b = [](auto xInB) {
  auto _233 = [xInB](auto pf) {
    auto _234 = [pf, xInB]() {
      auto _235 = pf;
      switch (_235.type) {
        case DCons: {
          auto _237 = *(_Disjoint_DCons<A>*)_235.data;
          auto i = _237._1;
          auto is = _237._2;
          auto pfFori = _237._3;
          auto others = _237._4;
          auto _238 = xInB;
          auto _236 = pfFori(_238);
          return _236;
        }
      }
    }();
    return _234;
  };
  return _233;
};

template <class A>
std::function<std::function<_Void(_Disjoint<A>)>(std::function<_Void(_Disjoint<A>)>)> lemma_xs_in_b = [](auto pf) {
  auto _239 = [pf](auto p) {
    auto _240 = [p, pf]() {
      auto _241 = p;
      switch (_241.type) {
        case DCons: {
          auto _243 = *(_Disjoint_DCons<A>*)_241.data;
          auto i = _243._1;
          auto is = _243._2;
          auto pfFori = _243._3;
          auto others = _243._4;
          auto _244 = others;
          auto _242 = pf(_244);
          return _242;
        }
      }
    }();
    return _240;
  };
  return _239;
};

std::function<std::function<_Dec<_Disjoint<_Nat>>(_List<_Nat>)>(_List<_Nat>)> decDisjointLists = [](auto a) {
  auto _245 = [a](auto b) {
    auto _246 = [a, b]() {
      auto _247 = a;
      switch (_247.type) {
        case Nil: {
          auto _249 = *(_List_Nil<_Nat>*)_247.data;
          auto _250 = _Disjoint<_Nat>::_DNil();
          auto _248 = _Dec<_Disjoint<_Nat>>::_Yes(_250);
          return _248;
        }
        case Cons: {
          auto _252 = *(_List_Cons<_Nat>*)_247.data;
          auto x = _252._1;
          auto xs = _252._2;
          auto _251 = [a, b, xs, x]() {
            auto _253 = b;
            switch (_253.type) {
              case Nil: {
                auto _255 = *(_List_Nil<_Nat>*)_253.data;
                auto _257 = a;
                auto _258 = _TyEq::_Refl();
                auto _256 = lemma_y_empty_disjoint<_Nat>(_257)(_258);
                auto _254 = _Dec<_Disjoint<_Nat>>::_Yes(_256);
                return _254;
              }
              case Cons: {
                auto _262 = *(_List_Cons<_Nat>*)_253.data;
                auto y = _262._1;
                auto ys = _262._2;
                auto _261 = [a, b, xs, x]() {
                  auto _264 = xs;
                  auto _265 = b;
                  auto _263 = decDisjointLists(_264)(_265);
                  switch (_263.type) {
                    case Yes: {
                      auto _267 = *(_Dec_Yes<_Disjoint<_Nat>>*)_263.data;
                      auto pf = _267._1;
                      auto _266 = [a, b, xs, x, pf]() {
                        auto _269 = x;
                        auto _270 = b;
                        auto _268 = isElem(_269)(_270);
                        switch (_268.type) {
                          case Yes: {
                            auto _272 = *(_Dec_Yes<_Elem<_Nat>>*)_268.data;
                            auto elemPf = _272._1;
                            auto _274 = elemPf;
                            auto _273 = lemma_x_in_b<_Nat>(_274);
                            auto _271 = _Dec<_Disjoint<_Nat>>::_No(_273);
                            return _271;
                          }
                          case No: {
                            auto _281 = *(_Dec_No<_Elem<_Nat>>*)_268.data;
                            auto p = _281._1;
                            auto _283 = x;
                            auto _284 = xs;
                            auto _285 = p;
                            auto _286 = pf;
                            auto _282 = _Disjoint<_Nat>::_DCons(_283, _284, _285, _286);
                            auto _280 = _Dec<_Disjoint<_Nat>>::_Yes(_282);
                            return _280;
                          }
                        }
                      }();
                      return _266;
                    }
                    case No: {
                      auto _288 = *(_Dec_No<_Disjoint<_Nat>>*)_263.data;
                      auto p = _288._1;
                      auto _290 = p;
                      auto _289 = lemma_xs_in_b<_Nat>(_290);
                      auto _287 = _Dec<_Disjoint<_Nat>>::_No(_289);
                      return _287;
                    }
                  }
                }();
                return _261;
              }
            }
          }();
          return _251;
        }
      }
    }();
    return _246;
  };
  return _245;
};
enum _enum_DisjointVec_type { DNilV, DConsV };
template <class A>
class _DisjointVec {
 public:
  enum _enum_DisjointVec_type type;
  void* data;
  static _DisjointVec<A> _DNilV();
  static _DisjointVec<A> _DConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _DisjointVec<A> _4);
};
template <class A>
class _DisjointVec_DNilV {
 public:
  _DisjointVec_DNilV(){};
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
};
template <class A>
inline _DisjointVec<A> _DisjointVec<A>::_DNilV() {
  _DisjointVec_DNilV<A>* _innerClass = new _DisjointVec_DNilV<A>();
  return _DisjointVec<A>{DNilV, _innerClass};
};
template <class A>
inline _DisjointVec<A> _DisjointVec<A>::_DConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _DisjointVec<A> _4) {
  _DisjointVec_DConsV<A>* _innerClass = new _DisjointVec_DConsV<A>(_1, _2, _3, _4);
  return _DisjointVec<A>{DConsV, _innerClass};
};

template <class A>
std::function<std::function<_DisjointVec<A>(_TyEq)>(_Vec<A>)> lemma_y_empty_disjoint_vec = [](auto a) {
  auto _295 = [a](auto pf) {
    auto _296 = [a, pf]() {
      auto _297 = a;
      switch (_297.type) {
        case NilV: {
          auto _299 = *(_Vec_NilV<A>*)_297.data;
          auto _298 = _DisjointVec<A>::_DNilV();
          return _298;
        }
        case ConsV: {
          auto _301 = *(_Vec_ConsV<A>*)_297.data;
          auto x = _301._1;
          auto xs = _301._2;
          auto _302 = x;
          auto _303 = xs;
          auto _307 = xNotInNilV<A>;
          auto _304 = _307;
          auto _311 = xs;
          auto _312 = pf;
          auto _305 = lemma_y_empty_disjoint_vec<A>(_311)(_312);
          auto _300 = _DisjointVec<A>::_DConsV(_302, _303, _304, _305);
          return _300;
        }
      }
    }();
    return _296;
  };
  return _295;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(_ElemVec<A>)> lemma_x_in_b_vec = [](auto xInB) {
  auto _316 = [xInB](auto pf) {
    auto _317 = [pf, xInB]() {
      auto _318 = pf;
      switch (_318.type) {
        case DConsV: {
          auto _320 = *(_DisjointVec_DConsV<A>*)_318.data;
          auto y = _320._1;
          auto ys = _320._2;
          auto pfFory = _320._3;
          auto others = _320._4;
          auto _321 = xInB;
          auto _319 = pfFory(_321);
          return _319;
        }
      }
    }();
    return _317;
  };
  return _316;
};

template <class A>
std::function<std::function<_Void(_DisjointVec<A>)>(std::function<_Void(_DisjointVec<A>)>)> lemma_xs_in_b_vec = [](auto pf) {
  auto _322 = [pf](auto p) {
    auto _323 = [p, pf]() {
      auto _324 = p;
      switch (_324.type) {
        case DConsV: {
          auto _326 = *(_DisjointVec_DConsV<A>*)_324.data;
          auto i = _326._1;
          auto is = _326._2;
          auto pfFori = _326._3;
          auto others = _326._4;
          auto _327 = others;
          auto _325 = pf(_327);
          return _325;
        }
      }
    }();
    return _323;
  };
  return _322;
};

std::function<std::function<_Dec<_DisjointVec<_Nat>>(_Vec<_Nat>)>(_Vec<_Nat>)> decDisjointVecs = [](auto a) {
  auto _328 = [a](auto b) {
    auto _329 = [a, b]() {
      auto _330 = a;
      switch (_330.type) {
        case NilV: {
          auto _332 = *(_Vec_NilV<_Nat>*)_330.data;
          auto _333 = _DisjointVec<_Nat>::_DNilV();
          auto _331 = _Dec<_DisjointVec<_Nat>>::_Yes(_333);
          return _331;
        }
        case ConsV: {
          auto _335 = *(_Vec_ConsV<_Nat>*)_330.data;
          auto x = _335._1;
          auto xs = _335._2;
          auto _334 = [a, b, xs, x]() {
            auto _336 = b;
            switch (_336.type) {
              case NilV: {
                auto _338 = *(_Vec_NilV<_Nat>*)_336.data;
                auto _340 = a;
                auto _341 = _TyEq::_Refl();
                auto _339 = lemma_y_empty_disjoint_vec<_Nat>(_340)(_341);
                auto _337 = _Dec<_DisjointVec<_Nat>>::_Yes(_339);
                return _337;
              }
              case ConsV: {
                auto _346 = *(_Vec_ConsV<_Nat>*)_336.data;
                auto y = _346._1;
                auto ys = _346._2;
                auto _345 = [a, b, xs, x]() {
                  auto _348 = xs;
                  auto _349 = b;
                  auto _347 = decDisjointVecs(_348)(_349);
                  switch (_347.type) {
                    case Yes: {
                      auto _353 = *(_Dec_Yes<_DisjointVec<_Nat>>*)_347.data;
                      auto pf = _353._1;
                      auto _352 = [a, b, xs, x, pf]() {
                        auto _355 = x;
                        auto _356 = b;
                        auto _354 = isElemVec(_355)(_356);
                        switch (_354.type) {
                          case Yes: {
                            auto _359 = *(_Dec_Yes<_ElemVec<_Nat>>*)_354.data;
                            auto elemPf = _359._1;
                            auto _361 = elemPf;
                            auto _360 = lemma_x_in_b_vec<_Nat>(_361);
                            auto _358 = _Dec<_DisjointVec<_Nat>>::_No(_360);
                            return _358;
                          }
                          case No: {
                            auto _370 = *(_Dec_No<_ElemVec<_Nat>>*)_354.data;
                            auto p = _370._1;
                            auto _372 = x;
                            auto _373 = xs;
                            auto _374 = p;
                            auto _375 = pf;
                            auto _371 = _DisjointVec<_Nat>::_DConsV(_372, _373, _374, _375);
                            auto _369 = _Dec<_DisjointVec<_Nat>>::_Yes(_371);
                            return _369;
                          }
                        }
                      }();
                      return _352;
                    }
                    case No: {
                      auto _378 = *(_Dec_No<_DisjointVec<_Nat>>*)_347.data;
                      auto p = _378._1;
                      auto _380 = p;
                      auto _379 = lemma_xs_in_b_vec<_Nat>(_380);
                      auto _377 = _Dec<_DisjointVec<_Nat>>::_No(_379);
                      return _377;
                    }
                  }
                }();
                return _345;
              }
            }
          }();
          return _334;
        }
      }
    }();
    return _329;
  };
  return _328;
};

std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjLem = [](auto prf1) {
  auto _387 = [](auto prf2) {
    auto _390 = prf2;
    auto _389 = f_equal<_Vec<_Nat>, _Vec<_Nat>>(_390);
    auto _388 = _389;
    return _388;
  };
  return _387;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjective = [](auto p1) {
  auto _396 = [](auto p2) {
    auto _399 = p2;
    auto _398 = f_equal<_Vec<A>, _Vec<A>>(_399);
    auto _397 = _398;
    return _397;
  };
  return _396;
};

template <class A>
std::function<std::function<_TyEq(_TyEq)>(_TyEq)> consVInjectiveTail = [](auto p1) {
  auto _405 = [](auto p2) {
    auto _407 = p2;
    auto _406 = f_equal<_Vec<A>, A>(_407);
    return _406;
  };
  return _405;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(_TyEq)> lemma_x_eq_xs_neq_vec = [](auto prf1) {
  auto _413 = [prf1](auto p) {
    auto _414 = [p, prf1](auto prf2) {
      auto _417 = prf1;
      auto _418 = prf2;
      auto _416 = consVInjective<A>(_417)(_418);
      auto _415 = p(_416);
      return _415;
    };
    return _414;
  };
  return _413;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(_TyEq)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_eq_vec = [](auto p) {
  auto _425 = [p](auto p2) {
    auto _426 = [p, p2](auto p3) {
      auto _429 = p2;
      auto _430 = p3;
      auto _428 = consVInjectiveTail<A>(_429)(_430);
      auto _427 = p(_428);
      return _427;
    };
    return _426;
  };
  return _425;
};

template <class A>
std::function<std::function<std::function<_Void(_TyEq)>(std::function<_Void(_TyEq)>)>(std::function<_Void(_TyEq)>)> lemma_x_neq_xs_neq_vec = [](auto p) {
  auto _437 = [p](auto p2) {
    auto _438 = [p](auto p3) {
      auto _441 = p3;
      auto _440 = f_equal<_Vec<A>, A>(_441);
      auto _439 = p(_440);
      return _439;
    };
    return _438;
  };
  return _437;
};

std::function<std::function<_Dec<_TyEq>(_Vec<_Nat>)>(_Vec<_Nat>)> decEqVec = [](auto a) {
  auto _447 = [a](auto b) {
    auto _448 = [a, b]() {
      auto _449 = a;
      switch (_449.type) {
        case NilV: {
          auto _451 = *(_Vec_NilV<_Nat>*)_449.data;
          auto _450 = [a, b]() {
            auto _452 = b;
            switch (_452.type) {
              case NilV: {
                auto _454 = *(_Vec_NilV<_Nat>*)_452.data;
                auto _455 = _TyEq::_Refl();
                auto _453 = _Dec<_TyEq>::_Yes(_455);
                return _453;
              }
            }
          }();
          return _450;
        }
        case ConsV: {
          auto _457 = *(_Vec_ConsV<_Nat>*)_449.data;
          auto x = _457._1;
          auto xs = _457._2;
          auto _456 = [a, b, x, xs]() {
            auto _458 = b;
            switch (_458.type) {
              case ConsV: {
                auto _460 = *(_Vec_ConsV<_Nat>*)_458.data;
                auto y = _460._1;
                auto ys = _460._2;
                auto _459 = [a, b, x, y, xs, ys]() {
                  auto _462 = x;
                  auto _463 = y;
                  auto _461 = decEqNat(_462)(_463);
                  switch (_461.type) {
                    case Yes: {
                      auto _465 = *(_Dec_Yes<_TyEq>*)_461.data;
                      auto xeqy = _465._1;
                      auto _464 = [a, b, x, y, xs, ys, xeqy]() {
                        auto _467 = xs;
                        auto _468 = ys;
                        auto _466 = decEqVec(_467)(_468);
                        switch (_466.type) {
                          case Yes: {
                            auto _471 = *(_Dec_Yes<_TyEq>*)_466.data;
                            auto xseqys = _471._1;
                            auto _473 = xeqy;
                            auto _474 = xseqys;
                            auto _472 = consVInjLem(_473)(_474);
                            auto _470 = _Dec<_TyEq>::_Yes(_472);
                            return _470;
                          }
                          case No: {
                            auto _481 = *(_Dec_No<_TyEq>*)_466.data;
                            auto xsneqys = _481._1;
                            auto _483 = xeqy;
                            auto _484 = xsneqys;
                            auto _482 = lemma_x_eq_xs_neq_vec<_Nat>(_483)(_484);
                            auto _480 = _Dec<_TyEq>::_No(_482);
                            return _480;
                          }
                        }
                      }();
                      return _464;
                    }
                    case No: {
                      auto _492 = *(_Dec_No<_TyEq>*)_461.data;
                      auto xneqy = _492._1;
                      auto _491 = [a, b, x, y, xs, ys, xneqy]() {
                        auto _494 = xs;
                        auto _495 = ys;
                        auto _493 = decEqVec(_494)(_495);
                        switch (_493.type) {
                          case Yes: {
                            auto _498 = *(_Dec_Yes<_TyEq>*)_493.data;
                            auto xseqys = _498._1;
                            auto _500 = xneqy;
                            auto _501 = xseqys;
                            auto _499 = lemma_x_neq_xs_eq_vec<_Nat>(_500)(_501);
                            auto _497 = _Dec<_TyEq>::_No(_499);
                            return _497;
                          }
                          case No: {
                            auto _509 = *(_Dec_No<_TyEq>*)_493.data;
                            auto xsneqys = _509._1;
                            auto _511 = xneqy;
                            auto _512 = xsneqys;
                            auto _510 = lemma_x_neq_xs_neq_vec<_Nat>(_511)(_512);
                            auto _508 = _Dec<_TyEq>::_No(_510);
                            return _508;
                          }
                        }
                      }();
                      return _491;
                    }
                  }
                }();
                return _459;
              }
            }
          }();
          return _456;
        }
      }
    }();
    return _448;
  };
  return _447;
};
enum _enum_UniqueVec_type { UNilV, UConsV };
template <class A>
class _UniqueVec {
 public:
  enum _enum_UniqueVec_type type;
  void* data;
  static _UniqueVec<A> _UNilV();
  static _UniqueVec<A> _UConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _UniqueVec<A> _4);
};
template <class A>
class _UniqueVec_UNilV {
 public:
  _UniqueVec_UNilV(){};
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
};
template <class A>
inline _UniqueVec<A> _UniqueVec<A>::_UNilV() {
  _UniqueVec_UNilV<A>* _innerClass = new _UniqueVec_UNilV<A>();
  return _UniqueVec<A>{UNilV, _innerClass};
};
template <class A>
inline _UniqueVec<A> _UniqueVec<A>::_UConsV(A _1, _Vec<A> _2, std::function<_Void(_ElemVec<A>)> _3, _UniqueVec<A> _4) {
  _UniqueVec_UConsV<A>* _innerClass = new _UniqueVec_UConsV<A>(_1, _2, _3, _4);
  return _UniqueVec<A>{UConsV, _innerClass};
};

template <class A>
std::function<std::function<_Void(_UniqueVec<A>)>(_ElemVec<A>)> lemma_x_in_xs_not_unique = [](auto pf) {
  auto _519 = [pf](auto p) {
    auto _520 = [p, pf]() {
      auto _521 = p;
      switch (_521.type) {
        case UConsV: {
          auto _523 = *(_UniqueVec_UConsV<A>*)_521.data;
          auto x = _523._1;
          auto xs = _523._2;
          auto xNInXs = _523._3;
          auto others = _523._4;
          auto _524 = pf;
          auto _522 = xNInXs(_524);
          return _522;
        }
      }
    }();
    return _520;
  };
  return _519;
};

template <class A>
std::function<std::function<_Void(_UniqueVec<A>)>(std::function<_Void(_UniqueVec<A>)>)> lemma_xs_not_unique = [](auto pf) {
  auto _525 = [pf](auto p) {
    auto _526 = [p, pf]() {
      auto _527 = p;
      switch (_527.type) {
        case UConsV: {
          auto _529 = *(_UniqueVec_UConsV<A>*)_527.data;
          auto x = _529._1;
          auto xs = _529._2;
          auto xNInXs = _529._3;
          auto others = _529._4;
          auto _530 = others;
          auto _528 = pf(_530);
          return _528;
        }
      }
    }();
    return _526;
  };
  return _525;
};

std::function<_Dec<_UniqueVec<_Nat>>(_Vec<_Nat>)> decUniqueVec = [](auto v) {
  auto _531 = [v]() {
    auto _532 = v;
    switch (_532.type) {
      case NilV: {
        auto _534 = *(_Vec_NilV<_Nat>*)_532.data;
        auto _535 = _UniqueVec<_Nat>::_UNilV();
        auto _533 = _Dec<_UniqueVec<_Nat>>::_Yes(_535);
        return _533;
      }
      case ConsV: {
        auto _537 = *(_Vec_ConsV<_Nat>*)_532.data;
        auto x = _537._1;
        auto xs = _537._2;
        auto _536 = [v, x, xs]() {
          auto _539 = x;
          auto _540 = xs;
          auto _538 = isElemVec(_539)(_540);
          switch (_538.type) {
            case Yes: {
              auto _543 = *(_Dec_Yes<_ElemVec<_Nat>>*)_538.data;
              auto xInXs = _543._1;
              auto _545 = xInXs;
              auto _544 = lemma_x_in_xs_not_unique<_Nat>(_545);
              auto _542 = _Dec<_UniqueVec<_Nat>>::_No(_544);
              return _542;
            }
            case No: {
              auto _551 = *(_Dec_No<_ElemVec<_Nat>>*)_538.data;
              auto xNInXs = _551._1;
              auto _550 = [v, x, xs, xNInXs]() {
                auto _553 = xs;
                auto _552 = decUniqueVec(_553);
                switch (_552.type) {
                  case Yes: {
                    auto _556 = *(_Dec_Yes<_UniqueVec<_Nat>>*)_552.data;
                    auto xsU = _556._1;
                    auto _558 = x;
                    auto _559 = xs;
                    auto _560 = xNInXs;
                    auto _561 = xsU;
                    auto _557 = _UniqueVec<_Nat>::_UConsV(_558, _559, _560, _561);
                    auto _555 = _Dec<_UniqueVec<_Nat>>::_Yes(_557);
                    return _555;
                  }
                  case No: {
                    auto _564 = *(_Dec_No<_UniqueVec<_Nat>>*)_552.data;
                    auto xsNU = _564._1;
                    auto _566 = xsNU;
                    auto _565 = lemma_xs_not_unique<_Nat>(_566);
                    auto _563 = _Dec<_UniqueVec<_Nat>>::_No(_565);
                    return _563;
                  }
                }
              }();
              return _550;
            }
          }
        }();
        return _536;
      }
    }
  }();
  return _531;
};
enum _enum_SubsetVec_type { SNilV1, SNilV2, SConsV };
template <class A>
class _SubsetVec {
 public:
  enum _enum_SubsetVec_type type;
  void* data;
  static _SubsetVec<A> _SNilV1();
  static _SubsetVec<A> _SNilV2();
  static _SubsetVec<A> _SConsV(A _1, _Vec<A> _2, _ElemVec<A> _3, _SubsetVec<A> _4);
};
template <class A>
class _SubsetVec_SNilV1 {
 public:
  _SubsetVec_SNilV1(){};
};
template <class A>
class _SubsetVec_SNilV2 {
 public:
  _SubsetVec_SNilV2(){};
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
};
template <class A>
inline _SubsetVec<A> _SubsetVec<A>::_SNilV1() {
  _SubsetVec_SNilV1<A>* _innerClass = new _SubsetVec_SNilV1<A>();
  return _SubsetVec<A>{SNilV1, _innerClass};
};
template <class A>
inline _SubsetVec<A> _SubsetVec<A>::_SNilV2() {
  _SubsetVec_SNilV2<A>* _innerClass = new _SubsetVec_SNilV2<A>();
  return _SubsetVec<A>{SNilV2, _innerClass};
};
template <class A>
inline _SubsetVec<A> _SubsetVec<A>::_SConsV(A _1, _Vec<A> _2, _ElemVec<A> _3, _SubsetVec<A> _4) {
  _SubsetVec_SConsV<A>* _innerClass = new _SubsetVec_SConsV<A>(_1, _2, _3, _4);
  return _SubsetVec<A>{SConsV, _innerClass};
};

template <class A>
std::function<std::function<_Void(_SubsetVec<A>)>(std::function<_Void(_ElemVec<A>)>)> lemma_x_not_in_b_vec = [](auto pfXNotInb) {
  auto _571 = [pfXNotInb](auto pf) {
    auto _572 = [pf, pfXNotInb]() {
      auto _573 = pf;
      switch (_573.type) {
        case SConsV: {
          auto _575 = *(_SubsetVec_SConsV<A>*)_573.data;
          auto a = _575._1;
          auto as = _575._2;
          auto pfFora = _575._3;
          auto others = _575._4;
          auto _576 = pfFora;
          auto _574 = pfXNotInb(_576);
          return _574;
        }
      }
    }();
    return _572;
  };
  return _571;
};

template <class A>
std::function<std::function<_Void(_SubsetVec<A>)>(std::function<_Void(_SubsetVec<A>)>)> lemma_xs_not_subset_b_vec = [](auto xsNotSubsetPf) {
  auto _577 = [xsNotSubsetPf](auto p) {
    auto _578 = [p, xsNotSubsetPf]() {
      auto _579 = p;
      switch (_579.type) {
        case SConsV: {
          auto _581 = *(_SubsetVec_SConsV<A>*)_579.data;
          auto a = _581._1;
          auto as = _581._2;
          auto pfFora = _581._3;
          auto others = _581._4;
          auto _582 = others;
          auto _580 = xsNotSubsetPf(_582);
          return _580;
        }
      }
    }();
    return _578;
  };
  return _577;
};

std::function<std::function<_Dec<_SubsetVec<_Nat>>(_Vec<_Nat>)>(_Vec<_Nat>)> decSubsetVecs = [](auto a) {
  auto _583 = [a](auto b) {
    auto _584 = [a, b]() {
      auto _585 = a;
      switch (_585.type) {
        case NilV: {
          auto _587 = *(_Vec_NilV<_Nat>*)_585.data;
          auto _588 = _SubsetVec<_Nat>::_SNilV1();
          auto _586 = _Dec<_SubsetVec<_Nat>>::_Yes(_588);
          return _586;
        }
        case ConsV: {
          auto _590 = *(_Vec_ConsV<_Nat>*)_585.data;
          auto x = _590._1;
          auto xs = _590._2;
          auto _589 = [a, b, xs, x]() {
            auto _591 = b;
            switch (_591.type) {
              case NilV: {
                auto _593 = *(_Vec_NilV<_Nat>*)_591.data;
                auto _594 = _SubsetVec<_Nat>::_SNilV2();
                auto _592 = _Dec<_SubsetVec<_Nat>>::_Yes(_594);
                return _592;
              }
              case ConsV: {
                auto _596 = *(_Vec_ConsV<_Nat>*)_591.data;
                auto y = _596._1;
                auto ys = _596._2;
                auto _595 = [a, b, xs, x]() {
                  auto _598 = xs;
                  auto _599 = b;
                  auto _597 = decSubsetVecs(_598)(_599);
                  switch (_597.type) {
                    case Yes: {
                      auto _603 = *(_Dec_Yes<_SubsetVec<_Nat>>*)_597.data;
                      auto pf = _603._1;
                      auto _602 = [a, b, xs, x, pf]() {
                        auto _605 = x;
                        auto _606 = b;
                        auto _604 = isElemVec(_605)(_606);
                        switch (_604.type) {
                          case Yes: {
                            auto _609 = *(_Dec_Yes<_ElemVec<_Nat>>*)_604.data;
                            auto elemPf = _609._1;
                            auto _611 = x;
                            auto _612 = xs;
                            auto _613 = elemPf;
                            auto _614 = pf;
                            auto _610 = _SubsetVec<_Nat>::_SConsV(_611, _612, _613, _614);
                            auto _608 = _Dec<_SubsetVec<_Nat>>::_Yes(_610);
                            return _608;
                          }
                          case No: {
                            auto _617 = *(_Dec_No<_ElemVec<_Nat>>*)_604.data;
                            auto p = _617._1;
                            auto _619 = p;
                            auto _618 = lemma_x_not_in_b_vec<_Nat>(_619);
                            auto _616 = _Dec<_SubsetVec<_Nat>>::_No(_618);
                            return _616;
                          }
                        }
                      }();
                      return _602;
                    }
                    case No: {
                      auto _628 = *(_Dec_No<_SubsetVec<_Nat>>*)_597.data;
                      auto p = _628._1;
                      auto _630 = p;
                      auto _629 = lemma_xs_not_subset_b_vec<_Nat>(_630);
                      auto _627 = _Dec<_SubsetVec<_Nat>>::_No(_629);
                      return _627;
                    }
                  }
                }();
                return _595;
              }
            }
          }();
          return _589;
        }
      }
    }();
    return _584;
  };
  return _583;
};
enum _enum_IO_type { MkIO };
template <class A>
class _IO {
 public:
  enum _enum_IO_type type;
  void* data;
  static _IO<A> _MkIO(A _1);
};
template <class A>
class _IO_MkIO {
 public:
  A _1;
  _IO_MkIO(A _1) { this->_1 = _1; };
};
template <class A>
inline _IO<A> _IO<A>::_MkIO(A _1) {
  _IO_MkIO<A>* _innerClass = new _IO_MkIO<A>(_1);
  return _IO<A>{MkIO, _innerClass};
};

template <class A>
std::function<_IO<A>(A)> returnIO = [](auto a) {
  auto _639 = a;
  auto _638 = _IO<A>::_MkIO(_639);
  return _638;
};

template <class A, class B>
std::function<std::function<_IO<B>(std::function<_IO<B>(A)>)>(_IO<A>)> bindEq = [](auto a) {
  auto _640 = [a](auto f) {
    auto _641 = [a, f]() {
      auto _642 = a;
      switch (_642.type) {
        case MkIO: {
          auto _644 = *(_IO_MkIO<A>*)_642.data;
          auto inner = _644._1;
          auto _645 = inner;
          auto _643 = f(_645);
          return _643;
        }
      }
    }();
    return _641;
  };
  return _640;
};

template <class A, class B>
std::function<std::function<_IO<B>(_IO<B>)>(_IO<A>)> bind = [](auto a) {
  auto _646 = [a](auto b) {
    auto _648 = a;
    auto _649 = [a, b](auto c) {
      auto _652 = b;
      return _652;
    };
    auto _647 = bindEq<A, B>(_648)(_649);
    return _647;
  };
  return _646;
};
enum _enum_Channel_type { MkChannel };
template <class A>
class _Channel {
 public:
  enum _enum_Channel_type type;
  void* data;
  static _Channel<A> _MkChannel(_Nat _1);
};
template <class A>
class _Channel_MkChannel {
 public:
  _Nat _1;
  _Channel_MkChannel(_Nat _1) { this->_1 = _1; };
};
template <class A>
inline _Channel<A> _Channel<A>::_MkChannel(_Nat _1) {
  _Channel_MkChannel<A>* _innerClass = new _Channel_MkChannel<A>(_1);
  return _Channel<A>{MkChannel, _innerClass};
};

template <class A>
std::function<_Bool(_Nat)> prim_create_channel = [](auto id) {
  LockingCQueue<_Maybe<A>>* q = new LockingCQueue<_Maybe<A>>();
  addChannel(intFromNat(id), q);
  return _Bool::_True();
};

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_Channel<A>)>(_Maybe<A>)>(_Nat)> channelEnqueue = [](auto id) {
  auto _629 = [id](auto x) {
    auto _630 = [id, x](auto ch) {
      LockingCQueue<_Maybe<A>>* queue = (LockingCQueue<_Maybe<A>>*)getChannel(intFromNat(id));
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
std::function<std::function<_IO<_Maybe<A>>(_Channel<A>)>(_Nat)> channelDequeue = [](auto id) {
  auto _630 = [id](auto ch) {
    LockingCQueue<_Maybe<A>>* queue = (LockingCQueue<_Maybe<A>>*)getChannel(intFromNat(id));
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
std::function<std::function<std::function<_IO<_Unit>(_Channel<A>)>(_Maybe<A>)>(_Nat)> send = [](auto id) {
  auto _653 = [id](auto x) {
    auto _654 = [id, x](auto ch) {
      auto _656 = id;
      auto _657 = x;
      auto _658 = ch;
      auto _655 = channelEnqueue<A>(_656)(_657)(_658);
      return _655;
    };
    return _654;
  };
  return _653;
};

template <class A>
std::function<std::function<_IO<_Maybe<A>>(_Channel<A>)>(_Nat)> receive = [](auto id) {
  auto _660 = [id](auto ch) {
    auto _662 = id;
    auto _663 = ch;
    auto _661 = channelDequeue<A>(_662)(_663);
    return _661;
  };
  return _660;
};

template <class A>
std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>>(std::function<_Void(_ElemVec<_Nat>)>)>(_Vec<_Nat>)>(_Nat)> link =
    [](auto id) {
      auto _665 = [id](auto idSet) {
        auto _666 = [id, idSet](auto pf) {
          auto _667 = [id, idSet]() {
            auto _669 = id;
            auto _668 = prim_create_channel<A>(_669);
            switch (_668.type) {
              case True: {
                auto _672 = *(_Bool_True*)_668.data;
                auto _676 = id;
                auto _680 = id;
                auto _678 = _Channel<A>::_MkChannel(_680);
                auto _683 = id;
                auto _684 = idSet;
                auto _681 = _Vec<_Nat>::_ConsV(_683, _684);
                auto _686 = _TyEq::_Refl();
                auto _687 = _TyEq::_Refl();
                auto _682 = _Sigma<_TyEq, _TyEq>::_Prod(_686, _687);
                auto _679 = _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>::_Prod(_681, _682);
                auto _677 = _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>::_Prod(_678, _679);
                auto _675 = _Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>::_Prod(_676, _677);
                auto _673 = _Maybe<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>::_Just(_675);
                auto _671 = returnIO<_Maybe<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>>(_673);
                return _671;
              }
              case False: {
                auto _689 = *(_Bool_False*)_668.data;
                auto _690 = _Maybe<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>::_Nothing();
                auto _688 = returnIO<_Maybe<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>>(_690);
                return _688;
              }
            }
          }();
          return _667;
        };
        return _666;
      };
      return _665;
    };

std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>(std::function<_Void(_ElemVec<_Nat>)>)>(_Vec<_Nat>)>(_Nat)>(_Nat)> spawn =
    [](auto pid) {
      auto _692 = [pid](auto n) {
        auto _693 = [pid](auto pidSet) {
          auto _694 = [pid, pidSet](auto pf) {
            auto _699 = pid;
            auto _703 = pid;
            auto _704 = pidSet;
            auto _701 = _Vec<_Nat>::_ConsV(_703, _704);
            auto _706 = _TyEq::_Refl();
            auto _707 = _TyEq::_Refl();
            auto _702 = _Sigma<_TyEq, _TyEq>::_Prod(_706, _707);
            auto _700 = _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>::_Prod(_701, _702);
            auto _698 = _Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>::_Prod(_699, _700);
            auto _696 = _Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>::_Just(_698);
            auto _695 = returnIO<_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>(_696);
            return _695;
          };
          return _694;
        };
        return _693;
      };
      return _692;
    };

std::function<std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_IO<_Unit>)>(_ElemVec<_Nat>)>(_Vec<_Nat>)>(_Nat)>(_Nat)> run = [](auto pid) {
  auto _708 = [](auto n) {
    auto _709 = [](auto pidSet) {
      auto _710 = [pidSet](auto pf) {
        auto _711 = [pidSet](auto process) {
          auto _716 = pidSet;
          auto _717 = _TyEq::_Refl();
          auto _715 = _Sigma<_Vec<_Nat>, _TyEq>::_Prod(_716, _717);
          auto _713 = _Maybe<_Sigma<_Vec<_Nat>, _TyEq>>::_Just(_715);
          auto _712 = returnIO<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_713);
          return _712;
        };
        return _711;
      };
      return _710;
    };
    return _709;
  };
  return _708;
};

std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>(_IO<_Unit>)>(std::function<_Void(_ElemVec<_Nat>)>)>(_Vec<_Nat>)>(_Nat)>
    spawnAndRun = [](auto pid) {
      auto _719 = [pid](auto pidSet) {
        auto _720 = [pid, pidSet](auto pf) {
          auto _721 = [pid, pidSet](auto proc) {  // Spawning the thread
            try {
              std::thread* t = new std::thread([proc]() { proc; });
              addThread(intFromNat(pid), t);
            } catch (std::system_error) {
              return returnIO<_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>(_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>::_Nothing());
            }
            auto _726 = pid;
            auto _730 = pid;
            auto _731 = pidSet;
            auto _728 = _Vec<_Nat>::_ConsV(_730, _731);
            auto _733 = _TyEq::_Refl();
            auto _734 = _TyEq::_Refl();
            auto _729 = _Sigma<_TyEq, _TyEq>::_Prod(_733, _734);
            auto _727 = _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>::_Prod(_728, _729);
            auto _725 = _Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>::_Prod(_726, _727);
            auto _723 = _Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>::_Just(_725);
            auto _722 = returnIO<_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>(_723);
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
class _Farm {
 public:
  enum _enum_Farm_type type;
  void* data;
  static _Farm<A> _MkFarm(_Nat _1, std::function<A(A)> _2);
};
template <class A>
class _Farm_MkFarm {
 public:
  _Nat _1;
  std::function<A(A)> _2;
  _Farm_MkFarm(_Nat _1, std::function<A(A)> _2) {
    this->_1 = _1;
    this->_2 = _2;
  };
};
template <class A>
inline _Farm<A> _Farm<A>::_MkFarm(_Nat _1, std::function<A(A)> _2) {
  _Farm_MkFarm<A>* _innerClass = new _Farm_MkFarm<A>(_1, _2);
  return _Farm<A>{MkFarm, _innerClass};
};

template <class A>
std::function<std::function<std::function<_IO<_Unit>(_List<A>)>(_Channel<A>)>(_Nat)> producerWrapper = [](auto id) {
  auto _718 = [id](auto ch) {
    auto _719 = [id, ch](auto list) {
      auto _720 = [list, id, ch]() {
        auto _721 = list;
        switch (_721.type) {
          case Nil: {
            auto _723 = *(_List_Nil<A>*)_721.data;
            auto _728 = id;
            auto _729 = _Maybe<A>::_Nothing();
            auto _730 = ch;
            auto _724 = send<A>(_728)(_729)(_730);
            auto _725 = end;
            auto _722 = bind<_Unit, _Unit>(_724)(_725);
            return _722;
          }
          case Cons: {
            auto _733 = *(_List_Cons<A>*)_721.data;
            auto x = _733._1;
            auto xs = _733._2;
            auto _738 = id;
            auto _742 = x;
            auto _739 = _Maybe<A>::_Just(_742);
            auto _740 = ch;
            auto _734 = send<A>(_738)(_739)(_740);
            auto _743 = id;
            auto _744 = ch;
            auto _745 = xs;
            auto _735 = producerWrapper<A>(_743)(_744)(_745);
            auto _732 = bind<_Unit, _Unit>(_734)(_735);
            return _732;
          }
        }
      }();
      return _720;
    };
    return _719;
  };
  return _718;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_Channel<A>)>(_Channel<A>)>(_Nat)>(_Nat)> workerWrapper = [](auto receiveId) {
  auto _747 = [receiveId](auto sendId) {
    auto _748 = [receiveId, sendId](auto receiveChannel) {
      auto _749 = [receiveId, receiveChannel, sendId](auto sendChannel) {
        auto _750 = [receiveId, receiveChannel, sendId, sendChannel](auto f) {
          auto _756 = receiveId;
          auto _757 = receiveChannel;
          auto _752 = receive<A>(_756)(_757);
          auto _753 = [receiveId, receiveChannel, sendId, sendChannel, f](auto mx) {
            auto _759 = [receiveId, receiveChannel, mx, sendId, sendChannel, f]() {
              auto _760 = mx;
              switch (_760.type) {
                case Nothing: {
                  auto _762 = *(_Maybe_Nothing<A>*)_760.data;
                  auto _767 = sendId;
                  auto _768 = _Maybe<A>::_Nothing();
                  auto _769 = sendChannel;
                  auto _763 = send<A>(_767)(_768)(_769);
                  auto _764 = end;
                  auto _761 = bind<_Unit, _Unit>(_763)(_764);
                  return _761;
                }
                case Just: {
                  auto _772 = *(_Maybe_Just<A>*)_760.data;
                  auto x = _772._1;
                  auto _777 = sendId;
                  auto _782 = x;
                  auto _781 = f(_782);
                  auto _778 = _Maybe<A>::_Just(_781);
                  auto _779 = sendChannel;
                  auto _773 = send<A>(_777)(_778)(_779);
                  auto _783 = receiveId;
                  auto _784 = sendId;
                  auto _785 = receiveChannel;
                  auto _786 = sendChannel;
                  auto _787 = f;
                  auto _774 = workerWrapper<A>(_783)(_784)(_785)(_786)(_787);
                  auto _771 = bind<_Unit, _Unit>(_773)(_774);
                  return _771;
                }
              }
            }();
            return _759;
          };
          auto _751 = bindEq<_Maybe<A>, _Unit>(_752)(_753);
          return _751;
        };
        return _750;
      };
      return _749;
    };
    return _748;
  };
  return _747;
};

template <class A>
std::function<std::function<_IO<_List<A>>(_Channel<A>)>(_Nat)> consumerWrapper = [](auto chid) {
  auto _789 = [chid](auto ch) {
    auto _795 = chid;
    auto _796 = ch;
    auto _791 = receive<A>(_795)(_796);
    auto _792 = [chid, ch](auto mx) {
      auto _798 = [chid, ch, mx]() {
        auto _799 = mx;
        switch (_799.type) {
          case Nothing: {
            auto _801 = *(_Maybe_Nothing<A>*)_799.data;
            auto _802 = _List<A>::_Nil();
            auto _800 = returnIO<_List<A>>(_802);
            return _800;
          }
          case Just: {
            auto _805 = *(_Maybe_Just<A>*)_799.data;
            auto x = _805._1;
            auto _810 = chid;
            auto _811 = ch;
            auto _806 = consumerWrapper<A>(_810)(_811);
            auto _807 = [chid, ch, mx, x](auto res) {
              auto _816 = x;
              auto _817 = res;
              auto _814 = _List<A>::_Cons(_816, _817);
              auto _813 = returnIO<_List<A>>(_814);
              return _813;
            };
            auto _804 = bindEq<_List<A>, _List<A>>(_806)(_807);
            return _804;
          }
        }
      }();
      return _798;
    };
    auto _790 = bindEq<_Maybe<A>, _List<A>>(_791)(_792);
    return _790;
  };
  return _789;
};

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<
    std::function<_IO<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(std::function<A(A)>)>(_Sigma<_Nat, _Channel<A>>)>(_Vec<_Sigma<_Nat, _Channel<A>>>)>(_UniqueVec<_Nat>)>(_Vec<_Nat>)>(_Nat)>(_Vec<_Nat>)>(_Nat)>
    spawnWorkersFarm = [](auto n) {
      auto _818 = [n](auto pidSet) {
        auto _819 = [pidSet, n](auto nDash) {
          auto _820 = [pidSet, n, nDash](auto pids) {
            auto _821 = [pids, pidSet, n, nDash](auto pidPf) {
              auto _822 = [pids, pidSet, pidPf, n, nDash](auto chs) {
                auto _823 = [pids, pidSet, pidPf, chs, n, nDash](auto consumerCh) {
                  auto _824 = [consumerCh, pids, pidSet, pidPf, chs, n, nDash](auto f) {
                    auto _825 = [consumerCh, pids, pidSet, pidPf, chs, f, n, nDash]() {
                      auto _826 = consumerCh;
                      switch (_826.type) {
                        case Prod: {
                          auto _828 = *(_Sigma_Prod<_Nat, _Channel<A>>*)_826.data;
                          auto consumerChid = _828._1;
                          auto consumerChannel = _828._2;
                          auto _827 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash]() {
                            auto _829 = pids;
                            switch (_829.type) {
                              case NilV: {
                                auto _831 = *(_Vec_NilV<_Nat>*)_829.data;
                                auto _835 = pidSet;
                                auto _836 = _TyEq::_Refl();
                                auto _834 = _Sigma<_Vec<_Nat>, _TyEq>::_Prod(_835, _836);
                                auto _832 = _Maybe<_Sigma<_Vec<_Nat>, _TyEq>>::_Just(_834);
                                auto _830 = returnIO<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_832);
                                return _830;
                              }
                              case ConsV: {
                                auto _838 = *(_Vec_ConsV<_Nat>*)_829.data;
                                auto x = _838._1;
                                auto xs = _838._2;
                                auto _837 = [consumerCh, pids, pidSet, pidPf, chs, consumerChid, consumerChannel, f, n, nDash, xs]() {
                                  auto _839 = pidPf;
                                  switch (_839.type) {
                                    case UConsV: {
                                      auto _841 = *(_UniqueVec_UConsV<_Nat>*)_839.data;
                                      auto y = _841._1;
                                      auto ys = _841._2;
                                      auto pf = _841._3;
                                      auto restPf = _841._4;
                                      auto _840 = [consumerCh, pids, pidSet, pidPf, chs, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf]() {
                                        auto _842 = chs;
                                        switch (_842.type) {
                                          case ConsV: {
                                            auto _844 = *(_Vec_ConsV<_Sigma<_Nat, _Channel<A>>>*)_842.data;
                                            auto curCh = _844._1;
                                            auto restChs = _844._2;
                                            auto _843 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, consumerChid, consumerChannel, f, n, nDash, xs, restPf, restChs]() {
                                              auto _845 = curCh;
                                              switch (_845.type) {
                                                case Prod: {
                                                  auto _847 = *(_Sigma_Prod<_Nat, _Channel<A>>*)_845.data;
                                                  auto currChid = _847._1;
                                                  auto currChannel = _847._2;
                                                  auto _852 = y;
                                                  auto _853 = ys;
                                                  auto _854 = pf;
                                                  auto _857 = currChid;
                                                  auto _858 = consumerChid;
                                                  auto _859 = currChannel;
                                                  auto _860 = consumerChannel;
                                                  auto _861 = f;
                                                  auto _855 = workerWrapper<A>(_857)(_858)(_859)(_860)(_861);
                                                  auto _848 = spawnAndRun(_852)(_853)(_854)(_855);
                                                  auto _849 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, n, nDash, xs, restPf,
                                                               restChs](auto mres) {
                                                    auto _863 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash, xs,
                                                                 restPf, restChs]() {
                                                      auto _864 = mres;
                                                      switch (_864.type) {
                                                        case Nothing: {
                                                          auto _866 = *(_Maybe_Nothing<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>*)_864.data;
                                                          auto _867 = _Maybe<_Sigma<_Vec<_Nat>, _TyEq>>::_Nothing();
                                                          auto _865 = returnIO<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_867);
                                                          return _865;
                                                        }
                                                        case Just: {
                                                          auto _870 = *(_Maybe_Just<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>*)_864.data;
                                                          auto res = _870._1;
                                                          auto _875 = n;
                                                          auto _876 = pidSet;
                                                          auto _884 = nDash;
                                                          auto _877 = pred(_884);
                                                          auto _878 = xs;
                                                          auto _879 = restPf;
                                                          auto _880 = restChs;
                                                          auto _881 = consumerCh;
                                                          auto _882 = f;
                                                          auto _871 = spawnWorkersFarm<A>(_875)(_876)(_877)(_878)(_879)(_880)(_881)(_882);
                                                          auto _872 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n, nDash,
                                                                       xs, restPf, restChs](auto mress) {
                                                            auto _885 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n,
                                                                         nDash, xs, restPf, restChs, mress]() {
                                                              auto _886 = mress;
                                                              switch (_886.type) {
                                                                case Nothing: {
                                                                  auto _888 = *(_Maybe_Nothing<_Sigma<_Vec<_Nat>, _TyEq>>*)_886.data;
                                                                  auto _889 = _Maybe<_Sigma<_Vec<_Nat>, _TyEq>>::_Nothing();
                                                                  auto _887 = returnIO<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_889);
                                                                  return _887;
                                                                }
                                                                case Just: {
                                                                  auto _892 = *(_Maybe_Just<_Sigma<_Vec<_Nat>, _TyEq>>*)_886.data;
                                                                  auto res = _892._1;
                                                                  auto _891 = [consumerCh, pids, pidSet, pidPf, chs, curCh, y, ys, pf, currChid, consumerChid, currChannel, consumerChannel, f, mres, n,
                                                                               nDash, xs, restPf, restChs, mress, res]() {
                                                                    auto _893 = res;
                                                                    switch (_893.type) {
                                                                      case Prod: {
                                                                        auto _895 = *(_Sigma_Prod<_Vec<_Nat>, _TyEq>*)_893.data;
                                                                        auto newPidSet = _895._1;
                                                                        auto pfNewPidSetCorrect = _895._2;
                                                                        auto _901 = y;
                                                                        auto _902 = newPidSet;
                                                                        auto _899 = _Vec<_Nat>::_ConsV(_901, _902);
                                                                        auto _904 = _TyEq::_Refl();
                                                                        auto _900 = _904;
                                                                        auto _898 = _Sigma<_Vec<_Nat>, _TyEq>::_Prod(_899, _900);
                                                                        auto _896 = _Maybe<_Sigma<_Vec<_Nat>, _TyEq>>::_Just(_898);
                                                                        auto _894 = returnIO<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_896);
                                                                        return _894;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _891;
                                                                }
                                                              }
                                                            }();
                                                            return _885;
                                                          };
                                                          auto _869 = bindEq<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>, _Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_871)(_872);
                                                          return _869;
                                                        }
                                                      }
                                                    }();
                                                    return _863;
                                                  };
                                                  auto _846 = bindEq<_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>, _Maybe<_Sigma<_Vec<_Nat>, _TyEq>>>(_848)(_849);
                                                  return _846;
                                                }
                                              }
                                            }();
                                            return _843;
                                          }
                                        }
                                      }();
                                      return _840;
                                    }
                                  }
                                }();
                                return _837;
                              }
                            }
                          }();
                          return _827;
                        }
                      }
                    }();
                    return _825;
                  };
                  return _824;
                };
                return _823;
              };
              return _822;
            };
            return _821;
          };
          return _820;
        };
        return _819;
      };
      return _818;
    };

template <class A>
std::function<
    std::function<std::function<std::function<std::function<_IO<_Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>>(_UniqueVec<_Nat>)>(_Vec<_Nat>)>(_Nat)>(_Vec<_Nat>)>(_Nat)>
    createChannelsFarm = [](auto m) {
      auto _905 = [m](auto chidSet) {
        auto _906 = [chidSet, m](auto mDash) {
          auto _907 = [chidSet, m, mDash](auto chids) {
            auto _908 = [chids, chidSet, m, mDash](auto chidPf) {
              auto _909 = [chids, chidSet, chidPf, m, mDash]() {
                auto _910 = chids;
                switch (_910.type) {
                  case NilV: {
                    auto _912 = *(_Vec_NilV<_Nat>*)_910.data;
                    auto _916 = _Vec<_Sigma<_Nat, _Channel<A>>>::_NilV();
                    auto _918 = chidSet;
                    auto _919 = _TyEq::_Refl();
                    auto _917 = _Sigma<_Vec<_Nat>, _TyEq>::_Prod(_918, _919);
                    auto _915 = _Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>::_Prod(_916, _917);
                    auto _913 = _Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>::_Just(_915);
                    auto _911 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>>(_913);
                    return _911;
                  }
                  case ConsV: {
                    auto _921 = *(_Vec_ConsV<_Nat>*)_910.data;
                    auto x = _921._1;
                    auto xs = _921._2;
                    auto _920 = [chids, chidSet, chidPf, m, mDash, xs]() {
                      auto _922 = chidPf;
                      switch (_922.type) {
                        case UConsV: {
                          auto _924 = *(_UniqueVec_UConsV<_Nat>*)_922.data;
                          auto y = _924._1;
                          auto ys = _924._2;
                          auto pf = _924._3;
                          auto restPf = _924._4;
                          auto _929 = y;
                          auto _930 = ys;
                          auto _931 = pf;
                          auto _925 = link<A>(_929)(_930)(_931);
                          auto _926 = [chids, chidSet, chidPf, y, ys, pf, m, mDash, xs, restPf](auto mres) {
                            auto _934 = [chids, chidSet, chidPf, y, ys, pf, mres, m, mDash, xs, restPf]() {
                              auto _935 = mres;
                              switch (_935.type) {
                                case Nothing: {
                                  auto _937 = *(_Maybe_Nothing<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>*)_935.data;
                                  auto _938 = _Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>::_Nothing();
                                  auto _936 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>>(_938);
                                  return _936;
                                }
                                case Just: {
                                  auto _941 = *(_Maybe_Just<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>*)_935.data;
                                  auto res = _941._1;
                                  auto _940 = [chids, chidSet, chidPf, y, ys, pf, mres, res, m, mDash, xs, restPf]() {
                                    auto _942 = res;
                                    switch (_942.type) {
                                      case Prod: {
                                        auto _944 = *(_Sigma_Prod<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>*)_942.data;
                                        auto resChid = _944._1;
                                        auto rest1 = _944._2;
                                        auto _943 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, m, mDash, xs, restPf]() {
                                          auto _945 = rest1;
                                          switch (_945.type) {
                                            case Prod: {
                                              auto _947 = *(_Sigma_Prod<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>*)_945.data;
                                              auto ch = _947._1;
                                              auto rest2 = _947._2;
                                              auto _946 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, m, mDash, xs, restPf, ch]() {
                                                auto _948 = rest2;
                                                switch (_948.type) {
                                                  case Prod: {
                                                    auto _950 = *(_Sigma_Prod<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>*)_948.data;
                                                    auto newChidSet = _950._1;
                                                    auto pfs = _950._2;
                                                    auto _949 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch]() {
                                                      auto _951 = pfs;
                                                      switch (_951.type) {
                                                        case Prod: {
                                                          auto _953 = *(_Sigma_Prod<_TyEq, _TyEq>*)_951.data;
                                                          auto chidEqResChidPf = _953._1;
                                                          auto pfNewChidSetCorrect = _953._2;
                                                          auto _958 = m;
                                                          auto _959 = chidSet;
                                                          auto _964 = mDash;
                                                          auto _960 = pred(_964);
                                                          auto _961 = xs;
                                                          auto _962 = restPf;
                                                          auto _954 = createChannelsFarm<A>(_958)(_959)(_960)(_961)(_962);
                                                          auto _955 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, ch](auto mress) {
                                                            auto _965 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ch]() {
                                                              auto _966 = mress;
                                                              switch (_966.type) {
                                                                case Nothing: {
                                                                  auto _968 = *(_Maybe_Nothing<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>*)_966.data;
                                                                  auto _969 = _Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>::_Nothing();
                                                                  auto _967 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>>(_969);
                                                                  return _967;
                                                                }
                                                                case Just: {
                                                                  auto _972 = *(_Maybe_Just<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>*)_966.data;
                                                                  auto ress = _972._1;
                                                                  auto _971 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, ch]() {
                                                                    auto _973 = ress;
                                                                    switch (_973.type) {
                                                                      case Prod: {
                                                                        auto _975 = *(_Sigma_Prod<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>*)_973.data;
                                                                        auto chs = _975._1;
                                                                        auto rest3 = _975._2;
                                                                        auto _974 = [chids, chidSet, chidPf, y, ys, pf, mres, res, rest1, rest2, pfs, m, mDash, xs, restPf, mress, ress, rest3, ch,
                                                                                     chs]() {
                                                                          auto _976 = rest3;
                                                                          switch (_976.type) {
                                                                            case Prod: {
                                                                              auto _978 = *(_Sigma_Prod<_Vec<_Nat>, _TyEq>*)_976.data;
                                                                              auto returnedChidSet = _978._1;
                                                                              auto pfReturnedChidSetCorrect = _978._2;
                                                                              auto _988 = y;
                                                                              auto _989 = ch;
                                                                              auto _987 = _Sigma<_Nat, _Channel<A>>::_Prod(_988, _989);
                                                                              auto _984 = _987;
                                                                              auto _985 = chs;
                                                                              auto _982 = _Vec<_Sigma<_Nat, _Channel<A>>>::_ConsV(_984, _985);
                                                                              auto _992 = y;
                                                                              auto _993 = returnedChidSet;
                                                                              auto _990 = _Vec<_Nat>::_ConsV(_992, _993);
                                                                              auto _995 = _TyEq::_Refl();
                                                                              auto _991 = _995;
                                                                              auto _983 = _Sigma<_Vec<_Nat>, _TyEq>::_Prod(_990, _991);
                                                                              auto _981 = _Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>::_Prod(_982, _983);
                                                                              auto _979 = _Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>::_Just(_981);
                                                                              auto _977 = returnIO<_Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>>(_979);
                                                                              return _977;
                                                                            }
                                                                          }
                                                                        }();
                                                                        return _974;
                                                                      }
                                                                    }
                                                                  }();
                                                                  return _971;
                                                                }
                                                              }
                                                            }();
                                                            return _965;
                                                          };
                                                          auto _952 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>,
                                                                             _Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>>(_954)(_955);
                                                          return _952;
                                                        }
                                                      }
                                                    }();
                                                    return _949;
                                                  }
                                                }
                                              }();
                                              return _946;
                                            }
                                          }
                                        }();
                                        return _943;
                                      }
                                    }
                                  }();
                                  return _940;
                                }
                              }
                            }();
                            return _934;
                          };
                          auto _923 =
                              bindEq<_Maybe<_Sigma<_Nat, _Sigma<_Channel<A>, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>>, _Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>>(
                                  _925)(_926);
                          return _923;
                        }
                      }
                    }();
                    return _920;
                  }
                }
              }();
              return _909;
            };
            return _908;
          };
          return _907;
        };
        return _906;
      };
      return _905;
    };

template <class A>
std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<std::function<
    std::function<std::function<_IO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(_List<A>)>(std::function<A(A)>)>(_TyEq)>(_TyEq)>(
    std::function<_Void(_TyEq)>)>(_Nat)>(_UniqueVec<_Nat>)>(_Vec<_Nat>)>(_Nat)>(_Vec<_Nat>)>(_Nat)>(_UniqueVec<_Nat>)>(_Vec<_Nat>)>(_Nat)>(_Vec<_Nat>)>(_Nat)>
    createFarm = [](auto n) {
      auto _996 = [n](auto pidSet) {
        auto _997 = [n, pidSet](auto nDash) {
          auto _998 = [n, pidSet, nDash](auto pids) {
            auto _999 = [pids, n, pidSet, nDash](auto pidPf) {
              auto _1000 = [pids, pidPf, n, pidSet, nDash](auto m) {
                auto _1001 = [m, pids, pidPf, n, pidSet, nDash](auto chidSet) {
                  auto _1002 = [m, chidSet, pids, pidPf, n, pidSet, nDash](auto mDash) {
                    auto _1003 = [m, chidSet, mDash, pids, pidPf, n, pidSet, nDash](auto chids) {
                      auto _1004 = [m, chidSet, mDash, chids, pids, pidPf, n, pidSet, nDash](auto chidPf) {
                        auto _1005 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash](auto numWorkers) {
                          auto _1006 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfNotZ) {
                            auto _1007 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfPidsNCorrect) {
                              auto _1008 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto pfChidsMCorrect) {
                                auto _1009 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, numWorkers](auto f) {
                                  auto _1010 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, n, pidSet, nDash, f, numWorkers](auto input) {
                                    auto _1016 = m;
                                    auto _1017 = chidSet;
                                    auto _1018 = mDash;
                                    auto _1019 = chids;
                                    auto _1020 = chidPf;
                                    auto _1012 = createChannelsFarm<A>(_1016)(_1017)(_1018)(_1019)(_1020);
                                    auto _1013 = [m, chidSet, mDash, chids, chidPf, pids, pidPf, input, n, pidSet, nDash, f, numWorkers](auto mres1) {
                                      auto _1022 = [m, chidSet, mDash, chids, chidPf, mres1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                        auto _1023 = mres1;
                                        switch (_1023.type) {
                                          case Nothing: {
                                            auto _1025 = *(_Maybe_Nothing<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>*)_1023.data;
                                            auto _1026 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>::_Nothing();
                                            auto _1024 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(_1026);
                                            return _1024;
                                          }
                                          case Just: {
                                            auto _1029 = *(_Maybe_Just<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>*)_1023.data;
                                            auto res1 = _1029._1;
                                            auto _1028 = [m, chidSet, mDash, chids, chidPf, mres1, res1, pids, pidPf, input, n, pidSet, nDash, f, numWorkers]() {
                                              auto _1030 = res1;
                                              switch (_1030.type) {
                                                case Prod: {
                                                  auto _1032 = *(_Sigma_Prod<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>*)_1030.data;
                                                  auto chs = _1032._1;
                                                  auto chidPfToReturn = _1032._2;
                                                  auto _1031 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, pids, pidPf, input, n, pidSet, nDash, f, numWorkers, chidPfToReturn]() {
                                                    auto _1033 = chs;
                                                    switch (_1033.type) {
                                                      case NilV: {
                                                        auto _1035 = *(_Vec_NilV<_Sigma<_Nat, _Channel<A>>>*)_1033.data;
                                                        auto _1036 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>::_Nothing();
                                                        auto _1034 = returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(_1036);
                                                        return _1034;
                                                      }
                                                      case ConsV: {
                                                        auto _1039 = *(_Vec_ConsV<_Sigma<_Nat, _Channel<A>>>*)_1033.data;
                                                        auto consumerCh = _1039._1;
                                                        auto otherChs = _1039._2;
                                                        auto _1038 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, input, n, pidSet, nDash, otherChs, f, numWorkers,
                                                                      chidPfToReturn]() {
                                                          auto _1040 = consumerCh;
                                                          switch (_1040.type) {
                                                            case Prod: {
                                                              auto _1042 = *(_Sigma_Prod<_Nat, _Channel<A>>*)_1040.data;
                                                              auto consumerChid = _1042._1;
                                                              auto consumerChannel = _1042._2;
                                                              auto _1041 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, consumerChid, consumerChannel, input, n,
                                                                            pidSet, nDash, otherChs, f, numWorkers, chidPfToReturn]() {
                                                                auto _1043 = pids;
                                                                switch (_1043.type) {
                                                                  case NilV: {
                                                                    auto _1045 = *(_Vec_NilV<_Nat>*)_1043.data;
                                                                    auto _1046 = _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>::_Nothing();
                                                                    auto _1044 =
                                                                        returnIO<_Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(_1046);
                                                                    return _1044;
                                                                  }
                                                                  case ConsV: {
                                                                    auto _1049 = *(_Vec_ConsV<_Nat>*)_1043.data;
                                                                    auto x = _1049._1;
                                                                    auto xs = _1049._2;
                                                                    auto _1048 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, consumerChid, consumerChannel, input, n,
                                                                                  pidSet, nDash, xs, otherChs, f, numWorkers, chidPfToReturn]() {
                                                                      auto _1050 = pidPf;
                                                                      switch (_1050.type) {
                                                                        case UConsV: {
                                                                          auto _1052 = *(_UniqueVec_UConsV<_Nat>*)_1050.data;
                                                                          auto producerPid = _1052._1;
                                                                          auto restPids = _1052._2;
                                                                          auto producerPidPf = _1052._3;
                                                                          auto restPfs = _1052._4;
                                                                          auto _1057 = producerPid;
                                                                          auto _1058 = restPids;
                                                                          auto _1059 = producerPidPf;
                                                                          auto _1062 = consumerChid;
                                                                          auto _1063 = consumerChannel;
                                                                          auto _1064 = input;
                                                                          auto _1060 = producerWrapper<A>(_1062)(_1063)(_1064);
                                                                          auto _1053 = spawnAndRun(_1057)(_1058)(_1059)(_1060);
                                                                          auto _1054 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                        producerPidPf, consumerChid, consumerChannel, input, n, pidSet, nDash, xs, restPfs, otherChs, f, numWorkers,
                                                                                        chidPfToReturn](auto mres2) {
                                                                            auto _1066 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                          producerPidPf, consumerChid, consumerChannel, input, mres2, n, pidSet, nDash, xs, restPfs, otherChs, f,
                                                                                          numWorkers, chidPfToReturn]() {
                                                                              auto _1067 = mres2;
                                                                              switch (_1067.type) {
                                                                                case Nothing: {
                                                                                  auto _1069 = *(_Maybe_Nothing<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>*)_1067.data;
                                                                                  auto _1070 = _Maybe<
                                                                                      _Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>::_Nothing();
                                                                                  auto _1068 = returnIO<
                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(_1070);
                                                                                  return _1068;
                                                                                }
                                                                                case Just: {
                                                                                  auto _1073 = *(_Maybe_Just<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>*)_1067.data;
                                                                                  auto res2 = _1073._1;
                                                                                  auto _1078 = n;
                                                                                  auto _1079 = pidSet;
                                                                                  auto _1087 = nDash;
                                                                                  auto _1080 = pred(_1087);
                                                                                  auto _1081 = xs;
                                                                                  auto _1082 = restPfs;
                                                                                  auto _1088 = otherChs;
                                                                                  auto _1083 = _1088;
                                                                                  auto _1084 = consumerCh;
                                                                                  auto _1085 = f;
                                                                                  auto _1074 = spawnWorkersFarm<A>(_1078)(_1079)(_1080)(_1081)(_1082)(_1083)(_1084)(_1085);
                                                                                  auto _1075 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                producerPidPf, consumerChid, consumerChannel, input, mres2, n, pidSet, nDash, xs, restPfs, otherChs, f,
                                                                                                numWorkers, chidPfToReturn](auto mres3) {
                                                                                    auto _1089 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid, restPids,
                                                                                                  producerPidPf, consumerChid, consumerChannel, input, mres2, n, pidSet, nDash, xs, restPfs, otherChs,
                                                                                                  f, mres3, numWorkers, chidPfToReturn]() {
                                                                                      auto _1090 = mres3;
                                                                                      switch (_1090.type) {
                                                                                        case Nothing: {
                                                                                          auto _1092 = *(_Maybe_Nothing<_Sigma<_Vec<_Nat>, _TyEq>>*)_1090.data;
                                                                                          auto _1093 =
                                                                                              _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>::
                                                                                                  _Nothing();
                                                                                          auto _1091 = returnIO<
                                                                                              _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(
                                                                                              _1093);
                                                                                          return _1091;
                                                                                        }
                                                                                        case Just: {
                                                                                          auto _1096 = *(_Maybe_Just<_Sigma<_Vec<_Nat>, _TyEq>>*)_1090.data;
                                                                                          auto workerPidPfs = _1096._1;
                                                                                          auto _1095 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                        restPids, producerPidPf, consumerChid, consumerChannel, input, mres2, n, pidSet, nDash, xs,
                                                                                                        restPfs, otherChs, f, mres3, workerPidPfs, numWorkers, chidPfToReturn]() {
                                                                                            auto _1097 = workerPidPfs;
                                                                                            switch (_1097.type) {
                                                                                              case Prod: {
                                                                                                auto _1099 = *(_Sigma_Prod<_Vec<_Nat>, _TyEq>*)_1097.data;
                                                                                                auto workersPidSet = _1099._1;
                                                                                                auto workerPidSetPf = _1099._2;
                                                                                                auto _1104 = consumerChid;
                                                                                                auto _1105 = consumerChannel;
                                                                                                auto _1100 = consumerWrapper<A>(_1104)(_1105);
                                                                                                auto _1101 = [m, chidSet, mDash, chids, chidPf, mres1, res1, chs, consumerCh, pids, pidPf, producerPid,
                                                                                                              restPids, producerPidPf, consumerChid, consumerChannel, input, mres2, n, pidSet, nDash,
                                                                                                              xs, restPfs, otherChs, f, mres3, workerPidPfs, numWorkers, workersPidSet, workerPidSetPf,
                                                                                                              chidPfToReturn](auto resultantList) {
                                                                                                  auto _1111 = resultantList;
                                                                                                  auto _1115 = numWorkers;
                                                                                                  auto _1116 = f;
                                                                                                  auto _1113 = _Farm<A>::_MkFarm(_1115, _1116);
                                                                                                  auto _1121 = producerPid;
                                                                                                  auto _1122 = workersPidSet;
                                                                                                  auto _1119 = _Vec<_Nat>::_ConsV(_1121, _1122);
                                                                                                  auto _1124 = _TyEq::_Refl();
                                                                                                  auto _1125 = workerPidSetPf;
                                                                                                  auto _1120 = consVInjLem(_1124)(_1125);
                                                                                                  auto _1117 = _Sigma<_Vec<_Nat>, _TyEq>::_Prod(_1119, _1120);
                                                                                                  auto _1118 = chidPfToReturn;
                                                                                                  auto _1114 = _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>::_Prod(_1117, _1118);
                                                                                                  auto _1112 = _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>::_Prod(
                                                                                                      _1113, _1114);
                                                                                                  auto _1110 =
                                                                                                      _Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>::
                                                                                                          _Prod(_1111, _1112);
                                                                                                  auto _1108 =
                                                                                                      _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>,
                                                                                                                                                      _Sigma<_Vec<_Nat>, _TyEq>>>>>::_Just(_1110);
                                                                                                  auto _1107 = returnIO<_Maybe<_Sigma<
                                                                                                      _List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(
                                                                                                      _1108);
                                                                                                  return _1107;
                                                                                                };
                                                                                                auto _1098 =
                                                                                                    bindEq<_List<A>, _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>,
                                                                                                                                                                     _Sigma<_Vec<_Nat>, _TyEq>>>>>>(
                                                                                                        _1100)(_1101);
                                                                                                return _1098;
                                                                                              }
                                                                                            }
                                                                                          }();
                                                                                          return _1095;
                                                                                        }
                                                                                      }
                                                                                    }();
                                                                                    return _1089;
                                                                                  };
                                                                                  auto _1072 =
                                                                                      bindEq<_Maybe<_Sigma<_Vec<_Nat>, _TyEq>>,
                                                                                             _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(
                                                                                          _1074)(_1075);
                                                                                  return _1072;
                                                                                }
                                                                              }
                                                                            }();
                                                                            return _1066;
                                                                          };
                                                                          auto _1051 = bindEq<_Maybe<_Sigma<_Nat, _Sigma<_Vec<_Nat>, _Sigma<_TyEq, _TyEq>>>>,
                                                                                              _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(
                                                                              _1053)(_1054);
                                                                          return _1051;
                                                                        }
                                                                      }
                                                                    }();
                                                                    return _1048;
                                                                  }
                                                                }
                                                              }();
                                                              return _1041;
                                                            }
                                                          }
                                                        }();
                                                        return _1038;
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
                                    auto _1011 = bindEq<_Maybe<_Sigma<_Vec<_Sigma<_Nat, _Channel<A>>>, _Sigma<_Vec<_Nat>, _TyEq>>>,
                                                        _Maybe<_Sigma<_List<A>, _Sigma<_Farm<A>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>>(_1012)(_1013);
                                    return _1011;
                                  };
                                  return _1010;
                                };
                                return _1009;
                              };
                              return _1008;
                            };
                            return _1007;
                          };
                          return _1006;
                        };
                        return _1005;
                      };
                      return _1004;
                    };
                    return _1003;
                  };
                  return _1002;
                };
                return _1001;
              };
              return _1000;
            };
            return _999;
          };
          return _998;
        };
        return _997;
      };
      return _996;
    };

std::function<_Nat(_Nat)> id = [](auto a) {
  auto _1131 = a;
  return _1131;
};

_IO<_Unit> main2 = []() {
  auto _1132 = []() {
    auto _1145 = _Nat::_Zero();
    auto _1144 = _Nat::_Succ(_1145);
    auto _1141 = _Nat::_Succ(_1144);
    auto _1149 = _Nat::_Zero();
    auto _1146 = _Nat::_Succ(_1149);
    auto _1147 = _Vec<_Nat>::_NilV();
    auto _1142 = _Vec<_Nat>::_ConsV(_1146, _1147);
    auto _1136 = _Vec<_Nat>::_ConsV(_1141, _1142);
    auto _1137 = _Vec<_Nat>::_NilV();
    auto _1134 = append<_Nat>(_1136)(_1137);
    auto _1133 = decUniqueVec(_1134);
    switch (_1133.type) {
      case Yes: {
        auto _1151 = *(_Dec_Yes<_UniqueVec<_Nat>>*)_1133.data;
        auto pf1 = _1151._1;
        auto _1156 = _Nat::_Zero();
        auto _1157 = _Vec<_Nat>::_NilV();
        auto _1174 = _Nat::_Zero();
        auto _1173 = _Nat::_Succ(_1174);
        auto _1158 = _Nat::_Succ(_1173);
        auto _1179 = _Nat::_Zero();
        auto _1178 = _Nat::_Succ(_1179);
        auto _1175 = _Nat::_Succ(_1178);
        auto _1183 = _Nat::_Zero();
        auto _1180 = _Nat::_Succ(_1183);
        auto _1181 = _Vec<_Nat>::_NilV();
        auto _1176 = _Vec<_Nat>::_ConsV(_1180, _1181);
        auto _1159 = _Vec<_Nat>::_ConsV(_1175, _1176);
        auto _1160 = pf1;
        auto _1161 = _Nat::_Zero();
        auto _1162 = _Vec<_Nat>::_NilV();
        auto _1185 = _Nat::_Zero();
        auto _1184 = _Nat::_Succ(_1185);
        auto _1163 = _Nat::_Succ(_1184);
        auto _1190 = _Nat::_Zero();
        auto _1189 = _Nat::_Succ(_1190);
        auto _1186 = _Nat::_Succ(_1189);
        auto _1194 = _Nat::_Zero();
        auto _1191 = _Nat::_Succ(_1194);
        auto _1192 = _Vec<_Nat>::_NilV();
        auto _1187 = _Vec<_Nat>::_ConsV(_1191, _1192);
        auto _1164 = _Vec<_Nat>::_ConsV(_1186, _1187);
        auto _1165 = pf1;
        auto _1195 = _Nat::_Zero();
        auto _1166 = _Nat::_Succ(_1195);
        auto _1200 = _Nat::_Zero();
        auto _1196 = ZnotS(_1200);
        auto _1167 = negEqSym<_Nat>(_1196);
        auto _1168 = _TyEq::_Refl();
        auto _1169 = _TyEq::_Refl();
        auto _1170 = id;
        auto _1203 = _Nat::_Zero();
        auto _1201 = _Nat::_Succ(_1203);
        auto _1202 = _List<_Nat>::_Nil();
        auto _1171 = _List<_Nat>::_Cons(_1201, _1202);
        auto _1152 = createFarm<_Nat>(_1156)(_1157)(_1158)(_1159)(_1160)(_1161)(_1162)(_1163)(_1164)(_1165)(_1166)(_1167)(_1168)(_1169)(_1170)(_1171);
        auto _1153 = end;
        auto _1150 = bind<_Maybe<_Sigma<_List<_Nat>, _Sigma<_Farm<_Nat>, _Sigma<_Sigma<_Vec<_Nat>, _TyEq>, _Sigma<_Vec<_Nat>, _TyEq>>>>>, _Unit>(_1152)(_1153);
        return _1150;
      }
    }
  }();
  return _1132;
}();
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
void addChannel(int chid, LockingCQueue<_Maybe<A>>* queue) {
  // Aquireing the lock
  std::lock_guard<std::mutex> lock(channelMutex);
  std::cout << queue << std::endl;
  // adding the channel
  channelsMap[chid] = queue;
}

int main() {
  
  //LockingCQueue<_Maybe<_Nat>>* q = new LockingCQueue<_Maybe<_Nat>>();

  //addChannel(intFromNat(_Nat::_Succ(_Nat::_Succ(_Nat::_Zero()))), q);
  //std::cout << getChannel(intFromNat(_Nat::_Succ(_Nat::_Succ(_Nat::_Zero())))) << std::endl;

  std::cout << intFromNat(_Nat::_Succ(_Nat::_Succ(_Nat::_Zero()))) << std::endl;
}