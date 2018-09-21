
#include <iostream>
#include <string>
#include <algorithm>

void print_tabs(size_t tabs_count) {
    for (size_t i = 0; i < tabs_count; ++i)
        std::cout << '\t';
}

void error_handler(int error_code, size_t tabs_count) {
    if (error_code != 0) {
        print_tabs(tabs_count);
        std::cout << "error: ";
    }

    switch (error_code) {
    case 1:
        std::cout << "'A' or '(' expected" << std::endl;
        break;
    case 2:
        std::cout << "'B' expected" << std::endl;
        break;
    case 3:
        std::cout << "')' expected" << std::endl;
        break;
    case 4:
        std::cout << "excess symbols" << std::endl;
        break;
    }
}

bool brackets(const std::string &str, size_t &index, size_t tabs_count) {
    print_tabs(tabs_count);
    std::cout << "call [index: " << index << "]" << std::endl;

    bool result = true;

    if (str[index] == 'A') {
        ++index;
        result = true;
    } 
    else if (str[index] == '(') {
        ++index;
        if (str[index] == 'B') {
            ++index;
            bool brackets1 = brackets(str, index, tabs_count + 1);
            bool brackets2 = brackets(str, index, tabs_count + 1);
            result = brackets1 && brackets2;
            if (str[index] == ')')
                ++index;
            else {
                result = false;
                error_handler(3, tabs_count);
            }
        }
        else {
            result = false;
            error_handler(2, tabs_count);
        }
    } else {
        result = false;
        error_handler(1, tabs_count);
    }

    print_tabs(tabs_count);
    std::cout << "llac" << std::endl;

    return result;
}

bool lexical_analyzer(std::string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    
    size_t index = 0;
    bool result = brackets(str, index, 0);
    
    if (result && str.length() != index) {
        result = false;   
        error_handler(4, 0);
    }

    return result;
}

int main() {

    std::string str;
    std::cin >> str;

    std::cout << "lexical analyser: " << std::endl;
    std::cout << "input: " << str << std::endl;    
    bool result = lexical_analyzer(str);

    std::cout << "result: ";
    if (result)
        std::cout << "success";
    else 
        std::cout << "failure";
    std::cout << std::endl << std::endl;

    return 0;
}