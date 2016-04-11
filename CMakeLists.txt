cmake_minimum_required(VERSION 3.5)
project(plazza)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

include_directories(include)
set(SOURCE_FILES src/main.cpp include/my.hh)
add_executable(cpp_plazza ${SOURCE_FILES})