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
const bool DEBUG = false;


// DEBUG function: load an SVG file and print out all of its nodes
void print_SVG(string filename) {
    // load file
    xml_document doc;
    xml_parse_result result = doc.load_file(filename.c_str());
    if(DEBUG) cout << "Load result: " << result.description() << endl;

    // print out the DOM tree
    xml_node svg = doc.child("svg");
    for (auto it = svg.begin(); it != svg.end(); ++it) {
        if(DEBUG) cout << it->name() << '\n';
        for (auto ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {
            if(DEBUG) cout << " " << ait->name() << "=" << ait->value();
        }
        if(DEBUG) cout << endl;
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
    r.attr({
        {"fill", "blue"},
        {"stroke", "black"},
        {"stroke-width", "5"}
    });
    r.attr("fill", "red");
    r.save(out_path);
}

void test_ani_scale(string out_path) {
    Circle c(100, 100, 100);
    c.attr({
        {"fill", "aqua"},
        {"opacity", "0.5"}
    });
    c.animate.scale(Point(0, 0), Point(1, 1))
             .duration("2.5s")
             .loop(true);
    c.save(out_path);
}

void test_ani_translate_rel(string out_path) {
    Circle c(100, 100, 100);
    c.attr({
        {"fill", "yellow"},
        {"opacity", "0.5"}
    });
    c.animate.translate(Point(100, 100), Point(0, 200), true)
             .duration("2.5s")
             .loop(true);
    c.save(out_path);
}

void test_ani_translate_abs(string out_path) {
    Circle c(100, 100, 100);
    c.attr({
        {"fill", "yellow"},
        {"opacity", "0.5"}
    });
    c.animate.translate(Point(100, 100), Point(0, 200))
             .duration("2.5s")
             .loop(true);
    c.save(out_path);
}

void test_ani_rotate(string out_path) {
    Rect r(20, 20, 100, 100, 3, 3);
    r.attr({
        {"fill", "red"},
        {"stroke", "black"},
        {"stroke-width", "5"}
    });
    Point center(70, 70);
    r.animate.rotate(center, 0, center, 360)
             .duration("10s")
             .loop(true);
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

    // Elementary animation tests
    test_ani_rotate(OUTPUT("rect_rotate.svg"));
    test_ani_scale(OUTPUT("circle_scale.svg"));
    test_ani_translate_abs(OUTPUT("circle_translate_abs.svg"));
    test_ani_translate_rel(OUTPUT("circle_translate_rel.svg"));

    // separate test for SVG path parser
    std::string path = "M3,7 5-6 L1,7 1e2-.4 m-10,10 l10,0       "
                       "V27 89 H23           v10 h10             "
                       "C33,43 38,47 43,47   c0,5 5,10 10,10     "
                       "S63,67 63,67         s-10,10 10,10       "
                       "Q50,50 73,57         q20,-5 0,-10        "
                       "T70,40               t0,-15              "
                       "A5,5 45 1,0 40,20    a5,5 20 0,1 -10-10  Z";
    // anipp::parser::test_parser(path);
    test_complex_path(path, "test/output/path_out.svg");

    return 0;
}
