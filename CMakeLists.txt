cmake_minimum_required(VERSION 3.21)
project(dataCpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(dataCpp main.cpp chapter2/SqList.cpp chapter2/SeqList.cpp chapter2/LNode.cpp)
