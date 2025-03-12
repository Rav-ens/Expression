#include <complex>
#include <map>
#include <iostream>

// Предполагаем, что класс Expression и функция parse уже определены в "Expression.cpp"
#include "Expression.cpp"

// Тесты для выражений с типом double
void test_expression_creation() {
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
    Expression<double> x = parse<double>("x^( 0.5 )");
    Expression<double> result = x.differ("x");
    std::map<std::string, double> map = {{"x", 0.25}};
    if (result.eval(map) == 1) {
        std::cout << "test_expression_differentiation: OK" << std::endl;
    } else {
        std::cout << "test_expression_differentiation: FAIL" << std::endl;
    }
}

// Тесты для выражений с типом std::complex<double>
void test_complex_expression_creation() {
    Expression<std::complex<double>> expr("x");
    if (expr.to_str() == "(x)") {
        std::cout << "test_complex_expression_creation: OK" << std::endl;
    } else {
        std::cout << "test_complex_expression_creation: FAIL" << std::endl;
    }
}

void test_complex_expression_addition() {
    Expression<std::complex<double>> expr1("x");
    Expression<std::complex<double>> expr2("y");
    Expression<std::complex<double>> result = expr1 + expr2;
    if (result.to_str() == "((x) + (y))") {
        std::cout << "test_complex_expression_addition: OK" << std::endl;
    } else {
        std::cout << "test_complex_expression_addition: FAIL" << std::endl;
    }
}

void test_complex_expression_multiplication() {
    Expression<std::complex<double>> expr1("x");
    Expression<std::complex<double>> expr2("y");
    Expression<std::complex<double>> result = expr1 * expr2;
    if (result.to_str() == "((x) * (y))") {
        std::cout << "test_complex_expression_multiplication: OK" << std::endl;
    } else {
        std::cout << "test_complex_expression_multiplication: FAIL" << std::endl;
    }
}

void test_complex_expression_evaluation() {
    Expression<std::complex<double>> expr("x");
    std::map<std::string, std::complex<double>> vars = {{"x", std::complex<double>(5.0, 3.0)}};
    std::complex<double> result = expr.eval(vars);
    if (result == std::complex<double>(5.0, 3.0)) {
        std::cout << "test_complex_expression_evaluation: OK" << std::endl;
    } else {
        std::cout << "test_complex_expression_evaluation: FAIL" << std::endl;
    }
}

void test_complex_expression_differentiation() {
    Expression<std::complex<double>> x = parse<std::complex<double>>("x ^ ( 0.5 )");
    Expression<std::complex<double>> result = x.differ("x");
    std::map<std::string, std::complex<double>> map = {{"x", std::complex<double>(0.25, 0.0)}};
    std::complex<double> eval_result = result.eval(map);
    if (std::abs(eval_result - std::complex<double>(1.0, 0.0)) < 1e-6) {
        std::cout << "test_complex_expression_differentiation: OK" << std::endl;
    } else {
        std::cout << "test_complex_expression_differentiation: FAIL" << std::endl;
    }
}

// Основная функция для запуска всех тестов
int main() {
    // Тесты для double
    std::cout << "Testing double expressions:" << std::endl;
    test_expression_creation();
    test_expression_addition();
    test_expression_multiplication();
    test_expression_evaluation();
    test_expression_differentiation();

    // Тесты для std::complex<double>
    std::cout << "\nTesting complex expressions:" << std::endl;
    test_complex_expression_creation();
    test_complex_expression_addition();
    test_complex_expression_multiplication();
    test_complex_expression_evaluation();
    test_complex_expression_differentiation();

    return 0;
}