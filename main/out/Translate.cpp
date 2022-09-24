#include <functional>
#include <iostream>



std::function<std::function<char(char)>(char)>id = [](auto a) { auto _1 = [a](auto b) { auto _2 = a; return _2;}; return _1;};

std::function<std::function<char(char)>(char)>doSomething = [](auto a) { auto _4 = a;auto _3 =  id(_4); return _3;};

int main() {

    std::cout << doSomething(68)(66) << std::endl;

    return 0;
}