
#include "AVLTree.hpp"

#include <iostream>
#include <typeinfo>
#include <algorithm>

typedef int Type;

int main() {
    const size_t max_count = 16;
    Type array[max_count];
    AVLTree<Type> avl_tree;

    Type element;
    std::cin >> element;

    Type value;
    size_t count = 0;
    while (!std::cin.eof()) {
        std::cin >> value;
        if (count < max_count)
            array[count] = value;
        ++count;

        avl_tree.insert(value);
    }
    
    std::cout << "AVL-Tree input:" << std::endl;
    std::cout << "\telement:\t" << element << std::endl;

    std::cout << "\tvalues:\t\t";
    if (count == 0)
        std::cout << "empty";
    if (count > 0)
        std::cout << array[0];
    for (size_t i = 1; i < std::min(count, max_count); ++i)
        std::cout << ", " << array[i];
    if (count > max_count)
        std::cout << "...";
    std::cout << " (" << count << ")" << std::endl;

    std::cout << "AVL-Tree task: " << std::endl;
    std::cout << "\telement\t\t" << (avl_tree.find(element) ? "" : "NOT ") << "found" << std::endl;
    avl_tree.remove(element);
    std::cout << "AVL-Tree information: " << std::endl;
    std::cout << "\tHeight:\t\t" << avl_tree.height() << std::endl;
    std::cout << "\tSize:\t\t" << avl_tree.size() << std::endl;
    
    try {
        std::cout << "\tMinimum:\t" << avl_tree.minimum() << std::endl;
    } catch (std::domain_error &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << "\tMaximum:\t" << avl_tree.maximum() << std::endl;
    } catch (std::domain_error &e) {
        std::cout << e.what() << std::endl;
    }

    if (avl_tree.size() <= max_count) {
        std::cout << "\tValues:\t\t";
        avl_tree.display_list();
        std::cout << "\tScheme:\t\t";
        avl_tree.display_tree();
    }

    std::cout << std::endl;

    return 0;
}