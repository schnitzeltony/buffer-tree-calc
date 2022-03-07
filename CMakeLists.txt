cmake_minimum_required(VERSION 3.14)

project(buffer-tree-calc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set project Version
set(BUFFER_TREE_CALC_VERSION_MAJOR "0")
set(BUFFER_TREE_CALC_VERSION_MINOR "0")
set(BUFFER_TREE_CALC_VERSION_PATCH "1")

set(PROJECT_VERSION "${BUFFER_TREE_CALC_VERSION_MAJOR}.${BUFFER_TREE_CALC_VERSION_MINOR}.${BUFFER_TREE_CALC_VERSION_PATCH}")

#Adding cmake functions like feature_summary()
include(FeatureSummary)
include(GNUInstallDirs)

file(GLOB HEADERS
    access-strategies/*.h
    buffers/*.h
    calc-components/*.h
    calc-components/calculators/*.h
    calc-components/template-implementations/*.h
)

# install public headers
set(HEADER_INSTALL_PATH ${CMAKE_INSTALL_INCLUDEDIR}/buffer-tree-calc)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/access-strategies DESTINATION ${HEADER_INSTALL_PATH} FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/buffers DESTINATION ${HEADER_INSTALL_PATH} FILES_MATCHING PATTERN "*.h")
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/calc-components DESTINATION ${HEADER_INSTALL_PATH} FILES_MATCHING PATTERN "*.h")

file(GLOB SOURCES
    access-strategies/*.cpp
    buffers/*.cpp
    calc-components/*.cpp
    calc-components/calculators/*.cpp
)

find_package (Threads)
find_package(PkgConfig REQUIRED)
pkg_check_modules(fftw3f REQUIRED fftw3f)
pkg_check_modules(fftw3 REQUIRED fftw3)

add_library(buffer-tree-calc SHARED
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries (buffer-tree-calc
    PUBLIC
    ${CMAKE_THREAD_LIBS_INIT}
    fftw3f
    fftw3
    )

# announce headers - target perspective
target_include_directories(buffer-tree-calc
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${HEADER_INSTALL_PATH}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

#set target Version
set_target_properties(buffer-tree-calc PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(buffer-tree-calc PROPERTIES SOVERSION ${BUFFER_TREE_CALC_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(buffer-tree-calc)

#install export header
#install(FILES
#    ${CMAKE_CURRENT_BINARY_DIR}/buffer-tree-calc_export.h
#    DESTINATION ${HEADER_INSTALL_PATH}
#    )

# install library
install(TARGETS buffer-tree-calc
    EXPORT BufferTreeCalcExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    BufferTreeCalcConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

# configure *Config.cmake
configure_file(BufferTreeCalcConfig.cmake.in BufferTreeCalcConfig.cmake @ONLY)

# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/BufferTreeCalcConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/BufferTreeCalcConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BufferTreeCalc
    )

# install targets cmake-files
install(EXPORT BufferTreeCalcExport
    FILE BufferTreeCalcTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BufferTreeCalc
    )

# unittests
find_package(GTest)
if(NOT CMAKE_CROSSCOMPILING AND ${GTest_FOUND})
    message(STATUS "unittest ${PROJECT_NAME}")
    enable_testing()

    add_test(NAME    ${PROJECT_NAME}-unittest
             COMMAND ${PROJECT_NAME}-unittest)

    file(GLOB UNITTESTS
        tests/*.cpp
        tests/*.h
    )

    add_executable(${PROJECT_NAME}-unittest
        ${UNITTESTS}
    )

    target_include_directories(${PROJECT_NAME}-unittest
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

    target_link_libraries(${PROJECT_NAME}-unittest
        PUBLIC
        gtest
        gtest_main
        ${PROJECT_NAME}
    )

endif()


# spawn out some info on configuration
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

