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
    return 0;
}