//
// Created by Twycross Redfort on 2/20/22.
//

#include <iostream>
#include <vector>
#include "vector.hpp"

using std::endl;
using std::string;
using std::cout;

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
public:
    int _a;
    string s;

    C(int a) {
        s = "a";
        if (a == -1)
            throw "error";
        _a = a;
    };
};

int main() {
//    std::unique_ptr<B> k2(new B(3));
//    std::unique_ptr<B> k3(new B(4));
//    std::unique_ptr<B> k4(new B(-1));
//
//    ft::vector<A> vecA;
//	ft::vector<B*> vecB;
//
//	vecB.push_back(&(*k2));
//	vecB.push_back(&(*k2));
//	vecB.push_back(&(*k2));
//    vecA.insert(vecA.begin(), vecB.begin(), vecB.end());
//    vecB.push_back(&(*k3));
//    vecB.push_back(&(*k4));

//	vecA.reserve(5);
//	cout << "size: " << vecA.size() << endl;
//	cout << "capacity: " << vecA.capacity() << endl;
//	try {
//        vecA.insert(vecA.begin(), vecB.begin(), vecB.end());
////        vecA.push_back(A(new B(1)));
////        vecA.insert(vecA.begin(), vecB.begin(), vecB.end());
//		cout << "***OK***" << endl;
//		cout << "size: " << vecA.size() << endl;
//		cout << "capacity: " << vecA.capacity() << endl;
//	} catch (...) {
//		cout << "***exception***" << endl;
//		cout << "size: " << vecA.size() << endl;
//		cout << "capacity: " << vecA.capacity() << endl;
//	}
//    std::vector<C> v1;
//    std::vector<C> v2;
////    v.reserve(10);
//    v1.push_back(C(1));
//    v1.push_back(C(2));
//    v1.push_back(C(3));
//
//    cout << "---size: " << v1.size() << "  ";
//    cout << "capacity: " << v1.capacity() << endl;
//    for (int i = 0; i < v1.size(); ++i) {
//        cout << "value[" << i << "]= " << v1[i]._a << endl;
//    }
//
//    v1.insert(v1.begin() + 2, 3, 5);
//
//    cout << "---size: " << v1.size() << "  ";
//    cout << "capacity: " << v1.capacity() << endl;
//    for (int i = 0; i < v1.size(); ++i) {
//        cout << "value[" << i << "]= " << v1[i]._a  << " " << v1[i].s << endl;
//    }
//    int x = 1000;
////    std::vector<int> tmp;
//    try { ft::vector<int> tmp5(-1, -1); }
//    catch (std::exception &e) {
//        cout << "exception" << endl;
//    }
//    ft::vector<int> vector;
////    tmp.assign(2600 * x, 1);
////    vector.assign(2200 * x, 1);
////    cout << "size: " << vector.size() << "  ";
////    cout << "capacity: " << vector.capacity() << endl;
////    vector.insert(vector.end() - 1400 * x, tmp.begin(), tmp.end());
//    cout << "size: " << vector.size() << "  ";
//    cout << "capacity: " << vector.capacity() << endl;

//    std::vector<int>::iterator it;
//    *it = 1;
//    cout << *it << endl;
//    it.base()
    ft::vector<int> ft;
    for (int i = 1; i < 6; ++i)
        ft.push_back(i);
    std::vector<int> std;
    for (int i = 1; i < 6; ++i)
        std.push_back(i);

    std::vector<int>::const_reverse_iterator it_std = std.rbegin();
    std::vector<int>::const_reverse_iterator ite_std = std.rend();
    ft::vector<int>::const_reverse_iterator it_ft = ft.rbegin();
    ft::vector<int>::const_reverse_iterator ite_ft = ft.rend();

    for (; it_std != ite_std ; ++it_std) {
        cout << *it_std << endl;
//        *it_std = 0;
    }

    cout << endl;
    for (; it_ft != ite_ft ; ++it_ft) {
        cout << *it_ft << endl;
//        *it_ft = 0;
    }

	return 0;
}
