cmake_minimum_required(VERSION 3.21)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(ft_containers
        map.hpp
        utility.hpp
        node.hpp
#        stack.hpp
#        vector.hpp
#        vector_test/assign.cpp
#        vector_test/capacity.cpp
#        vector_test/destructor.cpp
#        vector_test/front.cpp
#        vector_test/operator=.cpp
#        vector_test/push_back.cpp
#        vector_test/resize.cpp
#        vector_test/vector_test.hpp
#        vector_test/var.hpp
#        vector_test/at.cpp
#        vector_test/clear.cpp
#        vector_test/empty.cpp
#        vector_test/get_allocator.cpp
#        vector_test/operator[].cpp
#        vector_test/rbegin.cpp
#        vector_test/run_tests.cpp
#        vector_test/back.cpp
#        vector_test/constructor.cpp
#        vector_test/end.cpp
#        vector_test/insert.cpp
#        vector_test/operators.cpp
#        vector_test/rend.cpp
#        vector_test/size.cpp
#        vector_test/begin.cpp
#        vector_test/data.cpp
#        vector_test/erase.cpp
#        vector_test/max_size.cpp
#        vector_test/pop_back.cpp
#        vector_test/reserve.cpp
#        vector_test/swap.cpp
        IterMain.cpp
        )
