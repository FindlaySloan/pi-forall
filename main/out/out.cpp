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

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> plus = [](auto n) {auto _133 = [n](auto m) {return n+m;};return _133;};;

template <class a> std::function<uint64_t(_List<a>)> length = [](auto xs) { auto _1 = [xs]() { auto _2 = xs; switch (   _2.type) {  case Nil: {auto _4 = *(std::static_pointer_cast<_List_Nil<a>>(_2.data));auto _3 = (uint64_t)0; return _3;} case Cons: {auto _6 = *(std::static_pointer_cast<_List_Cons<a>>(_2.data));auto y = _6._1;auto ys = _6._2;auto _7 = (uint64_t)1;auto _9 = ys;auto _8 = length<a>(_9);auto _5 = plus(_7)(_8); return _5;}} }(); return _1;};

template <class a> std::function<std::function<_List<a>(_List<a>)>(_List<a>)> append = [](auto xs) { auto _11 = [xs](auto ys) { auto _12 = [xs,ys]() { auto _13 = xs; switch (   _13.type) {  case Nil: {auto _15 = *(std::static_pointer_cast<_List_Nil<a>>(_13.data));auto _14 = ys; return _14;} case Cons: {auto _17 = *(std::static_pointer_cast<_List_Cons<a>>(_13.data));auto x = _17._1;auto xs2 = _17._2;auto _18 = x;auto _20 = xs2;auto _21 = ys;auto _19 = append<a>(_20)(_21);auto _16 = _List<a>::_Cons(_18,_19); return _16;}} }(); return _12;}; return _11;};

std::function<std::function<_Bool(_Bool)>(_Bool)> orb = [](auto b1) { auto _23 = [b1](auto b2) { auto _24 = [b1,b2]() { auto _25 = b1; switch (   _25.type) {  case True: {auto _27 = *(std::static_pointer_cast<_Bool_True>(_25.data));auto _26 = _Bool::_True(); return _26;} case False: {auto _29 = *(std::static_pointer_cast<_Bool_False>(_25.data));auto _28 = b2; return _28;}} }(); return _24;}; return _23;};

std::function<std::function<_Bool(_Bool)>(_Bool)> andb = [](auto b1) { auto _30 = [b1](auto b2) { auto _31 = [b1,b2]() { auto _32 = b1; switch (   _32.type) {  case True: {auto _34 = *(std::static_pointer_cast<_Bool_True>(_32.data));auto _33 = b2; return _33;} case False: {auto _36 = *(std::static_pointer_cast<_Bool_False>(_32.data));auto _35 = _Bool::_False(); return _35;}} }(); return _31;}; return _30;};

std::function<std::function<_Bool(uint64_t)>(uint64_t)> nat_eq = [](auto x) { auto _37 = [x](auto y) { auto _38 = [x,y]() {auto _39 = x; if ( !_39 ) {auto _40 = [x,y]() {auto _41 = y; if ( !_41 ) {auto _42 = _Bool::_True();return _42; } else {auto n2 = _41 - 1;auto _42 = _Bool::_False();return _42;} }();return _40; } else {auto m2 = _39 - 1;auto _40 = [x,y,m2]() {auto _43 = y; if ( !_43 ) {auto _44 = _Bool::_False();return _44; } else {auto n2 = _43 - 1;auto _45 = m2;auto _46 = n2;auto _44 = nat_eq(_45)(_46);return _44;} }();return _40;} }(); return _38;}; return _37;};

std::function<std::function<uint64_t(uint64_t)>(uint64_t)> minus = [](auto n) {auto _133 = [n](auto m) {return n-m;};return _133;};;
enum _enum_Tuple2_type {MkTuple2};template <class a, class b> class _Tuple2_MkTuple2;
template <class a, class b> class _Tuple2 { public: enum _enum_Tuple2_type type; std::shared_ptr<void> data;static _Tuple2<a,b> _MkTuple2(a _1, b _2);_Tuple2<a,b>(_enum_Tuple2_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_Tuple2<a,b>(const _Tuple2<a,b>& other);
_Tuple2<a,b>() = default;};template <class a, class b> class _Tuple2_MkTuple2 { public: a _1;b _2;_Tuple2_MkTuple2 (a _1, b _2) {this->_1= _1;this->_2= _2;};_Tuple2_MkTuple2 (const _Tuple2_MkTuple2* other) { this->_1= other->_1;this->_2= other->_2;} };template <class a, class b>  inline _Tuple2<a,b> _Tuple2<a,b>::_MkTuple2(a _1, b _2){ return  _Tuple2<a,b> ( MkTuple2, std::make_shared<_Tuple2_MkTuple2<a,b>>(_1, _2)); };template <class a, class b> _Tuple2<a,b>::_Tuple2(const _Tuple2<a,b>& other) { type = other.type; data = other.data; } 

template <class a,class b> std::function<a(_Tuple2<a,b>)> fst = [](auto t) { auto _47 = [t]() { auto _48 = t; switch (   _48.type) {  case MkTuple2: {auto _50 = *(std::static_pointer_cast<_Tuple2_MkTuple2<a,b>>(_48.data));auto t1 = _50._1;auto t2 = _50._2;auto _49 = t1; return _49;}} }(); return _47;};

template <class a,class b> std::function<b(_Tuple2<a,b>)> snd = [](auto t) { auto _51 = [t]() { auto _52 = t; switch (   _52.type) {  case MkTuple2: {auto _54 = *(std::static_pointer_cast<_Tuple2_MkTuple2<a,b>>(_52.data));auto t1 = _54._1;auto t2 = _54._2;auto _53 = t2; return _53;}} }(); return _51;};

template <class a,class b> std::function<std::function<_List<_Tuple2<a,b>>(_List<b>)>(_List<a>)> zip = [](auto l1) { auto _55 = [l1](auto l2) { auto _56 = [l2,l1]() { auto _57 = l2; switch (   _57.type) {  case Nil: {auto _59 = *(std::static_pointer_cast<_List_Nil<b>>(_57.data));auto _58 = _List<_Tuple2<a,b>>::_Nil(); return _58;} case Cons: {auto _61 = *(std::static_pointer_cast<_List_Cons<b>>(_57.data));auto y = _61._1;auto ys = _61._2;auto _60 = [l2,l1,y,ys]() { auto _62 = l1; switch (   _62.type) {  case Nil: {auto _64 = *(std::static_pointer_cast<_List_Nil<a>>(_62.data));auto _63 = _List<_Tuple2<a,b>>::_Nil(); return _63;} case Cons: {auto _66 = *(std::static_pointer_cast<_List_Cons<a>>(_62.data));auto x = _66._1;auto xs = _66._2;auto _69 = x;auto _70 = y;auto _67 = _Tuple2<a,b>::_MkTuple2(_69,_70);auto _71 = xs;auto _72 = ys;auto _68 = zip<a,b>(_71)(_72);auto _65 = _List<_Tuple2<a,b>>::_Cons(_67,_68); return _65;}} }(); return _60;}} }(); return _56;}; return _55;};

template <class a,class b> std::function<std::function<std::function<b(_List<a>)>(b)>(std::function<std::function<b(b)>(a)>)> foldr = [](auto fn) { auto _75 = [fn](auto acc) { auto _76 = [acc,fn](auto list) { auto _77 = [list,acc,fn]() { auto _78 = list; switch (   _78.type) {  case Nil: {auto _80 = *(std::static_pointer_cast<_List_Nil<a>>(_78.data));auto _79 = acc; return _79;} case Cons: {auto _82 = *(std::static_pointer_cast<_List_Cons<a>>(_78.data));auto x = _82._1;auto xs = _82._2;auto _83 = x;auto _85 = fn;auto _86 = acc;auto _87 = xs;auto _84 = foldr<a,b>(_85)(_86)(_87);auto _81 = fn(_83)(_84); return _81;}} }(); return _77;}; return _76;}; return _75;};

std::function<_Bool(_Bool)> negb = [](auto b) { auto _90 = [b]() { auto _91 = b; switch (   _91.type) {  case True: {auto _93 = *(std::static_pointer_cast<_Bool_True>(_91.data));auto _92 = _Bool::_False(); return _92;} case False: {auto _95 = *(std::static_pointer_cast<_Bool_False>(_91.data));auto _94 = _Bool::_True(); return _94;}} }(); return _90;};

std::function<std::function<_Bool(_Tuple2<uint64_t,uint64_t>)>(_Tuple2<uint64_t,uint64_t>)> check = [](auto t1) { auto _96 = [t1](auto t2) { auto _97 = [t1,t2]() { auto _98 = t1; switch (   _98.type) {  case MkTuple2: {auto _100 = *(std::static_pointer_cast<_Tuple2_MkTuple2<uint64_t,uint64_t>>(_98.data));auto c = _100._1;auto l = _100._2;auto _99 = [t1,t2,l,c]() { auto _101 = t2; switch (   _101.type) {  case MkTuple2: {auto _103 = *(std::static_pointer_cast<_Tuple2_MkTuple2<uint64_t,uint64_t>>(_101.data));auto i = _103._1;auto j = _103._2;auto _108 = l;auto _109 = j;auto _106 = nat_eq(_108)(_109);auto _112 = c;auto _113 = j;auto _110 = plus(_112)(_113);auto _114 = i;auto _115 = j;auto _111 = plus(_114)(_115);auto _107 = nat_eq(_110)(_111);auto _104 = orb(_106)(_107);auto _118 = c;auto _119 = l;auto _116 = minus(_118)(_119);auto _120 = i;auto _121 = j;auto _117 = minus(_120)(_121);auto _105 = nat_eq(_116)(_117);auto _102 = orb(_104)(_105); return _102;}} }(); return _99;}} }(); return _97;}; return _96;};

std::function<std::function<_List<_Bool>(_Tuple2<uint64_t,uint64_t>)>(_List<_Tuple2<uint64_t,uint64_t>>)> mkSafeList = [](auto p) { auto _122 = [p](auto y) { auto _123 = [p,y]() { auto _124 = p; switch (   _124.type) {  case Nil: {auto _126 = *(std::static_pointer_cast<_List_Nil<_Tuple2<uint64_t,uint64_t>>>(_124.data));auto _125 = _List<_Bool>::_Nil(); return _125;} case Cons: {auto _128 = *(std::static_pointer_cast<_List_Cons<_Tuple2<uint64_t,uint64_t>>>(_124.data));auto x = _128._1;auto xs = _128._2;auto _132 = x;auto _133 = y;auto _131 = check(_132)(_133);auto _129 = negb(_131);auto _134 = xs;auto _135 = y;auto _130 = mkSafeList(_134)(_135);auto _127 = _List<_Bool>::_Cons(_129,_130); return _127;}} }(); return _123;}; return _122;};

std::function<std::function<_List<uint64_t>(uint64_t)>(uint64_t)> listSeq = [](auto n) { auto _136 = [n](auto c) { auto _137 = [n,c]() {auto _138 = n; if ( !_138 ) {auto _139 = _List<uint64_t>::_Nil();return _139; } else {auto m = _138 - 1;auto _140 = c;auto _142 = m;auto _144 = c;auto _143 = _144 + 1;;auto _141 = listSeq(_142)(_143);auto _139 = _List<uint64_t>::_Cons(_140,_141);return _139;} }(); return _137;}; return _136;};

std::function<std::function<_Bool(uint64_t)>(_List<uint64_t>)> safe2 = [](auto ap) { auto _145 = [ap](auto na) { auto _146 = [ap]() {auto _148 = apauto _147 = length<uint64_t>(_148); if ( !_147 ) {auto _150 = _Bool::_False();return _150; } else {auto l = _147 - 1;auto _150 = [ap,l]() {auto _152 = lauto _153 = (uint64_t)1auto _151 = plus(_152)(_153); if ( !_151 ) {auto _154 = _Bool::_False();return _154; } else {auto m = _151 - 1;auto _154 = _Bool::_True();return _154;} }();return _150;} }(); return _146;}; return _145;};

std::function<std::function<_List<_List<uint64_t>>(_List<uint64_t>)>(_List<_List<uint64_t>>)> makeList = [](auto p) { auto _155 = [p](auto n) { auto _156 = [p,n]() { auto _157 = p; switch (   _157.type) {  case Nil: {auto _159 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_157.data));auto _158 = _List<_List<uint64_t>>::_Nil(); return _158;} case Cons: {auto _161 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_157.data));auto pH = _161._1;auto pT = _161._2;auto _160 = [p,n,pH,pT]() { auto _162 = n; switch (   _162.type) {  case Nil: {auto _164 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_162.data));auto _163 = _List<_List<uint64_t>>::_Nil(); return _163;} case Cons: {auto _166 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_162.data));auto nH = _166._1;auto nT = _166._2;auto _165 = [p,n,pH,nH,pT,nT]() { auto _168 = pH;auto _169 = nH;auto _167 = safe2(_168)(_169); switch (   _167.type) {  case True: {auto _171 = *(std::static_pointer_cast<_Bool_True>(_167.data));auto _174 = pH;auto _177 = nH;auto _178 = _List<uint64_t>::_Nil();auto _175 = _List<uint64_t>::_Cons(_177,_178);auto _172 = append<uint64_t>(_174)(_175);auto _179 = pT;auto _180 = nT;auto _173 = makeList(_179)(_180);auto _170 = _List<_List<uint64_t>>::_Cons(_172,_173); return _170;} case False: {auto _182 = *(std::static_pointer_cast<_Bool_False>(_167.data));auto _183 = pT;auto _184 = nT;auto _181 = makeList(_183)(_184); return _181;}} }(); return _165;}} }(); return _160;}} }(); return _156;}; return _155;};

std::function<std::function<std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)>(_List<uint64_t>)>(_List<_List<uint64_t>>)> rainhasList = [](auto p) { auto _185 = [p](auto n) { auto _186 = [p,n](auto linHa) { auto _187 = [p,n,linHa](auto numero) { auto _188 = [p,n,linHa,numero]() { auto _189 = p; switch (   _189.type) {  case Nil: {auto _191 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_189.data));auto _190 = _List<_List<uint64_t>>::_Nil(); return _190;} case Cons: {auto _193 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_189.data));auto pH = _193._1;auto pT = _193._2;auto _192 = [p,n,linHa,numero,pH,pT]() { auto _194 = n; switch (   _194.type) {  case Nil: {auto _196 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_194.data));auto _195 = _List<_List<uint64_t>>::_Nil(); return _195;} case Cons: {auto _198 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_194.data));auto nH = _198._1;auto nT = _198._2;auto _197 = [p,n,linHa,numero,pH,nH,pT,nT]() { auto _203 = linHa;auto _204 = numero;auto _200 = listSeq(_203)(_204);auto _205 = (uint64_t)1;auto _207 = linHa;auto _208 = (uint64_t)1;auto _206 = minus(_207)(_208);auto _201 = listSeq(_205)(_206);auto _199 = append<uint64_t>(_200)(_201); switch (   _199.type) {  case Nil: {auto _210 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_199.data));auto _209 = [p,n,linHa,numero,pH,nH]() { auto _212 = pH;auto _213 = nH;auto _211 = safe2(_212)(_213); switch (   _211.type) {  case True: {auto _215 = *(std::static_pointer_cast<_Bool_True>(_211.data));auto _218 = pH;auto _219 = _List<uint64_t>::_Nil();auto _216 = append<uint64_t>(_218)(_219);auto _217 = _List<_List<uint64_t>>::_Nil();auto _214 = _List<_List<uint64_t>>::_Cons(_216,_217); return _214;} case False: {auto _222 = *(std::static_pointer_cast<_Bool_False>(_211.data));auto _221 = _List<_List<uint64_t>>::_Nil(); return _221;}} }(); return _209;} case Cons: {auto _224 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_199.data));auto aH = _224._1;auto aT = _224._2;auto _223 = [p,n,linHa,numero,pH,nH,pT,nT]() { auto _226 = pH;auto _227 = nH;auto _225 = safe2(_226)(_227); switch (   _225.type) {  case True: {auto _229 = *(std::static_pointer_cast<_Bool_True>(_225.data));auto _232 = pH;auto _235 = nH;auto _236 = _List<uint64_t>::_Nil();auto _233 = _List<uint64_t>::_Cons(_235,_236);auto _230 = append<uint64_t>(_232)(_233);auto _237 = pT;auto _238 = nT;auto _239 = linHa;auto _240 = numero;auto _231 = rainhasList(_237)(_238)(_239)(_240);auto _228 = _List<_List<uint64_t>>::_Cons(_230,_231); return _228;} case False: {auto _242 = *(std::static_pointer_cast<_Bool_False>(_225.data));auto _243 = pT;auto _244 = nT;auto _245 = linHa;auto _246 = numero;auto _241 = rainhasList(_243)(_244)(_245)(_246); return _241;}} }(); return _223;}} }(); return _197;}} }(); return _192;}} }(); return _188;}; return _187;}; return _186;}; return _185;};

std::function<std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)>(uint64_t)> rainhas2 = [](auto n) { auto _247 = [n](auto linHa) { auto _248 = [n,linHa](auto numero) { auto _249 = [n,linHa,numero]() {auto _250 = n; if ( !_250 ) {auto _252 = _List<uint64_t>::_Nil();auto _253 = _List<_List<uint64_t>>::_Nil();auto _251 = _List<_List<uint64_t>>::_Cons(_252,_253);return _251; } else {auto n2 = _250 - 1;auto _251 = [n,n2,linHa,numero]() { auto _255 = n2;auto _256 = linHa;auto _257 = numero;auto _254 = rainhas2(_255)(_256)(_257); switch (   _254.type) {  case Nil: {auto _259 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_254.data));auto _258 = _List<_List<uint64_t>>::_Nil(); return _258;} case Cons: {auto _261 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_254.data));auto rH = _261._1;auto rT = _261._2;auto _260 = [n,n2,linHa,numero,rH,rT]() { auto _266 = linHa;auto _267 = numero;auto _263 = listSeq(_266)(_267);auto _268 = (uint64_t)1;auto _270 = linHa;auto _271 = (uint64_t)1;auto _269 = minus(_270)(_271);auto _264 = listSeq(_268)(_269);auto _262 = append<uint64_t>(_263)(_264); switch (   _262.type) {  case Nil: {auto _273 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_262.data));auto _272 = _List<_List<uint64_t>>::_Nil(); return _272;} case Cons: {auto _275 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_262.data));auto aH = _275._1;auto aT = _275._2;auto _280 = rH;auto _281 = rT;auto _276 = _List<_List<uint64_t>>::_Cons(_280,_281);auto _282 = aH;auto _283 = aT;auto _277 = _List<uint64_t>::_Cons(_282,_283);auto _278 = linHa;auto _279 = numero;auto _274 = rainhasList(_276)(_277)(_278)(_279); return _274;}} }(); return _260;}} }();return _251;} }(); return _249;}; return _248;}; return _247;};

std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)> prainhas = [](auto numero) { auto _284 = [numero](auto linHa) { auto _286 = numero;auto _287 = linHa;auto _288 = numero;auto _285 = rainhas2(_286)(_287)(_288); return _285;}; return _284;};

template <class a> std::function<std::function<_List<a>(_List<a>)>(std::function<_Bool(a)>)> takeWhile = [](auto p) { auto _289 = [p](auto xs) { auto _290 = [xs,p]() { auto _291 = xs; switch (   _291.type) {  case Nil: {auto _293 = *(std::static_pointer_cast<_List_Nil<a>>(_291.data));auto _292 = _List<a>::_Nil(); return _292;} case Cons: {auto _295 = *(std::static_pointer_cast<_List_Cons<a>>(_291.data));auto x = _295._1;auto ts = _295._2;auto _294 = [xs,p,x,ts]() { auto _297 = x;auto _296 = p(_297); switch (   _296.type) {  case True: {auto _299 = *(std::static_pointer_cast<_Bool_True>(_296.data));auto _300 = x;auto _302 = p;auto _303 = ts;auto _301 = takeWhile<a>(_302)(_303);auto _298 = _List<a>::_Cons(_300,_301); return _298;} case False: {auto _306 = *(std::static_pointer_cast<_Bool_False>(_296.data));auto _305 = _List<a>::_Nil(); return _305;}} }(); return _294;}} }(); return _290;}; return _289;};

std::function<uint64_t(_List<uint64_t>)> head = [](auto xs) { auto _307 = [xs]() { auto _308 = xs; switch (   _308.type) {  case Nil: {auto _310 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_308.data));auto _309 = (uint64_t)0; return _309;} case Cons: {auto _312 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_308.data));auto y = _312._1;auto ys = _312._2;auto _311 = y; return _311;}} }(); return _307;};

std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)> search = [](auto numero) { auto _313 = [numero](auto n) { auto _315 = [n](auto a) { auto _321 = a;auto _319 = head(_321);auto _320 = n;auto _318 = nat_eq(_319)(_320); return _318;};auto _322 = numero;auto _323 = n;auto _316 = prainhas(_322)(_323);auto _314 = takeWhile<_List<uint64_t>>(_315)(_316); return _314;}; return _313;};

template <class a,class b> std::function<std::function<_List<b>(_List<a>)>(std::function<b(a)>)> map = [](auto f) { auto _324 = [f](auto xs) { auto _325 = [xs,f]() { auto _326 = xs; switch (   _326.type) {  case Nil: {auto _328 = *(std::static_pointer_cast<_List_Nil<a>>(_326.data));auto _327 = _List<b>::_Nil(); return _327;} case Cons: {auto _330 = *(std::static_pointer_cast<_List_Cons<a>>(_326.data));auto y = _330._1;auto ys = _330._2;auto _333 = y;auto _331 = f(_333);auto _334 = f;auto _335 = ys;auto _332 = map<a,b>(_334)(_335);auto _329 = _List<b>::_Cons(_331,_332); return _329;}} }(); return _325;}; return _324;};

std::function<_List<_List<_List<uint64_t>>>(uint64_t)> rainhas = [](auto n) { auto _339 = [n](auto x) { auto _344 = n;auto _345 = x;auto _343 = search(_344)(_345); return _343;};auto _346 = (uint64_t)1;auto _347 = n;auto _340 = listSeq(_346)(_347);auto _338 = map<uint64_t,_List<_List<uint64_t>>>(_339)(_340); return _338;};

std::function<uint64_t(uint64_t)> run = [](auto n) { auto _348 = [n]() { auto _350 = n;auto _349 = rainhas(_350); switch (   _349.type) {  case Cons: {auto _352 = *(std::static_pointer_cast<_List_Cons<_List<_List<uint64_t>>>>(_349.data));auto x = _352._1;auto xs = _352._2;auto _351 = [n,x]() { auto _353 = x; switch (   _353.type) {  case Nil: {auto _355 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_353.data));auto _354 = (uint64_t)0; return _354;} case Cons: {auto _357 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_353.data));auto y = _357._1;auto ys = _357._2;auto _356 = [n,x,y]() { auto _358 = y; switch (   _358.type) {  case Nil: {auto _360 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_358.data));auto _359 = (uint64_t)0; return _359;} case Cons: {auto _362 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_358.data));auto z = _362._1;auto zs = _362._2;auto _361 = z; return _361;}} }(); return _356;}} }(); return _351;}} }(); return _348;};
enum _enum_IO_type {MkIO};template <class A> class _IO_MkIO;
template <class A> class _IO { public: enum _enum_IO_type type; std::shared_ptr<void> data;static _IO<A> _MkIO(A _1);_IO<A>(_enum_IO_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_IO<A>(const _IO<A>& other);
_IO<A>() = default;};template <class A> class _IO_MkIO { public: A _1;_IO_MkIO (A _1) {this->_1= _1;};_IO_MkIO (const _IO_MkIO* other) { this->_1= other->_1;} };template <class A>  inline _IO<A> _IO<A>::_MkIO(A _1){ return  _IO<A> ( MkIO, std::make_shared<_IO_MkIO<A>>(_1)); };template <class A> _IO<A>::_IO(const _IO<A>& other) { type = other.type; data = other.data; } 

template <class A> std::function<_IO<A>(A)> returnIO = [](auto a) { auto _364 = a;auto _363 = _IO<A>::_MkIO(_364); return _363;};

template <class A,class B> std::function<std::function<_IO<B>(std::function<_IO<B>(A)>)>(_IO<A>)> bindEq = [](auto a) { auto _365 = [a](auto f) { auto _366 = [a,f]() { auto _367 = a; switch (   _367.type) {  case MkIO: {auto _369 = *(std::static_pointer_cast<_IO_MkIO<A>>(_367.data));auto inner = _369._1;auto _370 = inner;auto _368 = f(_370); return _368;}} }(); return _366;}; return _365;};

template <class A,class B> std::function<std::function<_IO<B>(_IO<B>)>(_IO<A>)> bind = [](auto a) { auto _371 = [a](auto b) { auto _373 = a;auto _374 = [a,b](auto c) { auto _377 = b; return _377;};auto _372 = bindEq<A,B>(_373)(_374); return _372;}; return _371;};

std::function<_IO<_Unit>(_List<char>)> print = [](auto l) {auto _653 = [l]() {auto _654 = l;switch (_654.type) {case Nil: {std::cout << "\n" << std::flush;return returnIO<_Unit>(_Unit::_unit());}case Cons: {auto _660 = *(std::static_pointer_cast<_List_Cons<char>>(_654.data));auto c = _660._1;auto cs = _660._2;std::cout << c;return print(cs);}}}();return _653;};

std::function<_IO<_Unit>(_List<_List<char>>)> printList = [](auto l) { auto _378 = [l]() { auto _379 = l; switch (   _379.type) {  case Nil: {auto _381 = *(std::static_pointer_cast<_List_Nil<_List<char>>>(_379.data));auto _382 = _Unit::_unit();auto _380 = returnIO<_Unit>(_382); return _380;} case Cons: {auto _385 = *(std::static_pointer_cast<_List_Cons<_List<char>>>(_379.data));auto x = _385._1;auto xs = _385._2;auto _390 = x;auto _386 = print(_390);auto _391 = xs;auto _387 = printList(_391);auto _384 = bind<_Unit,_Unit>(_386)(_387); return _384;}} }(); return _378;};

std::function<_IO<uint64_t>(uint64_t)> getTime = [](auto i) {return returnIO<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());};

std::function<_List<char>(uint64_t)> natToString = [](auto n) {std::string stringVersion = std::to_string(n);std::function<_List<char>(std::string)> toList = [&toList](std::string s) {if (s.empty()) {return _List<char>::_Nil();}return _List<char>::_Cons(s.at(0), toList(std::string(s).erase(0, 1)));};return toList(stringVersion);};

_IO<_Unit> end = []() {auto _631 = _Unit::_unit();auto _630 = returnIO<_Unit>(_631);return _630;}();

template <class A> std::function<_IO<_Unit>(A)> runInIO = [](auto f) { auto _393 = _Unit::_unit();auto _392 = returnIO<_Unit>(_393); return _392;};

template <class A> std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_List<A>)> baseRun = [](auto inList) { auto _395 = [inList](auto func) { auto _401 = (uint64_t)0;auto _397 = getTime(_401);auto _398 = [func,inList](auto startTime1) { auto _408 = startTime1;auto _407 = natToString(_408);auto _403 = print(_407);auto _415 = func;auto _416 = inList;auto _413 = map<A,A>(_415)(_416);auto _409 = runInIO<_List<A>>(_413);auto _423 = (uint64_t)0;auto _419 = getTime(_423);auto _420 = [startTime1,func,inList](auto endTime1) { auto _430 = endTime1;auto _429 = natToString(_430);auto _425 = print(_429);auto _426 = end;auto _424 = bind<_Unit,_Unit>(_425)(_426); return _424;};auto _410 = bindEq<uint64_t,_Unit>(_419)(_420);auto _404 = bind<_Unit,_Unit>(_409)(_410);auto _402 = bind<_Unit,_Unit>(_403)(_404); return _402;};auto _396 = bindEq<uint64_t,_Unit>(_397)(_398); return _396;}; return _395;};

std::function<_List<uint64_t>(uint64_t)> genListI = [](auto n) { auto _431 = [n]() {auto _432 = n; if ( !_432 ) {auto _433 = _List<uint64_t>::_Nil();return _433; } else {auto m = _432 - 1;auto _434 = (uint64_t)1000;auto _436 = m;auto _435 = genListI(_436);auto _433 = _List<uint64_t>::_Cons(_434,_435);return _433;} }(); return _431;};

_IO<_Unit> mainFunc = []() {auto _441 = (uint64_t)1;auto _438 = genListI(_441);auto _439 = run;auto _437 = baseRun<uint64_t>(_438)(_439); return _437;}();
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