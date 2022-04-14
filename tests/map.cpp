#include "../map.hpp"
#include <map>
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

template<class T1, class T2>
void checkValueMap(const std::map<T1, T2>& std, const ft::map<T1, T2>& ft) {
    if (std.size() == ft.size()) {
        msgOk("Size");
    } else {
        msgFail("Size");
        msgFail("Value");
        return;
    }
    typename ft::map<T1, T2>::const_iterator ft_it = ft.begin();
    typename std::map<T1, T2>::const_iterator std_it = std.begin();
    while (std_it != std.end()) {
        if (std_it->second != ft_it->second && std_it->first != ft_it->first) {
            msgFail("Value");
            return;
        }
        std_it++;
        ft_it++;
    }
    msgOk("Value");
}


int main() {
    typedef std::map<int, string, std::less<int>, std::allocator<std::pair<const int, string> > > sm;
    typedef ft::map<int, string, std::less<int>, std::allocator<std::pair<const int, string> > > fm;

    cout << "key_type is equal? " << (typeid(sm::key_type) == typeid(fm::key_type) ? TRUE : FALSE) << endl;
    cout << "mapped_type is equal? " << (typeid(sm::mapped_type) == typeid(fm::mapped_type) ? TRUE : FALSE) << endl;
    cout << "value_type is equal? " << ((typeid(sm::value_type) == typeid(std::pair<const int, string>)) == (typeid(fm::value_type) == typeid(ft::pair<const int, string>)) ? TRUE : FALSE) << endl;
    cout << "key_compare is equal? " << (typeid(sm::key_compare) == typeid(fm::key_compare) ? TRUE : FALSE) << endl;
    cout << "allocator_type is equal? " << (typeid(sm::allocator_type) == typeid(fm::allocator_type) ? TRUE : FALSE) << endl;
    cout << "reference is equal? " << (typeid(sm::reference) == typeid(fm::reference) ? TRUE : FALSE) << endl;
    cout << "const_reference is equal? " << (typeid(sm::const_reference) == typeid(fm::const_reference) ? TRUE : FALSE) << endl;
    cout << "pointer is equal? " << (typeid(sm::pointer) == typeid(fm::pointer) ? TRUE : FALSE) << endl;
    cout << "const_pointer is equal? " << (typeid(sm::const_pointer) == typeid(fm::const_pointer) ? TRUE : FALSE) << endl;
    cout << "difference_type is equal? " << (typeid(sm::difference_type) == typeid(fm::difference_type) ? TRUE : FALSE) << endl;
    cout << "size_type is equal? " << (typeid(sm::size_type) == typeid(fm::size_type) ? TRUE : FALSE) << endl;

    fm map;

    fm::iterator it = map.begin();
    fm::const_iterator cit = map.begin();
    fm::reverse_iterator rit = map.rbegin();
    fm::const_reverse_iterator crit = map.rbegin();


    typedef std::map<int, string>::iterator si;
    typedef ft::map<int, string>::iterator fi;

    cout << "* iterators *" << endl;
    cout << "iterator_category is equal? " << ((typeid(si::iterator_category) == typeid(std::random_access_iterator_tag)) == (typeid(fi::iterator_category) == typeid(ft::random_access_iterator_tag)) ? TRUE : FALSE) << endl;
//    cout << "value_type is equal? " << (typeid(si::value_type) == typeid(fi::value_type) ? TRUE : FALSE) << endl;
    cout << "difference_type is equal? " << (typeid(si::difference_type) == typeid(fi::difference_type) ? TRUE : FALSE) << endl;
//    cout << "pointer is equal? " << (typeid(si::pointer) == typeid(fi::pointer) ? TRUE : FALSE) << endl;
//    cout << "reference is equal? " << (typeid(si::reference) == typeid(fi::reference) ? TRUE : FALSE) << endl;


    {
        std::cout << "Constructors:" << std::endl;
        std::cout << "  Default:" << std::endl;
        ft::map<int, std::string> a;
        std::map<int, std::string> b;
        checkValueMap(b, a);
        std::cout << "  Copy:" << std::endl;
        ft::map<int, std::string> c(a);
        std::map<int, std::string> d(b);
        checkValueMap(d, c);
        std::cout << "  Assign:" << std::endl;
        a = c;
        b = d;
        checkValueMap(d, c);

        std::cout << "Allocator:" << std::endl;
        a.get_allocator() == b.get_allocator() ? msgOk("Get Allocator") : msgFail("Get Allocator");
    }

    {
        ft::map<int, std::string> a;
        std::map<int, std::string> b;

        a.empty() == b.empty() ? msgOk("Empty") : msgFail("Empty");
        a.size() == b.size() ? msgOk("Size") : msgFail("Size");

        ft::map<int, std::string>::iterator ft_it;
        std::map<int, std::string>::iterator std_it;

        ft::pair<ft::map<int, std::string>::iterator, bool> ftPair;
        std::pair<std::map<int, std::string>::iterator, bool> stdPair;

        std::cout << "Insert(value):" << std::endl;
        ftPair = a.insert(ft::make_pair(0, "VALUE"));
        stdPair = b.insert(std::make_pair(0, "VALUE"));
        checkValueMap<int, std::string>(b, a);
        (ftPair.second == stdPair.second) && (((*ftPair.first).first) == (*(stdPair.first)).first) ? msgOk(
                "Return value") : msgFail("Return value");

        std::cout << "Insert(position)" << std::endl;
        ft_it = a.insert(a.end(), ft::make_pair(1, "Position"));
        std_it = b.insert(b.end(), std::make_pair(1, "Position"));
        checkValueMap<int, std::string>(b, a);
        (*ft_it).first == (*std_it).first ? msgOk("Return value") : msgFail("Return value");

        std::cout << "Insert(range)" << std::endl;
        ft::map<int, std::string> a1;
        std::map<int, std::string> b1;
        a1.insert(ft::make_pair(2, "LOLO"));
        a1.insert(ft::make_pair(3, "kawai"));
        b1.insert(std::make_pair(2, "LOLO"));
        b1.insert(std::make_pair(3, "kawai"));
        a.insert(a1.begin(), a1.end());
        b.insert(b1.begin(), b1.end());
        checkValueMap(b, a);

        std::cout << "Find:" << std::endl;
        a1.find(3)->second == b1.find(3)->second ? msgOk("Value") : msgFail("Value");

        std::cout << "Count:" << std::endl;
        a1.count(2) == b1.count(2) ? msgOk("Value") : msgFail("Value");

        std::cout << "Erase(position):" << std::endl;
        a.erase(a.begin());
        b.erase(b.begin());
        checkValueMap(b, a);

        std::cout << "Erase(key):" << std::endl;
        a.erase(3);
        b.erase(3);
        checkValueMap(b, a);

        std::cout << "Erase(iterators):" << std::endl;
        a.erase(a.begin(), a.end());
        b.erase(b.begin(), b.end());
        checkValueMap(b, a);
    }
    {
        std::cout << "Swap:" << std::endl;
        ft::map<int, std::string> ft1;
        ft::map<int, std::string> ft2;
        std::map<int, std::string> std1;
        std::map<int, std::string> std2;
        ft1.insert(ft::make_pair(2, "First"));
        ft1.insert(ft::make_pair(3, "SECOND"));

        std1.insert(std::make_pair(2, "First"));
        std1.insert(std::make_pair(3, "SECOND"));

        ft2.insert(ft::make_pair(2, "THIRD"));
        ft2.insert(ft::make_pair(3, "fourth"));

        std2.insert(std::make_pair(2, "THIRD"));
        std2.insert(std::make_pair(3, "fourth"));
        ft1.swap(ft2);
        std1.swap(std2);
        ft1.begin()->second == std1.begin()->second ? msgOk("Value") : msgFail("Value");

        std::cout << "Clear:" << std::endl;
        ft1.clear();
        std1.clear();
        checkValueMap(std1, ft1);
    }
    {
        ft::map<int, std::string> ft;
        std::map<int, std::string> std;
        ft.insert(ft::make_pair(1, "10"));
        ft.insert(ft::make_pair(2, "20"));
        ft.insert(ft::make_pair(3, "30"));
        ft.insert(ft::make_pair(4, "40"));
        ft.insert(ft::make_pair(5, "50"));
        std.insert(std::make_pair(1, "10"));
        std.insert(std::make_pair(2, "20"));
        std.insert(std::make_pair(3, "30"));
        std.insert(std::make_pair(4, "40"));
        std.insert(std::make_pair(5, "50"));

        std::cout << "Lower:" << std::endl;
        ft.lower_bound(2)->second == std.lower_bound(2)->second ? msgOk("Value") : msgFail("Value");

        std::cout << "Upper:" << std::endl;
        ft.upper_bound(2)->second == std.upper_bound(2)->second ? msgOk("Value") : msgFail("Value");

        std::cout << "Equal_range:" << std::endl;
        ft.equal_range(4).first->first == std.equal_range(4).first->first &&
                ft.equal_range(4).first->second == std.equal_range(4).first->second &&
                ft.equal_range(4).second->first == std.equal_range(4).second->first &&
                ft.equal_range(4).second->second == std.equal_range(4).second->second
                ? msgOk("Value") : msgFail("Value");
    }
    {
        ft::map<int, int> ft;
        std::map<int, int> std;
        std::cout << "Element access map[k]:" << std::endl;
        ft[3] = 10;
        std[3] = 10;
        ft[3] == std[3] ? msgOk("Value") : msgFail("Value");
    }
    {
        std::cout << "is_integral:" << std::endl;
        ft::is_integral<int>().value == std::is_integral<int>().value ? msgOk("int") : msgFail("int");
        ft::is_integral<float>().value == std::is_integral<float>().value ? msgOk("float") : msgFail("float");
        ft::is_integral<bool>().value == std::is_integral<bool>().value ? msgOk("bool") : msgFail("bool");
    }

}