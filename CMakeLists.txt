# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)

project (klvp
  VERSION 1.1.0
  DESCRIPTION "STANAG 4609 KLV Parser Library"
  LANGUAGES C CXX
)

# Include sub-projects.
add_subdirectory (klvp)
add_subdirectory (ldsdb)

# Create an example app, klv2xml, that reads KLV encode stream and outputs XML representation.
add_executable(klv2xml)

target_sources(klv2xml
  PRIVATE
    src/klvp.h
    src/klvp.cpp
    src/KLVPrintVisitor.h
    src/KLVPrintVisitor.cpp
    src/KLVSecuritySetPrintVisitor.h
    src/KLVSecuritySetPrintVisitor.cpp
    src/TestKLVParser.h
    src/TestKLVParser.cpp
    src/TestKLVSecuritySetParser.h
    src/TestKLVSecuritySetParser.cpp
)

target_link_libraries(klv2xml
  PRIVATE
    klvp
    ldsdb
)

# install
install (TARGETS klv2xml)

install (FILES ${PROJECT_SOURCE_DIR}/data/klv.s3db
  TYPE DATA
)

option(ENABLE_DOCUMENTATION "Enable documentation" OFF)

if (ENABLE_DOCUMENTATION)
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

doxygen_add_docs(
  klvp_docs
  Index.md klvp/ ldsdb/ src/
  ALL
  COMMENT "Generating documentation for klvp library"
)
endif()

# Test cases
enable_testing()

add_subdirectory (tests)

add_test(NAME read_test 
  COMMAND klv2xml ${PROJECT_SOURCE_DIR}/sample/svt_testset_420_720p50_klved_4774.klv ${PROJECT_SOURCE_DIR}/data/klv.s3db
)
set_tests_properties(read_test
  PROPERTIES PASS_REGULAR_EXPRESSION "KLV count = 2503"
)