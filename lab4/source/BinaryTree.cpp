
#include "BinaryTree.hpp"

#include <iostream>
#include <cstddef>

void print_tabs(size_t tabs_count) {
    for (size_t i = 0; i < tabs_count; ++i)
        std::cout << '\t';
}

void error_handler(const std::string &string, size_t index, int error_code) {
    if (error_code == 0)
        return;
    std::cout << "ERROR CODE " << error_code << " at index " << index << " (symbol '" << string[index] << "'): ";
    switch (error_code) {
    case 1:
        std::cout << "'(' expected";
        break;
    case 2:
        std::cout << "')' expected";
        break;
    case 3:
        std::cout << "['0'-'9'] or ['a'..'z'] expected";
        break;
    case 4:
        std::cout << "excess symbols";
        break;
    }
    std::cout << std::endl;
}

void BinaryTree::read_non_empty_binary_tree(const std::string &string, size_t &index) {
    if (string[index] == '(') {
        ++index;
        read_root(string, index);
        read_binary_tree(string, index, LEFT);
        read_binary_tree(string, index, RIGHT);
        if (string[index] == ')')
            ++index;
        else {
            _constructed = false;
            error_handler(string, index, 2);
        }
    }
    else {
        _constructed = false;
        error_handler(string, index, 1);
    }
}

void BinaryTree::read_root(const std::string &string, size_t &index) {
    if (isdigit(string[index]) || islower(string[index])) {
        element = string[index];
        ++index;
    }
    else {
        _constructed = false;
        error_handler(string, index, 3);
    }
}

void BinaryTree::read_binary_tree(const std::string &string, size_t &index, side_t side) {
    if (string[index] == '.')
        ++index;
    else {
        if (side == LEFT) {
            left = new BinaryTree;
            left->parent = this;
            left->read_non_empty_binary_tree(string, index);
        }
        else {
            right = new BinaryTree;
            right->parent = this;
            right->read_non_empty_binary_tree(string, index);
        }
    }
        
}

void BinaryTree::_print(size_t tabs_count) {
    print_tabs(tabs_count);
    std::cout << element << std::endl;
    if (left)
        left->_print(tabs_count + 1);
    if (right)
        right->_print(tabs_count + 1);
}

BinaryTree* BinaryTree::_search_iterative(const char &key, Queue<BinaryTree *> &queue) {
    while (!queue.empty()) {
        BinaryTree *current = queue.peek();
        queue.pop();
        if (current->element == key)
            return current;
        if (current->left)
            queue.push(current->left);
        if (current->right)
            queue.push(current->right);
    }
    return NULL;
}

BinaryTree::BinaryTree() {
    left = NULL;
    parent = NULL;
    right = NULL;
}

BinaryTree::BinaryTree(const std::string &string) : BinaryTree() {
    _constructed = true;
    size_t index = 0;
    read_non_empty_binary_tree(string, index);
}

void BinaryTree::print() {
    size_t h = height();
    for (size_t i = 0; i < h; ++i)
        std::cout << i << '\t';
    std::cout << std::endl;
    _print(0);
    for (size_t i = 0; i < h; ++i)
        std::cout << i << '\t';
    std::cout << std::endl;
}

bool BinaryTree::constructed() {
    return _constructed;
}

size_t BinaryTree::height() const {
    size_t height_left = 0;
    if (left)
        height_left = left->height();
    size_t height_right = 0;
    if (right)
        height_right = right->height();
    return 1 + std::max(height_left, height_right);
}

size_t BinaryTree::depth() const {
    size_t h = 1;
    if (parent)
        h += parent->depth();
    else
        h = 0;
    return h;
}

BinaryTree* BinaryTree::search_recursive(const char &key) {
    if (element == key)
        return this;
    BinaryTree *search_left = NULL;
    BinaryTree *search_right = NULL;
    if (left)
        search_left = left->search_recursive(key);
    if (right)
        search_right = right->search_recursive(key);
    // Если элемент найден в обоих поддеревьях:
    if (search_left && search_right) {
        // Возвращаем указатель на ближайщий к корню найденный элемент
        size_t depth_left = left->depth();
        size_t depth_right = right->depth();
        if (depth_left < depth_right)
            return left;
        else
            return right;
    } 
    // Если элемент найден только в одном поддереве, возвращаем его
    else if (search_left)
        return search_left;
    else if (search_right)
        return search_right;
    // Если элемент не найден, возвращаем NULL
    return NULL;
}

BinaryTree* BinaryTree::search_iterative(const char &key) {
    Queue<BinaryTree *> queue;
    queue.push(this);
    return _search_iterative(key, queue);
}

BinaryTree::~BinaryTree() {
    if (left)
        delete left;
    if (right)
        delete right;
}