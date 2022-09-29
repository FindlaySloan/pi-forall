#include <functional>
#include <iostream>

enum _enum_Nati_type {
  Zeroi,
  Succi
};
class _Nati {
  public: enum _enum_Nati_type type;
  void * data;
  static _Nati _Zeroi();
  static _Nati _Succi(_Nati _1);
};
class _Nati_Zeroi {
  public: _Nati_Zeroi() {};
};
class _Nati_Succi {
  public: _Nati _1;
  _Nati_Succi(_Nati _1) {
    this -> _1 = _1;
  };
};
inline _Nati _Nati::_Zeroi() {
  _Nati_Zeroi * _innerClass = new _Nati_Zeroi();
  return _Nati {
    Zeroi,
    _innerClass
  };
};
inline _Nati _Nati::_Succi(_Nati _1) {
  _Nati_Succi * _innerClass = new _Nati_Succi(_1);
  return _Nati {
    Succi,
    _innerClass
  };
};

int main() {

//    std::cout << id(65)(66) << std::endl;

    return 0;
}