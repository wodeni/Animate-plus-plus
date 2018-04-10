//
// Created by xuanyuan on 4/10/18.
//

#ifndef ANIMATE_PLUS_PLUS_TEST_HPP
#define ANIMATE_PLUS_PLUS_TEST_HPP

#include <sstream>
#include "../../src/animate.hpp"

using namespace std;
using namespace pugi;
using namespace anipp;

// load a string filename and print the whole SVG file
void print_SVG(string);

// load a rectangle. test on "sample.svg".
Rect test_square(string);

// load a sphere. test on "sample.svg".
Circle test_circle(string);

// load a rectangle. test on "sample.svg".
Ellipse test_ellipse(string);

// load a sphere. test on "sample.svg".
Line test_line(string);

// generic test
template <typename T>
void test_shape(T (*test_func)(string), string, string);

#endif //ANIMATE_PLUS_PLUS_TEST_HPP
