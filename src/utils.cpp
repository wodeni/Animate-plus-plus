#include "utils.hpp"
using namespace std;
using namespace anipp;

// BUG: linker error if the function is uncommented
// template<typename Container>
// void print_container(const Container& cont) {
//    for (auto const& x : cont) {
//       std::cout << "\"" << x  << "\"" << " ";
//    }
//    std::cout << '\n';
// }

ostream& operator<< (ostream& out, const anipp::Command& cmd) {
    out << cmd.type_char << ": ";
    for (auto const& p : cmd.points)
        out <<  p  << " ";
        // out << "\"" << p  << "\"" << " ";
    return out;
}

string anipp::toString(Commands cmds) {
    string res;
    for(Command c : cmds) {
        res += c.type_char;
        res += " ";
        for(double p : c.points) {
            res += to_string(p);
            res += " ";
        }
    }
    return res;
}
