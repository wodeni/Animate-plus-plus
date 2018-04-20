#include "parser.hpp"

using namespace boost;

namespace anipp {

    namespace parser {

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
                char type_char = cmd[0];
                char type_char_upper = std::toupper(type_char);

                cmd = cmd.substr(1);
                while ( regex_search( cmd, matched, split_matcher ) ) {
                    points.push_back(std::stod(matched.prefix()));
                    cmd = matched.suffix();
                }

                // BUG: if there is a trailing coordinate, we should push it to the list
                if(cmd.size() != 0) points.push_back(std::stod(cmd));

                Command c = {
                    type_map.left.at(type_char_upper),            // type
                    type_char,                                    // type_char
                    std::isupper(type_char)? ABSOLUTE : RELATIVE, // relativity
                    points,                                       // points
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
                        cmd.type_char,
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
            throw "There should even number of points for " +
                std::string(1, cmd.type_char) + " command";
            if(pts.size() > 2) {
                for(int i = 0; i < pts.size(); i+=2) {
                    Command c = {
                        LINETO,
                        i == 0 ? cmd.type_char : 'L',
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
                    // std::cout << "Command not supported: " << cmd.type_char << '\n';
                }
            }

            //  If a relative moveto (m) appears as the first element of the path, then it is treated as a pair of absolute coordinates. In this case, subsequent pairs of coordinates are treated as relative even though the initial moveto is interpreted as an absolute moveto.
            if(valid_cmds[0].type == MOVETO &&
                valid_cmds[0].relativity == RELATIVE)
                valid_cmds[0].relativity = ABSOLUTE;

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

        void test_parser(std::string test) {
            Commands cmds = parse(test);
            for(auto c : cmds)
                std::cout << c << '\n';
        }

    }

    // /*
    // * Path description
    // * See standard https://www.w3.org/TR/SVG/paths.html
    // */
    // PathDescription::PathDescription(std::string s)
    // : commands(parser::parse(s))
    // { }
    //
    // ostream& operator<< (ostream& out, const anipp::Shape& shp) {
    //     shp.print(out);
    //     return out;
    // }

}
