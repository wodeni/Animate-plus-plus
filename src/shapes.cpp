#include "shapes.hpp"

using namespace anipp;
using namespace std;
using namespace experimental;
using namespace pugi;

 /////////////
 // helpers //
 /////////////

// xml_attribute append_attribute(xml_node node, string name, string value) {
//     auto attr = node.append_attribute(name);
//     attr.set_value(value);
//     return attr;
// }

int Shape::id_counter = 0;

xml_node anipp::Shape::add_animations(xml_document& doc, xml_node parent) {
    if(!animate.active()) return parent;
    vector<xml_node> anis = this->animate.export_SVG(doc);
    for(auto child : anis)
        parent.append_move(child);
    return parent;
}

void anipp::Shape::save(string filename) {
    xml_document doc_out;
    auto svg  = SVG_header(doc_out);
    auto node = this->export_SVG(doc_out);
    svg.append_move(node);
    doc_out.save_file(filename.c_str());
}

void anipp::Shape::load_attributes(xml_node & node, string type) {
    auto it = default_attributes.find(type);
    assert(it != default_attributes.end());
    set<string> variables = it -> second;
    for (auto ait = node.attributes_begin(); ait != node.attributes_end(); ++ait) {
        if(variables.find(ait->name()) == variables.end()) {
            (this->attributes).insert(pair<string, string>(ait->name(), ait->value()));
        }
    }
}

void anipp::Shape::export_attributes(xml_node & node) {
    for(auto it=this->attributes.begin(); it!=this->attributes.end(); ++it) {
        auto key = it->first;
        auto value = it->second;
        auto attr = node.append_attribute(key.c_str());
        attr.set_value(value.c_str());
    }
    // BUG: maybe a better place?
    node.append_attribute("id").set_value(this->id.c_str());
}

void anipp::Shape::print_attributes(ostream& out) const {
    for(auto it=this->attributes.begin(); it!=this->attributes.end(); ++it) {
        auto key = it->first;
        auto value = it->second;
        out << key << " = " << value << ", ";
    }
    out << "\n";
}

void anipp::Shape::attr(string key, string val) {
    this->attributes[key] = val;
}
void anipp::Shape::attr(Attributes attrs) {
    for(auto a : attrs)
        this->attributes[a.first] = a.second;
}

ShapePtr anipp::get_shape(pugi::xml_node node) {
    std::string name = node.name();
    Shape* res;
    try {
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
    } catch(...) {
        cout << "get_shape: error when processing command: ";
        node.print(cout);
        cout << '\n';
    }
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
    : Shape("rect_" + std::to_string(next_id()))
    , x{x}
    , y{y}
    , width{w}
    , height{h}
    , rx{rx}
    , ry{ry}
{ }

Rect::Rect(const Rect& r)
    : Shape("rect_" + std::to_string(next_id()))
    , x{r.x}
    , y{r.y}
    , width{r.width}
    , height{r.height}
    , rx{r.rx}
    , ry{r.ry}
{
    cout << "rect copy constructor\n'";
}

Rect::Rect(xml_node& rect)
    : Shape("rect_" + std::to_string(next_id()))
{
    this->x      = stod(rect.attribute("x").value());
    this->y      = stod(rect.attribute("y").value());
    this->width  = stod(rect.attribute("width").value());
    this->height = stod(rect.attribute("height").value());
    string rx_str = rect.attribute("rx").value();
    string ry_str = rect.attribute("ry").value();
    this->load_corners(rx_str, ry_str); // rx and ry requires special treatments
    this->load_attributes(rect, "rect");
}

void Rect::load_corners(std::string rx_str, std::string ry_str) {
    // If neither ‘rx’ nor ‘ry’ are properly specified, then set both rx and ry to 0. (This will result in square corners.)
    double rx, ry;
    if(!rx_str.empty()) rx = stod(rx_str); else rx = 0;
    if(!ry_str.empty()) ry = stod(ry_str); else ry = 0;
    // Otherwise, if a properly specified value is provided for ‘rx’, but not for ‘ry’, then set both rx and ry to the value of ‘rx’.
    if(!rx_str.empty()) ry = rx;
    // Otherwise, if a properly specified value is provided for ‘ry’, but not for ‘rx’, then set both rx and ry to the value of ‘ry’.
    if(!rx_str.empty()) rx = ry;
    // If rx is greater than half of ‘width’, then set rx to half of ‘width’.
    if(rx > this->width)  rx = this->width / 2;
    // If ry is greater than half of ‘height’, then set ry to half of ‘height’.
    if(ry > this->height) ry = this->height / 2;
    // The effective values of ‘rx’ and ‘ry’ are rx and ry, respectively.
    this->rx = rx;
    this->ry = ry;
}

xml_node Rect::export_SVG(xml_document& doc, bool standalone) {
    auto rect   = doc.append_child("rect");
    auto x      = rect.append_attribute("x");
    auto y      = rect.append_attribute("y");
    auto rx     = rect.append_attribute("rx");
    auto ry     = rect.append_attribute("ry");
    auto width  = rect.append_attribute("width");
    auto height = rect.append_attribute("height");
    x.set_value(this->x); y.set_value(this->y);
    rx.set_value(this->rx); ry.set_value(this->ry);
    width.set_value(this->width);
    height.set_value(this->height);
    this->export_attributes(rect);
    return this->add_animations(doc, rect);
}

ostream& Rect::print(ostream& out) const {
    out << "Rect: " <<
        "x = " << this->x <<
        ", y = " << this->y <<
        ", width = " << this->width <<
        ", height = " << this->height <<
        ", ";
    anipp::Shape::print_attributes(out);
    return out;
}

/*
 * Circle
 */
Circle::Circle(double cx, double cy, double r)
    : Shape("circle_" + std::to_string(next_id()))
    , cx{cx}
    , cy{cy}
    , r{r}
{ }

Circle::Circle(xml_node& circle)
    : Shape("circle_" + std::to_string(next_id()))
{
    this->cx = stod(circle.attribute("cx").value());
    this->cy = stod(circle.attribute("cy").value());
    this->r  = stod(circle.attribute("r").value());
    this->load_attributes(circle, "circle");
}

xml_node Circle::export_SVG(xml_document& doc, bool standalone) {
    auto circle = doc.append_child("circle");
    auto cx     = circle.append_attribute("cx");
    auto cy     = circle.append_attribute("cy");
    auto r      = circle.append_attribute("r");
    cx.set_value(this->cx);
    cy.set_value(this->cy);
    r.set_value(this->r);
    this->export_attributes(circle);
    return this->add_animations(doc, circle);
}

ostream& Circle::print(ostream& out) const {
    out << "Circle: " <<
        "cx = " << this->cx <<
        ", cy = " << this->cy <<
        ", r = " << this->r <<
        ", ";
    anipp::Shape::print_attributes(out);
    return out;
}

/*
 * Ellipse
 */
Ellipse::Ellipse(double cx, double cy, double rx, double ry)
    : Shape("ellipse_" + std::to_string(next_id()))
    , cx{cx}
    , cy{cy}
    , rx{rx}
    , ry{ry}
{ }

Ellipse::Ellipse(xml_node& ellipse)
    : Shape("ellipse_" + std::to_string(next_id()))
{
    this->cx = stod(ellipse.attribute("cx").value());
    this->cy = stod(ellipse.attribute("cy").value());
    this->rx = stod(ellipse.attribute("rx").value());
    this->ry = stod(ellipse.attribute("ry").value());
    this->load_attributes(ellipse, "ellipse");
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
    this->export_attributes(ellipse);
    return this->add_animations(doc, ellipse);
}

ostream& Ellipse::print(ostream& out) const {
    out << "Ellipse: " <<
        "cx = " << this->cx <<
        ", cy = " << this->cy <<
        ", rx = " << this->rx <<
        ", ry = " << this->ry <<
        ", ";
    anipp::Shape::print_attributes(out);
    return out;
}

/*
 * Line
 */
Line::Line(double x1, double y1, double x2, double y2)
    : Shape("line_" + std::to_string(next_id()))
    , x1{x1}
    , y1{y1}
    , x2{x2}
    , y2{y2}
{ }

Line::Line(xml_node& line)
    : Shape("line_" + std::to_string(next_id()))
{
    this->x1 = stod(line.attribute("x1").value());
    this->y1 = stod(line.attribute("y1").value());
    this->x2 = stod(line.attribute("x2").value());
    this->y2 = stod(line.attribute("y2").value());
    this->load_attributes(line, "line");
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
    this->export_attributes(line);
    return this->add_animations(doc, line);
}

ostream& Line::print(ostream& out) const {
    out << "Line: " <<
        "x1 = " << this->x1 <<
        ", y1 = " << this->y1 <<
        ", x2 = " << this->x2 <<
        ", y2 = " << this->y2 <<
        ", ";
    anipp::Shape::print_attributes(out);
    return out;
}


/*
 * Polyline
 */
Polyline::Polyline(vector<Point> & points)
    : Shape("polyline_" + std::to_string(next_id()))
    , points(points)
{ }

Polyline::Polyline(xml_node& polyline)
    : Shape("polyline_" + std::to_string(next_id()))
{
    this->points = parser::parse_points(polyline.attribute("points").value());
    this->load_attributes(polyline, "polyline");
}

xml_node Polyline::export_SVG(xml_document& doc, bool standalone) {
    auto polyline = doc.append_child("polyline");
    auto points   = polyline.append_attribute("points");
    points.set_value(toString(this->points).c_str());
    this->export_attributes(polyline);
    return this->add_animations(doc, polyline);
}

ostream& Polyline::print(ostream& out) const {
    out << "Polyline: points = ";
    for(auto it=this->points.begin(); it!=this->points.end(); ++it)
        out << (*it).toString() << " ";
    anipp::Shape::print_attributes(out);
    return out;
}

/*
 * Polygon
 */
Polygon::Polygon(vector<Point> & points)
    : Shape("polygon_" + std::to_string(next_id()))
    , points(points)
{ }

Polygon::Polygon(xml_node& polygon)
    : Shape("polygon_" + std::to_string(next_id()))
{
    this->points = parser::parse_points(polygon.attribute("points").value());
    this->load_attributes(polygon, "polygon");
}

xml_node Polygon::export_SVG(xml_document& doc, bool standalone) {
    auto polygon = doc.append_child("polygon");
    auto points = polygon.append_attribute("points");
    points.set_value(toString(this->points).c_str());
    this->export_attributes(polygon);
    return this->add_animations(doc, polygon);
}

ostream& Polygon::print(ostream& out) const {
    out << "Polygon: points = ";
    for(auto it=this->points.begin(); it!=this->points.end(); ++it)
        out << (*it).toString() << " ";
    anipp::Shape::print_attributes(out);
    return out;
}

/*
 * Path
 */

Path::Path()
    : Shape("path_" + std::to_string(next_id()))
{ }

Path::Path(string path_string)
    : Shape("path_" + std::to_string(next_id()))
{
    this->cmds = parser::parse(path_string);
}

Path::Path(xml_node& path)
    : Shape("path_" + std::to_string(next_id()))
{
    string d      = path.attribute("d").value();
    this->cmds = parser::parse(d);
    this->load_attributes(path, "path");
}

xml_node Path::export_SVG(xml_document& doc, bool standalone) {
    auto path = doc.append_child("path");
    auto d = path.append_attribute("d");
    d.set_value(toString(this->cmds).c_str());
    this->export_attributes(path);
    return this->add_animations(doc, path);
}

Path& Path::closePath() {
    Command c = { CLOSEPATH, get_type_char(CLOSEPATH), ABSOLUTE, {} };
    this->cmds.push_back(c);
    return *this;
}
Path& Path::moveTo(double x, double y, bool relative) {
    Command c = {
        MOVETO, get_type_char(MOVETO, relative),
        relative ? RELATIVE : ABSOLUTE, {x, y}
    };
    this->cmds.push_back(c);
    return *this;
}
Path& Path::lineTo(double x, double y, bool relative) {
    Command c = {
        LINETO, get_type_char(LINETO, relative),
        relative ? RELATIVE : ABSOLUTE, {x, y}
    };
    this->cmds.push_back(c);
    return *this;
}
Path& Path::quadraticCurveTo(double x, double y, bool relative) {
    Command c = {
        QUDRATIC, get_type_char(SMOOTH_QUDRATIC, relative),
        relative ? RELATIVE : ABSOLUTE, {x, y}
    };
    this->cmds.push_back(c);
    return *this;
}
Path& Path::quadraticCurveTo(double cpx, double cpy, double x, double y, bool relative) {
    Command c = {
        SMOOTH_QUDRATIC, get_type_char(SMOOTH_QUDRATIC, relative),
        relative ? RELATIVE : ABSOLUTE, {cpx, cpy, x, y}
    };
    this->cmds.push_back(c);
    return *this;
}
Path& Path::cubicCurveTo(double cp1x, double cp1y, double cp2x, double cp2y,  double x, double y, bool relative) {
    Command c = {
        CUBIC, get_type_char(CUBIC, relative),
        relative ? RELATIVE : ABSOLUTE, {cp1x, cp1y, cp2x, cp2y, x, y}
    };
    this->cmds.push_back(c);
    return *this;
}
Path& Path::cubicCurveTo(double cp2x, double cp2y,  double x, double y, bool relative) {
    Command c = {
        CUBIC, get_type_char(SMOOTH_CUBIC, relative),
        relative ? RELATIVE : ABSOLUTE, {cp2x, cp2y, x, y}
    };
    this->cmds.push_back(c);
    return *this;
}

Path& Path::arcTo(double rx, double ry, double x_axis_rotation, double large_arc_flag, double sweep_flag, double x, double y, bool relative) {
    Command c = {
        ELLIPTICAL, get_type_char(ELLIPTICAL, relative),
        relative ? RELATIVE : ABSOLUTE, {rx, ry, x_axis_rotation, large_arc_flag, sweep_flag, x, y}
    };
    this->cmds.push_back(c);
    return *this;
}

ostream& Path::print(ostream& out) const {
    for(auto c : this->cmds)
        std::cout << c << '\n';
    return out;
}

string Path::path_string() const {
    return toString(this->cmds);
}

/*
 * Shape Group
 */


Group::Group(ShapePtrList& shapes)
    : Shape("group_" + std::to_string(next_id()))
    , shapes(shapes)
{}

Group::Group(ShapeList& shapes)
    : Shape("group_" + std::to_string(next_id()))
{
    // BUG: no memory guarantees
    for(auto &s : shapes) {
        this->shapes.push_back(s.clone());
    }
}

Group::Group(xml_node& group)
    : Shape("group_" + std::to_string(next_id()))
{
    for(auto child : group.children()) {
        // cout << "Beginning with: ";
        // child.print(cout);
        // cout << '\n';
        auto shp = get_shape(child);
        this->shapes.push_back(shp);
        // cout << "Done with: ";
        // child.print(cout);
        // cout << '\n';
    }
    this->load_attributes(group, "group");
}

// template <class T, class... T2>
// Group::Group(T s, T2... rest) : Group(rest...) {
//     this->shapes.insert(this->shapes.begin(), s.clone());
// }


// void Group::add(Shape& s, ...) {
//
// }


xml_node Group::export_SVG(xml_document& doc, bool standalone) {
    auto group = doc.append_child("g");
    for(auto& shp : this->shapes) {
        // TODO: to be tested
        auto node = shp->export_SVG(doc);
        group.append_move(this->add_animations(doc, node));
    }
    this->export_attributes(group);
    return this->add_animations(doc, group);
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

ShapePtr anipp::load(string filename) {
    xml_document doc_in;
    xml_parse_result result = doc_in.load_file(filename.c_str());
    if (!result)
        die("Failed to load SVG file: " + filename);
    ShapePtrList shapes;
    for(auto child : doc_in.child("svg")) {
        auto shp = get_shape(child);
        shapes.push_back(shp);
        // cout << *shp << "\n";
    }
    Shape* g = new Group(shapes);
    return ShapePtr{g};
}

//////////////
// Animator //
//////////////

// NOTE: ad-hoc solution is detect whether the animation should use
// animateTransform
bool isTransfrom(AnimationType t) {
    return t == ROTATE    ||
           t == TRANSLATE ||
           t == SCALE     ||
           t == SKEWX     ||
           t == SKEWY;
           // t == TRANSFORM; //TODO
}

Animation& Animator::translate(Point p1, Point p2, bool relative) {
     Animation ani;
     ani.type(TRANSLATE)
        .name("translate")
        .from(p1.toString());
    if(relative)
        ani.by(p2.toString());
    else
        ani.to(p2.toString());
    animations.push_back(ani);
    return animations.back();
}

Animation& Animator::rotate(Point c1, double d1, Point c2, double d2) {
    Animation ani;
    ani.type(ROTATE)
       .name("rotate")
       .from(dtos(d1) + " " + c1.toString())
       .to  (dtos(d2) + " " + c2.toString());
   animations.push_back(ani);
   return animations.back();
}

Animation& Animator::scale(Point from_scale, Point to_scale) {
    Animation ani;
    ani.type(SCALE)
       .name("scale")
       .from(from_scale.toString())
       .to(to_scale.toString());
    animations.push_back(ani);
    return animations.back();
}

Animation& Animator::move_along(Path& path) {
    Animation ani;
    Attributes a;
    a["xlink:href"] = "#" + path.id;
    ani.type(MOVE)
       .add_element("mpath", a);
    animations.push_back(ani);
    return animations.back();
}

// void Animator::loop(bool isLooping) { this->_loop = isLooping; }

string Animator::toString() {
    string res;
    for(auto a : this->animations)
        res += a.toString() + '\n';
    return res;
}

vector<xml_node> Animator::export_SVG(xml_document& doc) {
    vector<xml_node> res;
    for(auto& a : this->animations) {
        auto node = a.export_SVG(doc);
        res.push_back(node);
    }
    return res;
}

bool Animator::active() { return this->animations.size() != 0; }

///////////////
// Animation //
///////////////

string Animation::toString() {
    // TODO
    // string res = "Attribute to animate: " + this->attributeName;
                 // "\nfrom: " + this->attributes["from"] +
                 // "\nto: "   + this->_to;
    // res += "\nduration: " + (this->dur ? dtos(*this->dur) : "indefinite");
    // return res;
}

Animation& Animation::type(AnimationType t) {
    this->_type = t;
    return *this;
}
Animation& Animation::name(string n) {
    this->_name = n;
    return *this;
}
Animation& Animation::attribute(string attr) {
    this->attributes["attributeName"] = attr;
    return *this;
}

Animation& Animation::from(string t) {
    this->attributes["from"] = t;
    return *this;
}
Animation& Animation::to(string t) {
    this->attributes["to"] = t;
    return *this;
}
Animation& Animation::by(string t) {
    this->attributes["by"] = t;
    return *this;
}
Animation& Animation::duration(string t) {
    this->attributes["dur"] = t;
    return *this;
}
Animation& Animation::repeat(double t) {
    this->attributes["repeatCount"] = dtos(t);
    return *this;
}
Animation& Animation::loop(bool isLooping) {
    this->attributes["repeatCount"] = "indefinite";
    return *this;
}
Animation& Animation::custom_attribute(string key, string val) {
    this->attributes[key] = val;
    return *this;
}
Animation& Animation::add_element(string name, Attributes a) {
    this->elements[name] = a;
    return *this;
}

pugi::xml_node Animation::export_SVG(pugi::xml_document& doc) {

    // figure out which type of animate tag to use and initialize the node
    string node_name;
    xml_node ani_node;
    if(isTransfrom(this->_type)) {
        node_name = "animateTransform";
        ani_node = doc.append_child(node_name.c_str());
        ani_node.append_attribute("attributeName").set_value("transform");
        ani_node.append_attribute("type").set_value(this->_name.c_str());
    }
    else if(this->_type == MOVE) {
        node_name = "animateMotion";
        ani_node = doc.append_child(node_name.c_str());
    }

    // custom attributes
    for(auto it=this->attributes.begin(); it!=this->attributes.end(); ++it) {
        auto key = it->first;
        auto value = it->second;
        auto attr = ani_node.append_attribute(key.c_str());
        attr.set_value(value.c_str());
    }

    // if there is any child node of an animation, add them.
    if(!elements.empty()) {
        for(auto element : this->elements) {
            auto child = ani_node.append_child(element.first.c_str());
            for(auto a : element.second)
                child.append_attribute(a.first.c_str())
                     .set_value(a.second.c_str());
        }
    }

    return ani_node;
}
