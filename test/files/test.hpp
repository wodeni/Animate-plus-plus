//
// Created by xuanyuan on 4/10/18.
//

#ifndef ANIMATE_PLUS_PLUS_TEST_HPP
#define ANIMATE_PLUS_PLUS_TEST_HPP

#include "../../src/animate.hpp"

// load a string filename and print the whole SVG file
void print_SVG(std::string);

// load a rectangle. test on "Rect.svg".
anipp::Rect test_square(std::string);

// load a sphere. test on "Circle.svg".
anipp::Circle test_circle(std::string);

// load a ellipse. test on "Ellipse.svg".
anipp::Ellipse test_ellipse(std::string);

// load a line. test on "Line.svg".
anipp::Line test_line(std::string);

// load a polyline. test on "Polyline.svg".
anipp::Polyline test_polyline(std::string);

// load a polygon. test on "Polygon.svg".
anipp::Polygon test_polygon(std::string);

// generic test
template <typename T>
void test_shape(T (*test_func)(std::string), std::string, std::string);

#endif //ANIMATE_PLUS_PLUS_TEST_HPP
