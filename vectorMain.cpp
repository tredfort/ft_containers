#include "vector.hpp"
#include <vector>

using std::string;
using std::cout;
using std::endl;

int main()
{
    std::vector<int> s;
    for (int i = 0; i < 3; ++i) {
        s.push_back(i);
    }
    for (std::vector<int>::iterator it = s.begin(), ite = s.end(); it != ite; ++it) {
        cout << *it << endl;
        *it = -1;
    }
    for (std::vector<int>::const_iterator it = s.begin(), ite = s.end(); it != ite; ++it) {
        cout << *it << endl;
    }
    for (std::vector<int>::reverse_iterator it = s.rbegin(), ite = s.rend(); it != ite; ++it) {
        cout << *it << endl;
        *it = -1;
    }
    for (std::vector<int>::const_reverse_iterator it = s.rbegin(), ite = s.rend(); it != ite; ++it) {
        cout << *it << endl;
    }

    cout << "----------" << endl;

    ft::vector<int> f;
    for (int i = 0; i < 3; ++i) {
        f.push_back(i);
    }
    for (ft::vector<int>::iterator it = f.begin(), ite = f.end(); it != ite; ++it) {
        cout << *it << endl;
        *it = -1;
    }
    for (ft::vector<int>::const_iterator it = f.begin(), ite = f.end(); it != ite; ++it) {
        cout << *it << endl;
    }
    for (ft::vector<int>::reverse_iterator it = f.rbegin(), ite = f.rend(); it != ite; ++it) {
        cout << *it << endl;
        *it = -1;
    }
    for (ft::vector<int>::const_reverse_iterator it = f.rbegin(), ite = f.rend(); it != ite; ++it) {
        cout << *it << endl;
    }

}