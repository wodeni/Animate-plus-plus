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
