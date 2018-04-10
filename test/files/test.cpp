/*
 * Main test file for Animate++ library
 * @author: Wode "Nimo" Ni, Xuanyuan Zhang
 * @version: 04/04/2018
 */

#include "test.hpp"

// DEBUG function: load an SVG file and print out all of its nodes
void print_SVG(string filename) {
    // load file
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    cout << "Load result: " << result.description() << endl;

    // print out the DOM tree
    xml_node svg = doc.child("svg");
    for (auto it = svg.begin(); it != svg.end(); ++it) {
        cout << it->name() << '\n';
        for (auto ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {
            cout << " " << ait->name() << "=" << ait->value();
        }
        cout << endl;
    }
}

Rect test_square(string filename) {
    // load
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if (!result)
        throw "Failed to load SVG file!";
    else {
        xml_node svg = doc.child("svg");
        xml_node rect = svg.child("rect");
        double x = stod(rect.attribute("x").value());
        double y = stod(rect.attribute("y").value());
        double width = stod(rect.attribute("width").value());
        double height = stod(rect.attribute("height").value());
        Rect rectangle(x, y, width, height);
        return rectangle;
    }
}

Circle test_circle(string filename) {
    // load
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if(!result)
        throw "Failed to load SVG file!";
    else {
        xml_node svg  = doc.child("svg");
        xml_node circle_node = svg.child("circle");
        double cx = stod(circle_node.attribute("cx").value());
        double cy = stod(circle_node.attribute("cy").value());
        double r = stod(circle_node.attribute("r").value());
        Circle circle(cx, cy, r);
        return circle;
    }
}

Ellipse test_ellipse(string filename) {
    // load
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if(!result)
        throw "Failed to load SVG file!";
    else {
        xml_node svg  = doc.child("svg");
        xml_node ellipse_node = svg.child("ellipse");
        double cx = stod(ellipse_node.attribute("cx").value());
        double cy = stod(ellipse_node.attribute("cy").value());
        double rx = stod(ellipse_node.attribute("rx").value());
        double ry = stod(ellipse_node.attribute("ry").value());
        Ellipse ellipse(cx, cy, rx, ry);
        return ellipse;
    }
}

template<typename T>
void test_shape(T (*test_func)(string), string in_path, string out_path) {
    T obj = test_func(in_path);
    cout << obj << endl;
    xml_document doc = obj.export_SVG();
    doc.save_file(out_path.c_str());
}

int main() {
    string in_path = "test/svgs/sample.svg";
    test_shape<Rect>(test_square, in_path, "test/svgs/Rect.svg");
    test_shape<Circle>(test_circle, in_path, "test/svgs/Circle.svg");
    test_shape<Ellipse>(test_ellipse, in_path, "test/svgs/Ellipse.svg");

    return 0;
}
