cmake_minimum_required (VERSION 3.21)
project(ldsdb
    VERSION 1.0.0 
    DESCRIPTION "STANAG 4609 ST 0601 LDS Database library"
    LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(sqlite
    GIT_REPOSITORY https://github.com/alex85k/sqlite3-cmake.git
    GIT_TAG master
)

FetchContent_MakeAvailable(sqlite)

include_directories(${CMAKE_BINARY_DIR}/_deps/sqlite-src/src)

add_library(ldsdb STATIC)

file(GLOB SRC_LIST
    src/*.cpp)

target_sources(ldsdb PRIVATE ${SRC_LIST})

set_property(TARGET ldsdb PROPERTY POSITION_INDEPENDENT_CODE ON)

# specify the C++ standard
target_compile_features(
    ldsdb
    PUBLIC cxx_std_14
)

target_include_directories(ldsdb
    PRIVATE src/ldsdb
    PUBLIC include
)
