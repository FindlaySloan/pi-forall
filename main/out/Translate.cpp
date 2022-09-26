#include <functional>
#include <iostream>




std::function<std::function<int(int)>(int)>doSomething = [](auto a) { auto _1 = [](auto b) { auto _2 = 7; return _2;}; return _1;};


int main() {

    std::cout << doSomething(1)(2) << std::endl;

    return 0;
}