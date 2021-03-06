#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <iostream>
#include <algorithm>    // std::all_of
#include <cctype>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp> // to_upper
#include <regex>
#include "utils.hpp"

namespace anipp {

    namespace parser {

        // matches the spliting points between points
        static boost::regex const split_matcher(
            "\\s*,\\s*|"
            "\\s+|"
            "(?<=[0-9])(?=[-+])|"
            "(?<=[Ee\\.][0-9])(?=[\\.])" // BUG: should be [0-9]+ boost does NOT
            // support variable length patterns
        );

        // splits commands by looking for the command chars
        static boost::regex const cmd_matcher(
            "[mMzZlLhHvVcCsSqQtTaA]"    // command string
            "(?:\\s|[^mMzZlLhHvVcCsSqQtTaA])*"  // followed by a stream of characters
        );

        // Top-level function that parses a SVG command string into a list of Command
        // structures
        Commands parse(std::string);

        // This function can be used in constructing polyline and polygon
        // Taking the string as input and return a vector of points.
        // ex:
        // load_points("100 50 40 30") -> {Point(100, 50), Point(40, 30)}
        std::vector<Point> parse_points(std::string);
        void test_parser(std::string);

    }
    //
    //
    // /*
    // * Abstract representation of <d> in <path>, which is a path descriptor
    // * Five line command:
    // *   - moveto (M, m)
    // *   - lineto (L, l, H, h, V, v)
    // *   - curveto (C, Q, T, S)
    // *   - arcto (TODO)
    // *   - closepath (Z)
    // */
    //
    // class PathDescription {
    // private:
    //     parser::Commands commands;
    // public:
    //     PathDescription(std::string path_string);
    //     ~PathDescription();
    //     void as_string(); // TODO: operator>>?
    //     // PathDescription& operator>> ();
    //     // TODO: add handles for modifying a path description
    //     void move_to(double, double);
    // };
    //
}

#endif
