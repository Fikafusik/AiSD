
#ifndef __AVLNODE_HPP__
#define __AVLNODE_HPP__

#include "Additional.hpp"

#include <algorithm>
#include <iostream>
#include <cstddef>

template <class Type>
struct AVLNode {
    Type value;
    size_t height;
    AVLNode *left;
    AVLNode *right;
    AVLNode(const Type& value, size_t height = 1, AVLNode *left = nullptr, AVLNode *right = nullptr) :
        value(value), height(height), left(left), right(right) { }
    
    size_t size() const;
    
    AVLNode *minimum();
    AVLNode *maximum();

    int balance_factor() const;
    void height_update();

    AVLNode *rotate_left();
    AVLNode *rotate_right();

    AVLNode *balance();

    AVLNode *remove_minimum();
    AVLNode *insert(const Type& value);
    AVLNode *search(const Type& value);
    AVLNode *remove(const Type& value);

    void display_tree(size_t depth) const;
    void display_list() const;
};

template <class Type>
size_t AVLNode<Type>::size() const {
    return 1 + (left ? left->size() : 0) + (right ? right->size() : 0);
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::minimum() {
    return (left ? left->minimum() : this);
}
template <class Type>
AVLNode<Type> *AVLNode<Type>::maximum() {
    return (right ? right->maximum() : this);
}

template <class Type>
int AVLNode<Type>::balance_factor() const {
    return (right ? right->height : 0) - (left ? left->height : 0);
}

template <class Type>
void AVLNode<Type>::height_update() {
    height = std::max(right ? right->height : 0, left ? left->height : 0) + 1;
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::rotate_left() {
    AVLNode<Type> *node = right;
    right = node->left;
    node->left = this;
    height_update();
    node->height_update();
    return node;
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::rotate_right() {
    AVLNode<Type> *node = left;
    left = node->right;
    node->right = this;
    height_update();
    node->height_update();
    return node;
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::balance() {
    height_update();
	if (balance_factor() == 2) {
		if (right->balance_factor() < 0)
			right = right->rotate_right();
		return rotate_left();
	}
	if (balance_factor() == -2) {
		if (left->balance_factor() > 0)
			left = left->rotate_left();
		return rotate_right();
	}
	return this;
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::remove_minimum() {
    if (!left)
        return right;
    left = left->remove_minimum();
    return balance();
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::insert(const Type& value) {
    if (value < this->value) {
        if (left)
            left = left->insert(value);
        else
            left = new AVLNode<Type>(value);
    }
    else {
        if (right)
            right = right->insert(value);
        else
            right = new AVLNode<Type>(value);
    }
    return balance();
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::search(const Type& value) {
    if (value < this->value) {
		if (left)
            return left->search(value);
    }
	else if (value > this->value) {
        if (right)
		    return right->search(value);	
    }
    else 
        return this;
    return nullptr;
}

template <class Type>
AVLNode<Type> *AVLNode<Type>::remove(const Type& value) {
	if (value < this->value) {
		if (left)
            left = left->remove(value);
    }
	else if (value > this->value) {
        if (right)
		    right = right->remove(value);	
    }
	else {
		AVLNode<Type>* l = left;
		AVLNode<Type>* r = right;
		delete this;
		if (!r) 
            return l;
		AVLNode<Type>* m = r->minimum();
		m->right = r->remove_minimum();
		m->left = l;
		return m->balance();
	}
	return balance();
}

template <class Type>
void AVLNode<Type>::display_tree(size_t depth) const {
    std::cout << value << std::endl;
    if (left) {
        print_tabs(depth);
        std::cout << "\tleft:\t";
        left->display_tree(depth + 1);
    } 
    if (right) {
        print_tabs(depth);
        std::cout << "\tright:\t";
        right->display_tree(depth + 1);
    }
}

template <class Type>
void AVLNode<Type>::display_list() const {
    if (left)
        left->display_list();
    std::cout << value << " ";
    if (right)
        right->display_list();
}
#endif