
#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <stack>
#include <cstddef>

template <class Type>
class Stack {
private:
    // Количество реально хранимых элементов
    size_t _top;
    // Под сколько элементов выделено памяти 
    size_t _size;
    // Массив данных
    Type *_data;
    // Множитель объёма памяти при переполнении стэка
    static const size_t incr_factor = 2;
    // если _top < _size / decr_factor (пороговое значение),
    // то следует уменьшить объём выделенной памяти.
    // для оптимального выделения памяти decr_factor > incr_factor
    static const size_t decr_factor = 3;
public:
    Stack();

    Type top();
    void pop();
    void push(const Type& value);
    
    size_t size() const;
    bool empty() const;

    ~Stack();
};

template <class Type>
Stack<Type>::Stack() {
    _top = 0;
    _size = 1;
    _data = new Type[_size];
}

template <class Type>
Type Stack<Type>::top() {
    return _data[_top - 1];
}

template <class Type>
void Stack<Type>::pop() {
    --_top;
    // Если стэке хранится меньше, чем _size / decr_factor элементов
    // то размер выделенной памяти вменьшается в incr_factor раз
    if (_top * decr_factor < _size && _size > 1) {
        size_t new_size = _size / incr_factor;
        // Копирование содержимого стэка в новую область памяти
        Type *new_data = new Type[new_size];
        for (size_t index = 0; index < new_size; ++index)
            new_data[index] = _data[index];
        // Освобождение старых ресурсов
        delete[] _data;

        _size = new_size;
        _data = new_data;
    }
}

template <class Type>
void Stack<Type>::push(const Type& value) {
    _data[_top] = value;
    ++_top;
    // Если стэк переполнен, то объём выделенной 
    // памяти увеличивается в incr_factor раз
    if (_top == _size) {
        size_t new_size = _size * incr_factor;
        // Копирование содержимого стэка в новую область памяти
        Type *new_data = new Type[new_size];
        for (size_t index = 0; index < _size; ++index)
            new_data[index] = _data[index];
        // Освобождение старых ресурсов
        delete[] _data;

        _size = new_size;
        _data = new_data;
    }
}

template <class Type>
size_t Stack<Type>::size() const {
    return (_top);
}

template <class Type>
bool Stack<Type>::empty() const {
    return (!_top);
}

template <class Type>
Stack<Type>::~Stack() {
    // Память выделена даже для пустого стэка, поэтому
    // дополнительная проверка не требуется
    delete[] _data;
}

#endif