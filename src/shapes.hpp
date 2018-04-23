#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

#include <iostream>
#include <memory>
#include <sstream>
#include <cassert>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "pugixml.hpp"
#include "parser.hpp"
#include "utils.hpp"

namespace anipp {
    ///////////////////////////////////////////////////////////////////////////
    class Scene;
    class Shape;
    class Group;
    class Circle;
    class Rect;
    class Ellipse;
    class Line;
    class Polyline;
    class Polygon;
    class Path;
    ///////////////////////////////////////////////////////////////////////////

    typedef std::map<std::string, std::string> Properties;
    typedef std::map<std::string, std::set<std::string>> DefaultProperties;
    typedef std::shared_ptr<Shape> ShapePtr;
    typedef std::vector<ShapePtr> ShapeList;

    /*
     * A table contains key value pair of shape and necessary properties
     * We ignore those properties when we are parsing external properties.
     */
    const DefaultProperties default_properties ({
        {"circle", {"cx", "cy", "r"}},
        {"rect", {"x", "y", "height", "width", "rx", "ry"}},
        {"ellipse", {"rx", "ry", "cx", "cy"}},
        {"line", {"x1", "y1", "x2", "y2"}},
        {"polyline", {"points"}},
        {"polygon", {"points"}},
        {"path", {"d"}},
        {"group", { }}
    });

    class Animator {
        // TODO: to be implemented
    };

    /*
     * Top level abstract class for all shapes
     */
    class Shape {
    private:
        Animator animate;      // The animator of a graphical primitive
        Properties properties; // CSS styling properties of the object
    public:
        virtual std::ostream& print(std::ostream& out) const = 0;
        virtual pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false) = 0;
        Properties get_properties() const { return this->properties; }
        void print_properties(std::ostream& out) const;
        void load_properties(pugi::xml_node & node, std::string type) ;
        void export_properties(pugi::xml_node & node) ;
        void save(std::string);
    };

    /*
     * a group of multiple primitives
     */
    class Group : public Shape {
    private:
        ShapeList shapes;
    public:
        Group();
        Group(ShapeList&);
        Group(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
    };

    /*
     * Circle class
     */
    class Circle : public Shape {
    private:
        double cx;
        double cy;
        double r; // the radius of the circle
    public:
        Circle(double, double, double);
        Circle(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
    };

    /*
     * Rectangle class
     */
    class Rect : public Shape {
    private:
        double x;
        double y;
        double width;  // The width of the rectangle
        double height; // The height of the rectangle
        double rx;     // The x radius of the corners of the rectangle
        double ry;     // The y radius of the corners of the rectangle
    public:
        Rect(double, double, double, double, double rx=0, double ry=0);
        Rect(pugi::xml_node&); // import SVG
        Rect(const Rect&); // copy constructor
        // ~Rect() {} // TODO: destructor needed?
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        virtual std::ostream& print(std::ostream& out) const;
        void load_corners(std::string, std::string);
    };

    /*
     * Ellipse class
     */
    class Ellipse : public Shape {
    private:
        double rx; // The x radius of the ellipse.
        double ry; // The y radius of the ellipse.
        double cx; // The x position of the center of the ellipse.
        double cy; // The y position of the center of the ellipse.
    public:
        Ellipse(double, double, double, double);
        Ellipse(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
    };

    /*
     * Line class
     */
    class Line : public Shape {
    private:
        double x1; // The x position of point 1.
        double y1; // The y position of point 1.
        double x2; // The x position of point 2.
        double y2; // The y position of point 2.
    public:
        Line(double, double, double, double);
        Line(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
    };

    /*
     * Polyline class
     */
    class Polyline : public Shape {
    private:
        std::vector<Point> points; // A list of points
    public:
        Polyline(std::vector<Point> &);
        Polyline(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
    };

    /*
     * Polygon class
     */
    class Polygon : public Shape {
    private:
        std::vector<Point> points; // A list of points
    public:
        Polygon(std::vector<Point> &);
        Polygon(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
    };


    /*
     * Path class
     */
    class Path : public Shape {
    private:
        // PathDescription d;
        Commands cmds;
    public:
        Path(std::string);
        Path(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
    };

    ///////////////////////////////////////////////////////////////////////////
    // helper functions

    // Based on the name of a node, call appropriate constructor and return
    // corresponding shape object (e.g.: "circle" -> Circle object)
    ShapePtr get_shape(pugi::xml_node node);

    // Load from an SVG file
    ShapePtr load(std::string);
}

// A wrapper function that allows `cout << shape` kind of syntax
// TODO: why do I have to predefine this function here for it to work???
std::ostream& operator<< (std::ostream& out, const anipp::Shape& shp);

#endif
