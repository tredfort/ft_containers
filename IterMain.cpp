#include "map.hpp"
#include <map>

using std::string;
using std::cout;
using std::endl;

int main() {

    typedef std::map<int, string>::iterator s;
    typedef ft::map<int, string>::iterator f;

    cout << "pointer equal: " << (sizeof(s::pointer) == sizeof(f::pointer)) << endl;
    cout << "reference equal: " << (sizeof(s::reference) == sizeof(f::reference)) << endl;
    cout << "difference_type equal: " << (sizeof(s::difference_type) == sizeof(f::difference_type)) << endl;
    cout << "value_type equal: " << (sizeof(s::value_type) == sizeof(f::value_type)) << endl;
    cout << "iterator_category equal: " << (sizeof(s::iterator_category) == sizeof(f::iterator_category)) << endl;


    typedef std::map<int, string> sm;
    typedef ft::map<int, string> fm;


    sm sm1;

    std::pair<s, bool> pair = sm1.insert(std::make_pair(1, "hello"));

    fm fm1;
    ft::pair<f, bool> pair = fm1.insert(ft::make_pair(1, "hello"));

    return 0;
}