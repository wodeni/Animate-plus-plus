#ifndef __SHAPES_HPP__
#define __SHAPES_HPP__

#include <iostream>
#include <memory>
#include <sstream>
#include <cassert>
#include <map>
#include <set>
#include <string>
#include <experimental/optional>
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

    typedef std::map<std::string, std::string> Attributes;
    typedef std::map<std::string, std::set<std::string>> DefaultAttributes;
    typedef std::shared_ptr<Shape> ShapePtr;
    typedef std::vector<ShapePtr> ShapeList;

    /*
     * A table contains key value pair of shape and necessary attributes
     * We ignore those attributes when we are parsing external attributes.
     */
    const DefaultAttributes default_attributes ({
        {"circle", {"cx", "cy", "r"}},
        {"rect", {"x", "y", "height", "width", "rx", "ry"}},
        {"ellipse", {"rx", "ry", "cx", "cy"}},
        {"line", {"x1", "y1", "x2", "y2"}},
        {"polyline", {"points"}},
        {"polygon", {"points"}},
        {"path", {"d"}},
        {"group", { }}
    });

    enum AnimationType {
        ROTATE,
        TRANSLATE,
        SCALE,
        SKEWX,
        SKEWY,
        TRANSFORM,
        COMPOUND,
        CSS
    };

    class Animation {
    private:
        AnimationType _type;
        Attributes attributes;
    public:
        std::string _name;                 // the name of the animation
        Animation& type(AnimationType);
        Animation& name(std::string);
        Animation& attribute(std::string);
        Animation& from(std::string);
        Animation& to(std::string);
        Animation& by(std::string);
        Animation& repeat(double);
        Animation& loop(bool);
        Animation& duration(std::string); // TODO: std::chrono::duration?
        Animation& add(std::string);
        std::string toString();
        pugi::xml_node export_SVG(pugi::xml_document&);
    };

    /**
     * An interface to plug in animation to a Shape element
     */
    class Animator {
    private:
        // bool _loop;
        std::vector<Animation> animations;
    public:
        Animation& translate(Point, Point, bool relative=false);
        Animation& rotate(Point, double, Point, double);
        Animation& scale(Point, Point);
        Animation& move(Path &);
        bool active();

        std::vector<pugi::xml_node> export_SVG(pugi::xml_document&);
        std::string toString();
    };

    // Animation& translate(Animator& anim, Point from, Point to);
    // Animation& rotate(Animator& anim, Point from, Point to);

    /*
     * Top level abstract class for all shapes
     */
    class Shape {
    private:
        Attributes attributes; // CSS styling attributes of the object
    public:
        Animator animate;      // The animator of a graphical primitive

        virtual std::ostream& print(std::ostream& out) const = 0;
        virtual pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false) = 0;
        Attributes get_attributes() const { return this->attributes; }
        // virtual ShapePtr clone() const = 0;
        virtual Shape* clone() const;

        // print all attributes
        void print_attributes(std::ostream& out) const;

        /**
         * load attributes from string into map
         * @param node TODO
         * @param type TODO
         */
        void load_attributes(pugi::xml_node & node, std::string type) ;
        /**
         * export attributes to the given node
         * @param node TODO
         */
        void export_attributes(pugi::xml_node & node) ;

        // TODO: documentation
        pugi::xml_node add_animations(pugi::xml_document&, pugi::xml_node);

        /**
         * add an arbitrary attribute to the shape element
         * @param std::string key
         * @param std::string value
         */
        void attr(std::string, std::string);
        /**
         * add multiple attributes to the shape element
         * @param attributes a map of attributes
         */
        void attr(Attributes);
        /**
         * Save the Shape as a standalone SVG file
         * @param filename the name of the output file
         */
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
        Group(std::vector<Shape> shapes);
        Group(pugi::xml_node&); // import SVG
        Group* clone() const { return new Group(*this); };
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
        Path();
        Path(std::string);
        Path(pugi::xml_node&); // import SVG
        pugi::xml_node export_SVG(pugi::xml_document&, bool standalone=false);
        std::ostream& print(std::ostream& out) const;
        std::string path_string() const;
        // functions to construct a path
        Path& closePath();
        Path& moveTo(double x, double y, bool relative=false);
        Path& lineTo(double x, double y, bool relative=false);
        Path& quadraticCurveTo(double cpx, double cpy, double x, double y, bool relative=false);
        Path& bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y,  double x, double y, bool relative=false);
        Path& arcTo(double rx, double ry, double x_axis_rotation, double large_arc_flag, double sweep_flag, double x, double y, bool relative=false);
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
