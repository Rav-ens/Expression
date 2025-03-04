#include "Expression.cpp"
#include <iostream>
#include <map>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [--eval | --diff] ..." << endl;
        return 1;
    }

    string mode = argv[1];

    if (mode == "--eval") {
        if (argc < 3) {
            cerr << "Missing expression for --eval" << endl;
            return 1;
        }
        string expr_str = argv[2];
        auto expr = parse<double>(expr_str);

        map<string, double> vars;
        for (int i = 3; i < argc; ++i) {
            string arg = argv[i];
            size_t eq_pos = arg.find('=');
            if (eq_pos == string::npos) {
                cerr << "Invalid variable assignment: " << arg << endl;
                return 1;
            }
            string var = arg.substr(0, eq_pos);
            double val = stod(arg.substr(eq_pos + 1));
            vars[var] = val;
        }

        cout << expr.eval(vars) << endl;

    } else if (mode == "--diff") {
        if (argc < 5 || string(argv[3]) != "--by") {
            cerr << "Usage: " << argv[0] << " --diff \"expression\" --by var" << endl;
            return 1;
        }
        string expr_str = argv[2];
        string by_var = argv[4];

        auto expr = parse<double>(expr_str);
        auto derivative = expr.differ(by_var);

        cout << derivative.to_str() << endl;

    } else {
        cerr << "Unknown mode: " << mode << endl;
        return 1;
    }

    return 0;
}
