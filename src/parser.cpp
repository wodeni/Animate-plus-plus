#include <iostream>
#include <regex>

using namespace std;

int main() {
    static regex const cmd_matcher(
        "([mMzZlLhHvVcCsSqQtTaA])"    // command string
        "([^mMzZlLhHvVcCsSqQtTaA]+)"  // all other characters TODO: [^0-9]|[^Ee]
    );
    static regex const number_matcher(
        R"(([-+]?\d*\.?\d+([eE][-+]?\d+)?)|[-+]?\d+)"
    );

    static regex const test_matcher {
        "^(([-+]?\\d*\\.?\\d+([eE][-+]?\\d+)?)"
        "|"
        "[-+]?\\d+\\.([eE][-+]?\\d+)?)"
    };
    vector<string> test_list = {
        "4.",
        "4.443",
        "4.E-3",
        ".4E+3"
    };
    std::smatch matched;
    for(auto test : test_list) {
        while ( std::regex_search( test, matched, test_matcher ) ) {
            for(auto pat : matched) std:cout << pat << '\n';
            test = matched.suffix();
        }
    }

    // string line = "M12C12";
    // std::smatch matched;
    // // for all possible matches
    // while ( std::regex_search( line, matched, command_matcher ) ) {
    //     // extract
    //     string cmd = matched[0];
    //     string number_list = matched[1];
    //     // for(auto pat : matched) std:cout << pat << '\n';
    //
    //     // update the buffer to exclude the matched portion
    //     line = matched.suffix();
    // }
}
