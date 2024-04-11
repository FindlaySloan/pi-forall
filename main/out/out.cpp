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

std::function<std::function<_Bool(_List<uint64_t>)>(uint64_t)> safe2 = [](auto na) { auto _145 = [na](auto ap) { auto _147 = [](auto x) { auto _152 = [x](auto y) { auto _154 = x;auto _155 = y;auto _153 = andb(_154)(_155); return _153;}; return _152;};auto _148 = _Bool::_True();auto _162 = (uint64_t)1;auto _164 = ap;auto _163 = length<uint64_t>(_164);auto _158 = listSeq(_162)(_163);auto _159 = ap;auto _156 = zip<uint64_t,uint64_t>(_158)(_159);auto _170 = ap;auto _168 = length<uint64_t>(_170);auto _169 = (uint64_t)1;auto _166 = plus(_168)(_169);auto _167 = na;auto _157 = _Tuple2<uint64_t,uint64_t>::_MkTuple2(_166,_167);auto _149 = mkSafeList(_156)(_157);auto _146 = foldr<_Bool,_Bool>(_147)(_148)(_149); return _146;}; return _145;};

std::function<std::function<_List<_List<uint64_t>>(_List<uint64_t>)>(_List<_List<uint64_t>>)> makeList = [](auto p) { auto _172 = [p](auto n) { auto _173 = [p,n]() { auto _174 = p; switch (   _174.type) {  case Nil: {auto _176 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_174.data));auto _175 = _List<_List<uint64_t>>::_Nil(); return _175;} case Cons: {auto _178 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_174.data));auto pH = _178._1;auto pT = _178._2;auto _177 = [p,n,pH,pT]() { auto _179 = n; switch (   _179.type) {  case Nil: {auto _181 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_179.data));auto _180 = _List<_List<uint64_t>>::_Nil(); return _180;} case Cons: {auto _183 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_179.data));auto nH = _183._1;auto nT = _183._2;auto _182 = [p,n,nH,pH,pT,nT]() { auto _185 = nH;auto _186 = pH;auto _184 = safe2(_185)(_186); switch (   _184.type) {  case True: {auto _188 = *(std::static_pointer_cast<_Bool_True>(_184.data));auto _191 = pH;auto _194 = nH;auto _195 = _List<uint64_t>::_Nil();auto _192 = _List<uint64_t>::_Cons(_194,_195);auto _189 = append<uint64_t>(_191)(_192);auto _196 = pT;auto _197 = nT;auto _190 = makeList(_196)(_197);auto _187 = _List<_List<uint64_t>>::_Cons(_189,_190); return _187;} case False: {auto _199 = *(std::static_pointer_cast<_Bool_False>(_184.data));auto _200 = pT;auto _201 = nT;auto _198 = makeList(_200)(_201); return _198;}} }(); return _182;}} }(); return _177;}} }(); return _173;}; return _172;};

std::function<std::function<std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)>(_List<uint64_t>)>(_List<_List<uint64_t>>)> rainhasList = [](auto p) { auto _202 = [p](auto n) { auto _203 = [p,n](auto linHa) { auto _204 = [p,n,linHa](auto numero) { auto _205 = [p,n,linHa,numero]() { auto _206 = p; switch (   _206.type) {  case Nil: {auto _208 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_206.data));auto _207 = _List<_List<uint64_t>>::_Nil(); return _207;} case Cons: {auto _210 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_206.data));auto pH = _210._1;auto pT = _210._2;auto _209 = [p,n,linHa,numero,pH,pT]() { auto _211 = n; switch (   _211.type) {  case Nil: {auto _213 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_211.data));auto _212 = _List<_List<uint64_t>>::_Nil(); return _212;} case Cons: {auto _215 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_211.data));auto nH = _215._1;auto nT = _215._2;auto _214 = [p,n,linHa,numero,nH,pH,pT,nT]() { auto _220 = linHa;auto _221 = numero;auto _217 = listSeq(_220)(_221);auto _222 = (uint64_t)1;auto _224 = linHa;auto _225 = (uint64_t)1;auto _223 = minus(_224)(_225);auto _218 = listSeq(_222)(_223);auto _216 = append<uint64_t>(_217)(_218); switch (   _216.type) {  case Nil: {auto _227 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_216.data));auto _226 = [p,n,linHa,numero,nH,pH]() { auto _229 = nH;auto _230 = pH;auto _228 = safe2(_229)(_230); switch (   _228.type) {  case True: {auto _232 = *(std::static_pointer_cast<_Bool_True>(_228.data));auto _235 = pH;auto _236 = _List<uint64_t>::_Nil();auto _233 = append<uint64_t>(_235)(_236);auto _234 = _List<_List<uint64_t>>::_Nil();auto _231 = _List<_List<uint64_t>>::_Cons(_233,_234); return _231;} case False: {auto _239 = *(std::static_pointer_cast<_Bool_False>(_228.data));auto _238 = _List<_List<uint64_t>>::_Nil(); return _238;}} }(); return _226;} case Cons: {auto _241 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_216.data));auto aH = _241._1;auto aT = _241._2;auto _240 = [p,n,linHa,numero,nH,pH,pT,nT]() { auto _243 = nH;auto _244 = pH;auto _242 = safe2(_243)(_244); switch (   _242.type) {  case True: {auto _246 = *(std::static_pointer_cast<_Bool_True>(_242.data));auto _249 = pH;auto _252 = nH;auto _253 = _List<uint64_t>::_Nil();auto _250 = _List<uint64_t>::_Cons(_252,_253);auto _247 = append<uint64_t>(_249)(_250);auto _254 = pT;auto _255 = nT;auto _256 = linHa;auto _257 = numero;auto _248 = rainhasList(_254)(_255)(_256)(_257);auto _245 = _List<_List<uint64_t>>::_Cons(_247,_248); return _245;} case False: {auto _259 = *(std::static_pointer_cast<_Bool_False>(_242.data));auto _260 = pT;auto _261 = nT;auto _262 = linHa;auto _263 = numero;auto _258 = rainhasList(_260)(_261)(_262)(_263); return _258;}} }(); return _240;}} }(); return _214;}} }(); return _209;}} }(); return _205;}; return _204;}; return _203;}; return _202;};

std::function<std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)>(uint64_t)> rainhas2 = [](auto n) { auto _264 = [n](auto linHa) { auto _265 = [n,linHa](auto numero) { auto _266 = [n,linHa,numero]() {auto _267 = n; if ( !_267 ) {auto _269 = _List<uint64_t>::_Nil();auto _270 = _List<_List<uint64_t>>::_Nil();auto _268 = _List<_List<uint64_t>>::_Cons(_269,_270);return _268; } else {auto n2 = _267 - 1;auto _268 = [n,n2,linHa,numero]() { auto _272 = n2;auto _273 = linHa;auto _274 = numero;auto _271 = rainhas2(_272)(_273)(_274); switch (   _271.type) {  case Nil: {auto _276 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_271.data));auto _275 = _List<_List<uint64_t>>::_Nil(); return _275;} case Cons: {auto _278 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_271.data));auto rH = _278._1;auto rT = _278._2;auto _277 = [n,n2,linHa,numero,rH,rT]() { auto _283 = linHa;auto _284 = numero;auto _280 = listSeq(_283)(_284);auto _285 = (uint64_t)1;auto _287 = linHa;auto _288 = (uint64_t)1;auto _286 = minus(_287)(_288);auto _281 = listSeq(_285)(_286);auto _279 = append<uint64_t>(_280)(_281); switch (   _279.type) {  case Nil: {auto _290 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_279.data));auto _289 = _List<_List<uint64_t>>::_Nil(); return _289;} case Cons: {auto _292 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_279.data));auto aH = _292._1;auto aT = _292._2;auto _297 = rH;auto _298 = rT;auto _293 = _List<_List<uint64_t>>::_Cons(_297,_298);auto _299 = aH;auto _300 = aT;auto _294 = _List<uint64_t>::_Cons(_299,_300);auto _295 = linHa;auto _296 = numero;auto _291 = rainhasList(_293)(_294)(_295)(_296); return _291;}} }(); return _277;}} }();return _268;} }(); return _266;}; return _265;}; return _264;};

std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)> prainhas = [](auto numero) { auto _301 = [numero](auto linHa) { auto _303 = numero;auto _304 = linHa;auto _305 = numero;auto _302 = rainhas2(_303)(_304)(_305); return _302;}; return _301;};

template <class a> std::function<std::function<_List<a>(_List<a>)>(std::function<_Bool(a)>)> takeWhile = [](auto p) { auto _306 = [p](auto xs) { auto _307 = [xs,p]() { auto _308 = xs; switch (   _308.type) {  case Nil: {auto _310 = *(std::static_pointer_cast<_List_Nil<a>>(_308.data));auto _309 = _List<a>::_Nil(); return _309;} case Cons: {auto _312 = *(std::static_pointer_cast<_List_Cons<a>>(_308.data));auto x = _312._1;auto ts = _312._2;auto _311 = [xs,p,x,ts]() { auto _314 = x;auto _313 = p(_314); switch (   _313.type) {  case True: {auto _316 = *(std::static_pointer_cast<_Bool_True>(_313.data));auto _317 = x;auto _319 = p;auto _320 = ts;auto _318 = takeWhile<a>(_319)(_320);auto _315 = _List<a>::_Cons(_317,_318); return _315;} case False: {auto _323 = *(std::static_pointer_cast<_Bool_False>(_313.data));auto _322 = _List<a>::_Nil(); return _322;}} }(); return _311;}} }(); return _307;}; return _306;};

std::function<uint64_t(_List<uint64_t>)> head = [](auto xs) { auto _324 = [xs]() { auto _325 = xs; switch (   _325.type) {  case Nil: {auto _327 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_325.data));auto _326 = (uint64_t)0; return _326;} case Cons: {auto _329 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_325.data));auto y = _329._1;auto ys = _329._2;auto _328 = y; return _328;}} }(); return _324;};

std::function<std::function<_List<_List<uint64_t>>(uint64_t)>(uint64_t)> search = [](auto numero) { auto _330 = [numero](auto n) { auto _332 = [n](auto a) { auto _338 = a;auto _336 = head(_338);auto _337 = n;auto _335 = nat_eq(_336)(_337); return _335;};auto _339 = numero;auto _340 = n;auto _333 = prainhas(_339)(_340);auto _331 = takeWhile<_List<uint64_t>>(_332)(_333); return _331;}; return _330;};

template <class a,class b> std::function<std::function<_List<b>(_List<a>)>(std::function<b(a)>)> map = [](auto f) { auto _341 = [f](auto xs) { auto _342 = [xs,f]() { auto _343 = xs; switch (   _343.type) {  case Nil: {auto _345 = *(std::static_pointer_cast<_List_Nil<a>>(_343.data));auto _344 = _List<b>::_Nil(); return _344;} case Cons: {auto _347 = *(std::static_pointer_cast<_List_Cons<a>>(_343.data));auto y = _347._1;auto ys = _347._2;auto _350 = y;auto _348 = f(_350);auto _351 = f;auto _352 = ys;auto _349 = map<a,b>(_351)(_352);auto _346 = _List<b>::_Cons(_348,_349); return _346;}} }(); return _342;}; return _341;};

std::function<_List<_List<_List<uint64_t>>>(uint64_t)> rainhas = [](auto n) { auto _356 = [n](auto x) { auto _361 = n;auto _362 = x;auto _360 = search(_361)(_362); return _360;};auto _363 = (uint64_t)1;auto _364 = n;auto _357 = listSeq(_363)(_364);auto _355 = map<uint64_t,_List<_List<uint64_t>>>(_356)(_357); return _355;};

std::function<uint64_t(uint64_t)> run = [](auto n) { auto _365 = [n]() { auto _367 = n;auto _366 = rainhas(_367); switch (   _366.type) {  case Cons: {auto _369 = *(std::static_pointer_cast<_List_Cons<_List<_List<uint64_t>>>>(_366.data));auto x = _369._1;auto xs = _369._2;auto _368 = [n,x]() { auto _370 = x; switch (   _370.type) {  case Nil: {auto _372 = *(std::static_pointer_cast<_List_Nil<_List<uint64_t>>>(_370.data));auto _371 = (uint64_t)0; return _371;} case Cons: {auto _374 = *(std::static_pointer_cast<_List_Cons<_List<uint64_t>>>(_370.data));auto y = _374._1;auto ys = _374._2;auto _373 = [n,x,y]() { auto _375 = y; switch (   _375.type) {  case Nil: {auto _377 = *(std::static_pointer_cast<_List_Nil<uint64_t>>(_375.data));auto _376 = (uint64_t)0; return _376;} case Cons: {auto _379 = *(std::static_pointer_cast<_List_Cons<uint64_t>>(_375.data));auto z = _379._1;auto zs = _379._2;auto _378 = z; return _378;}} }(); return _373;}} }(); return _368;}} }(); return _365;};
enum _enum_IO_type {MkIO};template <class A> class _IO_MkIO;
template <class A> class _IO { public: enum _enum_IO_type type; std::shared_ptr<void> data;static _IO<A> _MkIO(A _1);_IO<A>(_enum_IO_type t, std::shared_ptr<void> d) {type=t; data=d;} 
_IO<A>(const _IO<A>& other);
_IO<A>() = default;};template <class A> class _IO_MkIO { public: A _1;_IO_MkIO (A _1) {this->_1= _1;};_IO_MkIO (const _IO_MkIO* other) { this->_1= other->_1;} };template <class A>  inline _IO<A> _IO<A>::_MkIO(A _1){ return  _IO<A> ( MkIO, std::make_shared<_IO_MkIO<A>>(_1)); };template <class A> _IO<A>::_IO(const _IO<A>& other) { type = other.type; data = other.data; } 

template <class A> std::function<_IO<A>(A)> returnIO = [](auto a) { auto _381 = a;auto _380 = _IO<A>::_MkIO(_381); return _380;};

template <class A,class B> std::function<std::function<_IO<B>(std::function<_IO<B>(A)>)>(_IO<A>)> bindEq = [](auto a) { auto _382 = [a](auto f) { auto _383 = [a,f]() { auto _384 = a; switch (   _384.type) {  case MkIO: {auto _386 = *(std::static_pointer_cast<_IO_MkIO<A>>(_384.data));auto inner = _386._1;auto _387 = inner;auto _385 = f(_387); return _385;}} }(); return _383;}; return _382;};

template <class A,class B> std::function<std::function<_IO<B>(_IO<B>)>(_IO<A>)> bind = [](auto a) { auto _388 = [a](auto b) { auto _390 = a;auto _391 = [a,b](auto c) { auto _394 = b; return _394;};auto _389 = bindEq<A,B>(_390)(_391); return _389;}; return _388;};

std::function<_IO<_Unit>(_List<char>)> print = [](auto l) {auto _653 = [l]() {auto _654 = l;switch (_654.type) {case Nil: {std::cout << "\n" << std::flush;return returnIO<_Unit>(_Unit::_unit());}case Cons: {auto _660 = *(std::static_pointer_cast<_List_Cons<char>>(_654.data));auto c = _660._1;auto cs = _660._2;std::cout << c;return print(cs);}}}();return _653;};

std::function<_IO<_Unit>(_List<_List<char>>)> printList = [](auto l) { auto _395 = [l]() { auto _396 = l; switch (   _396.type) {  case Nil: {auto _398 = *(std::static_pointer_cast<_List_Nil<_List<char>>>(_396.data));auto _399 = _Unit::_unit();auto _397 = returnIO<_Unit>(_399); return _397;} case Cons: {auto _402 = *(std::static_pointer_cast<_List_Cons<_List<char>>>(_396.data));auto x = _402._1;auto xs = _402._2;auto _407 = x;auto _403 = print(_407);auto _408 = xs;auto _404 = printList(_408);auto _401 = bind<_Unit,_Unit>(_403)(_404); return _401;}} }(); return _395;};

std::function<_IO<uint64_t>(uint64_t)> getTime = [](auto i) {return returnIO<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());};

std::function<_List<char>(uint64_t)> natToString = [](auto n) {std::string stringVersion = std::to_string(n);std::function<_List<char>(std::string)> toList = [&toList](std::string s) {if (s.empty()) {return _List<char>::_Nil();}return _List<char>::_Cons(s.at(0), toList(std::string(s).erase(0, 1)));};return toList(stringVersion);};

_IO<_Unit> end = []() {auto _631 = _Unit::_unit();auto _630 = returnIO<_Unit>(_631);return _630;}();

template <class A> std::function<_IO<_Unit>(A)> runInIO = [](auto f) { auto _410 = _Unit::_unit();auto _409 = returnIO<_Unit>(_410); return _409;};

template <class A> std::function<std::function<_IO<_Unit>(std::function<A(A)>)>(_List<A>)> baseRun = [](auto inList) { auto _412 = [inList](auto func) { auto _418 = (uint64_t)0;auto _414 = getTime(_418);auto _415 = [func,inList](auto startTime1) { auto _425 = startTime1;auto _424 = natToString(_425);auto _420 = print(_424);auto _432 = func;auto _433 = inList;auto _430 = map<A,A>(_432)(_433);auto _426 = runInIO<_List<A>>(_430);auto _440 = (uint64_t)0;auto _436 = getTime(_440);auto _437 = [startTime1,func,inList](auto endTime1) { auto _447 = endTime1;auto _446 = natToString(_447);auto _442 = print(_446);auto _443 = end;auto _441 = bind<_Unit,_Unit>(_442)(_443); return _441;};auto _427 = bindEq<uint64_t,_Unit>(_436)(_437);auto _421 = bind<_Unit,_Unit>(_426)(_427);auto _419 = bind<_Unit,_Unit>(_420)(_421); return _419;};auto _413 = bindEq<uint64_t,_Unit>(_414)(_415); return _413;}; return _412;};

std::function<_List<uint64_t>(uint64_t)> genListI = [](auto n) { auto _448 = [n]() {auto _449 = n; if ( !_449 ) {auto _450 = _List<uint64_t>::_Nil();return _450; } else {auto m = _449 - 1;auto _451 = (uint64_t)3;auto _453 = m;auto _452 = genListI(_453);auto _450 = _List<uint64_t>::_Cons(_451,_452);return _450;} }(); return _448;};

_IO<_Unit> mainFunc = []() {auto _458 = (uint64_t)1;auto _455 = genListI(_458);auto _456 = run;auto _454 = baseRun<uint64_t>(_455)(_456); return _454;}();
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