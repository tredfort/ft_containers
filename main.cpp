#include <iostream>
//#include <vector>
//#include "vector.hpp"
#include "map.hpp"
#include <map>
#include <sys/time.h>

using std::string;
using std::endl;
using std::cout;

template <typename T>
void print(T* vector) {
    cout << "size: " << vector->size() << endl;
    cout << "capacity: " << vector->capacity() << endl;
}

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};


class C {
    typedef struct s_array {
        char* _ptr;
        int _size;
        int _capacity;
        s_array(char* ptr, int size, int capacity) : _ptr(ptr), _size(size), _capacity(capacity) {};
    } t_array;
public:
    t_array array;
    C() : array(nullptr, 1, 2) {
//        array(nullptr, 1, 2);
    };

};

time_t timer() {
    struct timeval start = {};
    gettimeofday(&start, nullptr);
    time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
    return msecs_time;
}


int main() {
//    ft::vector<int> v = ft::vector<int>();
//    cout << "size: " << v._array._size << endl;
//    cout << "capacity: " << v._array._capacity << endl;

//    std::vector<int>* std = new std::vector<int>();
//    std->resize(7);
//    print(std);
//    ft::vector<int>* ft = new ft::vector<int>();
//    ft->resize(7);
//    print(ft);

//int _ratio = 10000;
//    ft::vector<int> vector;
//    std::vector<int> v;
//    vector.assign(9900 * _ratio, 1);
//    vector.resize(5000 * _ratio);
//    vector.reserve(5000 * _ratio);
//    v.push_back(vector.size());
//    v.push_back(vector.capacity());
//    vector.resize(7000 * _ratio);
//    v.push_back(vector.size());
//    v.push_back(vector.capacity());
//    vector.resize(15300 * _ratio, T());
//    v.push_back(vector.size());
//    v.push_back(vector.capacity());
//    v.push_back(vector[65]);
//    print(&v);
//    print(&vector);

//    ft::vector<int> v;
//    cout << "size v: " << v.size() << endl;
//    cout << "size v: " << v.capacity() << endl;
//    v.insert(v.begin(), 1);
//    cout << "size v: " << v.size() << endl;
//    cout << "size v: " << v.capacity() << endl;

//    ft::vector<int>vector;
//    ft::vector<int> v;
//    vector.assign(2600 * 1000, 1);
//    v.push_back(*(vector.insert(vector.end() - 800 * 1000, 44)));
//    v.push_back(vector.size());
//    v.push_back(vector.capacity());
//    std::unique_ptr<B> k2(new B(3));
//    std::unique_ptr<B> k3(new B(4));
//    std::unique_ptr<B> k4(new B(-1));
//    ft::vector<A> vv;
//    ft::vector<B*> v1;
//
//    v1.push_back(&(*k2));
//    v1.push_back(&(*k3));
//    v1.push_back(&(*k4));
//    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
//    catch (...) {
//        cout << "CATCH A!"  << endl;

//    	v.push_back(vv.size());
//    	v.push_back(vv.capacity());
//    }
//    cout << "1 ft:: size: " << vector.size() << " capacity: " << vector.capacity() << endl;
//    cout << "2 ft:: size: " << v.size() << " capacity: " << v.capacity() << endl;

//    std::vector<int> v1(5,5);
//    cout << "size: " << v1.size() << endl;
//    cout << "capacity: " << v1.capacity() << endl;
//    v1.resize(8);
//    cout << "value[7] : " << v1.back() << endl;
//    cout << "size: " << v1.size() << endl;
//    cout << "capacity: " << v1.capacity() << endl;


//    std::vector<int> v;
//    v.reserve(0);
//    v.resize(0);
//    cout << "size: " << v.size() << endl;
//    cout << "capacity: " << v.capacity() << endl;

//
//    std::vector<int> v1;
//    v1.push_back(1);
//    v1.push_back(4);
//    v1.push_back(5);
////    v1.reserve(10);
//    std::vector<int> v2;
//    v2.push_back(2);
//    v2.push_back(3);
//
//    cout << "size: " << v1.size() << endl;
//    cout << "capacity: " << v1.capacity() << endl;
//    for (int i = 0; i < v1.size(); ++i) {
//        cout << "v[" << i << "] = " << v1[i] << endl;
//    }
//    cout << endl;
//    v1.insert(v1.begin() + 1, v2.begin(), v2.end());
//    for (int i = 0; i < v1.size(); ++i) {
//        cout << "v[" << i << "] = " << v1[i] << endl;
//    }
//    cout << "size: " << v1.size() << endl;
//    cout << "capacity: " << v1.capacity() << endl;


//    try { ft::vector<int> tmp5(-1, -1); }
//    catch (std::exception &e) {
//        cout << e.what() << endl;
//    }
//    std::vector<int> std;
//    int x = 10000000;
//    time_t start;
//    for (int i = 0; i < 9 * x; ++i)
//        std.push_back(i);
//    start = timer();
//    std.erase(std.begin() + 10);
//
//    cout << "time: " << timer() - start << endl;
//    cout << "size: " << std.size() << endl;
//    cout << "capacity: " << std.capacity() << endl;
//
//    ft::vector<int> ft;
//    for (int i = 0; i < 9 * x; ++i)
//        ft.push_back(i);
//    start = timer();
//    ft.erase(ft.begin() + 10);
//    cout << "time: " << timer() - start << endl;
//    cout << "size: " << ft.size() << endl;
//    cout << "capacity: " << ft.capacity() << endl;

//    int x = 10000;
//    ft::vector<int> v1;
//    ft::vector<int> v2;
//    ft::vector<int> tmp0(v1);
//    ft::vector<int> tmp(1000 * x, 4), tmp2(1000 * x, 5);
//    tmp = tmp2;
//    ft::vector<int> tmp3(tmp);
//    time_t start = timer();
//    ft::vector<int> tmp4(tmp.begin(), tmp.end());
//    time_t end = timer();
//    v1.push_back(tmp4.size());
//    v1.push_back(tmp4.capacity());
//    v1.push_back(tmp[2]);
//    v1.push_back(tmp3[2]);
//    v1.push_back(tmp4[2]);
//    try { ft::vector<int> tmp5(-1, -1); }
//    catch (std::exception &e) {
//        v1.push_back(1);
//    }

    ft::map<int, string> map;

    return 0;
}
