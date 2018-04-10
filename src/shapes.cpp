#include "shapes.hpp"

using namespace anipp;

Rect::Rect(double x, double y, double w, double h, double rx, double ry)
    : x{x}
    , y{y}
    , width{w}
    , height{h}
    , rx{rx}
    , ry{ry}
{ }

pugi::xml_document Rect::export_SVG() const {
    pugi::xml_document doc;
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

ostream& operator<< (ostream& out, const anipp::Shape& shp) {
    shp.print(out);
    return out;
}
