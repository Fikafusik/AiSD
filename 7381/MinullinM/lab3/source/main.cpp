
#include <string>
#include <iostream>
#include <stack>

#include "stack.hpp"

// Приоритеты обрабатываемых операций
enum operation_t { NOTHING = 0, ADDITION = 1, SUBSTRACTION = 1, MULTIPLICATION = 2, DIVIDING = 2, POWER = 3 };

bool is_digit(char c);
bool is_letter(char c);
bool is_operation(char c);

operation_t get_operation(char c);

bool is_valid_postfix(const std::string& postfix);
std::string postfix_to_infix(const std::string& postfix);

int main() {
    std::string postfix;
    std::getline(std::cin, postfix);
    
    std::cout << "input: " << postfix << std::endl;
    
    if (is_valid_postfix(postfix)) 
        std::cout << "result: " << postfix_to_infix(postfix) << std::endl;
    std::cout << std::endl;
    
    return 0;
}

bool is_digit(char c) {
    return ('0' <= c && c <= '9');
}

bool is_letter(char c) {
    return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

bool is_operation(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

operation_t get_operation(char c) {
    switch (c) {
    case '+':
        return ADDITION;
    case '-':
        return SUBSTRACTION;
    case '*':
        return MULTIPLICATION;
    case '/':
        return DIVIDING;
    case '^':
        return POWER;
    default:
        return NOTHING;
    }
}

bool is_valid_postfix(const std::string& postfix) {
    // Имеет ли строка нулевую длину без пробельных символов,
    bool empty = true;
    for (size_t index = 0; index < postfix.length(); ++index)
        if (!isspace(postfix[index]))
            empty = false;
    if (empty) {
        std::cout << "error: input is empty" << std::endl;
        return false;
    }

    // Переменная, эмулирующая количество элементов в стэке
    int operands = 0;
    for (size_t index = 0; index < postfix.length(); ++index) {
        // Числа и буквы считаются операндами
        if (is_digit(postfix[index]) || is_letter(postfix[index]))
            ++operands;
        // Знаки "+", "-", "*", "/", "^" считаются операциями
        else if (is_operation(postfix[index])) {
            // Если в стэке меньше 2 элементов, входные данные некорректны
            if (operands < 2) {
                std::cout << "error (index: " << index << ", symbol: " << postfix[index] << "): operand expected" << std::endl; 
                return false;
            }
            // Извлечь 2 операнда, вернуть в стэк 1, итого: -1 операнд
            --operands;
        }
        // Символ не входит в алфавит возможных символов входных данных
        else if (!isspace(postfix[index])) {
            std::cout << "error (index: " << index << ", symbol: " << postfix[index] << "): not supported symbol" << std::endl; 
            return false;
        }

    }
    // В стэке должен остаться ровно 1 элемент
    if (operands != 1) {
        std::cout << "error: too little operations" << std::endl; 
        return false;
    }
    return true;
}

std::string postfix_to_infix(const std::string& postfix) {
    Stack< std::pair<std::string, operation_t> > stack;

    for (size_t index = 0; index < postfix.length(); ++index) {
        if (is_digit(postfix[index]) || is_letter(postfix[index]))
            stack.push(std::make_pair(postfix.substr(index, 1), NOTHING));
        else if (is_operation(postfix[index])) {
            // Вытаскиваем с вершины стека 2 операнда в обратном порядке:
            // сначала - правый, затем - левый
            std::pair<std::string, operation_t> operand_r = stack.top();
            stack.pop();
            std::pair<std::string, operation_t> operand_l = stack.top();
            stack.pop();

            operation_t new_operation = get_operation(postfix[index]);

            // Добавляем скобки, если приоритет новой операции выше 
            // приоритета sub operation левого операнда 
            if (operand_l.second != NOTHING && operand_l.second < new_operation)
                operand_l.first = "(" + operand_l.first + ")";
            // Добавляем скобки, если приоритет новой операции выше 
            // приоритета sub operation правого операнда 
            if (operand_r.second != NOTHING && operand_r.second < new_operation)
                operand_r.first = "(" + operand_r.first + ")";

            // Возвращаем в стек объединение 2 операндов и знак операции,
            // обрамлённый двумя пробельными символами справа и слева
            stack.push(std::make_pair(operand_l.first + " " + postfix.substr(index, 1) + " " + operand_r.first, new_operation));
        }
    }

    // Возвращаем единственный оставший операнд стеке - решение задачи
    return stack.top().first;
}