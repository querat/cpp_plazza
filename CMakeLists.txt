cmake_minimum_required(VERSION 3.5)
project(plazza)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

include_directories(include)
set(SOURCE_FILES querat_g tmp "tmp/Essaie ouverture FIle/test.cpp" "tmp/Essaie ouverture FIle/test.hh" src/main.cpp include
        src/ChildProcess.cpp src/dataCollector.cpp src/NamedPipe.cpp src/Parser.cpp src/PlazzaNameSpace.cpp src/Plazza.cpp)
add_executable(cpp_plazza ${SOURCE_FILES})