#include "../set.hpp"
#include <set>
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

template<class T>
void checkValueset(const std::set<T>& std, const ft::set<T>& ft) {
    if (std.size() == ft.size()) {
        msgOk("Size");
    } else {
        msgFail("Size");
        msgFail("Value");
        return;
    }
    typename ft::set<T>::const_iterator ft_it = ft.begin();
    typename std::set<T>::const_iterator std_it = std.begin();
    while (std_it != std.end()) {
        if (*std_it != *ft_it) {
            msgFail("Value");
            return;
        }
        std_it++;
        ft_it++;
    }
    msgOk("Value");
}


int main() {
    typedef std::set<int, std::less<int>, std::allocator<int> > ss;
    typedef ft::set<int, std::less<int>, std::allocator<int> > fs;

    cout << "key_type is equal? " << (typeid(ss ::key_type) == typeid(fs::key_type) ? TRUE : FALSE) << endl;
    cout << "value_type is equal? " << ((typeid(ss::value_type) == typeid(std::pair<const int, string>)) == (typeid(fs::value_type) == typeid(ft::pair<const int, string>)) ? TRUE : FALSE) << endl;
    cout << "key_compare is equal? " << (typeid(ss::key_compare) == typeid(fs::key_compare) ? TRUE : FALSE) << endl;
    cout << "allocator_type is equal? " << (typeid(ss::allocator_type) == typeid(fs::allocator_type) ? TRUE : FALSE) << endl;
    cout << "reference is equal? " << (typeid(ss::reference) == typeid(fs::reference) ? TRUE : FALSE) << endl;
    cout << "const_reference is equal? " << (typeid(ss::const_reference) == typeid(fs::const_reference) ? TRUE : FALSE) << endl;
    cout << "pointer is equal? " << (typeid(ss::pointer) == typeid(fs::pointer) ? TRUE : FALSE) << endl;
    cout << "const_pointer is equal? " << (typeid(ss::const_pointer) == typeid(fs::const_pointer) ? TRUE : FALSE) << endl;
    cout << "difference_type is equal? " << (typeid(ss::difference_type) == typeid(fs::difference_type) ? TRUE : FALSE) << endl;
    cout << "size_type is equal? " << (typeid(ss::size_type) == typeid(fs::size_type) ? TRUE : FALSE) << endl;

    typedef std::set<int>::iterator si;
    typedef ft::set<int>::iterator fi;

    fs set;

    fs::iterator it = set.begin();
    fs::const_iterator cit = set.begin();
    fs::reverse_iterator rit = set.rbegin();
    fs::const_reverse_iterator crit = set.rbegin();

    cout << "* iterators *" << endl;
    cout << "iterator_category is equal? " << ((typeid(si::iterator_category) == typeid(std::random_access_iterator_tag)) == (typeid(fi::iterator_category) == typeid(ft::random_access_iterator_tag)) ? TRUE : FALSE) << endl;
//    cout << "value_type is equal? " << (typeid(si::value_type) == typeid(fi::value_type) ? TRUE : FALSE) << endl;
    cout << "difference_type is equal? " << (typeid(si::difference_type) == typeid(fi::difference_type) ? TRUE : FALSE) << endl;
//    cout << "pointer is equal? " << (typeid(si::pointer) == typeid(fi::pointer) ? TRUE : FALSE) << endl;
//    cout << "reference is equal? " << (typeid(si::reference) == typeid(fi::reference) ? TRUE : FALSE) << endl;


    {
        std::cout << "Constructors:" << std::endl;
        std::cout << "  Default:" << std::endl;
        ft::set<int> a;
        std::set<int> b;
        checkValueset(b, a);
        std::cout << "  Copy:" << std::endl;
        ft::set<int> c(a);
        std::set<int> d(b);
        checkValueset(d, c);
        std::cout << "  Assign:" << std::endl;
        a = c;
        b = d;
        checkValueset(d, c);

        std::cout << "Allocator:" << std::endl;
        a.get_allocator() == b.get_allocator() ? msgOk("Get Allocator") : msgFail("Get Allocator");
    }

    {
        ft::set<int> a;
        std::set<int> b;

        a.empty() == b.empty() ? msgOk("Empty") : msgFail("Empty");
        a.size() == b.size() ? msgOk("Size") : msgFail("Size");

        ft::set<int>::iterator ft_it;
        std::set<int>::iterator std_it;

        ft::pair<ft::set<int>::iterator, bool> ftPair;
        std::pair<std::set<int>::iterator, bool> stdPair;

        std::cout << "Insert(value):" << std::endl;
        ftPair = a.insert(0);
        stdPair = b.insert(0);
        checkValueset<int>(b, a);
        (ftPair.second == stdPair.second) && (((*ftPair.first)) == (*(stdPair.first))) ? msgOk(
                "Return value") : msgFail("Return value");

        std::cout << "Insert(position)" << std::endl;
        ft_it = a.insert(a.end(), 1);
        std_it = b.insert(b.end(), 1);
        checkValueset<int>(b, a);
        (*ft_it) == (*std_it) ? msgOk("Return value") : msgFail("Return value");

        std::cout << "Insert(range)" << std::endl;
        ft::set<int> a1;
        std::set<int> b1;
        a1.insert(2);
        a1.insert(3);
        b1.insert(2);
        b1.insert(3);
        a.insert(a1.begin(), a1.end());
        b.insert(b1.begin(), b1.end());
        checkValueset(b, a);

        std::cout << "Find:" << std::endl;
        *a1.find(3) == *b1.find(3) ? msgOk("Value") : msgFail("Value");

        std::cout << "Count:" << std::endl;
        a1.count(2) == b1.count(2) ? msgOk("Value") : msgFail("Value");

        std::cout << "Erase(position):" << std::endl;
        a.erase(a.begin());
        b.erase(b.begin());
        checkValueset(b, a);

        std::cout << "Erase(key):" << std::endl;
        a.erase(3);
        b.erase(3);
        checkValueset(b, a);

        std::cout << "Erase(iterators):" << std::endl;
        a.erase(a.begin(), a.end());
        b.erase(b.begin(), b.end());
        checkValueset(b, a);
    }
    {
        std::cout << "Swap:" << std::endl;
        ft::set<int> ft1;
        ft::set<int> ft2;
        std::set<int> std1;
        std::set<int> std2;
        ft1.insert(2);
        ft1.insert(3);

        std1.insert(2);
        std1.insert(3);

        ft2.insert(2);
        ft2.insert(3);

        std2.insert(2);
        std2.insert(3);
        ft1.swap(ft2);
        std1.swap(std2);
        *ft1.begin() == *std1.begin() ? msgOk("Value") : msgFail("Value");

        std::cout << "Clear:" << std::endl;
        ft1.clear();
        std1.clear();
        checkValueset(std1, ft1);
    }
    {
        ft::set<int> ft;
        std::set<int> std;
        ft.insert(1);
        ft.insert(2);
        ft.insert(3);
        ft.insert(4);
        ft.insert(5);
        std.insert(1);
        std.insert(2);
        std.insert(3);
        std.insert(4);
        std.insert(5);

        std::cout << "Lower:" << std::endl;
        *ft.lower_bound(2) == *std.lower_bound(2) ? msgOk("Value") : msgFail("Value");

        std::cout << "Upper:" << std::endl;
        *ft.upper_bound(2) == *std.upper_bound(2) ? msgOk("Value") : msgFail("Value");

        std::cout << "Equal_range:" << std::endl;
        *ft.equal_range(4).first == *std.equal_range(4).first &&
                *ft.equal_range(4).first == *std.equal_range(4).first &&
                *ft.equal_range(4).second == *std.equal_range(4).second &&
                *ft.equal_range(4).second == *std.equal_range(4).second
                ? msgOk("Value") : msgFail("Value");
    }
    {
        std::cout << "is_integral:" << std::endl;
        ft::is_integral<int>().value == std::is_integral<int>().value ? msgOk("int") : msgFail("int");
        ft::is_integral<float>().value == std::is_integral<float>().value ? msgOk("float") : msgFail("float");
        ft::is_integral<bool>().value == std::is_integral<bool>().value ? msgOk("bool") : msgFail("bool");
    }
}