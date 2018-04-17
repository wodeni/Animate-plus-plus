/*
 * Main test file for Animate++ library
 * @author: Wode "Nimo" Ni, Xuanyuan Zhang
 * @version: 04/04/2018
 */

#include "test.hpp"


using namespace std;
using namespace pugi;
using namespace anipp;


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
        rectangle.load_properties(rect, "rect");
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
        circle.load_properties(circle_node, "circle");
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
        ellipse.load_properties(ellipse_node, "ellipse");
        return ellipse;
    }
}

Line test_line(string filename) {
    // load
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if(!result)
        throw "Failed to load SVG file!";
    else {
        xml_node svg  = doc.child("svg");
        xml_node line_node = svg.child("line");
        double x1 = stod(line_node.attribute("x1").value());
        double y1 = stod(line_node.attribute("y1").value());
        double x2 = stod(line_node.attribute("x2").value());
        double y2 = stod(line_node.attribute("y2").value());
        Line line(x1, y1, x2, y2);
        line.load_properties(line_node, "line");
        return line;
    }
}

Polyline test_polyline(string filename) {
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if(!result)
        throw "Failed to load SVG file!";
    else {
        xml_node svg  = doc.child("svg");
        xml_node polyline_node = svg.child("polyline");
        vector<Point> points = load_points(polyline_node.attribute("points").value());
        Polyline polyline(points);
        polyline.load_properties(polyline_node, "polyline");
        return polyline;
    }
}

Polygon test_polygon(string filename) {
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if(!result)
        throw "Failed to load SVG file!";
    else {
        xml_node svg  = doc.child("svg");
        xml_node polygon_node= svg.child("polygon");
        vector<Point> points = load_points(polygon_node.attribute("points").value());
        Polygon polygon(points);
        polygon.load_properties(polygon_node, "polygon");
        return polygon;
    }
}

template<typename T>
void test_shape(T (*test_func)(string), string in_path, string out_path) {
    T obj = test_func(in_path);
    cout << obj << "\n";
    xml_document doc = obj.export_SVG();
    doc.save_file(out_path.c_str());
}

int main() {
    string in_path = "test/svgs/sample.svg";
    test_shape<Rect>(test_square, in_path, "test/svgs/Rect.svg");
    test_shape<Circle>(test_circle, in_path, "test/svgs/Circle.svg");
    test_shape<Ellipse>(test_ellipse, in_path, "test/svgs/Ellipse.svg");
    test_shape<Line>(test_line, in_path, "test/svgs/Line.svg");
    test_shape<Polyline>(test_polyline, in_path, "test/svgs/Polyline.svg");
    test_shape<Polygon>(test_polygon, in_path, "test/svgs/Polygon.svg");

    std::string path = "M3,7 5-6 L1,7 1e2-.4 m-10,10 l10,0       "
                       "V27 89 H23           v10 h10             "
                       "C33,43 38,47 43,47   c0,5 5,10 10,10     "
                       "S63,67 63,67         s-10,10 10,10       "
                       "Q50,50 73,57         q20,-5 0,-10        "
                       "T70,40               t0,-15              "
                       "A5,5 45 1,0 40,20    a5,5 20 0,1 -10-10  Z";
    anipp::parser::test_parser(path);

    return 0;
}
