#include "map.hpp"
#include <map>

using std::string;
using std::cout;
using std::endl;

int main()
{
    typedef std::map<int, string> st;
    typedef ft::map<int, string> f;
    st m1;
//    f f1;
//    m1.get_allocator();
//    f1.get_allocator();
//
//    s::value_type::first_type sptr(10);
//    f::value_type::first_type fptr(sptr);
//    s::value_type::second_type se("10");
//    f::value_type::second_type fe(se);
//    s::pointer p;
//    s::const_pointer cp;
////    cp->first;
//    f::const_pointer cp1;
////    cp1->first;
//    s::size_type size(-1);
//    cout << "size= " << size << endl;
//    f::size_type size1(-1);
//    cout << "size= " << size1 << endl;
//    f::reference ref1();
////    f::value_type fptr;
////    sptr.;
////    fptr.;
    cout << "pointer equal: " << (sizeof(st::pointer) == sizeof(f::pointer)) << endl;
    cout << "const_pointer equal: " << (sizeof(st::const_pointer) == sizeof(f::const_pointer)) << endl;
    cout << "size_type equal: " << (sizeof(st::size_type) == sizeof(f::size_type)) << endl;
    cout << "difference_type equal: " << (sizeof(st::difference_type) == sizeof(f::difference_type)) << endl;
    cout << "reference equal: " << (sizeof(st::reference) == sizeof(f::reference)) << endl;
    cout << "const_reference equal: " << (sizeof(st::const_reference) == sizeof(f::const_reference)) << endl;
    cout << "key_type equal: " << (sizeof(st::key_type) == sizeof(f::key_type)) << endl;
    cout << "key_compare equal: " << (sizeof(st::key_compare) == sizeof(f::key_compare)) << endl;
    cout << "mapped_type equal: " << (sizeof(st::mapped_type) == sizeof(f::mapped_type)) << endl;
    cout << "value_type equal: " << (sizeof(st::value_type) == sizeof(f::value_type)) << endl;
    cout << "allocator_type equal: " << (sizeof(st::allocator_type) == sizeof(f::allocator_type)) << endl;
    std::map<int, string> m2;
    m1.insert(std::pair<int, string>(1, "A"));
    m1.insert(std::make_pair(2, "B"));
    m1.insert(std::make_pair(3, "C"));
    m1.insert(std::make_pair(4, "D"));
    m1.insert(std::make_pair(5, "E"));
    m1.insert(std::make_pair(6, "F"));
    for (std::map<int, string>::iterator it = m1.begin(), ite = m1.end(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
        it->second = "777";
    }
    for (std::map<int, string>::const_iterator it = m1.begin(), ite = m1.end(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
//        it->second = "777";
    }
    for (std::map<int, string>::reverse_iterator it = m1.rbegin(), ite = m1.rend(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
        it->second = "777";
    }
    for (std::map<int, string>::const_reverse_iterator it = m1.rbegin(), ite = m1.rend(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
//        it->second = "777";
    }
    cout << "size= " << m1.size() << endl << endl;

    ft::map<int, string> f1;
    ft::map<int, string> f2;
    f1.insert(ft::pair<int, string>(1, "A"));
    f1.insert(f1.begin(), ft::make_pair(2, "B"));
    f1.insert(f2.end(), ft::make_pair(3, "C"));
    f1.insert(ft::make_pair(4, "D"));
    f1.insert(ft::make_pair(5, "E"));
    f1.insert(ft::make_pair(6, "F"));
    for (ft::map<int, string>::iterator it = f1.begin(), ite = f1.end(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
        it->second = "777";
    }
    for (ft::map<int, string>::const_iterator it = f1.begin(), ite = f1.end(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
//        it->second = "777";
    }
    for (ft::map<int, string>::reverse_iterator it = f1.rbegin(), ite = f1.rend(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
        it->second = "777";
    }
    for (ft::map<int, string>::const_reverse_iterator it = f1.rbegin(), ite = f1.rend(); it!=ite; ++it) {
        cout << "key=" << it->first << " value=" << it->second << endl;
//        it->first = 777;
//        it->second = "777";
    }
//    cout << "size= " << f1.size() << endl << endl;
//    cout << "lower_bound " << endl;
//    cout << "std = " << m1.lower_bound(3)->second << endl;
//    cout << "ft = " << f1.lower_bound(3)->second << endl;
//
//    cout << "upper_bound " << endl;
//    cout << "std = " << m1.upper_bound(3)->second << endl;
//    cout << "ft = " << f1.upper_bound(3)->second << endl;
//
//    cout << "std iterator category " << ((typeid(std::map<int, string>::iterator::iterator_category)) == (typeid(std::bidirectional_iterator_tag) )) << endl;
//    cout << "ft iterator category " << ((typeid(ft::map<int, string>::iterator::iterator_category)) == (typeid(ft::bidirectional_iterator_tag) )) << endl;
    std::map<int, string> s;
    cout << "count " << s.count(0) << endl;

//    ft::map<int, string> f;
//    cout << "count " << f.count(0) << endl;

    ft::map<int, int> mp;

    mp.insert(ft::make_pair(10, 10));
    mp.insert(ft::make_pair(20, 20));
    mp.insert(ft::make_pair(30, 30));
    mp.insert(ft::make_pair(40, 40));
    mp.insert(ft::make_pair(50, 50));
    mp.insert(ft::make_pair(60, 60));
    const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair = mp.equal_range(10);
    ft::map<int, int> map;
    ft::map<int, int>::reverse_iterator rit = map.rbegin();
//    rit->
    std::map<int, int> std;
    std::map<int, int>::reverse_iterator srit = std.rbegin();
    return 0;
}
