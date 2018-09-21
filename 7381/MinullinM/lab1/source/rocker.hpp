
#ifndef __ROCKER_HPP__
#define __ROCKER_HPP__

#include <string>

void print_tabs(size_t tabs_count);
size_t read_number(const std::string& str, size_t& index);
void error_handler(const std::string& str, size_t index, int error_code, size_t depth);

enum side_t { LEFT, RIGHT };

class Rocker {
private:
    size_t length1;
    size_t length2;
    size_t weight1;
    size_t weight2;
    Rocker *left;
    Rocker *right;
    bool is_valid;

    bool rocker(const std::string& str, size_t& index, size_t depth);
    bool arm(const std::string& str, size_t& index, side_t side, size_t depth);
    bool cargo(const std::string& str, size_t& index, side_t side, size_t depth);
public:
    Rocker();
    Rocker(const std::string& str);

    bool validity();
    void print_info();

    size_t length();
    size_t weight();
    size_t dumbbells();

    bool balanced();

    ~Rocker();
};

#endif