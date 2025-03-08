cmake_minimum_required(VERSION 3.12)
project(Examples
    VERSION 1.0.0
    DESCRIPTION "Examples of using mylib"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MYLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${MYLIB_INCLUDE_DIR})

set(MYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)
link_directories(${MYLIB_DIR})

add_executable(static_demo static_demo.cpp)
target_link_libraries(static_demo 
    PRIVATE
        -Wl,-Bstatic
        -lmylib
        -Wl,-Bdynamic)

add_executable(dynamic_demo dynamic_demo.cpp)
target_link_libraries(dynamic_demo PRIVATE mylib)
