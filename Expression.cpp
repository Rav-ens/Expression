#include "expression.hpp"

template<typename T>
Expression<T>::Expression() : head(nullptr) {}

template<typename T>
Expression<T>::Expression(const std::string& exp) {
    head = new Node<T>;
    head->type = 2;
    head->v_var = Variable<T>(exp);
    head->left = nullptr;
    head->right = nullptr;
}

template<typename T>
Expression<T>::Expression(T exp) {
    head = new Node<T>;
    head->type = 2;
    head->v_var = Variable<T>(exp);
    head->left = nullptr;
    head->right = nullptr;
}

template<typename T>
Expression<T>::Expression(const Expression& other) {
    head = copyNode(other.head);
}

template<typename T>
Expression<T>::~Expression() {
    deleteTree(head);
}

template<typename T>
Expression<T>& Expression<T>::operator=(const Expression& other) {
    if (this != &other) {
        deleteTree(head);
        head = copyNode(other.head);
    }
    return *this;
}

template<typename T>
Expression<T> Expression<T>::operator+(const Expression& other) {
    Expression x;
    x.head = new Node<T>;
    x.head->type = 0;
    x.head->v_op = '+';
    x.head->left = copyNode(this->head);
    x.head->right = copyNode(other.head);
    return x;
}

template<typename T>
Expression<T> Expression<T>::operator*(const Expression& other) {
    Expression x;
    x.head = new Node<T>;
    x.head->type = 0;
    x.head->v_op = '*';
    x.head->left = copyNode(this->head);
    x.head->right = copyNode(other.head);
    return x;
}

template<typename T>
Expression<T> Expression<T>::operator/(const Expression& other) {
    Expression x;
    x.head = new Node<T>;
    x.head->type = 0;
    x.head->v_op = '/';
    x.head->left = copyNode(this->head);
    x.head->right = copyNode(other.head);
    return x;
}

template<typename T>
Expression<T> Expression<T>::operator-(const Expression& other) {
    Expression x;
    x.head = new Node<T>;
    x.head->type = 0;
    x.head->v_op = '-';
    x.head->left = copyNode(this->head);
    x.head->right = copyNode(other.head);
    return x;
}

template<typename T>
Expression<T> Expression<T>::operator^(const Expression& other) {
    Expression x;
    x.head = new Node<T>;
    x.head->type = 0;
    x.head->v_op = '^';
    x.head->left = copyNode(this->head);
    x.head->right = copyNode(other.head);
    return x;
}

template<typename T>
Expression<T> sin(const Expression<T>& expr) {
    Expression<T> result;
    result.head = new Node<T>();
    result.head->type = 1;
    result.head->v_op = 's';
    result.head->left = nullptr;
    result.head->right = Expression<T>::copyNode(expr.head);
    return result;
}

template<typename T>
Expression<T> cos(const Expression<T>& expr) {
    Expression<T> result;
    result.head = new Node<T>();
    result.head->type = 1;
    result.head->v_op = 'c';
    result.head->left = nullptr;
    result.head->right = Expression<T>::copyNode(expr.head);
    return result;
}

template<typename T>
Expression<T> ln(const Expression<T>& expr) {
    Expression<T> result;
    result.head = new Node<T>();
    result.head->type = 1;
    result.head->v_op = 'l';
    result.head->left = nullptr;
    result.head->right = Expression<T>::copyNode(expr.head);
    return result;
}

template<typename T>
Expression<T> exp(const Expression<T>& expr) {
    Expression<T> result;
    result.head = new Node<T>();
    result.head->type = 1;
    result.head->v_op = 'e';
    result.head->left = nullptr;
    result.head->right = Expression<T>::copyNode(expr.head);
    return result;
}

template<typename T>
std::string Expression<T>::to_str() {
    std::ostringstream oss;
    oss << to_string(head);
    return oss.str();
}

template<typename T>
void Expression<T>::replace(const std::string& k, T v) {
    repl(head, k, v);
}

template<typename T>
T Expression<T>::eval(std::map<std::string, T>& mp) {
    return eval_rec(head, mp);
}

template<typename T>
void Expression<T>::deleteTree(Node<T>* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template<typename T>
Node<T>* Expression<T>::copyNode(const Node<T>* src) {
    if (!src) return nullptr;

    Node<T>* newNode = new Node<T>();
    newNode->type = src->type;
    newNode->v_op = src->v_op;
    newNode->v_var = src->v_var;

    newNode->left = copyNode(src->left);
    newNode->right = copyNode(src->right);

    return newNode;
}

template<typename T>
std::string Expression<T>::to_string(Node<T>* h) {
    if (!h) return "";
    std::ostringstream oss;
    oss << "(";
    oss << to_string(h->left);
    if (h->type == 0) oss << " " << h->v_op << " ";
    else if (h->type == 1) {
        if (h->v_op == 's') oss << "sin";
        if (h->v_op == 'c') oss << "cos";
        if (h->v_op == 'l') oss << "ln";
        if (h->v_op == 'e') oss << "exp";
    } else {
        if (h->v_var.is_num) oss << h->v_var.exp_n;
        else oss << h->v_var.exp_s;
    }
    oss << to_string(h->right) << ")";
    return oss.str();
}

template<typename T>
void Expression<T>::repl(Node<T>* h, const std::string& k, T v) {
    if (!h) return;
    if (h->type == 2) {
        if (h->v_var.is_num == 0 && h->v_var.exp_s == k) {
            h->v_var.is_num = 1;
            h->v_var.exp_n = v;
        }
    }
    repl(h->left, k, v);
    repl(h->right, k, v);
}

template<typename T>
T Expression<T>::eval_rec(Node<T>* h, std::map<std::string, T>& mp) {
    if (h->type == 2) {
        if (h->v_var.is_num) return h->v_var.exp_n;
        else return mp[h->v_var.exp_s];
    }
    if (h->type == 0) {
        if (h->v_op == '+')
            return eval_rec(h->left, mp) + eval_rec(h->right, mp);
        if (h->v_op == '-')
            return eval_rec(h->left, mp) - eval_rec(h->right, mp);
        if (h->v_op == '/')
            return eval_rec(h->left, mp) / eval_rec(h->right, mp);
        if (h->v_op == '*')
            return eval_rec(h->left, mp) * eval_rec(h->right, mp);
        if (h->v_op == '^')
            return std::exp(eval_rec(h->left, mp) * std::log(eval_rec(h->right, mp)));
    }
    if (h->type == 1) {
        if (h->v_op == 's')
            return std::sin(eval_rec(h->right, mp));
        if (h->v_op == 'c')
            return std::cos(eval_rec(h->right, mp));
        if (h->v_op == 'e')
            return std::exp(eval_rec(h->right, mp));
        if (h->v_op == 'l')
            return std::log(eval_rec(h->right, mp));
    }
    return 0;
}

int main() {
    std::string f = "Z";
    Expression<std::complex<double>> x(f);
    Expression<std::complex<double>> y(f);
    Expression<std::complex<double>> z = x;
    Expression<std::complex<double>> n = sin(x);
    n.replace(f, 123.134);
    std::cout << std::endl;
    std::map<std::string, std::complex<double>> g = {{f, {1.0,1.0}}};
    std::cout << (x ^ x).eval(g);
}