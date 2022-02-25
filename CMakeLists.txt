cmake_minimum_required(VERSION 3.14)

project(magic-calc LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

file(GLOB HEADERS
    *.h
    access-strategies/*.h
    calc-composite/*.h
    calc-strategies/*.h
)

file(GLOB SOURCES
    *.cpp
    access-strategies/*.cpp
    calc-composite/*.cpp
    calc-strategies/*.cpp
)

add_executable(magic-calc
    ${HEADERS}
    ${SOURCES}
)
target_link_libraries(magic-calc Qt${QT_VERSION_MAJOR}::Core)
