#include "shapes.hpp"

using namespace anipp;

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

xml_document Rect::export_SVG() const {
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
    return doc;
}

ostream& Rect::print(ostream& out) const {
    out << "Rect: " <<
        "x = " << this->x <<
        ", y = " << this->y <<
        ", width = " << this->width <<
        ", height = " << this->height << '\n';
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

xml_document Circle::export_SVG() const {
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
    return doc;
}

ostream& Circle::print(ostream& out) const {
    out << "Circle: " <<
        "cx = " << this->cx <<
        ", cy = " << this->cy <<
        ", r = " << this->r << '\n';
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

xml_document Ellipse::export_SVG() const {
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
    return doc;
}

ostream& Ellipse::print(ostream& out) const {
    out << "Ellipse: " <<
        "cx = " << this->cx <<
        ", cy = " << this->cy <<
        ", rx = " << this->rx <<
        ", ry = " << this->ry << '\n';
    return out;
}

ostream& operator<< (ostream& out, const anipp::Shape& shp) {
    shp.print(out);
    return out;
}
