cmake_minimum_required(VERSION 3.8)

project(RNADecoder VERSION 1.0.0)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

include (scripts/clang-format.cmake)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR}/lib/json/include/)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/doctest)

message(STATUS ${Boost_LIBRARIES})

find_package(Boost REQUIRED system)
find_package(Threads REQUIRED)

set(SOURCES
    main.cpp
    engine/CompoundBase.cpp
    engine/DecoderEngine.cpp
    api/HttpUtils.cpp
    api/HttpParser.cpp
    api/HttpServer.cpp
    api/TcpConnection.cpp
)

list(TRANSFORM SOURCES PREPEND ${PROJECT_SOURCE_DIR}/src/)

add_executable(${PROJECT_NAME} ${SOURCES})


target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} Threads::Threads)
