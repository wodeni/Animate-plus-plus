//
// Created by xuanyuan on 4/10/18.
//

#ifndef ANIMATE_PLUS_PLUS_TEST_HPP
#define ANIMATE_PLUS_PLUS_TEST_HPP

#include "../../src/animate.hpp"

// load a string filename and print the whole SVG file
void print_SVG(std::string);
void test_group(std::string, std::string);
void test_square(std::string);

// generic test
template <typename T>
void test_shape(T (*test_func)(std::string), std::string, std::string);

#endif //ANIMATE_PLUS_PLUS_TEST_HPP
