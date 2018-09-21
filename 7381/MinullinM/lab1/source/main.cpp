
#include "rocker.hpp"

#include <iostream>

int main() {
    std::string str;
    std::getline(std::cin, str);
    
    std::cout << "input: " << str << std::endl;
    Rocker rocker(str);
    
    if (rocker.validity())
        rocker.print_info();
        
    std::cout << "result: ";
    if (rocker.validity())
        std::cout << "success";
    else
        std::cout << "failure";
    std::cout << std::endl << std::endl;

    return 0;
}