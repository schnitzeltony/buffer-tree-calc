cmake_minimum_required(VERSION 3.14)

project(magic-calc LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HEADERS
    *.h
    access-strategies/*.h
    buffers/*.h
    calc-components/*.h
    calc-components/calculators/*.h
)

file(GLOB SOURCES
    *.cpp
    access-strategies/*.cpp
    buffers/*.cpp
    calc-components/*.cpp
    calc-components/calculators/*.cpp
)

find_package (Threads)

add_executable(magic-calc
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries (magic-calc ${CMAKE_THREAD_LIBS_INIT})
