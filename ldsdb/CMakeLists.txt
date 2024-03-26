cmake_minimum_required (VERSION 3.21)

project(ldsdb
  VERSION 1.0.0
  DESCRIPTION "STANAG 4609 ST 0601 LDS Database library"
  LANGUAGES C CXX
)

find_package(unofficial-sqlite3 CONFIG REQUIRED)

# set the postfix "d" for the resulting .so or .dll files when building the
# library in debug mode
set(CMAKE_DEBUG_POSTFIX d)

add_library(ldsdb STATIC)

target_sources(ldsdb 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ldsdb/ldsdb.h>
    $<INSTALL_INTERFACE:include/ldsdb/ldsdb.h>
  PRIVATE
    src/ldsdb.cpp
)

set_property(TARGET ldsdb PROPERTY POSITION_INDEPENDENT_CODE ON)

# specify the C++ standard
target_compile_features( ldsdb PUBLIC cxx_std_14)

target_include_directories(ldsdb
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    src
    include/ldsdb
)

target_link_libraries(ldsdb PRIVATE unofficial::sqlite3::sqlite3)

include(GNUInstallDirs)

install(TARGETS ldsdb
  EXPORT ldsdb_export
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (EXPORT ldsdb_export
  FILE ldsdb-config.cmake
  NAMESPACE lcss::
  DESTINATION lib/cmake/ldsdb
)

if (WIN32)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Debug/ldsdbd.pdb DESTINATION lib OPTIONAL)
endif()

# Defines write_basic_package_version_file
include(CMakePackageConfigHelpers)

# Create a package version file for the package. This will allow consumers to specify
# version argument to select between several versions of the package via specifying VERSION argument
# to find_package().
# We're not explicitly specifying the VERSION parameter to allow `write_basic_package_version_file` to 
# get it from project(...) version (which is 1.0.0)
write_basic_package_version_file(
  "ldsdb-config-version.cmake"
  VERSION ${ldsdb_VERSION}
  # Package compatibility strategy. SameMajorVersion is essentially `semantic versioning`.
  COMPATIBILITY SameMajorVersion
)

# Install command for deploying Config-file package files into the target system. It must be present
# in the same directory as `klvp-config.cmake` file.
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/ldsdb-config-version.cmake"
  DESTINATION lib/cmake/ldsdb
)