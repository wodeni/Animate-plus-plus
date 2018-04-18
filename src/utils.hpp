#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <vector>
#include <iostream>


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

    // BUG: linker error if the function is uncommented
    // template<typename Container>
    // void print_container(const Container&);
}

// print out function for a command in the format of "<cmd-char>: <list-of-pts>"
std::ostream& operator<< (std::ostream& out, const anipp::Command& cmd);

#endif
