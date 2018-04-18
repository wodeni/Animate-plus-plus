#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

#include <iostream>
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
    class Point;
    class Circle;
    class Rect;
    class Ellipse;
    class Line;
    class Polyline;
    class Polygon;
    class Path;
    // class PathDescription; // see parser.hpp
    // class Commands; // see parser.hpp
    ///////////////////////////////////////////////////////////////////////////

    typedef std::map<std::string, std::string> Properties;
    typedef std::map<std::string, std::set<std::string>> Table;

    const Table internal_properties (
            {
                    {"circle", {"cx", "cy", "r"}},
                    {"rect", {"x", "y", "height", "width", "rx", "ry"}},
                    {"ellipse", {"rx", "ry", "cx", "cy"}},
                    {"line", {"x1", "y1", "x2", "y2"}},
                    {"polyline", {"points"}},
                    {"polygon", {"points"}},
                    {"path", {"d"}}
            }
            );
    // A table contains key value pair of
    // shape and necessary properties
    // We ignore those properties when we
    // are parsing external properties.
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
        virtual pugi::xml_document export_SVG() = 0;
        virtual Properties get_properties() const {return this->properties;}
        void print_properties(std::ostream& out) const;
        void load_properties(pugi::xml_node & node, std::string type) ;
        void export_properties(pugi::xml_node & node) ;
    };

    /*
     * a group of multiple primitives
     */
    class Group : public Shape {
    private:
        std::vector<Shape> shapes;
    public:
        Group();
        Group(std::vector<Shape>&);
        ~Group();
        std::ostream& print(std::ostream& out) const;
    };

    /*
     * Point class
     */
    class Point : public Shape {
    private:
        double x;
        double y;
    public:
        Point(double, double);
        std::string display() const; // print (x y)
        pugi::xml_document export_SVG() ;
        std::ostream& print(std::ostream& out) const;
    };

    std::vector<Point> load_points(std::string str);
    std::string toString(std::vector<Point> vec);

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
        pugi::xml_document export_SVG() ;
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
        ~Rect() {}
        pugi::xml_document export_SVG() ;
        std::ostream& print(std::ostream& out) const;
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
        pugi::xml_document export_SVG() ;
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
        pugi::xml_document export_SVG() ;
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
        pugi::xml_document export_SVG() ;
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
        pugi::xml_document export_SVG() ;
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
        pugi::xml_document export_SVG();
        std::ostream& print(std::ostream& out) const;
    };
}

// A wrapper function that allows `cout << shape` kind of syntax
// TODO: why do I have to predefine this function here for it to work???
std::ostream& operator<< (std::ostream& out, const anipp::Shape& shp);

#endif
