#include "Expression.cpp"
#include <filesystem>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>


void test_expression_creation(){
    Expression<double> expr("x");
    if (expr.to_str() == "(x)") {
        std::cout << "test_expression_creation: OK" << std::endl;
    } else {
        std::cout << "test_expression_creation: FAIL" << std::endl;
    }
}

void test_expression_addition() {
    Expression<double> expr1("x");
    Expression<double> expr2("y");
    Expression<double> result = expr1 + expr2;
    if (result.to_str() == "((x) + (y))") {
        std::cout << "test_expression_addition: OK" << std::endl;
    } else {
        std::cout << "test_expression_addition: FAIL" << std::endl;
    }
}

void test_expression_multiplication() {
    Expression<double> expr1("x");
    Expression<double> expr2("y");
    Expression<double> result = expr1 * expr2;
    if (result.to_str() == "((x) * (y))") {
        std::cout << "test_expression_multiplication: OK" << std::endl;
    } else {
        std::cout << "test_expression_multiplication: FAIL" << std::endl;
    }
}

void test_expression_evaluation() {
    Expression<double> expr("x");
    std::map<std::string, double> vars = {{"x", 5.0}};
    double result = expr.eval(vars);
    if (result == 5.0) {
        std::cout << "test_expression_evaluation: OK" << std::endl;
    } else {
        std::cout << "test_expression_evaluation: FAIL" << std::endl;
    }
}

void test_expression_differentiation() {
    Expression<double> x = parse<double>("x ^ ( 0.5 )");
    Expression<double> result = x.differ("x");
    std::map<std::string, double> map = {{"x",0.25}};
    //std::cout<<result.eval(map)<<std::endl;    
    if (result.eval(map) == 1) {
        std::cout << "test_expression_differentiation: OK" << std::endl;
    } else {
        std::cout << "test_expression_differentiation: FAIL" << std::endl;
    }
}

int testing() {
    test_expression_creation();
    test_expression_addition();
    test_expression_multiplication();
    test_expression_evaluation();
    test_expression_differentiation();

    return 0;
}