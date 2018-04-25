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

// https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros/13709929
string anipp::dtos(double d) {
    std::string str{std::to_string (d)};
    int offset{1};
    if (str.find_last_not_of('0') == str.find('.')) { offset = 0; } str.erase(str.find_last_not_of('0') + offset, std::string::npos);
    return str;
}

char anipp::get_type_char(CommandType t, bool isRelative) {
    char c = type_map.right.at(t);
    return isRelative ? tolower(c) : c;
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
            res += dtos(p);
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
    return dtos(this->x) + " " + dtos(this->y);
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

void anipp::die(string msg) {
    cout << msg << '\n';
    exit(-1);
}
