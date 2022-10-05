#include <functional>
#include <iostream>


enum _enum_Maybe_type {Nothing,Just};template <class A> class _Maybe { public: enum _enum_Maybe_type type; void* data;static _Maybe<A> _Nothing();static _Maybe<A> _Just(A _1);};template <class A> class _Maybe_Nothing { public: _Maybe_Nothing () {}; };template <class A> class _Maybe_Just { public: A _1;_Maybe_Just (A _1) {this->_1= _1;}; };template <class A>  inline _Maybe<A> _Maybe<A>::_Nothing(){ _Maybe_Nothing<A>* _innerClass = new _Maybe_Nothing<A>(); return  _Maybe<A> { Nothing, _innerClass }; };template <class A>  inline _Maybe<A> _Maybe<A>::_Just(A _1){ _Maybe_Just<A>* _innerClass = new _Maybe_Just<A>(_1); return  _Maybe<A> { Just, _innerClass }; };
extern std::function<bool(_Maybe<_Maybe<char>>)> f;
std::function<bool(_Maybe<_Maybe<char>>)>f = [](auto b) { auto _19 = [b]() { auto _20 = b; switch ( _20.type) { case Nothing: {auto _22 = *(_Maybe_Nothing<_Maybe<char>>*)_20.data;auto _21 = false; return _21;}case Just: {auto _24 = *(_Maybe_Just<_Maybe<char>>*)_20.data;auto n = _24._1;auto _23 = true; return _23;}} }(); return _19;};
extern std::function<bool(char)> g;
std::function<bool(char)>g = []() {return [](auto b) { auto _26 = _Maybe<_Maybe<char>>::_Nothing();auto _25 = f(_26); return _25;};}();


//extern char main;
//std:: function < char(_List < char > ) > main = auto _10 = _List::_Nil();
//auto _11 = 'b';
//auto _8 = _List::_Cons();
//auto _9 = 'a';
//auto _7 = _List::_Cons();
//head(_7);
int main() {



    std::cout << "test"<< std::endl;
    std::cout << g('a') << std::endl;

    return 0;
}