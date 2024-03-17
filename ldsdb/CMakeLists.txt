cmake_minimum_required (VERSION 3.21)

project(ldsdb
  VERSION 1.0.0
  DESCRIPTION "STANAG 4609 ST 0601 LDS Database library"
  LANGUAGES C CXX
)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_library(ldsdb STATIC)

target_sources(ldsdb 
  PRIVATE
    src/ldsdb.cpp
    include/ldsdb/ldsdb.h
)

set_property(TARGET ldsdb PROPERTY POSITION_INDEPENDENT_CODE ON)

# specify the C++ standard
target_compile_features( ldsdb PUBLIC cxx_std_14)

target_include_directories(ldsdb
  PUBLIC
    include
  PRIVATE
    src/ldsdb
)

target_link_libraries(ldsdb PRIVATE unofficial::sqlite3::sqlite3)

install(TARGETS ldsdb)
