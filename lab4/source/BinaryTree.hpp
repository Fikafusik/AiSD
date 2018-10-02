
#ifndef __BINARYTREE_HPP__
#define __BINARYTREE_HPP__

#include <string>

#include "Queue.hpp"

void print_tabs(size_t tabs_count);
void error_handler(const std::string &string, size_t index, int error_code);

enum side_t { LEFT, RIGHT };

class BinaryTree {
private:
    char element;

    BinaryTree *left;
    BinaryTree *parent;
    BinaryTree *right;
    bool _constructed;

    void read_non_empty_binary_tree(const std::string &string, size_t &index);
    void read_root(const std::string &string, size_t &index);
    void read_binary_tree(const std::string &string, size_t &index, side_t side);

    void _print(size_t tabs_count);
    BinaryTree* _search_iterative(const char &key, Queue<BinaryTree *> &queue);
public:
    BinaryTree();
    BinaryTree(const std::string &string);

    void print();

    bool constructed();

    size_t height() const;
    size_t depth() const;

    BinaryTree* search_recursive(const char &key);
    BinaryTree* search_iterative(const char &key);

    ~BinaryTree();
};

#endif