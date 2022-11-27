cmake_minimum_required(VERSION 3.8)

project(RNADecoder VERSION 1.0.0)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

include (scripts/clang-format.cmake)

set(SOURCES
    main.cpp
)

list(TRANSFORM SOURCES PREPEND ${PROJECT_SOURCE_DIR}/src/)

add_executable(${PROJECT_NAME} ${SOURCES})
