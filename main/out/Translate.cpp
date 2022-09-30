#include <functional>
#include <iostream>

enum _enum_Maybe_type {
    Nothing,
    Just
};
template < class A > class _Maybe {
    public: enum _enum_Maybe_type type;
    void * data;
    static _Maybe < A > _Nothing();
    static _Maybe < A > _Just(A _1);
};
template < class A > class _Maybe_Nothing {
    public: _Maybe_Nothing() {};
};
template < class A > class _Maybe_Just {
    public: A _1;
    _Maybe_Just(A _1) {
        this -> _1 = _1;
    };
};
template < class A > inline _Maybe < A > _Maybe < A > ::_Nothing() {
    _Maybe_Nothing < A > * _innerClass = new _Maybe_Nothing < A > ();
    return _Maybe < A > {
        Nothing,
        _innerClass
    };
};
template < class A > inline _Maybe < A > _Maybe < A > ::_Just(A _1) {
    _Maybe_Just < A > * _innerClass = new _Maybe_Just < A > (_1);
    return _Maybe < A > {
        Just,
        _innerClass
    };
};


//enum _enum_Nati_type {
//  Zeroi,
//  Succi
//};
//class _Nati {
//  public: enum _enum_Nati_type type;
//  void * data;
//  static _Nati _Zeroi();
//  static _Nati _Succi(_Nati _1);
//};
//class _Nati_Zeroi {
//  public: _Nati_Zeroi() {};
//};
//class _Nati_Succi {
//  public: _Nati _1;
//  _Nati_Succi(_Nati _1) {
//    this -> _1 = _1;
//  };
//};
//inline _Nati _Nati::_Zeroi() {
//  _Nati_Zeroi * _innerClass = new _Nati_Zeroi();
//  return _Nati {
//    Zeroi,
//    _innerClass
//  };
//};
//inline _Nati _Nati::_Succi(_Nati _1) {
//  _Nati_Succi * _innerClass = new _Nati_Succi(_1);
//  return _Nati {
//    Succi,
//    _innerClass
//  };
//};
//extern std:: function < char(_Nati) > show;
//std:: function < char(_Nati) > show = [](auto s) {
//  auto _1 = [s]() {
//    auto _2 = s;
//    switch (_2.type) {
//    case Zeroi: {
//      auto _4 = * (_Nati_Zeroi * ) _2.data;
//      auto _3 = '0';
//      return _3;
//    }
//    case Succi: {
//      auto _6 = * (_Nati_Succi * ) _2.data;
//      auto n = _6._1;
//      auto _5 = '1';
//      return _5;
//    }
//    }
//  }();
//  return _1;
//};
//extern std:: function < char(_Nati) > pred;
//std:: function < char(_Nati) > pred = [](auto n) {
//  auto _7 = [n]() {
//    auto _8 = n;
//    switch (_8.type) {
//    case Zeroi: {
//      auto _10 = * (_Nati_Zeroi * ) _8.data;
//      auto _11 = _Nati::_Zeroi();
//      auto _9 = show(_11);
//      return _9;
//    }
//    case Succi: {
//      auto _13 = * (_Nati_Succi * ) _8.data;
//      auto nn = _13._1;
//      auto _14 = nn;
//      auto _12 = show(_14);
//      return _12;
//    }
//    }
//  }();
//  return _7;
//};

int main() {

    _Maybe<int> a = _Maybe<int>::_Just(123);
    auto aa = (*(_Maybe_Just<int>*)a.data)._1;
    std::cout << aa << std::endl;

//    std::cout << pred(_Nati::_Succi(_Nati::_Succi(_Nati::_Zeroi()))) << std::endl;

    return 0;
}