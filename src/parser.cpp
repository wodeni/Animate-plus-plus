#include "parser.hpp"

using namespace boost;


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

typedef boost::bimap< std::string, CommandType > TypeMap;

TypeMap type_map;

struct Command {
    CommandType         type;
    std::string         type_string;
    Relativity          relativity;
    std::vector<double> points;
};

typedef std::vector<Command> Commands;

template<typename Container>
void print(const Container& cont) {
   for (auto const& x : cont) {
      std::cout << "\"" << x  << "\"" << " ";
   }
   std::cout << '\n';
}

static regex const split_matcher(
    "\\s*,\\s*|"
    "\\s+|"
    "(?<=[0-9])(?=[-+])|"
    "(?<=[Ee\\.][0-9])(?=[\\.])" // BUG: should be [0-9]+ boost does NOT
                                 // support variable length patterns
);

static regex const cmd_matcher(
    "[mMzZlLhHvVcCsSqQtTaA]"    // command string
    "(?:\\s|[^mMzZlLhHvVcCsSqQtTaA])*"  // followed by a stream of characters
);

std::vector<std::string> parse_commands(std::string path_string) {
    smatch matched;
    std::vector<std::string> cmds;
    // split the string by command first
    while ( regex_search( path_string, matched, cmd_matcher ) ) {
        for(auto pat : matched) cmds.push_back(pat);
        path_string = matched.suffix();
    }
    return std::move(cmds);
}

// split a list of commands as a list of objects
Commands split_commands(std::vector<std::string>& cmds) {
    Commands cmd_list;
    for(auto cmd : cmds) {
        smatch matched;
        std::vector<double> points;

        // strip off the command char
        std::string type_str = std::string(1, cmd[0]);
        std::string type_str_upper = type_str;
        boost::to_upper(type_str_upper);

        cmd = cmd.substr(1);
        while ( regex_search( cmd, matched, split_matcher ) ) {
            points.push_back(std::stod(matched.prefix()));
            cmd = matched.suffix();
        }

        // BUG: if there is a trailing coordinate, we should push it to the list
        if(cmd.size() != 0) points.push_back(std::stod(cmd));

        bool uppercase = std::all_of(
            type_str.begin(), type_str.end(),
            [](char c) { return std::isupper(c); }
        );

        Command c = {
            type_map.left.at(type_str_upper),         // type
            type_str,                                 // type_string
            uppercase ? ABSOLUTE : RELATIVE,          // relativity
            points,                                   // points
        };
        cmd_list.push_back(c);
    }
    return std::move(cmd_list);
}

/*
 * Check a horizontal line-to or vertical line-to. If there is more than one
 * point. generate more commands.
 */
Commands split_singles(Command cmd) {
    std::vector<Command> res;
    CommandType type         = cmd.type;
    std::vector<double> pts  = cmd.points;
    if(pts.size() > 1) {
        for(int i = 0; i < pts.size(); ++i) {
            Command c = {
                type,
                cmd.type_string,
                cmd.relativity,
                {pts[i]}
            };
            res.push_back(c);
        }
    } else {
        res.push_back(cmd);
    }
    return std::move(res);
}

/*
 * Check a moveto or lineto command
 * MOVETO: If a moveto is followed by multiple pairs of coordinates, the subsequent pairs are treated as implicit lineto commands. Hence, implicit lineto commands will be relative if the moveto is relative, and absolute if the moveto is absolute.
 * LINETO: A number of coordinates pairs may be specified to draw a polyline. At the end of the command, the new current point is set to the final set of coordinates provided.
 */
Commands split_pairs(Command cmd) {
    std::vector<Command> res;
    CommandType type         = cmd.type;
    std::vector<double> pts  = cmd.points;
    if(pts.size() % 2 != 0)
        throw "There should even number of points for " + cmd.type_string + " command";
    if(pts.size() > 2) {
        for(int i = 0; i < pts.size(); i+=2) {
            Command c = {
                LINETO,
                i == 0 ? cmd.type_string : "L",
                cmd.relativity,
                {pts[i], pts[i+1]}
            };
            res.push_back(c);
        }
    } else {
        res.push_back(cmd);
    }
    return std::move(res);
}


Commands validate_commands(Commands cmds) {

    Commands valid_cmds;
    //  If a relative moveto (m) appears as the first element of the path, then it is treated as a pair of absolute coordinates. In this case, subsequent pairs of coordinates are treated as relative even though the initial moveto is interpreted as an absolute moveto.
    if(cmds[0].type == MOVETO)
        cmds[0].relativity = ABSOLUTE;

    for(auto cmd : cmds) {
        CommandType type         = cmd.type;
        std::vector<double> pts  = cmd.points;
        // if it's a moveto, the subsequent pairs are
        if(type == MOVETO || type == LINETO) {
            auto res = split_pairs(cmd);
            valid_cmds.insert(valid_cmds.end(), res.begin(), res.end());
        }
        else if (type == HORIZONTAL || type == VERTICAL) {
            auto res = split_singles(cmd);
            valid_cmds.insert(valid_cmds.end(), res.begin(), res.end());
        }
        else {
            valid_cmds.push_back(cmd); // ignored
            // std::cout << "Command " + cmd.type_string + " not supported!" << '\n';
        }
    }
    return valid_cmds;
}

Commands parse(std::string path_string) {
    // get (possibly invalid) commands
    std::vector<std::string> cmd_strs = parse_commands(path_string);
    // split commands into (letter, list of numbers)
    Commands cmds = split_commands(cmd_strs);
    // validate the commands and transform them if necessary
    Commands valid_cmds = validate_commands(cmds);
    return std::move(valid_cmds);
}

int main() {
    std::vector<TypeMap::value_type > v = {
        {"M", MOVETO},
        {"Z", CLOSEPATH},
        {"L", LINETO},
        {"H", HORIZONTAL},
        {"V", VERTICAL},
        {"Q", QUDRATIC},
        {"T", SMOOTH_QUDRATIC},
        {"C", CUBIC},
        {"S", SMOOTH_CUBIC},
        {"A", ELLIPTICAL}
    };

    type_map = TypeMap(v.begin(),v.end());

    std::vector<std::string> test_list = {
        "M3,7 5-6 L1,7 1e2-.4 m-10,10 l10,0       "
        "V27 89 H23           v10 h10             "
        "C33,43 38,47 43,47   c0,5 5,10 10,10     "
        "S63,67 63,67         s-10,10 10,10       "
        "Q50,50 73,57         q20,-5 0,-10        "
        "T70,40               t0,-15              "
        "A5,5 45 1,0 40,20    a5,5 20 0,1 -10-10  Z"
    };

    for(auto test : test_list) {
        Commands cmds = parse(test);
        for(auto c : cmds) {
            std::cout << c.type_string << ": ";
            print(c.points);
        }
    }

}
