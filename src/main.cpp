/*
 * Main test file for Animate++ library
 * @author: Wode "Nimo" Ni, Xuanyuan Zhang
 * @version: 04/04/2018
 */

#include <iostream>
#include <string>
#include <sstream>
#include "pugixml.hpp"
#include "animate.hpp"

using namespace std;
using namespace pugi;

// DEBUG function: load an SVG file and print out all of its nodes
void print_SVG(string filename) {
    // load
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    cout << "Load result: " << result.description() << endl;

    xml_node svg = doc.child("svg");
    for (auto it = svg.begin(); it != svg.end(); ++it) {
        cout << it->name() << '\n';
        for (auto ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {
            std::cout << " " << ait->name() << "=" << ait->value();
        }
        cout << endl;
    }
}

int main() {
    print_SVG("test/sample.svg");
    return 0;
}
