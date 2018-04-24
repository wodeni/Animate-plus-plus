/*
 * Main test file for Animate++ library
 * @author: Wode "Nimo" Ni, Xuanyuan Zhang
 * @version: 04/04/2018
 */

#include "test.hpp"

#define OUTPUT(s) out_dir + "/" + s

using namespace std;
using namespace pugi;
using namespace anipp;

const string out_dir = "test/output";


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

void test_complex_path(string path_string, string out_path) {
    xml_document doc;
    auto svg = SVG_header(doc);
    Path p(path_string);
    auto node = p.export_SVG(doc);
    svg.append_move(node);
    doc.save_file(out_path.c_str());
}

void test_group(string in_path, string out_path) {
    // load SVG
    ShapePtr g = load(in_path);
    // output the object to an SVG file
    g->save(out_path);
}

void test_square(string out_path) {
    Rect r(0, 0, 100, 100, 3, 3);
    // r.attr("fill", "red");
    r.attr({
        {"fill", "red"},
        {"stroke", "black"},
        {"stroke-width", "5"}
    });

    r.save(out_path);
}

void test_ani_square(string out_path) {
    Rect r(0, 0, 100, 100, 3, 3);
    r.attr("fill", "red");
    // r.animate.rotate()
    r.save(out_path);
}

int main() {
    // I/O tests
    test_group("test/svgs/sample.svg", "test/output/sample_out.svg");
    test_group("test/svgs/tiger.svg", "test/output/tiger_out.svg");
    test_group("test/svgs/lowpoly-wolf.svg", "test/output/lowpoly-wolf_out.svg");
    test_group("test/svgs/lowpoly-tiger.svg", "test/output/lowpoly-tiger_out.svg");
    test_group("test/svgs/sketch.svg", "test/output/sketch_out.svg");
    test_group("test/svgs/satellite.svg", "test/output/satellite_out.svg");

    // Simple shape tests
    test_square(OUTPUT("simple_rect.svg"));

    // separate test for SVG path parser
    std::string path = "M3,7 5-6 L1,7 1e2-.4 m-10,10 l10,0       "
                       "V27 89 H23           v10 h10             "
                       "C33,43 38,47 43,47   c0,5 5,10 10,10     "
                       "S63,67 63,67         s-10,10 10,10       "
                       "Q50,50 73,57         q20,-5 0,-10        "
                       "T70,40               t0,-15              "
                       "A5,5 45 1,0 40,20    a5,5 20 0,1 -10-10  Z";
    anipp::parser::test_parser(path);
    test_complex_path(path, "test/output/path_out.svg");

    return 0;
}
