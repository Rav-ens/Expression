#include "Expression.hpp"
#include <locale>
#include <stack>
#include <vector>

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
            return std::exp(eval_rec(h->right, mp) * std::log(eval_rec(h->left, mp)));
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

template<typename T>
bool Expression<T>::is_var(Node<T>* h, const std::string& v){
	if(not h) return 0;
	if(h->type == 2 && h->v_var.is_num == 0 && h->v_var.exp_s == v) return 1;
	return is_var(h->left,v) || is_var(h->right,v);
}

template<typename T>
Expression<T> Expression<T>::differ(const std::string& v){
		if(head->type == 2){
			if(head->v_var.is_num == 0 && head->v_var.exp_s == v){
				return Expression(1.0);
			}
			return Expression(0.0);
		}
		else if(head -> type == 0){
			Expression l,r;
			l.head = copyNode(head->left);
			r.head = copyNode(head->right);
			if(head->v_op == '+'){
				return l.differ(v) +  r.differ(v);
			}
			if(head->v_op == '-'){
				return l.differ(v) -  r.differ(v);
			}
			if(head->v_op == '*'){
				return l.differ(v) * r + r.differ(v) * l;
			}
			if(head->v_op == '/'){
				return  (l.differ(v)*r - r.differ(v) * l) / r * r;
			}
			if(head->v_op == '^'){
                return r*(l^(r-Expression(1)))*l.differ(v) + (l^r)*(r.differ(v))*ln(l);
			}
	   }
		else{
			Expression r;
			r.head = copyNode(head->right);
			if(head->v_op == 'c'){
				return Expression(-1.0) * sin(r) * r.differ(v); 
			}
			if(head->v_op == 's'){
				return  cos(r) * r.differ(v); 
			}
			if(head->v_op == 'l'){
				return Expression(1.0) / r * r.differ(v); 
			}
			if(head->v_op == 'e'){
				return  exp(r) * r.differ(v); 
			}
		}
        std::cout<<"WTF???"<<std::endl;
        return Expression(0.0);
}

template<typename T>
Token<T>::Token(std::string s):is_oper(0),is_func(0),is_var(1),sco(0),scc(0){
    if(s == ")") { scc = 1;is_var = 0;}
    if(s == "("){ sco = 1; is_var = 0;}
    for(auto i : map){
        if(s==i.first){
            is_var = 0;
            oper = s[0];
            prior = i.second;
            if(prior>=4)is_func =1;
            else is_oper = 1;
            break;
        }
    }
    if(is_var){
        std::istringstream iss(s);
        T num;
        if(iss >> num){
            v= Variable<T>(num);
        }else{
            v= Variable<T>(s);
        }
    }
}

template<typename T>
std::vector<Token<T>> tokenize(std::string& s){
    std::vector<std::string> oper = {"+","-","*","/","sin","cos","ln","exp","^"};
    std::string buffer = "";
    s = " ( " + s;
    s += " ) ";
    std::vector<Token<T>> v;
    for(auto i : s){
        if(i == ' ') {
            if(buffer!=""){
                v.push_back(Token<T>(buffer));
                buffer = "";
            }
        }else if(i == '(' || i ==')' || i == '+' || i =='-'|| i == '*' || i == '/' || i == '^' ){
            if(buffer != "") v.push_back(Token<T>(buffer));
            buffer = "";
            buffer += i;
            v.push_back(Token<T>(buffer));
            buffer = "";

        }else{
            buffer+=i;
        }

        for(auto s : oper){
            if(buffer == s){
                v.push_back(Token<T>(buffer));
                buffer = "";
            }
        }

    }
    return v;
}

template<typename T>
std::vector<Node<T>*> to_opz(std::string& s){
    std::vector<Token<T>> tokens = tokenize<T>(s);
    std::stack<Token<T>> stack{};
    std::vector<Node<T> *> ans;
    for(auto t: tokens){
        if(t.is_var){
            Node<T>* n = new Node<T>;
            n->type = 2;
            n->v_var = t.v;
            ans.push_back(n);
        }else{
            if(t.sco){
                stack.push(t);
            }
            else if(t.scc){
                while(stack.top().sco != 1){
                    Node<T>* n = new Node<T>;
                    n->type = int(stack.top().is_func);
                    n->v_op = stack.top().oper;
                    ans.push_back(n);
                    stack.pop();
                }
                stack.pop();
            }else{
                while(stack.size() && stack.top().prior > t.prior){
                    Node<T>* n = new Node<T>;
                    n->type = int(stack.top().is_func);
                    n->v_op = stack.top().oper;
                    ans.push_back(n);
                    stack.pop();
                }
                stack.push(t);
            }
        }
    }
    return ans;
}

template<typename T>
Expression<T> parse(std::string s){
    std::vector<Node<T>*> ops = to_opz<T>(s);
    std::stack<Node<T>*> st;
    for(auto i: ops){
        if(i->type == 0){
            i->right = st.top();st.pop();
            i->left = st.top();st.pop();
        }else if(i->type == 1){
            i->right = st.top();st.pop();
        }
        st.push(i);
    };
    Expression<T> x; x.head = st.top();
    return x;
}
