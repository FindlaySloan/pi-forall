#include <functional>
#include <iostream>


enum _enum_Nati_type {Zeroi,Succi};

class _Nati {
    public:
        enum _enum_Nati_type type;
        _Nati_Zeroi;
        void* data;
};

class _Nati_Zeroi {
    public:
};

class _Nati_Succi {
    public:
        _Nati _1;
};

std::function<_Nati(_Nati)>pred = [](auto n) {
    auto _1 = [n]() {
        auto _2 = n;
        switch ( _2.type) {
        case Zeroi: {
            auto _4 = *(_Nati_Zeroi*)_2.data;
            auto _3 = _Nati{};
            return _3;}
        case Succi: {
            auto _6 = *(_Nati_Succi*)_2.data;
            auto _5 = _Nati{};
            return _5;}
        default: return _Nati{};
        }
    }();;
    return _1;
};



int main() {

//    std::cout << id(65)(66) << std::endl;

    return 0;
}