#include "../stack.hpp"
#include <stack>
#include <vector>
#include <iostream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;

#define FALSE		"\033[0;31mFALSE\033[0m"
#define TRUE		"\033[0;32mTRUE\033[0m"

#define COLOR_DEFAULT "\e[0m"
#define RED "\e[31m"
#define GREEN "\e[32m"

void print_msg(const std::string& msg, bool isOK) {
    std::ios state(nullptr);
    state.copyfmt(std::cout);
    std::cout << "  "
              << std::setw(40)
              << std::left
              << msg
              << std:: right
              << (isOK ? GREEN : RED)
              << (isOK ? "OK" : "KO")
              << COLOR_DEFAULT
              << std::endl;
    std::cout.copyfmt(state);
}

void msgOk(const std::string& msg) {
    print_msg(msg, true);
}
void msgFail(const std::string& msg) {
    print_msg(msg, false);
}

int main() {
    typedef std::stack<int, std::vector<int> > ss;
    typedef ft::stack<int, std::vector<int> > fs;

    cout << "value_type is equal? " << (typeid(ss::value_type) == typeid(fs::value_type) ? TRUE : FALSE) << endl;
    cout << "container_type is equal? " << (typeid(ss::container_type) == typeid(fs::container_type) ? TRUE : FALSE) << endl;
    cout << "size_type is equal? " << (typeid(ss::size_type) == typeid(fs::size_type) ? TRUE : FALSE) << endl;

    ss st1;
    ss st11;
    fs st2;
    fs st22;
    for (int i = 0; i < 15; i++) {
        if (i % 2) {
            st1.push(i * 10);
            st11.push(i * 10);
            st2.push(i * 10);
            st22.push(i * 10);
        } else {
            st1.push(i);
            st11.push(i);
            st2.push(i);
            st22.push(i);
        }
    }

    for (int i = 0; i < 5; i++) {
       st11.pop();
       st22.pop();
    }

    cout << "empty is equal? " << (st1.empty() == st2.empty() ? TRUE : FALSE) << endl;
    cout << "size is equal? " << (st1.size() == st2.size() ? TRUE : FALSE) << endl;
    cout << "top is equal? " << (st1.top() == st2.top() ? TRUE : FALSE) << endl;
    cout << "operator== is equal? " << ((st1 == st11) == (st2 == st22) ? TRUE : FALSE) << endl;
    cout << "operator!= is equal? " << ((st1 != st11) == (st2 != st22) ? TRUE : FALSE) << endl;
    cout << "operator<= is equal? " << ((st1 <= st11) == (st2 <= st22) ? TRUE : FALSE) << endl;
    cout << "operator> is equal? " << ((st1 > st11) == (st2 > st22) ? TRUE : FALSE) << endl;
    cout << "operator< is equal? " << ((st1 < st11) == (st2 < st22) ? TRUE : FALSE) << endl;
    cout << "operator>= is equal? " << ((st1 >= st11) == (st2 >= st22) ? TRUE : FALSE) << endl;


    ft::stack<int> ft;
    std::stack<int> std;
    std::cout << "Constructor:" << std::endl;
    ft.empty() == std.empty() ? msgOk("empty") : msgFail("empty");
    ft.size() == std.size() ? msgOk("size") : msgFail("size");

    std::cout << "Push:" << std::endl;
    for (int i = 1; i <= 3; ++i) {
        ft.push(i);
        std.push(i);
    }
    ft.empty() == std.empty() ? msgOk("empty") : msgFail("empty");
    ft.size() == std.size() ? msgOk("size") : msgFail("size");
    ft.top() == std.top() ? msgOk("top") : msgFail("top");

    std::cout << "Pop:" << std::endl;
    ft.pop();
    std.pop();
    ft.empty() == std.empty() ? msgOk("empty") : msgFail("empty");
    ft.size() == std.size() ? msgOk("size") : msgFail("size");
    ft.top() == std.top() ? msgOk("top") : msgFail("top");

    std::cout << "Operators:" << std::endl;
    ft::stack<int> ft1;
    std::stack<int> std1;
    ft1.push(5);
    std1.push(5);
    (ft == ft1) == (std == std1) ? msgOk("Operator ==") : msgFail("Operator ==");
    (ft != ft1) == (std != std1) ? msgOk("Operator !=") : msgFail("Operator !=");
    (ft > ft1) == (std > std1) ? msgOk("Operator >") : msgFail("Operator >");
    (ft >= ft1) == (std >= std1) ? msgOk("Operator >=") : msgFail("Operator >=");
    (ft < ft1) == (std < std1) ? msgOk("Operator <") : msgFail("Operator <");
    (ft <= ft1) == (std <= std1) ? msgOk("Operator <=") : msgFail("Operator <=");

}