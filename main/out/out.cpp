#include <vector>
#include <functional>
#include <thread>
#include <optional>
#include <iostream>
#include <memory>
#include <system_error>
#include <map>
#include <string>
#include <cstdint>
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

inline _TyEq _TyEq::_Refl() {
    return _TyEq{};
}enum _enum_Sigma_type {Prod};template <class a, class b> class _Sigma_Prod;
template <class a, class b> class _Sigma { public: enum _enum_Sigma_type type; std::shared_ptr<void> data;static _Sigma<a,b> _Prod(a _1, b _2);_Sigma<a,b>(_enum_Sigma_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_Sigma<a,b>(const _Sigma<a,b>& other);
_Sigma<a,b>() = default;};template <class a, class b> class _Sigma_Prod { public: a _1;b _2;_Sigma_Prod (a _1, b _2) {this->_1= _1;this->_2= _2;};_Sigma_Prod (const _Sigma_Prod* other) { this->_1= other->_1;this->_2= other->_2;} };template <class a, class b>  inline _Sigma<a,b> _Sigma<a,b>::_Prod(a _1, b _2){ return  _Sigma<a,b> ( Prod, std::make_shared<_Sigma_Prod<a,b>>(_1, _2)); };template <class a, class b> _Sigma<a,b>::_Sigma(const _Sigma<a,b>& other) { type = other.type; data = other.data; } 
enum _enum_Unit_type {unit};class _Unit_unit;
class _Unit { public: enum _enum_Unit_type type; std::shared_ptr<void> data;static _Unit _unit();_Unit(_enum_Unit_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_Unit(const _Unit& other);
_Unit() = default;};class _Unit_unit { public: _Unit_unit () {};_Unit_unit (const _Unit_unit* other) { } }; inline _Unit _Unit::_unit(){ return  _Unit ( unit, std::make_shared<_Unit_unit>()); };_Unit::_Unit(const _Unit& other) { type = other.type; data = other.data; } 
enum _enum_Bool_type {False,True};class _Bool_False;
class _Bool_True;
class _Bool { public: enum _enum_Bool_type type; std::shared_ptr<void> data;static _Bool _False();static _Bool _True();_Bool(_enum_Bool_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_Bool(const _Bool& other);
_Bool() = default;};class _Bool_False { public: _Bool_False () {};_Bool_False (const _Bool_False* other) { } };class _Bool_True { public: _Bool_True () {};_Bool_True (const _Bool_True* other) { } }; inline _Bool _Bool::_False(){ return  _Bool ( False, std::make_shared<_Bool_False>()); }; inline _Bool _Bool::_True(){ return  _Bool ( True, std::make_shared<_Bool_True>()); };_Bool::_Bool(const _Bool& other) { type = other.type; data = other.data; } 
enum _enum_List_type {Nil,Cons};template <class c> class _List_Nil;
template <class c> class _List_Cons;
template <class c> class _List { public: enum _enum_List_type type; std::shared_ptr<void> data;static _List<c> _Nil();static _List<c> _Cons(c _1, _List<c> _2);_List<c>(_enum_List_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_List<c>(const _List<c>& other);
_List<c>() = default;};template <class c> class _List_Nil { public: _List_Nil () {};_List_Nil (const _List_Nil* other) { } };template <class c> class _List_Cons { public: c _1;_List<c> _2;_List_Cons (c _1, _List<c> _2) {this->_1= _1;this->_2= _2;};_List_Cons (const _List_Cons* other) { this->_1= other->_1;this->_2= other->_2;} };template <class c>  inline _List<c> _List<c>::_Nil(){ return  _List<c> ( Nil, std::make_shared<_List_Nil<c>>()); };template <class c>  inline _List<c> _List<c>::_Cons(c _1, _List<c> _2){ return  _List<c> ( Cons, std::make_shared<_List_Cons<c>>(_1, _2)); };template <class c> _List<c>::_List(const _List<c>& other) { type = other.type; data = other.data; } 
enum _enum_Tuple_type {MkTuple};template <class a, class b> class _Tuple_MkTuple;
template <class a, class b> class _Tuple { public: enum _enum_Tuple_type type; std::shared_ptr<void> data;static _Tuple<a,b> _MkTuple(a _1, b _2);_Tuple<a,b>(_enum_Tuple_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_Tuple<a,b>(const _Tuple<a,b>& other);
_Tuple<a,b>() = default;};template <class a, class b> class _Tuple_MkTuple { public: a _1;b _2;_Tuple_MkTuple (a _1, b _2) {this->_1= _1;this->_2= _2;};_Tuple_MkTuple (const _Tuple_MkTuple* other) { this->_1= other->_1;this->_2= other->_2;} };template <class a, class b>  inline _Tuple<a,b> _Tuple<a,b>::_MkTuple(a _1, b _2){ return  _Tuple<a,b> ( MkTuple, std::make_shared<_Tuple_MkTuple<a,b>>(_1, _2)); };template <class a, class b> _Tuple<a,b>::_Tuple(const _Tuple<a,b>& other) { type = other.type; data = other.data; } 

template <class a,class b> std::function<std::function<_List<b>(_List<a>)>(std::function<b(a)>)> map = [](auto f) { auto _1 = [f](auto xs) { auto _2 = [xs,f]() { auto _3 = xs; switch (   _3.type) {  case Nil: {auto _5 = *(std::static_pointer_cast<_List_Nil<a>>(_3.data));auto _4 = _List<b>::_Nil(); return _4;} case Cons: {auto _7 = *(std::static_pointer_cast<_List_Cons<a>>(_3.data));auto y = _7._1;auto ys = _7._2;auto _10 = y;auto _8 = f(_10);auto _11 = f;auto _12 = ys;auto _9 = map<a,b>(_11)(_12);auto _6 = _List<b>::_Cons(_8,_9); return _6;}} }(); return _2;}; return _1;};

template <class a,class b> std::function<a(_Tuple<a,b>)> fst = [](auto t) { auto _15 = [t]() { auto _16 = t; switch (   _16.type) {  case MkTuple: {auto _18 = *(std::static_pointer_cast<_Tuple_MkTuple<a,b>>(_16.data));auto t1 = _18._1;auto t2 = _18._2;auto _17 = t1; return _17;}} }(); return _15;};

template <class a,class b> std::function<b(_Tuple<a,b>)> snd = [](auto t) { auto _19 = [t]() { auto _20 = t; switch (   _20.type) {  case MkTuple: {auto _22 = *(std::static_pointer_cast<_Tuple_MkTuple<a,b>>(_20.data));auto t1 = _22._1;auto t2 = _22._2;auto _21 = t2; return _21;}} }(); return _19;};

template <class a> std::function<std::function<_List<a>(_List<a>)>(_List<a>)> append = [](auto xs) { auto _23 = [xs](auto ys) { auto _24 = [xs,ys]() { auto _25 = xs; switch (   _25.type) {  case Nil: {auto _27 = *(std::static_pointer_cast<_List_Nil<a>>(_25.data));auto _26 = ys; return _26;} case Cons: {auto _29 = *(std::static_pointer_cast<_List_Cons<a>>(_25.data));auto x = _29._1;auto xs2 = _29._2;auto _30 = x;auto _32 = xs2;auto _33 = ys;auto _31 = append<a>(_32)(_33);auto _28 = _List<a>::_Cons(_30,_31); return _28;}} }(); return _24;}; return _23;};

template <class A,class B,class C> std::function<std::function<std::function<_List<C>(_List<B>)>(_List<A>)>(std::function<std::function<C(B)>(A)>)> zipWith = [](auto f) { auto _35 = [f](auto l1) { auto _36 = [l1,f](auto l2) { auto _37 = [l1,l2,f]() { auto _38 = l1; switch (   _38.type) {  case Nil: {auto _40 = *(std::static_pointer_cast<_List_Nil<A>>(_38.data));auto _39 = _List<C>::_Nil(); return _39;} case Cons: {auto _42 = *(std::static_pointer_cast<_List_Cons<A>>(_38.data));auto x = _42._1;auto xs = _42._2;auto _41 = [l1,l2,f,x,xs]() { auto _43 = l2; switch (   _43.type) {  case Nil: {auto _45 = *(std::static_pointer_cast<_List_Nil<B>>(_43.data));auto _44 = _List<C>::_Nil(); return _44;} case Cons: {auto _47 = *(std::static_pointer_cast<_List_Cons<B>>(_43.data));auto y = _47._1;auto ys = _47._2;auto _50 = x;auto _51 = y;auto _48 = f(_50)(_51);auto _52 = f;auto _53 = xs;auto _54 = ys;auto _49 = zipWith<A,B,C>(_52)(_53)(_54);auto _46 = _List<C>::_Cons(_48,_49); return _46;}} }(); return _41;}} }(); return _37;}; return _36;}; return _35;};

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> plus = [](auto n) {auto _133 = [n](auto m) {return n+m;};return _133;};;

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> times = [](auto n) { auto _58 = [n](auto m) { auto _59 = [n,m]() {auto _60 = n; if ( !_60 ) {auto _61 = (uint64_t)0;return _61; } else {auto pred = _60 - 1;auto _62 = m;auto _64 = pred;auto _65 = m;auto _63 = times(_64)(_65);auto _61 = plus(_62)(_63);return _61;} }(); return _59;}; return _58;};

std::function<_Tuple<_List<uint64_t>,_List<_List<uint64_t>>>(_List<_List<uint64_t>>)> split = [](auto ls) { auto _66 = [ls]() { auto _67 = ls; switch (   _67.type) {  case Nil: {auto _69 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_67.data));auto _70 = _List<uint64_t>::_Nil();auto _71 = _List<_List<uint64_t>>::_Nil();auto _68 = _Tuple<_List<uint64_t>,_List<_List<uint64_t>>>::_MkTuple(_70,_71); return _68;} case Cons: {auto _73 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_67.data));auto y = _73._1;auto xss = _73._2;auto _72 = [ls,y,xss]() { auto _74 = y; switch (   _74.type) {  case Nil: {auto _76 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_74.data));auto _77 = _List<uint64_t>::_Nil();auto _78 = _List<_List<uint64_t>>::_Nil();auto _75 = _Tuple<_List<uint64_t>,_List<_List<uint64_t>>>::_MkTuple(_77,_78); return _75;} case Cons: {auto _80 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_74.data));auto x = _80._1;auto xs = _80._2;auto _79 = [ls,y,xss,x,xs]() { auto _82 = xss;auto _81 = split(_82); switch (   _81.type) {  case MkTuple: {auto _84 = *(std::static_pointer_cast<_Tuple_MkTuple<_List<uint64_t>,_List<_List<uint64_t>>>>(_81.data));auto hd = _84._1;auto tl = _84._2;auto _87 = x;auto _88 = hd;auto _85 = _List<uint64_t>::_Cons(_87,_88);auto _89 = xs;auto _90 = tl;auto _86 = _List<_List<uint64_t>>::_Cons(_89,_90);auto _83 = _Tuple<_List<uint64_t>,_List<_List<uint64_t>>>::_MkTuple(_85,_86); return _83;}} }(); return _79;}} }(); return _72;}} }(); return _66;};

std::function<std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)>(_Tuple<_List<uint64_t>,_List<_List<uint64_t>>>)> tP = [](auto tup) { auto _91 = [tup](auto z) { auto _92 = [tup,z]() { auto _93 = tup; switch (   _93.type) {  case MkTuple: {auto _95 = *(std::static_pointer_cast<_Tuple_MkTuple<_List<uint64_t>,_List<_List<uint64_t>>>>(_93.data));auto a = _95._1;auto b = _95._2;auto _94 = [tup,a,z,b]() { auto _96 = a; switch (   _96.type) {  case Nil: {auto _98 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_96.data));auto _97 = z; return _97;} case Cons: {auto _100 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_96.data));auto g = _100._1;auto gs = _100._2;auto _103 = b;auto _101 = split(_103);auto _104 = z;auto _107 = a;auto _108 = _List<_List<uint64_t>>::_Nil();auto _105 = _List<_List<uint64_t>>::_Cons(_107,_108);auto _102 = append<_List<uint64_t>>(_104)(_105);auto _99 = tP(_101)(_102); return _99;}} }(); return _94;}} }(); return _92;}; return _91;};

std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)> transpose = [](auto m) { auto _112 = m;auto _110 = split(_112);auto _111 = _List<_List<uint64_t>>::_Nil();auto _109 = tP(_110)(_111); return _109;};

std::function<std::function<uint64_t(_List<uint64_t>)>(_List<uint64_t>)> dot = [](auto lA) { auto _113 = [lA](auto lB) { auto _114 = [lA,lB]() { auto _115 = lA; switch (   _115.type) {  case Nil: {auto _117 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_115.data));auto _116 = (uint64_t)0; return _116;} case Cons: {auto _119 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_115.data));auto x = _119._1;auto xs = _119._2;auto _118 = [lA,lB,x,xs]() { auto _120 = lB; switch (   _120.type) {  case Nil: {auto _122 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_120.data));auto _121 = (uint64_t)0; return _121;} case Cons: {auto _124 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_120.data));auto y = _124._1;auto ys = _124._2;auto _127 = x;auto _128 = y;auto _125 = times(_127)(_128);auto _129 = xs;auto _130 = ys;auto _126 = dot(_129)(_130);auto _123 = plus(_125)(_126); return _123;}} }(); return _118;}} }(); return _114;}; return _113;};

std::function<std::function<_List<uint64_t>(_List<_List<uint64_t>>)>(_List<uint64_t>)> rowXcol = [](auto r) { auto _131 = [r](auto l) { auto _132 = [l,r]() { auto _133 = l; switch (   _133.type) {  case Nil: {auto _135 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_133.data));auto _134 = _List<uint64_t>::_Nil(); return _134;} case Cons: {auto _137 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_133.data));auto c = _137._1;auto cs = _137._2;auto _140 = r;auto _141 = c;auto _138 = dot(_140)(_141);auto _142 = r;auto _143 = cs;auto _139 = rowXcol(_142)(_143);auto _136 = _List<uint64_t>::_Cons(_138,_139); return _136;}} }(); return _132;}; return _131;};

std::function<std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)>(_List<_List<uint64_t>>)> multP = [](auto l1) { auto _144 = [l1](auto b) { auto _145 = [l1,b]() { auto _146 = l1; switch (   _146.type) {  case Nil: {auto _148 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_146.data));auto _147 = _List<_List<uint64_t>>::_Nil(); return _147;} case Cons: {auto _150 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_146.data));auto a = _150._1;auto as = _150._2;auto _153 = a;auto _154 = b;auto _151 = rowXcol(_153)(_154);auto _155 = as;auto _156 = b;auto _152 = multP(_155)(_156);auto _149 = _List<_List<uint64_t>>::_Cons(_151,_152); return _149;}} }(); return _145;}; return _144;};

std::function<std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)>(_List<_List<uint64_t>>)> multPar = [](auto l1) { auto _157 = [l1](auto b) { auto _159 = [b](auto a) { auto _164 = a;auto _165 = b;auto _163 = rowXcol(_164)(_165); return _163;};auto _160 = l1;auto _158 = map<_List<uint64_t>,_List<uint64_t>>(_159)(_160); return _158;}; return _157;};

std::function<std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)>(_List<_List<uint64_t>>)> multM = [](auto m1) { auto _166 = [m1](auto m2) { auto _168 = m1;auto _170 = m2;auto _169 = transpose(_170);auto _167 = multP(_168)(_169); return _167;}; return _166;};

std::function<std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)>(_List<_List<uint64_t>>)> multMPar = [](auto m1) { auto _171 = [m1](auto m2) { auto _173 = m1;auto _175 = m2;auto _174 = transpose(_175);auto _172 = multPar(_173)(_174); return _172;}; return _171;};

std::function<std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)>(_List<_List<uint64_t>>)> add = [](auto l1) { auto _176 = [l1](auto l2) { auto _177 = [l1,l2]() { auto _178 = l1; switch (   _178.type) {  case Nil: {auto _180 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_178.data));auto _179 = _List<_List<uint64_t>>::_Nil(); return _179;} case Cons: {auto _182 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_178.data));auto xs = _182._1;auto xss = _182._2;auto _181 = [l1,l2,xs,xss]() { auto _183 = l2; switch (   _183.type) {  case Nil: {auto _185 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_183.data));auto _184 = _List<_List<uint64_t>>::_Nil(); return _184;} case Cons: {auto _187 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_183.data));auto ys = _187._1;auto yss = _187._2;auto _190 = plus;auto _191 = xs;auto _192 = ys;auto _188 = zipWith<uint64_t,uint64_t,uint64_t>(_190)(_191)(_192);auto _196 = xss;auto _197 = yss;auto _189 = add(_196)(_197);auto _186 = _List<_List<uint64_t>>::_Cons(_188,_189); return _186;}} }(); return _181;}} }(); return _177;}; return _176;};
enum _enum_IO_type {MkIO};template <class A> class _IO_MkIO;
template <class A> class _IO { public: enum _enum_IO_type type; std::shared_ptr<void> data;static _IO<A> _MkIO(A _1);_IO<A>(_enum_IO_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_IO<A>(const _IO<A>& other);
_IO<A>() = default;};template <class A> class _IO_MkIO { public: A _1;_IO_MkIO (A _1) {this->_1= _1;};_IO_MkIO (const _IO_MkIO* other) { this->_1= other->_1;} };template <class A>  inline _IO<A> _IO<A>::_MkIO(A _1){ return  _IO<A> ( MkIO, std::make_shared<_IO_MkIO<A>>(_1)); };template <class A> _IO<A>::_IO(const _IO<A>& other) { type = other.type; data = other.data; } 

template <class A> std::function<_IO<A>(A)> returnIO = [](auto a) { auto _199 = a;auto _198 = _IO<A>::_MkIO(_199); return _198;};

template <class A,class B> std::function<std::function<_IO<B>(std::function<_IO<B>(A)>)>(_IO<A>)> bindEq = [](auto a) { auto _200 = [a](auto f) { auto _201 = [a,f]() { auto _202 = a; switch (   _202.type) {  case MkIO: {auto _204 = *(std::static_pointer_cast<_IO_MkIO<A>>(_202.data));auto inner = _204._1;auto _205 = inner;auto _203 = f(_205); return _203;}} }(); return _201;}; return _200;};

template <class A,class B> std::function<std::function<_IO<B>(_IO<B>)>(_IO<A>)> bind = [](auto a) { auto _206 = [a](auto b) { auto _208 = a;auto _209 = [a,b](auto c) { auto _212 = b; return _212;};auto _207 = bindEq<A,B>(_208)(_209); return _207;}; return _206;};

std::function<_IO<_Unit>(_List<char>)> print = [](auto l) {auto _653 = [l]() {auto _654 = l;switch (_654.type) {case Nil: {std::cout << "\n" << std::flush;return returnIO<_Unit>(_Unit::_unit());}case Cons: {auto _660 = *(std::static_pointer_cast<_List_Cons<char>>(_654.data));auto c = _660._1;auto cs = _660._2;std::cout << c;return print(cs);}}}();return _653;};

std::function<_IO<_Unit>(_List<_List<char>>)> printList = [](auto l) { auto _213 = [l]() { auto _214 = l; switch (   _214.type) {  case Nil: {auto _216 = *(std::static_pointer_cast<_List_Nil<_List<char>>>(_214.data));auto _217 = _Unit::_unit();auto _215 = returnIO<_Unit>(_217); return _215;} case Cons: {auto _220 = *(std::static_pointer_cast<_List_Cons<_List<char>>>(_214.data));auto x = _220._1;auto xs = _220._2;auto _225 = x;auto _221 = print(_225);auto _226 = xs;auto _222 = printList(_226);auto _219 = bind<_Unit,_Unit>(_221)(_222); return _219;}} }(); return _213;};

std::function<_IO<uint64_t>(uint64_t)> getTime = [](auto i) {return returnIO<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());};

std::function<_List<char>(uint64_t)> natToString = [](auto n) {std::string stringVersion = std::to_string(n);std::function<_List<char>(std::string)> toList = [&toList](std::string s) {if (s.empty()) {return _List<char>::_Nil();}return _List<char>::_Cons(s.at(0), toList(std::string(s).erase(0, 1)));};return toList(stringVersion);};

_IO<_Unit> end = []() {auto _631 = _Unit::_unit();auto _630 = returnIO<_Unit>(_631);return _630;}();

template <class A> std::function<_IO<_Unit>(A)> runInIO = [](auto f) { auto _228 = _Unit::_unit();auto _227 = returnIO<_Unit>(_228); return _227;};

template <class A> std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_List<A>)> baseRun = [](auto inList) { auto _230 = [inList](auto func) { auto _236 = (uint64_t)0;auto _232 = getTime(_236);auto _233 = [func,inList](auto startTime1) { auto _243 = startTime1;auto _242 = natToString(_243);auto _238 = print(_242);auto _250 = func;auto _251 = inList;auto _248 = map<A,A>(_250)(_251);auto _244 = runInIO<_List<A>>(_248);auto _258 = (uint64_t)0;auto _254 = getTime(_258);auto _255 = [startTime1,func,inList](auto endTime1) { auto _265 = endTime1;auto _264 = natToString(_265);auto _260 = print(_264);auto _261 = end;auto _259 = bind<_Unit,_Unit>(_260)(_261); return _259;};auto _245 = bindEq<uint64_t,_Unit>(_254)(_255);auto _239 = bind<_Unit,_Unit>(_244)(_245);auto _237 = bind<_Unit,_Unit>(_238)(_239); return _237;};auto _231 = bindEq<uint64_t,_Unit>(_232)(_233); return _231;}; return _230;};

std::function<std::function<std::function<_IO<_Unit>(std::function<std::function<_List<_List<uint64_t>>(_List<_List<uint64_t>>)>(_List<_List<uint64_t>>)>)>(_List<_List<uint64_t>>)>(_List<_List<uint64_t>>)> baseRun2 = [](auto m1) { auto _266 = [m1](auto m2) { auto _267 = [m1,m2](auto func) { auto _273 = (uint64_t)0;auto _269 = getTime(_273);auto _270 = [func,m1,m2](auto startTime1) { auto _280 = startTime1;auto _279 = natToString(_280);auto _275 = print(_279);auto _287 = m1;auto _288 = m2;auto _285 = func(_287)(_288);auto _281 = returnIO<_List<_List<uint64_t>>>(_285);auto _282 = [startTime1,func,m1,m2](auto result) { auto _294 = (uint64_t)0;auto _290 = getTime(_294);auto _291 = [startTime1,func,m1,m2](auto endTime1) { auto _301 = endTime1;auto _300 = natToString(_301);auto _296 = print(_300);auto _297 = end;auto _295 = bind<_Unit,_Unit>(_296)(_297); return _295;};auto _289 = bindEq<uint64_t,_Unit>(_290)(_291); return _289;};auto _276 = bindEq<_List<_List<uint64_t>>,_Unit>(_281)(_282);auto _274 = bind<_Unit,_Unit>(_275)(_276); return _274;};auto _268 = bindEq<uint64_t,_Unit>(_269)(_270); return _268;}; return _267;}; return _266;};

std::function<_List<uint64_t>(uint64_t)> genListI = [](auto n) { auto _302 = [n]() {auto _303 = n; if ( !_303 ) {auto _304 = _List<uint64_t>::_Nil();return _304; } else {auto m = _303 - 1;auto _305 = (uint64_t)10;auto _307 = m;auto _306 = genListI(_307);auto _304 = _List<uint64_t>::_Cons(_305,_306);return _304;} }(); return _302;};

std::function<_List<uint64_t>(uint64_t)> randoms = [](auto m) { auto _308 = [m]() {auto _309 = m; if ( !_309 ) {auto _310 = _List<uint64_t>::_Nil();return _310; } else {auto n = _309 - 1;auto _311 = (uint64_t)1024;auto _313 = n;auto _312 = randoms(_313);auto _310 = _List<uint64_t>::_Cons(_311,_312);return _310;} }(); return _308;};

std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)> genMatrix = [](auto m) { auto _314 = [m](auto n) { auto _315 = [m,n]() {auto _316 = m; if ( !_316 ) {auto _317 = _List<_List<uint64_t>>::_Nil();return _317; } else {auto m2 = _316 - 1;auto _320 = n;auto _318 = randoms(_320);auto _321 = m2;auto _322 = n;auto _319 = genMatrix(_321)(_322);auto _317 = _List<_List<uint64_t>>::_Cons(_318,_319);return _317;} }(); return _315;}; return _314;};

_IO<_Unit> mainFunc = []() {auto _327 = (uint64_t)300;auto _328 = (uint64_t)300;auto _324 = genMatrix(_327)(_328);auto _329 = (uint64_t)300;auto _330 = (uint64_t)300;auto _325 = genMatrix(_329)(_330);auto _326 = multM;auto _323 = baseRun2(_324)(_325)(_326); return _323;}();
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


int main(){}