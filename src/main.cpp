/*
 * Main test file for Animate++ library
 * @author: Wode "Nimo" Ni, Xuanyuan Zhang
 * @version: 04/04/2018
 */

#include <string>
#include <sstream>
#include "animate.hpp"

using namespace std;
using namespace pugi;

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
            std::cout << " " << ait->name() << "=" << ait->value();
        }
        cout << endl;
    }
}

anipp::Rect test_square(string filename) {
    // load
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if(!result)
        throw "Failed to load SVG file!";
    else {
        xml_node svg  = doc.child("svg");
        xml_node rect = svg.child("rect");
        double x = stod(rect.attribute("x").value());
        double y = stod(rect.attribute("y").value());
        double width = stod(rect.attribute("width").value());
        double height = stod(rect.attribute("height").value());
        anipp::Rect rectangle(x, y, width, height);
        return rectangle;
    }
}

int main() {
    print_SVG("test/sample.svg");
    anipp::Rect r = test_square("test/sample.svg");
    cout << r << endl;
    auto doc = r.export_SVG();
    doc.save_file("test/output.svg");
    return 0;
}
