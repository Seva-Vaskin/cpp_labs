cmake_minimum_required(VERSION 3.16)
project(lab-14_linq)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_link_options("-fsanitize=address")
#add_link_options("-fsanitize=leak")
#add_link_options("-fsanitize=undefined")
#add_compile_options("-fsanitize=address")
#add_compile_options("-fsanitize=leak")
#add_compile_options("-fsanitize=undefined")

include_directories(../include)

add_executable(lab-14_linq
        main.cpp
        )
