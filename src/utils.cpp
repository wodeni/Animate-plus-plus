#include "utils.hpp"
using namespace std;
using namespace anipp;
using namespace pugi;

// BUG: linker error if the function is uncommented
// template<typename Container>
// void print_container(const Container& cont) {
//    for (auto const& x : cont) {
//       std::cout << "\"" << x  << "\"" << " ";
//    }
//    std::cout << '\n';
// }

ostream& operator<< (ostream& out, const anipp::Command& cmd) {
    out << cmd.type_char << ": ";
    for (auto const& p : cmd.points)
        out <<  p  << " ";
        // out << "\"" << p  << "\"" << " ";
    return out;
}

string anipp::toString(Commands cmds) {
    string res;
    for(Command c : cmds) {
        char type = c.relativity == RELATIVE ?
                    tolower(c.type_char)    :
                    toupper(c.type_char);
        res += type;
        res += " ";
        for(double p : c.points) {
            res += to_string(p);
            res += " ";
        }
    }
    return res;
}

/*
 * Point
 */
Point::Point(double x, double y)
        : x{x}
        , y{y}
{ }

// This print x and y value together with a space between them.
string Point::toString() const {
    return to_string(this->x) + " " + to_string(this->y);
}

// This function can be used in constructing polyline and polygon
// Taking the string as input and return a vector of points.
// ex:
// load_points("100 50 40 30") -> {Point(100, 50), Point(40, 30)}
vector<Point> anipp::load_points(string str) {
    string buf;
    stringstream ss(str);
    vector<string> vec;
    while(ss >> buf) {
        vec.push_back(buf);
    }
    assert(vec.size()%2 == 0);
    vector<Point> vec_res;
    auto it = vec.begin();
    while(it != vec.end()) {
        Point p(stod(*it), stod(*(it+1)));
        vec_res.push_back(p);
        it += 2;
    }
    return vec_res;
}

// This function can be used in export polyline and polygon
// Taking a vector of points as input and return a string containing
// all points in the vector.
// ex:
// toString({Point(100, 50), Point(40, 30)}) -> "100 50 40 30"
string anipp::toString(vector<Point> points) {
    string res;
    auto it=points.begin();
    for(; it!=points.end()-1; ++it)
        res = res + (*it).toString() + " ";
    return res + (*it).toString();
}

xml_node anipp::SVG_header(xml_document& doc) {
    auto svg = doc.append_child("svg");
    svg.append_attribute("version").set_value("1.1");
    svg.append_attribute("xmlns").set_value("http://www.w3.org/2000/svg");
    // TODO: what should be the default value?
    // svg.append_attribute("width").set_value("1000");
    // svg.append_attribute("height").set_value("1000");
    return svg;
}
