cmake_minimum_required(VERSION 3.7)
project(gmock-generator)

option(GG_BUILD_TESTS "Build unit tests" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(LibClang REQUIRED)
message(STATUS ${LIBCLANG_CXXFLAGS})

if(GG_BUILD_TESTS AND NOT APPLE)
    include(CodeCoverage)
    set(COVERAGE_EXCLUDES '*/c++/*' '*/3rdParty/*' '*/tests/*' '*/main.cpp')
    append_coverage_compiler_flags()
endif()

add_subdirectory(3rdParty)
add_subdirectory(src)

if(GG_BUILD_TESTS)
    add_subdirectory(3rdParty/gtest)
    enable_testing()
    add_subdirectory(tests)
endif()
