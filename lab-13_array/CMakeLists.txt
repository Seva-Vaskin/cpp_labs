cmake_minimum_required(VERSION 3.16)
project(lab-13_array)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_link_options("-fsanitize=address")
#add_link_options("-fsanitize=leak")
#add_link_options("-fsanitize=undefined")
#add_compile_options("-fsanitize=address")
#add_compile_options("-fsanitize=leak")
#add_compile_options("-fsanitize=undefined")

include_directories(include)

add_executable(lab-13_array
        src/main.cpp
        )
