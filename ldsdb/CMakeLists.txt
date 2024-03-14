cmake_minimum_required (VERSION 3.21)

project(ldsdb
    VERSION 1.0.0
    DESCRIPTION "STANAG 4609 ST 0601 LDS Database library"
    LANGUAGES C CXX)

include(GNUInstallDirs)

# include the module `ExternalProject`
include(ExternalProject)

# Add an external project from a downloaded source archive
ExternalProject_Add(
  sqlite3
  URL https://github.com/alex85k/sqlite3-cmake/archive/refs/tags/v3.24.0.tar.gz
  URL_HASH MD5=15ab81bf8cfbdb9a9a3b3abd38c7598b
  BUILD_IN_SOURCE true
)

ExternalProject_Get_Property(sqlite3 SOURCE_DIR)

set(SQLITE3_DIR "${SOURCE_DIR}")

include_directories(${SQLITE3_DIR}/src)

add_library(ldsdb STATIC)

target_sources(ldsdb PRIVATE
    src/ldsdb.cpp
    include/ldsdb/ldsdb.h
)

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