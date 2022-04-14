#include "../vector.hpp"
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

class Person {
public:
    std::string name;

    Person(const std::string& name = "COLOR_DEFAULT name") :
            name(name) {}
};

int test_range_constructor();


template<class T>
int helper(T first, T second) {
    return first != second;
}

void print_format(const std::string& code, const std::string& msg) {
    std::cout << code << msg << COLOR_DEFAULT << std::endl;
}

void print_status(int status) {
    if (status)
        print_format(RED, "WRONG");
    else
        print_format(GREEN, "OK");
}

template<typename T>
int check_cap_size(bool debug, const ft::vector<T>& my, const std::vector<T>& orig) {
    if (debug)
        std::cout << "capacity" << std::endl;
    if (helper(my.capacity(), orig.capacity()))
        return EXIT_FAILURE;
    if (debug)
        std::cout << "size" << std::endl;
    if (helper(my.size(), orig.size()))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


int test_default_constructor(bool debug = false) {
    std::cout << "COLOR_DEFAULT CONSTRUCTOR() " << std::endl;
    if (debug) {

    }
    {
        std::vector<int> orig;
        ft::vector<int> my;

        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
    }
    {
        std::vector<int>* orig = new std::vector<int>();
        ft::vector<int>* my = new ft::vector<int>();

        if (helper(my->capacity(), orig->capacity()))
            return EXIT_FAILURE;
        if (helper(my->size(), orig->size()))
            return EXIT_FAILURE;
        delete orig;
        delete my;
    }
    return EXIT_SUCCESS;
}


int test_fill_constructor(bool debug = false) {
    std::cout << "FILL CONSTRUCTOR() " << std::endl;
    {
        std::vector<int> orig(3);
        ft::vector<int> my(3);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "initialization primitive" << GREEN << " OK" << COLOR_DEFAULT << std::endl;
    }
    {
        std::vector<Person> orig(3);
        ft::vector<Person> my(3);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "initialization objects" << GREEN << " OK" << COLOR_DEFAULT << std::endl;
    }
    {
        if (debug)
            std::cout << "IN HEAP" << std::endl;
        std::vector<Person>* orig = new std::vector<Person>(3);
        ft::vector<Person>* my = new ft::vector<Person>(3);
        if (helper(my->capacity(), orig->capacity()))
            return EXIT_FAILURE;
        if (helper(my->size(), orig->size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "initialization objects" << GREEN << " OK" << COLOR_DEFAULT << std::endl;
        delete my;
        delete orig;
    }
    return EXIT_SUCCESS;
}


int test_push_back() {
    std::cout << "PUSH_BACK()" << std::endl;

    std::vector<int> orig;
    ft::vector<int> my;

    if (helper(my.capacity(), orig.capacity()))
        return EXIT_FAILURE;
    if (helper(my.size(), orig.size()))
        return EXIT_FAILURE;

    orig.push_back(22);
    orig.push_back(22);
    orig.push_back(22);

    my.push_back(22);
    my.push_back(22);
    my.push_back(22);

    if (helper(my.capacity(), orig.capacity()))
        return EXIT_FAILURE;
    if (helper(my.size(), orig.size()))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


int test_max_size() {
    std::cout << "MAX_SIZE()" << std::endl;
    std::vector<int> orig;
    ft::vector<int> my;

    if (helper(my.max_size(), orig.max_size()))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}


int test_resize(bool debug = false) {
    std::cout << "RESIZE()" << std::endl;

    {
        std::vector<int> orig;
        ft::vector<int> my;

        orig.resize(0);
        my.resize(0);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "empty vector par = 5" << std::endl;
    }
    {
        std::vector<int> orig;
        ft::vector<int> my;

        orig.resize(10);
        my.resize(10);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "increase" << std::endl;

        orig.resize(5);
        my.resize(5);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "decrease" << std::endl;
    }
    {
        std::vector<int> orig(7, 90);
        ft::vector<int> my(7, 90);

        orig.resize(10);
        my.resize(10);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "increase" << std::endl;

        orig.resize(5);
        my.resize(5);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "decrease" << std::endl;
    }
    return EXIT_SUCCESS;
}


int vec_reserve(bool debug = false) {
    std::cout << "RESERVE() " << std::endl;
    {
        std::vector<int> orig;
        ft::vector<int> my;

        orig.reserve(5);
        my.reserve(5);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug) {
            std::cout << "vector<int>:" << std::endl << "TEST 1" << std::endl;
            std::cout << "empty vector, reserve for 5 " << GREEN << "OK" << COLOR_DEFAULT << std::endl;
        }
    }
    {
        std::vector<int> orig(5);
        ft::vector<int> my(5);

        orig.reserve(5);
        my.reserve(5);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "vector size 5 reserve for 5 " << GREEN << "OK" << COLOR_DEFAULT << std::endl;
    }
    {
        if (debug)
            std::cout << "vector<int>(5):" << std::endl;
        ft::vector<int> my(5);
        std::vector<int> orig(5);

        orig.reserve(6);
        my.reserve(6);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "vector size 5 reserve for 6 " << GREEN << "OK" << COLOR_DEFAULT << std::endl;
    }
    {
        if (debug)
            std::cout << "vector<Person>:" << std::endl;
        ft::vector<Person> my(5);
        std::vector<Person> orig(5);

        orig.reserve(6);
        my.reserve(6);
        if (helper(my.capacity(), orig.capacity()))
            return EXIT_FAILURE;
        if (helper(my.size(), orig.size()))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "vector size 5, reserve for 6 " << GREEN << "OK" << COLOR_DEFAULT << std::endl;
    }
    return EXIT_SUCCESS;
}


int vec_assign(bool debug = true) {
    std::cout << "ASSIGN()" << std::endl;
    {
        if (debug)
            std::cout << "vector<int> " << std::endl;

        ft::vector<int> my;
        std::vector<int> orig;

        orig.assign(3, 8);
        my.assign(3, 8);

        if (check_cap_size(debug, my, orig))
            return EXIT_FAILURE;
        if (debug)
            std::cout << "empty vector assign for 3 " << GREEN << "OK" << COLOR_DEFAULT << std::endl;
        if (debug)
            std::cout << "equals elements" << std::endl;

        std::vector<int> orig1;
        orig1.assign(3, 8);
        if (orig1[1] != orig[1])
            return EXIT_FAILURE;

        if (debug)
            std::cout << "equals elements" << std::endl;
        if (my[1] != orig[1])
            return EXIT_FAILURE;

    }
    return EXIT_SUCCESS;
}

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

template<class vector1, class vector2>
void checkValue(const std::vector<vector1>& stdVector, const ft::vector<vector2>& ftVector) {
    stdVector.size() == ftVector.size() ? msgOk("Size") : msgFail("Size");
    stdVector.capacity() == ftVector.capacity() ? msgOk("Capacity") : msgFail("Capacity");
    cout << "std: " << stdVector.capacity() << "   ft: " << ftVector.capacity() << endl;
    for (size_t i = 0; i < stdVector.size(); ++i) {
        if (stdVector[i] != ftVector[i]) {
            msgFail("Value");
            return;
        }
    }
    msgOk("Value");
}

void vec_modifiers() {
    std::cout << "Modifiers:" << std::endl;
    ft::vector<int> ft_f;
    std::vector<int> std_f;
    ft_f.push_back(1);
    ft_f.push_back(2);
    ft_f.push_back(3);
    ft_f.push_back(4);
    ft_f.push_back(5);
    std_f.push_back(1);
    std_f.push_back(2);
    std_f.push_back(3);
    std_f.push_back(4);
    std_f.push_back(5);
    ft::vector<int>::iterator ft_it = ft_f.begin();
    ft::vector<int>::iterator ft_it2 = ft_f.begin();
    std::vector<int>::iterator std_it = std_f.begin();
    std::vector<int>::iterator std_it2 = std_f.begin();

    *(++ft_it) == *(++std_it) ? msgOk("++Operator") : msgFail("++Operator");
    *(ft_it++) == *(std_it++) ? msgOk("Operator++") : msgFail("Operator++");

    ft_it = ft_f.begin();
    std_it = std_f.begin();
    *ft_it = 10;
    *std_it = 10;
    *ft_it == *std_it ? msgOk("Operator*=") : msgFail("Operator*=");

    *ft_it++;
    *std_it++;
    *ft_it = 20;
    *std_it = 20;
    *ft_it == *std_it ? msgOk("Operator*++") : msgFail("Operator*++");
    *(ft_it + 1) == *(std_it + 1) ? msgOk("Operator +") : msgFail("Operator +");
    *(1 + ft_it) == *(1 + std_it) ? msgOk("+ Operator") : msgFail("+ Operator");
    *(ft_it - 1) == *(std_it - 1) ? msgOk("Operator -") : msgFail("Operator -");
    (ft_it - ft_it2) == (std_it - std_it2) ? msgOk("Operator - it") : msgFail("Operator - it");
    *(ft_it += 1) == *(std_it += 1) ? msgOk("Operator +=") : msgFail("Operator +=");
    *(ft_it -= 1) == *(std_it -= 1) ? msgOk("Operator -=") : msgFail("Operator -=");
    ft_it[1] == std_it[1] ? msgOk("Operator []") : msgFail("Operator []");

    std::cout << "Check containers after vec_modifiers:" << std::endl;
    checkValue(std_f, ft_f);
}

void vec_iterators() {
    std::cout << std::endl << "==== Iterators ====" << std::endl << std::endl;
    std::cout << "Get Iterators:" << std::endl;
    std::vector<int> std_1;
    ft::vector<int> ft_1;
    std_1.push_back(1);
    std_1.push_back(2);
    std_1.push_back(3);
    ft_1.push_back(1);
    ft_1.push_back(2);
    ft_1.push_back(3);
    ft_1.capacity() == std_1.capacity() ? msgOk("capac ok") : msgFail("capac Fail");
    *ft_1.begin() == *std_1.begin() ? msgOk("begin()") : msgFail("begin()");
    *(ft_1.end() - 1) == *(std_1.end() - 1) ? msgOk("end()") : msgFail("end()");
    *ft_1.rbegin() == *std_1.rbegin() ? msgOk("rbegin()") : msgFail("rbegin()");
    *(ft_1.rend() - 1) == *(std_1.rend() - 1) ? msgOk("rend()") : msgFail("rend()");
}

void vec_iter_relational() {
    std::cout << "Iterator relational operators:" << std::endl;
    ft::vector<int> ft_e(5, 10);
    ft::vector<int>::iterator iter1 = ft_e.begin();
    ft::vector<int>::iterator iter2 = ft_e.begin();
    ft::vector<int>::iterator iter3 = ft_e.end();
    iter1 == iter2 ? msgOk("Operator ==") : msgFail("Operator ==");
    iter1 != iter3 ? msgOk("Operator !=") : msgFail("Operator !=");
    iter3 > iter1 ? msgOk("Operator >") : msgFail("Operator >");
    iter2 >= iter1 ? msgOk("Operator >=") : msgFail("Operator >=");
    iter1 < iter3 ? msgOk("Operator <") : msgFail("Operator <");
    iter2 <= iter1 ? msgOk("Operator <=") : msgFail("Operator <=");
}

void vec_exceptions() {
    std::cout << "Exceptions test:" << std::endl;
    try {
        std::vector<int> vec(-1, -1);
    }
    catch (std::exception& e) {
        std::cout << "\tCatch: " << e.what() << std::endl;
    }
    try {
        ft::vector<int> bec(-1, -1);
    }
    catch (std::exception& e) {
        std::cout << "\tCatch: " << e.what() << std::endl;
    }
}

int test_range_constructor() {
    std::cout << "RANGE CONSTRUCTOR" << std::endl;
    ft::vector<int> src_ft;
    src_ft.push_back(1);
    src_ft.push_back(2);
    src_ft.push_back(3);

    ft::vector<int>::iterator beg_ft = src_ft.begin();
    ft::vector<int>::iterator end_ft = src_ft.end();

    ft::vector<int> ft_stack(beg_ft, end_ft);

    ft::vector<int>* ft_heap = new ft::vector<int>(beg_ft, end_ft);

    std::vector<int> src_std;
    src_std.push_back(1);
    src_std.push_back(2);
    src_std.push_back(3);
    std::vector<int>::iterator beg_std = src_std.begin();
    std::vector<int>::iterator end_std = src_std.end();

    std::vector<int> std_stack(beg_std, end_std);

    std::vector<int>* std_heap = new std::vector<int>(beg_std, end_std);

    if (helper(ft_stack.size(), std_stack.size())) {
        msgFail("RANGE CONSTRUCTOR size stack");
        return EXIT_FAILURE;
    }
    if (helper(ft_stack.capacity(), std_stack.capacity())) {
        msgFail("RANGE CONSTRUCTOR capacity stack");
        return EXIT_FAILURE;
    }
    if (helper(ft_heap->size(), std_heap->size())){
        msgFail("RANGE CONSTRUCTOR size heap");
        return EXIT_FAILURE;
    }
    if (helper(ft_heap->capacity(), std_heap->capacity())){
        msgFail("RANGE CONSTRUCTOR capacity heap");
        return EXIT_FAILURE;
    }
    delete ft_heap;
    delete std_heap;
    return EXIT_SUCCESS;
}


void vec_swap() {
    std::cout << "Swap:" << std::endl;
    std::vector<int> std_k(10, 1);
    std::vector<int> std_k1(5, 2);
    ft::vector<int> ft_k(10, 1);
    ft::vector<int> ft_k1(5, 2);
    std_k.swap(std_k1);
    ft_k.swap(ft_k1);
    checkValue(std_k, ft_k);
    std::cout << "Swap(no member):" << std::endl;
    std::swap(ft_k, ft_k1);
    swap(std_k, std_k1);
    checkValue(std_k, ft_k);
}

void vec_relational_operators() {
    std::cout << "Operators:" << std::endl;
    std::vector<int> std_l(10, 1);
    std::vector<int> std_l1(5, 2);
    ft::vector<int> ft_l(10, 1);
    ft::vector<int> ft_l1(5, 2);
    (ft_l == ft_l1) == (std_l == std_l1) ? msgOk("Operator ==") : msgFail("Operator ==");
    (ft_l != ft_l1) == (std_l != std_l1) ? msgOk("Operator !=") : msgFail("Operator !=");
    (ft_l < ft_l1) == (std_l < std_l1) ? msgOk("Operator <") : msgFail("Operator <");
    (ft_l <= ft_l1) == (std_l <= std_l1) ? msgOk("Operator <=") : msgFail("Operator <=");
    (ft_l > ft_l1) == (std_l > std_l1) ? msgOk("Operator >") : msgFail("Operator >");
    (ft_l >= ft_l1) == (std_l >= std_l1) ? msgOk("Operator >=") : msgFail("Operator >=");
}


int main() {
    typedef std::vector<int> sv;
    typedef ft::vector<int> fv;

    cout << "value_type is equal? " << (typeid(sv::value_type) == typeid(fv::value_type) ? TRUE : FALSE) << endl;
    cout << "allocator_type is equal? " << (typeid(sv::allocator_type) == typeid(fv::allocator_type) ? TRUE : FALSE) << endl;
    cout << "reference is equal? " << (typeid(sv::reference) == typeid(fv::reference) ? TRUE : FALSE) << endl;
    cout << "const_reference is equal? " << (typeid(sv::const_reference) == typeid(fv::const_reference) ? TRUE : FALSE) << endl;
    cout << "pointer is equal? " << (typeid(sv::pointer) == typeid(fv::pointer) ? TRUE : FALSE) << endl;
    cout << "const_pointer is equal? " << (typeid(sv::const_pointer) == typeid(fv::const_pointer) ? TRUE : FALSE) << endl;
    cout << "difference_type is equal? " << (typeid(sv::difference_type) == typeid(fv::difference_type) ? TRUE : FALSE) << endl;
    cout << "size_type is equal? " << (typeid(sv::size_type) == typeid(fv::size_type) ? TRUE : FALSE) << endl;
    typedef std::vector<int>::iterator si;
    typedef ft::vector<int>::iterator fi;

    fv vec;

    fv::iterator it = vec.begin();
    fv::const_iterator cit = vec.begin();
    fv::reverse_iterator rit = vec.rbegin();
    fv::const_reverse_iterator crit = vec.rbegin();

    cout << "iterator_type is equal? " << (typeid(si::iterator_type) == typeid(fi::iterator_type) ? TRUE : FALSE) << endl;
    cout << "iterator_category is equal? " << ((typeid(si::iterator_category) == typeid(std::random_access_iterator_tag)) == (typeid(fi::iterator_category) == typeid(ft::random_access_iterator_tag)) ? TRUE : FALSE) << endl;
    cout << "value_type is equal? " << (typeid(si::value_type) == typeid(fi::value_type) ? TRUE : FALSE) << endl;
    cout << "difference_type is equal? " << (typeid(si::difference_type) == typeid(fi::difference_type) ? TRUE : FALSE) << endl;
    cout << "pointer is equal? " << (typeid(si::pointer) == typeid(fi::pointer) ? TRUE : FALSE) << endl;
    cout << "reference is equal? " << (typeid(si::reference) == typeid(fi::reference) ? TRUE : FALSE) << endl;

    sv sv1;
    sv sv2(10);
    sv sv3(sv2.begin(), sv2.end());
    fv fv1;
    fv fv2(10);
    fv fv3(sv2.begin(), sv2.end());

    cout << "constructor is equal? " << ((sv1.size() == fv1.size() && sv2.size() == fv2.size() && sv3.size() == fv3.size() && sv1.capacity() == fv1.capacity() && sv2.capacity() == fv2.capacity() && sv3.capacity() == fv3.capacity()) ? TRUE : FALSE) << endl;
//    cout << "size is equal? " << (st1.size() == st2.size() ? TRUE : FALSE) << endl;
//    cout << "operator== is equal? " << ((st1 == st11) == (st2 == st22) ? TRUE : FALSE) << endl;
//    cout << "operator!= is equal? " << ((st1 != st11) == (st2 != st22) ? TRUE : FALSE) << endl;
//    cout << "operator<= is equal? " << ((st1 <= st11) == (st2 <= st22) ? TRUE : FALSE) << endl;
//    cout << "operator> is equal? " << ((st1 > st11) == (st2 > st22) ? TRUE : FALSE) << endl;
//    cout << "operator< is equal? " << ((st1 < st11) == (st2 < st22) ? TRUE : FALSE) << endl;
//    cout << "operator>= is equal? " << ((st1 >= st11) == (st2 >= st22) ? TRUE : FALSE) << endl;


    std::cout << "Empty constructor:" << std::endl;
    ft::vector<int> ft_a;
    std::vector<int> std_a;
    ft_a.empty() == std_a.empty() ? msgOk("Empty()") : msgFail("Empty()");
    checkValue(std_a, ft_a);

    std::cout << "Fill constructor:" << std::endl;
    ft::vector<int> ft_b(3, 10);
    std::vector<int> std_b(3, 10);
    ft_b.empty() == std_b.empty() ? msgOk("Empty()") : msgFail("Empty()");
    checkValue(std_b, ft_b);

    std::cout << "Range constructor:" << std::endl;
    ft::vector<int> ft_b1(ft_b.begin(), ft_b.end());
    std::cout << "FT" << std::endl;
    std::vector<int> std_b1(std_b.begin(), std_b.end());
    ft_b1.empty() == std_b1.empty() ? msgOk("Empty()") : msgFail("Empty()");
    checkValue(std_b1, ft_b1);

    std::cout << "Copy constructor:" << std::endl;
    ft::vector<int> ft_b2(ft_b);
    std::vector<int> std_b2(std_b);
    ft_b1.empty() == std_b1.empty() ? msgOk("Empty()") : msgFail("Empty()");
    checkValue(std_b1, ft_b1);

    std::cout << "Allocator:" << std::endl;
    ft_b.get_allocator() == std_b.get_allocator() ? msgOk("Get Allocator") : msgFail("Get Allocator");

    std::cout << "max capacity:" << std::endl;
    ft_b.max_size() == std_b.max_size() ? msgOk("Max capacity") : msgFail("Max capacity");

    std::cout << "Reserve:" << std::endl;
    ft_b.reserve(230000000);
    std_b.reserve(230000000);
    checkValue(std_b, ft_b);

    std::cout << "Resize:" << std::endl;
    std::cout << "  - small:" << std::endl;
    ft_b.resize(10, 14);
    std_b.resize(10, 14);
    checkValue(std_b, ft_b);
    std::cout << "  - big:" << std::endl;
    ft_b.resize(12, 35);
    std_b.resize(12, 35);
    checkValue(std_b, ft_b);

    std::cout << "Push back:" << std::endl;
    ft::vector<int> ft_c;
    std::vector<int> std_c;
    ft_c.push_back(1);
    ft_c.push_back(2);
    ft_c.push_back(3);
    std_c.push_back(1);
    std_c.push_back(2);
    std_c.push_back(3);
    checkValue(std_c, ft_c);

    std::cout << "Pop back:" << std::endl;
    ft_c.pop_back();
    std_c.pop_back();
    checkValue(std_c, ft_c);

    std::cout << "Assign:" << std::endl;
    std::cout << "  - Assign big:" << std::endl;
    std_c.assign(6, 10);
    ft_c.assign(6, 10);
    checkValue(std_c, ft_c);
    std::cout << "  - Assign small:" << std::endl;
    std_c.assign(2, 8);
    ft_c.assign(2, 8);
    checkValue(std_c, ft_c);

    std::cout << "Assign (iterators):" << std::endl;
    ft::vector<int> ft_g(3, 3);
    std::vector<int> std_g(5, 5);
    std::vector<int> std_g1(1, 1);
    ft_g.assign(std_g.begin(), std_g.end());
    checkValue(std_g, ft_g);

    std::cout << "Insert:" << std::endl;
    std::cout << "  - Insert 1:" << std::endl;
    std::vector<std::string> std_i(10, "aboba");
    ft::vector<std::string> ft_i(10, "aboba");
    std_i.insert(std_i.begin() + 5, "hello");
    ft_i.insert(ft_i.begin() + 5, "hello");
    checkValue(std_i, ft_i);
    std::cout << "  - Insert with count:" << std::endl;
    std::cout << "     - small:" << std::endl;
    std_i.insert(std_i.begin() + 5, 12, "hi");
    ft_i.insert(ft_i.begin() + 5, 12, "hi");
    checkValue(std_i, ft_i);
    std::cout << "     - big:" << std::endl;
    std_i.insert(std_i.begin() + 5, 1000, "hi");
    ft_i.insert(ft_i.begin() + 5, 1000, "hi");
    checkValue(std_i, ft_i);
    std::cout << "  - Insert range:" << std::endl;
    std_i.insert(std_i.begin() + 5, std_i.begin(), std_i.end());
    ft_i.insert(ft_i.begin() + 5, ft_i.begin(), ft_i.end());
    checkValue(std_i, ft_i);

    std::cout << "Erase:" << std::endl;
    std::cout << "  - Erase 1" << std::endl;
    std::vector<std::string> std_h;
    std_h.push_back("Hello");
    std_h.push_back("To");
    std_h.push_back("My");
    std_h.push_back("Beautiful");
    std_h.push_back("World");
    std_h.push_back("!");
    std_h.push_back("haha");
    std_h.push_back("hoho");
    ft::vector<std::string> ft_h;
    ft_h.assign(std_h.begin(), std_h.end());
    ft_h.erase(ft_h.begin() + 1);
    std_h.erase(std_h.begin() + 1);
    checkValue(std_h, ft_h);
    std::cout << "  - Erase many" << std::endl;
    ft_h.erase(ft_h.begin() + 1, ft_h.begin() + 3);
    std_h.erase(std_h.begin() + 1, std_h.begin() + 3);
    checkValue(std_h, ft_h);

    vec_swap();

    std::cout << "Operator =" << std::endl;
    std::vector<int> std_d;
    ft::vector<int> ft_d;
    std_d = std_c;
    ft_d = ft_c;
    checkValue(std_d, ft_d);

    std::cout << "Clear:" << std::endl;
    std_c.clear();
    ft_c.clear();
    checkValue(std_c, ft_c);

    vec_relational_operators();

    vec_iterators();
    vec_iter_relational();
    vec_modifiers();
    vec_exceptions();



}