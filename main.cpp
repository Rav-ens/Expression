#include <iostream>
#include <map>
#include <string>
#include "Expression.cpp"

void print_usage() {
    std::cout << "Usage: differentiator --eval <expression> [variable=value...]\n";
    std::cout << "       differentiator --diff <expression> --by <variable>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "--eval") {
        if (argc < 3) {
            print_usage();
            return 1;
        }

        std::string expression_str = argv[2];
        std::map<std::string, double> variables;

        for (int i = 3; i < argc; ++i) {
            std::string arg = argv[i];
            size_t eq_pos = arg.find('=');
            if (eq_pos == std::string::npos) {
                std::cerr << "Invalid variable assignment: " << arg << "\n";
                return 1;
            }
            std::string var = arg.substr(0, eq_pos);
            double value = std::stod(arg.substr(eq_pos + 1));
            variables[var] = value;
        }

        Expression<double> expr = parse<double>(expression_str);
        double result = expr.eval(variables);
        std::cout << result << "\n";

    } else if (mode == "--diff") {
        if (argc < 5 || std::string(argv[3]) != "--by") {
            print_usage();
            return 1;
        }

        std::string expression_str = argv[2];
        std::string variable = argv[4];

        Expression<double> expr = parse<double>(expression_str);
        Expression<double> derivative = expr.differ(variable);
        std::cout << derivative.to_str() << "\n";

    } else {
        print_usage();
        return 1;
    }

    return 0;
}