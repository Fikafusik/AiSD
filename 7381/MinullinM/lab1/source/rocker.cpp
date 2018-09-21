
#include "rocker.hpp"

#include <iostream>

void print_tabs(size_t tabs_count) {
    for (size_t i = 0; i < tabs_count; ++i)
        std::cout << '\t';
}

size_t read_number(const std::string& str, size_t& index) {
    size_t result = 0;
    while (isdigit(str[index])) {
        result *= 10;
        result += str[index] - '0';
        ++index;
    }
    return result;
}

void error_handler(int error_code, size_t index, const std::string& str, size_t depth) { 
    if (error_code == 0)
        return;
    print_tabs(depth);
    std::cout << "ERROR CODE " << error_code << " at index " << index << " (symbol '" << str[index] << "'): ";
    switch (error_code) {
    case 1:
        std::cout << "'(' expected";
        break;
    case 2:
        std::cout << "')' expected";
        break;
    case 3:
        std::cout << "['0'-'9'] expected";
        break;
    case 4:
        std::cout << "'(' or ['0'-'9'] expected";
        break;    
    case 5:
        std::cout << "excess symbols";
        break;
    }
    std::cout << std::endl;
}
bool Rocker::rocker(const std::string& str, size_t& index, size_t depth) {
    print_tabs(depth);
    std::cout << "call .rocker [index: " << index << " , symbol: " << str[index] << "]" << std::endl;

    bool result = true;
    
    if (str[index] == '(') {
        ++index;
        // Считывается левое плечо
        if (!arm(str, index, LEFT, depth + 1))
            result = false;
        // Считывается правое плечо
        if (!arm(str, index, RIGHT, depth + 1))
            result = false;

        if (str[index] == ')')
            ++index;
        else {
            // Ожидалась закрывающася скобка
            error_handler(2, index, str, depth);
            result = false;
        }
    }
    else {
        // Ожидалась открывающаяся скобка
        error_handler(1, index, str, depth);
        result = false;
    }

    print_tabs(depth);
    std::cout << "llac .rocker" << std::endl;

    return result;
}

bool Rocker::arm(const std::string& str, size_t& index, side_t side, size_t depth) {
    print_tabs(depth);
    std::cout << "call .arm [index: " << index << " , symbol: " << str[index] << "]" << std::endl;
    
    bool result = true;

    if (str[index] == '(') 
        ++index;
    else {

        error_handler(1, index, str, depth);
        result = false;
    }
    if (!isdigit(str[index])) {
        // Ожидалась цифра
        error_handler(3, index, str, depth);
        result = false;
    }
    size_t length = read_number(str, index);

    if (side == LEFT)
        length1 = length;
    if (side == RIGHT)
        length2 = length;

    if (str[index] == ' ')
        ++index;
    if (!cargo(str, index, side, depth + 1))
        result = false;

    if (str[index] == ')')
        ++index;
    else {
        error_handler(2, index, str, depth);
        result = false;
    }

    print_tabs(depth);
    std::cout << "llac .arm" << std::endl;

    return result;
}

bool Rocker::cargo(const std::string& str, size_t& index, side_t side, size_t depth) {
    print_tabs(depth);
    std::cout << "call .cargo [index: " << index << " , symbol: " << str[index] << "]" << std::endl;
    
    bool result = true;

    if (isdigit(str[index])) {
        size_t weight = read_number(str, index);
        if (side == LEFT)
            weight1 = weight;
        if (side == RIGHT)
            weight2 = weight;
    }
    else if (str[index] == '(') {
        if (side == LEFT) {
            left = new Rocker;
            if (!(left->rocker(str, index, depth + 1)))
                result = false;
        }
        if (side == RIGHT) {
            right = new Rocker;
            if (!right->rocker(str, index, depth + 1))
                result = false;
        }
    }
    else {
        // Ожидалась открывающаяся скобка или цифра
        error_handler(4, index, str, depth);
        result = false;
    }

    print_tabs(depth);
    std::cout << "llac .cargo" << std::endl;

    return result;
}

Rocker::Rocker() {
    length1 = 0;
    length2 = 0;
    weight1 = 0;
    weight2 = 0;
    left = right = NULL;
    is_valid = false;
}

Rocker::Rocker(const std::string& str) {
    length1 = 0;
    length2 = 0;
    weight1 = 0;
    weight2 = 0;
    left = right = NULL;
    is_valid = false;

    size_t index = 0;
    if (rocker(str, index, 0)) {
        is_valid = true;
        if (index != str.length()) {
            is_valid = false;
            // Лишние символы в строке
            error_handler(5, index, str, 0);
        }
    }
}

bool Rocker::validity() {
    return is_valid;
}

void Rocker::print_info() {
    std::cout <<    length() << "\t : summary length of arms" << std::endl;
    std::cout <<    weight() << "\t : summary weight of cargoes" << std::endl;
    std::cout << dumbbells() << "\t : count of dumbbells" << std::endl;
    std::cout << (balanced() ? "yes" : "no") << "\t : balancing status" << std::endl; 
}

size_t Rocker::length() {
    size_t result = length1 + length2;
    
    if (left) 
        result += left->length();
    if (right)
        result += right->length();
        
    return result;
}

size_t Rocker::weight() {
    size_t result = weight1 + weight2;

    if (left)
        result += left->weight();
    if (right)
        result += right->weight();

    return result;
}

size_t Rocker::dumbbells() {
    size_t result = 0;

    if (left)
        result += left->dumbbells();
    else
        ++result;

    if (right)
        result += right->dumbbells();
    else
        ++result;

    return result;
}

bool Rocker::balanced() {
    // Вращающий момент левого поддерева
    size_t torque1 = (length1 * (left ? left->weight() : weight1));
    // Вращающий момент правого поддерева
    size_t torque2 = (length2 * (right ? right->weight() : weight2));
    return (torque1 == torque2);
}

Rocker::~Rocker() {
    if (left)
        delete left;
    if (right)
        delete right;
}
