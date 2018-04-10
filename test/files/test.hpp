//
// Created by xuanyuan on 4/10/18.
//

#ifndef ANIMATE_PLUS_PLUS_TEST_HPP
#define ANIMATE_PLUS_PLUS_TEST_HPP

#include "../../src/animate.hpp"

using namespace std;
using namespace pugi;
using namespace anipp;

// load a string filename and print the whole SVG file
void print_SVG(string);

// load a rectangle. test on "Rect.svg".
Rect test_square(string);

// load a sphere. test on "Circle.svg".
Circle test_circle(string);

// load a ellipse. test on "Ellipse.svg".
Ellipse test_ellipse(string);

// load a line. test on "Line.svg".
Line test_line(string);

// load a polyline. test on "Polyline.svg".
Polyline test_polyline(string);

// load a polygon. test on "Polygon.svg".
Polygon test_polygon(string);

// generic test
template <typename T>
void test_shape(T (*test_func)(string), string, string);

#endif //ANIMATE_PLUS_PLUS_TEST_HPP
