cmake_minimum_required(VERSION 3.16)
project(lab-06_int-vector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(lab-06_int-vector
        src/my_vector.cpp
        src/main.cpp
        )
