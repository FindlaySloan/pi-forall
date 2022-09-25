#include <functional>
#include <iostream>





int main() {

    std::cout << doSomething([](auto a){return 'b';}) << std::endl;

    return 0;
}