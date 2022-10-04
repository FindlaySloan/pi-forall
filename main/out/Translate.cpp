#include <functional>
#include <iostream>

//enum _enum_Maybe_type {
//    Nothing,
//    Just
//};
//template < class A > class _Maybe {
//    public: enum _enum_Maybe_type type;
//    void * data;
//    static _Maybe < A > _Nothing();
//    static _Maybe < A > _Just(A _1);
//};
//template < class A > class _Maybe_Nothing {
//    public: _Maybe_Nothing() {};
//};
//template < class A > class _Maybe_Just {
//    public: A _1;
//    _Maybe_Just(A _1) {
//        this -> _1 = _1;
//    };
//};
//template < class A > inline _Maybe < A > _Maybe < A > ::_Nothing() {
//    _Maybe_Nothing < A > * _innerClass = new _Maybe_Nothing < A > ();
//    return _Maybe < A > {
//        Nothing,
//        _innerClass
//    };
//};
//template < class A > inline _Maybe < A > _Maybe < A > ::_Just(A _1) {
//    _Maybe_Just < A > * _innerClass = new _Maybe_Just < A > (_1);
//    return _Maybe < A > {
//        Just,
//        _innerClass
//    };
//};

//std:: function < char(_Maybe < char > ) > f = [](auto b) {
//  auto _1 = [b]() {
//    auto _2 = b;
//    switch (_2.type) {
//    case Nothing: {
//      auto _4 = * (_Maybe_Nothing<char> * ) _2.data;
//      auto _3 = 'a';
//      return _3;
//    }
//    case Just: {
//      auto _6 = * (_Maybe_Just<char> * ) _2.data;
//      auto n = _6._1;
//      auto _5 = n;
//      return _5;
//    }
//    }
//  }();
//  return _1;
//};

int main() {



    std::cout << f(_Maybe<char>::_Just('b')) << std::endl;

    return 0;
}