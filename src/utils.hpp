#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <cassert>
#include <vector>
#include <sstream>
#include <iostream>
#include "pugixml.hpp"


namespace anipp {
    // Types and constants


    enum Relativity { ABSOLUTE, RELATIVE };
    enum CommandType {
        MOVETO,           // M or m
        CLOSEPATH,        // Z or z (same)
        LINETO,           // L or l
        HORIZONTAL,       // H or h
        VERTICAL,         // V or v
        QUDRATIC,         // Q or q
        SMOOTH_QUDRATIC,  // T or t
        CUBIC,            // C or c
        SMOOTH_CUBIC,     // S or s
        ELLIPTICAL,       // A or a
    };

    // structure that represents a command in an SVG path
    struct Command {
        CommandType         type;
        char                type_char;
        Relativity          relativity;
        std::vector<double> points;
    };

    // container for a list of commands
    typedef std::vector<Command> Commands;

    std::string toString(Commands);

    /*
     * Point class
     */
    class Point {
    private:
        double x;
        double y;
    public:
        Point(double, double);
        std::string toString() const; // print (x y)
        std::ostream& print(std::ostream& out) const;
    };

    std::vector<Point> load_points(std::string str);
    // same as std::to_string, but removes the trailing zeros
    std::string toString(std::vector<Point> vec);

    // BUG: linker error if the function is uncommented
    // template<typename Container>
    // void print_container(const Container&);

    /*
     * SVG helpers
     */
    // pugi::xml_node SVG_header();
    pugi::xml_node SVG_header(pugi::xml_document& );
    std::string dtos(double);
}

// print out function for a command in the format of "<cmd-char>: <list-of-pts>"
std::ostream& operator<< (std::ostream& out, const anipp::Command& cmd);

#endif
