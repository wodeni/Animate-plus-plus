#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

#include "animate.hpp"
using namespace std;
using namespace pugi;

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
    class PathDescription;
    ///////////////////////////////////////////////////////////////////////////

    typedef map<string, string> Properties;
    struct Point {
        double x;
        double y;
    };
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
        virtual ostream& print(ostream& out) const = 0;
        virtual pugi::xml_document export_SVG() const = 0;
    };

    /*
     * a group of multiple primitives
     */
    class Group : public Shape {
    private:
        vector<Shape> shapes;
    public:
        Group();
        Group(vector<Shape>&);
        ~Group();
        ostream& print(ostream& out) const;
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
        xml_document export_SVG() const;
        ostream& print(ostream& out) const;
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
        xml_document export_SVG() const;
        ostream& print(ostream& out) const;
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
        xml_document export_SVG() const;
        ostream& print(ostream& out) const;
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
        ostream& print(ostream& out) const;
    };

    /*
     * Polyline class
     */
    class Polyline : public Shape {
    private:
        vector<Point> points; // A list of points
    public:
        Polyline(vector<Point> &);
        ~Polyline();
        ostream& print(ostream& out) const;
    };

    /*
     * Polygon class
     */
    class Polygon : public Shape {
    private:
        vector<Point> points; // A list of points
    public:
        Polygon(vector<Point> &);
        ~Polygon();
        ostream& print(ostream& out) const;
    };

    /*
     * Abstract representation of <d> in <path>, which is a path descriptor
     * Five line command:
     *   - moveto (M, m)
     *   - lineto (L, l, H, h, V, v)
     *   - curveto (C, Q, T, S)
     *   - arcto (TODO)
     *   - closepath (Z)
     */

    class PathDescription {
        // TODO
    private:
        // key: command symbol
        // value: list of numbers with variable length
        map<string, vector<double>> commands;
    public:
        PathDescription(string path_string);
        ~PathDescription();
        void to_path_string(); // TODO: operator>>?
        // TODO: add handles for modifying a path description
        void move_to(double, double);
    };


    /*
     * Path class
     */
    class Path : public Shape {
    private:
        PathDescription d;
    public:
        Path(vector<Point> &);
        ostream& print(ostream& out) const;
    };
}

// A wrapper function that allows `cout << shape` kind of syntax
// TODO: why do I have to predefine this function here for it to work???
ostream& operator<< (ostream& out, const anipp::Shape& shp);

#endif
