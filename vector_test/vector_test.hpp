#ifndef VECTOR_TEST_HPP
#define VECTOR_TEST_HPP

#include <vector>
#include <iostream>
#include <sys/time.h>
#include "../vector.hpp"
#include "var.hpp"

# define BGREEN		string("\033[1;32m")
# define BYELLOW	"\033[1;33m"
# define BRED		string("\033[1;31m")
# define RESET		"\033[0m"

using std::vector;
using std::cout;
using std::endl;
using std::string;

template <typename T1, typename T2>
bool veccmp(T1 v1, T2 v2) {
    if (v1.size() != v2.size() || v1.capacity() != v2.capacity())
        return false;
    for (int i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

template <typename T1, typename T2>
bool veccmp(T1* v1, T2* v2) {
    if (v1->size() != v2->size() || v1->capacity() != v2->capacity())
        return false;
    for (int i = 0; i < v1->size(); ++i) {
        if ((*v1)[i] != (*v2)[i])
            return false;
    }
    return true;
}



void run_vector_test();
bool constructor_vector();


#endif
