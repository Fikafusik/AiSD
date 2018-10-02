
#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <cstddef>

template <class Type>
class Queue {
private:
    Type _value;
    Queue *_first;
    Queue *_last;
    Queue *_next;
    size_t _size;
public:
    Queue();

    void push(const Type& value);
    Type peek();
    void pop();

    size_t size() const;
    bool empty() const;

    ~Queue();
};

template <class Type>
Queue<Type>::Queue() {
    _first = nullptr;
    _last = nullptr;
    _next = nullptr;
    _size = 0;
}

template <class Type>
void Queue<Type>::push(const Type& value) {
    Queue *temp = new Queue;
    temp->_value = value;
    temp->_next = nullptr;
    if (_size == 0) 
        _last = _first = temp;
    else
        _last = _last->_next = temp;
    ++_size;
}

template <class Type>
Type Queue<Type>::peek() {
    return _first->_value;
}

template <class Type>
void Queue<Type>::pop() {
    Queue *temp = _first;
    _first = _first->_next;
    delete temp;
    --_size;
}

template <class Type>
size_t Queue<Type>::size() const {
    return _size;
}

template <class Type>
bool Queue<Type>::empty() const {
    return !_size;
}

template <class Type>
Queue<Type>::~Queue() {
    Queue *temp;
    for (Queue *curr = _first; curr; curr = temp) {
        temp = curr->_next;
        delete curr;
    }
}

#endif