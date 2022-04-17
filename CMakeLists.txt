cmake_minimum_required(VERSION 3.20.2)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(ft_containers
        map.hpp
        tests/stack.cpp
        )
