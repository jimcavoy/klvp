cmake_minimum_required (VERSION 3.21)

project(ldsdb
  VERSION 1.0.0
  DESCRIPTION "STANAG 4609 LDS Database library"
  LANGUAGES C CXX
)

############################################################################
# Doxygen configuration
############################################################################
# Locate Doxygen in the environment. This will set DOXYGEN_FOUND variable 
# as a result. When Doxygen is found, DOXYGEN_VERSION variable will be 
# also set to found Doxygen version.
find_package(Doxygen REQUIRED)

# Override the default doxygen output directory, which is CMAKE_CURRENT_BINARY_DIR. 
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
# Enable HTML documentation generation
set(DOXYGEN_GENERATE_HTML YES)
# Enable MAN page generation
set(DOXYGEN_GENERATE_MAN NO)
# Enable markdown support
set(DOXYGEN_MARKDOWN_SUPPORT YES)
# Enable autolink support
set(DOXYGEN_AUTOLINK_SUPPORT YES)
# Enable dot graph support
set(DOXYGEN_HAVE_DOT YES)
# Include collaboration diagrams in class documentation
set(DOXYGEN_COLLABORATION_GRAPH NO)
# Include class diagrams in class documentation
set(DOXYGEN_CLASS_GRAPH YES)
# Generate UML-like graphs
set(DOXYGEN_UML_LOOK YES)
# Include type and parameter information in UML graphs
set(DOXYGEN_DOT_UML_DETAILS YES)
# Max per-line length for graph content
set(DOXYGEN_DOT_WRAP_THRESHOLD 100)
# Enables drawing call graphs for the functions
set(DOXYGEN_CALL_GRAPH YES)
# Suppress the output messages
set(DOXYGEN_QUIET YES)
############################################################################

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

doxygen_add_docs(
  ldsdb_docs
  ${CMAKE_CURRENT_LIST_DIR}
  ALL
  COMMENT "Generating documentation for ldsdb library"
)

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