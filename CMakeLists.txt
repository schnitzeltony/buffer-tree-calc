cmake_minimum_required(VERSION 3.14)

project(magic-calc LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HEADERS
    *.h
    access-strategies/*.h
    buffers/*.h
    calc-composite/*.h
    calc-composite/leaf-components/*.h
)

file(GLOB SOURCES
    *.cpp
    access-strategies/*.cpp
    buffers/*.cpp
    calc-composite/*.cpp
    calc-composite/leaf-components/*.cpp
)

add_executable(magic-calc
    ${HEADERS}
    ${SOURCES}
)
