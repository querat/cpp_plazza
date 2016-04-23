cmake_minimum_required(VERSION 3.5)
project(plazza)

include_directories(include)
set(SOURCE_FILES src/main.cpp include
        src/ChildProcess.cpp src/DataCollector.cpp src/NamedPipe.cpp src/Parser.cpp src/PlazzaNameSpace.cpp src/Plazza.cpp
        src/SafeDeque.cpp src/SubMain.cpp src/ThreadPool.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

add_executable(cpp_plazza ${SOURCE_FILES})