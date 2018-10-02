
#include <iostream>
#include <string>

#include "BinaryTree.hpp"

int main() {
    std::string string;
    std::getline(std::cin, string);
    std::cout << "input tree: " << string << std::endl;

    BinaryTree binary_tree(string);
    if (!binary_tree.constructed()) {
        std::cout << std::endl;
        return 0;
    }
        
    std::cout << "binary tree successfully built:" << std::endl;
    binary_tree.print();

    char search_item;
    std::cin >> search_item;
    std::cout << "input search item: " << search_item << std::endl;

    BinaryTree *searched_recursive = binary_tree.search_recursive(search_item);
    std::cout << "recursive search result: " << (searched_recursive ? (int)searched_recursive->depth() : -1) << std::endl;
    BinaryTree *searched_iterative = binary_tree.search_iterative(search_item);
    std::cout << "iterative search result: " << (searched_iterative ? (int)searched_iterative->depth() : -1) << std::endl;
    std::cout << std::endl;
    
    return 0;
}