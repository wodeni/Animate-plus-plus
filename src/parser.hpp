#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <iostream>
#include <algorithm>    // std::all_of
#include <cctype>
#include <boost/regex.hpp>
#include <boost/bimap.hpp>
#include <boost/algorithm/string.hpp> // to_upper
#include <regex>
#include "utils.hpp"

namespace anipp {

    namespace parser {

        // a map that maps a string representation of a command type to the enum
        // representation and vice versa. Uses boost's bidirectional map
        // TODO: change to normal std::map
        typedef boost::bimap< char, CommandType > TypeMap;

        static std::vector<TypeMap::value_type > type_map_vec = {
            {'M', MOVETO},
            {'Z', CLOSEPATH},
            {'L', LINETO},
            {'H', HORIZONTAL},
            {'V', VERTICAL},
            {'Q', QUDRATIC},
            {'T', SMOOTH_QUDRATIC},
            {'C', CUBIC},
            {'S', SMOOTH_CUBIC},
            {'A', ELLIPTICAL}
        };
        static TypeMap type_map =
            TypeMap(type_map_vec.begin(), type_map_vec.end());


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
