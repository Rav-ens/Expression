#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <complex>

template<typename T>
class Variable {
public:
    std::string exp_s;
    T exp_n;
    int is_num;
    Variable() : exp_n(0), is_num(0) {}
    Variable(const std::string& exp) : exp_s(exp), is_num(0) {}
    Variable(T exp) : exp_n(exp), is_num(1) {}
};

template<typename T>
class Node {
public:
    Node() : type(-1), left(nullptr), right(nullptr) {}
    int type;
    Node* left;
    Node* right;
    char v_op;
    Variable<T> v_var;
};

template<typename T>
class Expression {
public:
    Node<T>* head;
    Expression();
    Expression(const std::string& exp);
    Expression(T exp);
    Expression(const Expression& other);
    ~Expression();
    Expression& operator=(const Expression& other);

    Expression operator+(const Expression& other);
    Expression operator*(const Expression& other);
    Expression operator/(const Expression& other);
    Expression operator-(const Expression& other);
    Expression operator^(const Expression& other);
    template<typename HHH>
    friend Expression sin(const Expression& expr);
    template<typename HHH>
    friend Expression cos(const Expression& expr);
    template<typename HHH>
    friend Expression ln(const Expression& expr);
    template<typename HHH>
    friend Expression exp(const Expression& expr);

    std::string to_str();
    void replace(const std::string& k, T v);
    T eval(std::map<std::string, T>& mp);

    static void deleteTree(Node<T>* node);
    static Node<T>* copyNode(const Node<T>* src);
    static std::string to_string(Node<T>* h);
    void repl(Node<T>* h, const std::string& k, T v);
    T eval_rec(Node<T>* h, std::map<std::string, T>& mp);
};

#endif // EXPRESSION_HPP