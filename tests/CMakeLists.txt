cmake_minimum_required(VERSION 3.8)

option(TestName "Test name" "")

string(REGEX MATCH ".*\.cpp" CPP_EXT "${TestName}")

if (NOT ${CPP_EXT} STREQUAL "")
    message(ERROR "Name of test has to given without any extention")
endif()

project(${TestName} VERSION 0.0.1)

add_executable(${TestName} ${TestName}.cpp)
