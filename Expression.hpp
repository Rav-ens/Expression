#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <complex>
#include <vector>

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
class Token{
public:
    const std::map<std::string, int> map = {
        {"(", 0},
        {"+", 1},
        {"-",1},
        {"*",2},
        {"/",2},
        {"^",3},
        {"sin",4},
        {"cos",4},
        {"ln",4},
        {"exp",4},
    };
    bool is_oper;
    bool is_func;
    bool is_var;
    bool sco;
    bool scc;
    char oper;
    char prior;
    Variable<T> v;
    Token(std::string s);


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
    static Node<T>* copyNode(const Node<T>* src);
    Expression differ(const std::string& v);
    
    template<typename HHH>
    friend std::vector<Token<T>> tokenize(std::string& s);
    template<typename HHH>
    friend std::vector<Node<T>*> to_opz(std::string& s);
    template<typename HHH>
    friend Expression<T> parse(std::string s);


private:
    static void deleteTree(Node<T>* node);
    static std::string to_string(Node<T>* h);
    void repl(Node<T>* h, const std::string& k, T v);
    T eval_rec(Node<T>* h, std::map<std::string, T>& mp);
    bool is_var(Node<T>* h,const std::string& v);


};

#endif // EXPRESSION_HPP
