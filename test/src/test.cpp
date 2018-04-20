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

void test_group(string in_path, string out_path) {
    // load
    xml_document doc_in;
    xml_parse_result result = doc_in.load_file(in_path.c_str());
    if (!result)
        throw "Failed to load SVG file!";
    ShapeList shapes;
    for(auto child : doc_in.child("svg")) {
        auto shp = get_shape(child);
        shapes.push_back(shp);
        cout << *shp << "\n";
    }

    // output the object to an SVG file
    xml_document doc_out;
    auto svg = SVG_header(doc_out);
    for(auto& shp : shapes) {
        auto node = shp->export_SVG(doc_out);
        svg.append_move(node);
    }
    doc_out.save_file(out_path.c_str());
}


template<typename T>
void test_shape(string in_path, string out_path) {
    // T obj = test_func(in_path);
    // Reading the SVG file into an object representation
    xml_document doc_in;
    xml_parse_result result = doc_in.load_file(in_path.c_str());
    if (!result)
        throw "Failed to load SVG file!";
    T obj(doc_in);
    cout << obj << "\n";

    // output the object to an SVG file
    xml_document doc_out;
    auto svg = SVG_header(doc_out);
    auto node = obj.export_SVG(doc_out);
    svg.append_move(node);
    doc_out.save_file(out_path.c_str());
}

int main() {
    string in_path = "test/svgs/sample.svg";
    // test_shape<Rect>(in_path, "test/output/Rect.svg");
    // test_shape<Circle>(in_path, "test/output/Circle.svg");
    // test_shape<Ellipse>(in_path, "test/output/Ellipse.svg");
    // test_shape<Line>(in_path, "test/output/Line.svg");
    // test_shape<Polyline>(in_path, "test/output/Polyline.svg");
    // test_shape<Polygon>(in_path, "test/output/Polygon.svg");
    // test_shape<Path>(in_path, "test/output/Path.svg");
    // test_shape<Group>(test_group, in_path, "test/svgs/Group.svg");
    test_group(in_path, "test/svgs/sample_out.svg");

    // separate test for SVG path parser
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
