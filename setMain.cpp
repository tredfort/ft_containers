#include "set.hpp"
#include <set>

using std::string;
using std::cout;
using std::endl;

int main() {
    typedef std::set<int> s;
    typedef ft::set<int> f;

//    cout << "pointer equal: " << (sizeof(s::pointer) == sizeof(f::pointer)) << endl;
//    cout << "const_pointer equal: " << (sizeof(s::const_pointer) == sizeof(f::const_pointer)) << endl;
//    cout << "size_type equal: " << (sizeof(s::size_type) == sizeof(f::size_type)) << endl;
//    cout << "difference_type equal: " << (sizeof(s::difference_type) == sizeof(f::difference_type)) << endl;
//    cout << "reference equal: " << (sizeof(s::reference) == sizeof(f::reference)) << endl;
//    cout << "const_reference equal: " << (sizeof(s::const_reference) == sizeof(f::const_reference)) << endl;
//    cout << "key_type equal: " << (sizeof(s::key_type) == sizeof(f::key_type)) << endl;
//    cout << "key_compare equal: " << (sizeof(s::key_compare) == sizeof(f::key_compare)) << endl;
//    cout << "value_type equal: " << (sizeof(s::value_type) == sizeof(f::value_type)) << endl;
//    cout << "allocator_type equal: " << (sizeof(s::allocator_type) == sizeof(f::allocator_type)) << endl;

    typedef std::set<int>::iterator its;
    typedef ft::set<int>::iterator itf;
    cout << "iterators" << endl;
    cout << "pointer equal: " << (sizeof(its::pointer) == sizeof(itf::pointer)) << endl;
    cout << "reference equal: " << (sizeof(its::reference) == sizeof(itf::reference)) << endl;
    cout << "difference_type equal: " << (sizeof(its::difference_type) == sizeof(itf::difference_type)) << endl;
    cout << "value_type equal: " << (sizeof(its::value_type) == sizeof(itf::value_type)) << endl;
    cout << "iterator_category equal: " << (sizeof(its::iterator_category) == sizeof(itf::iterator_category)) << endl;

//    std::set<int> s1;
//    s1.insert(1);
//    s1.insert(2);
//    s1.insert(3);
//    for (s::iterator it = s1.begin(), ite = s1.end(); it!=ite; ++it) {
//        cout << "key=" << *it << endl;
////        *it = -1;
//    }
//    for (s::const_iterator it = s1.begin(), ite = s1.end(); it!=ite; ++it) {
//        cout << "key=" << *it << endl;
////        *it = -1;
//    }
//    for (s::reverse_iterator it = s1.rbegin(), ite = s1.rend(); it!=ite; ++it) {
//        cout << "key=" << *it << endl;
////        *it = -1;
//    }
//    for (s::const_reverse_iterator it = s1.rbegin(), ite = s1.rend(); it!=ite; ++it) {
//        cout << "key=" << *it << endl;
////        *it = -1;
//    }
//
//    cout << "size= " << s1.size() << endl << endl;

    return 0;
}