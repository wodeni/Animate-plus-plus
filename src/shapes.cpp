#include "shapes.hpp"

using namespace anipp;
using namespace std;

/*
 * Point
 */
Point::Point(double x, double y)
        : x{x}
        , y{y}
{ }

// This print x and y value together with a space between them.
// Used for "toString" method.
string Point::display() const {
    return to_string(this->x) + " " + to_string(this->y);
}

//TODO: is there anyway we can skip virtual function?
xml_document Point::export_SVG() {
    xml_document doc;
    return doc;
}

ostream& Point::print(ostream& out) const {
    out << "Point: " <<
        "x = " << this->x <<
        " y = " << this->y << "\n";
    return out;
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
        res = res + (*it).display() + " ";
    return res + (*it).display();
}

// load properties from string into map
void anipp::Shape::load_properties(xml_node & node, string type) {
    auto it = internal_properties.find(type);
    assert(it != internal_properties.end());
    set<string> variables = it -> second;
    for (auto ait = node.attributes_begin(); ait != node.attributes_end(); ++ait) {
        if(variables.find(ait->name()) == variables.end()) {
            (this->properties).insert(pair<string, string>(ait->name(), ait->value()));
        }
    }
}

// export properties to the given node
void anipp::Shape::export_properties(xml_node & node) {
    for(auto it=this->properties.begin(); it!=this->properties.end(); ++it) {
        auto key = it->first;
        auto value = it->second;
        auto attr = node.append_attribute(key.c_str());
        attr.set_value(value.c_str());
    }
}

// print all properties
void anipp::Shape::print_properties(ostream& out) const {
    for(auto it=this->properties.begin(); it!=this->properties.end(); ++it) {
        auto key = it->first;
        auto value = it->second;
        out << key << " = " << value << ", ";
    }
    out << "\n";
}


/*
 * Rectangle
 */
Rect::Rect(double x, double y, double w, double h, double rx, double ry)
    : x{x}
    , y{y}
    , width{w}
    , height{h}
    , rx{rx}
    , ry{ry}
{ }

xml_document Rect::export_SVG() {
    xml_document doc;
    auto svg  = doc.append_child("svg");
    svg.append_attribute("version").set_value("1.1");
    svg.append_attribute("xmlns").set_value("http://www.w3.org/2000/svg");
    auto rect = svg.append_child("rect");
    auto x    = rect.append_attribute("x");
    auto y    = rect.append_attribute("y");
    auto width  = rect.append_attribute("width");
    auto height = rect.append_attribute("height");
    x.set_value(this->x);
    y.set_value(this->y);
    width.set_value(this->width);
    height.set_value(this->height);
    this->export_properties(rect);
    return doc;
}

ostream& Rect::print(ostream& out) const {
    out << "Rect: " <<
        "x = " << this->x <<
        ", y = " << this->y <<
        ", width = " << this->width <<
        ", height = " << this->height <<
        ", ";
    anipp::Shape::print_properties(out);
    return out;
}

/*
 * Circle
 */
Circle::Circle(double cx, double cy, double r)
    : cx{cx}
    , cy{cy}
    , r{r}
{ }

xml_document Circle::export_SVG() {
    xml_document doc;
    auto svg  = doc.append_child("svg");
    svg.append_attribute("version").set_value("1.1");
    svg.append_attribute("xmlns").set_value("http://www.w3.org/2000/svg");
    auto circle = svg.append_child("circle");
    auto cx    = circle.append_attribute("cx");
    auto cy    = circle.append_attribute("cy");
    auto r    = circle.append_attribute("r");
    cx.set_value(this->cx);
    cy.set_value(this->cy);
    r.set_value(this->r);
    this->export_properties(circle);
    return doc;
}

ostream& Circle::print(ostream& out) const {
    out << "Circle: " <<
        "cx = " << this->cx <<
        ", cy = " << this->cy <<
        ", r = " << this->r <<
        ", ";
    anipp::Shape::print_properties(out);
    return out;
}

/*
 * Ellipse
 */
Ellipse::Ellipse(double cx, double cy, double rx, double ry)
        : cx{cx}
        , cy{cy}
        , rx{rx}
        , ry{ry}
{ }

xml_document Ellipse::export_SVG() {
    xml_document doc;
    auto svg  = doc.append_child("svg");
    svg.append_attribute("version").set_value("1.1");
    svg.append_attribute("xmlns").set_value("http://www.w3.org/2000/svg");
    auto ellipse = svg.append_child("ellipse");
    auto cx    = ellipse.append_attribute("cx");
    auto cy    = ellipse.append_attribute("cy");
    auto rx    = ellipse.append_attribute("rx");
    auto ry    = ellipse.append_attribute("ry");
    cx.set_value(this->cx);
    cy.set_value(this->cy);
    rx.set_value(this->rx);
    ry.set_value(this->ry);
    this->export_properties(ellipse);
    return doc;
}

ostream& Ellipse::print(ostream& out) const {
    out << "Ellipse: " <<
        "cx = " << this->cx <<
        ", cy = " << this->cy <<
        ", rx = " << this->rx <<
        ", ry = " << this->ry <<
        ", ";
    anipp::Shape::print_properties(out);
    return out;
}

/*
 * Line
 */
Line::Line(double x1, double y1, double x2, double y2)
        : x1{x1}
        , y1{y1}
        , x2{x2}
        , y2{y2}
{ }

xml_document Line::export_SVG() {
    xml_document doc;
    auto svg  = doc.append_child("svg");
    svg.append_attribute("version").set_value("1.1");
    svg.append_attribute("xmlns").set_value("http://www.w3.org/2000/svg");
    auto line = svg.append_child("line");
    auto x1 = line.append_attribute("x1");
    auto y1 = line.append_attribute("y1");
    auto x2 = line.append_attribute("x2");
    auto y2 = line.append_attribute("y2");
    x1.set_value(this->x1);
    y1.set_value(this->y1);
    x2.set_value(this->x2);
    y2.set_value(this->y2);
    this->export_properties(line);
    return doc;
}

ostream& Line::print(ostream& out) const {
    out << "Line: " <<
        "x1 = " << this->x1 <<
        ", y1 = " << this->y1 <<
        ", x2 = " << this->x2 <<
        ", y2 = " << this->y2 <<
        ", ";
    anipp::Shape::print_properties(out);
    return out;
}


/*
 * Polyline
 */
Polyline::Polyline(vector<Point> & points)
        : points(points)
{ }

xml_document Polyline::export_SVG() {
    xml_document doc;
    auto svg  = doc.append_child("svg");
    svg.append_attribute("version").set_value("1.1");
    svg.append_attribute("xmlns").set_value("http://www.w3.org/2000/svg");
    auto polyline = svg.append_child("polyline");
    auto points = polyline.append_attribute("points");
    points.set_value(toString(this->points).c_str());
    this->export_properties(polyline);
    return doc;
}

ostream& Polyline::print(ostream& out) const {
    out << "Polyline: points = ";
    for(auto it=this->points.begin(); it!=this->points.end(); ++it)
        out << (*it).display() << " ";
    anipp::Shape::print_properties(out);
    return out;
}

/*
 * Polygon
 */
Polygon::Polygon(vector<Point> & points)
        : points(points)
{ }

xml_document Polygon::export_SVG() {
    xml_document doc;
    auto svg  = doc.append_child("svg");
    svg.append_attribute("version").set_value("1.1");
    svg.append_attribute("xmlns").set_value("http://www.w3.org/2000/svg");
    auto polygon= svg.append_child("polygon");
    auto points = polygon.append_attribute("points");
    points.set_value(toString(this->points).c_str());
    this->export_properties(polygon);
    return doc;
}

ostream& Polygon::print(ostream& out) const {
    out << "Polygon: points = ";
    for(auto it=this->points.begin(); it!=this->points.end(); ++it)
        out << (*it).display() << " ";
    anipp::Shape::print_properties(out);
    return out;
}

/*
 * Path
 */
Path::Path(vector<Point>& points) {


}

ostream& Path::print(ostream& out) const {

}


/*
 * Path description
 * See standard https://www.w3.org/TR/SVG/paths.html
 */
 PathDescription::PathDescription(string s) {
     cout << s << '\n';
 }

ostream& operator<< (ostream& out, const anipp::Shape& shp) {
    shp.print(out);
    return out;
}
