#include "shapes.hpp"

using namespace anipp;
using namespace std;
using namespace pugi;

/*
 * Helpers
 */


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

Rect::Rect(xml_document& doc) {
    xml_node svg  = doc.child("svg");
    xml_node rect = svg.child("rect");
    this->x = stod(rect.attribute("x").value());
    this->y = stod(rect.attribute("y").value());
    this->width = stod(rect.attribute("width").value());
    this->height = stod(rect.attribute("height").value());
    this->load_properties(rect, "rect");
}

xml_node Rect::export_SVG(xml_document& doc, bool standalone) {
    auto rect = doc.append_child("rect");
    auto x    = rect.append_attribute("x");
    auto y    = rect.append_attribute("y");
    auto width  = rect.append_attribute("width");
    auto height = rect.append_attribute("height");
    x.set_value(this->x);
    y.set_value(this->y);
    width.set_value(this->width);
    height.set_value(this->height);
    this->export_properties(rect);
    return rect;
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

Circle::Circle(xml_document& doc) {
    xml_node svg  = doc.child("svg");
    xml_node circle_node = svg.child("circle");
    this->cx = stod(circle_node.attribute("cx").value());
    this->cy = stod(circle_node.attribute("cy").value());
    this->r  = stod(circle_node.attribute("r").value());
    this->load_properties(circle_node, "circle");
}

xml_node Circle::export_SVG(xml_document& doc, bool standalone) {
    auto circle = doc.append_child("circle");
    auto cx     = circle.append_attribute("cx");
    auto cy     = circle.append_attribute("cy");
    auto r      = circle.append_attribute("r");
    cx.set_value(this->cx);
    cy.set_value(this->cy);
    r.set_value(this->r);
    this->export_properties(circle);
    return circle;
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

Ellipse::Ellipse(xml_document& doc) {
    xml_node svg  = doc.child("svg");
    xml_node ellipse_node = svg.child("ellipse");
    this->cx = stod(ellipse_node.attribute("cx").value());
    this->cy = stod(ellipse_node.attribute("cy").value());
    this->rx = stod(ellipse_node.attribute("rx").value());
    this->ry = stod(ellipse_node.attribute("ry").value());
    this->load_properties(ellipse_node, "ellipse");
}

xml_node Ellipse::export_SVG(xml_document& doc, bool standalone) {
    auto ellipse = doc.append_child("ellipse");
    auto cx      = ellipse.append_attribute("cx");
    auto cy      = ellipse.append_attribute("cy");
    auto rx      = ellipse.append_attribute("rx");
    auto ry      = ellipse.append_attribute("ry");
    cx.set_value(this->cx);
    cy.set_value(this->cy);
    rx.set_value(this->rx);
    ry.set_value(this->ry);
    this->export_properties(ellipse);
    return ellipse;
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

Line::Line(xml_document& doc) {
    xml_node svg  = doc.child("svg");
    xml_node line_node = svg.child("line");
    this->x1 = stod(line_node.attribute("x1").value());
    this->y1 = stod(line_node.attribute("y1").value());
    this->x2 = stod(line_node.attribute("x2").value());
    this->y2 = stod(line_node.attribute("y2").value());
    this->load_properties(line_node, "line");
}

xml_node Line::export_SVG(xml_document& doc, bool standalone) {
    auto line = doc.append_child("line");
    auto x1   = line.append_attribute("x1");
    auto y1   = line.append_attribute("y1");
    auto x2   = line.append_attribute("x2");
    auto y2   = line.append_attribute("y2");
    x1.set_value(this->x1);
    y1.set_value(this->y1);
    x2.set_value(this->x2);
    y2.set_value(this->y2);
    this->export_properties(line);
    return line;
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

Polyline::Polyline(xml_document& doc) {
    xml_node svg  = doc.child("svg");
    xml_node polyline_node = svg.child("polyline");
    this->points = load_points(polyline_node.attribute("points").value());
    this->load_properties(polyline_node, "polyline");
}

xml_node Polyline::export_SVG(xml_document& doc, bool standalone) {
    auto polyline = doc.append_child("polyline");
    auto points   = polyline.append_attribute("points");
    points.set_value(toString(this->points).c_str());
    this->export_properties(polyline);
    return polyline;
}

ostream& Polyline::print(ostream& out) const {
    out << "Polyline: points = ";
    for(auto it=this->points.begin(); it!=this->points.end(); ++it)
        out << (*it).toString() << " ";
    anipp::Shape::print_properties(out);
    return out;
}

/*
 * Polygon
 */
Polygon::Polygon(vector<Point> & points)
        : points(points)
{ }

Polygon::Polygon(xml_document& doc) {
    xml_node svg  = doc.child("svg");
    xml_node polygon_node= svg.child("polygon");
    this->points = load_points(polygon_node.attribute("points").value());
    this->load_properties(polygon_node, "polygon");
}

xml_node Polygon::export_SVG(xml_document& doc, bool standalone) {
    auto polygon = doc.append_child("polygon");
    auto points = polygon.append_attribute("points");
    points.set_value(toString(this->points).c_str());
    this->export_properties(polygon);
    return polygon;
}

ostream& Polygon::print(ostream& out) const {
    out << "Polygon: points = ";
    for(auto it=this->points.begin(); it!=this->points.end(); ++it)
        out << (*it).toString() << " ";
    anipp::Shape::print_properties(out);
    return out;
}

/*
 * Path
 */
Path::Path(string path_string) {
    this->cmds = parser::parse(path_string);
}

Path::Path(xml_document& doc) {
    xml_node svg  = doc.child("svg");
    xml_node path = svg.child("path");
    string d      = path.attribute("d").value();
    this->cmds = parser::parse(d);
    this->load_properties(path, "path");
}

xml_node Path::export_SVG(xml_document& doc, bool standalone) {
    auto path = doc.append_child("path");
    auto d = path.append_attribute("d");
    d.set_value(toString(this->cmds).c_str());
    this->export_properties(path);
    return path;
}


ostream& Path::print(ostream& out) const {
    for(auto c : this->cmds)
        std::cout << c << '\n';
    return out;
}

ostream& operator<< (ostream& out, const anipp::Shape& shp) {
    shp.print(out);
    return out;
}
