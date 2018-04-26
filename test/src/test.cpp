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

void test_ellipse(string out_path) {
    Ellipse e(100, 50, 100, 50);
    e.attr({
        {"fill", "DarkGoldenrod"},
        {"stroke", "black"},
        {"stroke-width", "3"},
        {"stroke-dasharray", "5, 5"}
    });
    e.save(out_path);
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

void test_ani_rotate_complex(string in_path, string out_path) {
    ShapePtr g = load(in_path);
    Point center(70, 70);
    g->animate.rotate(center, 0, center, 360)
              .duration("10s")
              .loop(true);
    g->save(out_path);
}

void test_ani_rotate(string out_path) {
    Rect r(20, 20, 100, 100, 3, 3);
    r.attr({
        {"fill", "red"},
        {"stroke", "black"},
        {"stroke-width", "5"}
    });
    Point center(100, 100);
    r.animate.rotate(center, 0, center, 360)
             .duration("10s")
             .loop(true);
    r.save(out_path);
}

void test_heart(string out_path) {
    Path p;
    p.moveTo(121, 251)
     .cubicCurveTo(-25, -80, -50,-80, -100, -130, true)
     .arcTo(70, 70, -45, 0, 1, 100, -100, true)
     .arcTo(70, 70, 45, 0, 1, 100, 100, true)
     .cubicCurveTo(-50, 50, -75, 50, -100, 130, true);
    p.animate.blink(2);
    p.attr("fill", "DeepPink");
    p.save(out_path);
}

void test_path(string out_path) {
    Path p;
    p.moveTo(10, 110)
     .arcTo(120, 120, -45, 0, 1, 110, 10)
     .arcTo(120, 120, -45, 0, 1, 10,  110);
    p.attr({
        {"stroke", "lightgrey"},
        {"stroke-width", "2"},
        {"fill", "none"},
    });
    p.save(out_path);
}

void test_motion(string out_path) {
    Path p;
    p.moveTo(10, 110)
     .arcTo(120, 120, -45, 0, 1, 110, 10)
     .arcTo(120, 120, -45, 0, 1, 10,  110);
    p.attr({
        {"stroke", "lightgrey"},
        {"stroke-width", "2"},
        {"fill", "none"},
    });
    Circle end_point1(10, 110, 3);
    end_point1.attr("fill", "lightgrey");
    Circle end_point2(110, 10, 3);
    end_point2.attr("fill", "lightgrey");
    Circle ball(0, 0, 5);
    ball.attr("fill", "red");
    ball.animate.move_along(p)
                .duration("6s")
                .loop(true);

    Group g(p, end_point1, end_point2, ball);
    g.save(out_path);
}

void test_motion_group(string in_path, string out_path) {
    Path p;
    p.moveTo(10, 110)
     .arcTo(120, 120, -45, 0, 1, 110, 10)
     .arcTo(120, 120, -45, 0, 1, 10,  110);
    p.attr("visibility", "hidden");
    ShapePtr tiger = load(in_path);
    tiger->animate.translate(Point(0, 0), Point(300, 0), true)
                  .begin("0s")
                  .duration("3s");
    tiger->animate.move_along(p)
                  .begin("3s")
                  .duration("6s")
                  .loop(true);
    Group g(p, *tiger);
    g.save(out_path);
}

void test_blink(string out_path) {
    Circle c(100, 100, 20);
    c.attr({
        {"fill", "red"},
        {"stroke", "black"},
        {"stroke-width", "3"},
    });
    c.animate.blink(0.5);
    c.save(out_path);
}

void test_blink_group(string in_path, string out_path) {
    ShapePtr g = load(in_path);
    g->animate.blink(3);
    g->save(out_path);
}

void test_satellite(string out_path) {
    Circle globe(80, 80, 50);
    Path satellite, half_globe;
    satellite.moveTo(0, 70)
             .arcTo(65, 70, 0, 0, 0, 65, 0)
             .arcTo(5, 5, 0, 0, 1, 75, 0)
             .arcTo(75, 70, 0, 0, 1, 0, 70)
             .closePath();
    satellite.attr("fill", "#FFF");
    satellite.animate.rotate(Point(0, 0), 360, Point(0, 0), 0)
                     .duration("1s")
                     .loop(true);
    half_globe.moveTo(50, 0)
              .arcTo(50, 50, 0, 0, 0, -50, 0)
              .closePath();
    // satellite.transfrom.matrix(0.866, -0.5, 0.25, 0.433, 80, 80);
    // half_globe.transfrom.matrix(0.866, -0.5, 0.5, 0.866, 80, 80);

    Group g(globe, half_globe, satellite);
    g.save(out_path);
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
    // test_circle(OUTPUT("simple_circle.svg"));
    test_ellipse(OUTPUT("simple_ellipse.svg"));
    test_path(OUTPUT("simple_path.svg"));
    test_ellipse(OUTPUT("simple_ellipse.svg"));
    test_heart(OUTPUT("heart.svg"));

    // Elementary animation tests
    test_ani_rotate(OUTPUT("rect_rotate.svg"));
    test_ani_rotate_complex("test/svgs/tiger.svg", OUTPUT("tiger_rotate.svg"));
    test_ani_scale(OUTPUT("circle_scale.svg"));
    test_ani_translate_abs(OUTPUT("circle_translate_abs.svg"));
    test_ani_translate_rel(OUTPUT("circle_translate_rel.svg"));
    test_motion(OUTPUT("bezier_motion.svg"));
    test_motion_group("test/svgs/tiger.svg", OUTPUT("bezier_motion_tiger.svg"));

    // compound animation tests
    test_blink(OUTPUT("blink.svg"));
    test_blink_group("test/svgs/tiger.svg", OUTPUT("blink_group.svg"));
    test_satellite(OUTPUT("satellite.svg"));


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
