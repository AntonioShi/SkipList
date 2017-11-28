cmake_minimum_required(VERSION 3.8)
project(SkipList)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SkipList.h)
add_executable(SkipList ${SOURCE_FILES} SkipList.h)