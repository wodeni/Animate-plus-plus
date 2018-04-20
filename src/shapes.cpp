#include "shapes.hpp"

using namespace anipp;
using namespace std;
using namespace pugi;

/*
 * Helpers
 */


// load properties from string into map
void anipp::Shape::load_properties(xml_node & node, string type) {
    auto it = default_properties.find(type);
    assert(it != default_properties.end());
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

ShapePtr anipp::get_shape(pugi::xml_node node) {
    std::string name = node.name();
    Shape* res;
    if     (name == "circle") res = new Circle(node);
    else if(name == "ellipse") res = new Ellipse(node);
    else if(name == "g") res = new Group(node);
    else if(name == "circle") res = new Circle(node);
    else if(name == "rect") res = new Rect(node);
    else if(name == "ellipse") res = new Ellipse(node);
    else if(name == "line") res = new Line(node);
    else if(name == "polyline") res = new Polyline(node);
    else if(name == "polygon") res = new Polygon(node);
    else if(name == "path") res = new Path(node);
    else throw "getShape: SVG shape element tag not recognized";
    // https://stackoverflow.com/questions/34882140/why-cant-a-pointer-be-automatically-converted-into-a-unique-ptr-when-returning
    return ShapePtr{res};
}

// /*
//  * Shape base class
//  */
//
// Shape::Shape() {}
//
// Shape::~Shape() {}
//
// xml_node Shape::export_SVG(xml_document& doc, bool standalone) {
//     // throw "Shape::export_SVG: the base class version should never be used.";
//     return xml_node();
// }
//
// std::ostream& Shape::print(std::ostream& out) const {
//     // throw "Shape::print: the base class version should never be used.";
//     cout << "Shape::print: the base class version should never be used.\n";
//     return out;
// }



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

Rect::Rect(const Rect& r)
    : x{r.x}
    , y{r.y}
    , width{r.width}
    , height{r.height}
    , rx{r.rx}
    , ry{r.ry}
{
    cout << "rect copy constructor\n'";
}

Rect::Rect(xml_node& rect) {
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

Circle::Circle(xml_node& circle) {
    this->cx = stod(circle.attribute("cx").value());
    this->cy = stod(circle.attribute("cy").value());
    this->r  = stod(circle.attribute("r").value());
    this->load_properties(circle, "circle");
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

Ellipse::Ellipse(xml_node& ellipse) {
    this->cx = stod(ellipse.attribute("cx").value());
    this->cy = stod(ellipse.attribute("cy").value());
    this->rx = stod(ellipse.attribute("rx").value());
    this->ry = stod(ellipse.attribute("ry").value());
    this->load_properties(ellipse, "ellipse");
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

Line::Line(xml_node& line) {
    this->x1 = stod(line.attribute("x1").value());
    this->y1 = stod(line.attribute("y1").value());
    this->x2 = stod(line.attribute("x2").value());
    this->y2 = stod(line.attribute("y2").value());
    this->load_properties(line, "line");
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

Polyline::Polyline(xml_node& polyline) {
    this->points = load_points(polyline.attribute("points").value());
    this->load_properties(polyline, "polyline");
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

Polygon::Polygon(xml_node& polygon) {
    this->points = load_points(polygon.attribute("points").value());
    this->load_properties(polygon, "polygon");
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

Path::Path(xml_node& path) {
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

/*
 * Shape Group
 */

Group::Group(ShapeList& shapes)
    : shapes(shapes)
{}

Group::Group(xml_node& group) {
    for(auto child : group.children()) {
        auto shp = get_shape(child);
        this->shapes.push_back(shp);
    }
}

xml_node Group::export_SVG(xml_document& doc, bool standalone) {
    auto group = doc.append_child("g");
    for(auto& shp : this->shapes) {
        auto node = shp->export_SVG(doc);
        group.append_move(node);
    }
    return group;
}

ostream& Group::print(ostream& out) const {
    for(auto& s : shapes)
        out << *s << '\n';
    return out;
}

ostream& operator<< (ostream& out, const anipp::Shape& shp) {
    shp.print(out);
    return out;
}
