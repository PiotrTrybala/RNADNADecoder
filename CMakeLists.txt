cmake_minimum_required(VERSION 3.8)

project(RNADecoder VERSION 1.0.0)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

include (scripts/clang-format.cmake)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR}/lib/json/include/)

set(SOURCES
    main.cpp
    engine/CompoundBase.cpp
    engine/DecoderEngine.cpp
)

list(TRANSFORM SOURCES PREPEND ${PROJECT_SOURCE_DIR}/src/)

add_executable(${PROJECT_NAME} ${SOURCES})
