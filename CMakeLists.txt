# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)

project (klvp
  VERSION 1.0.0
  DESCRIPTION "STANAG 4609 ST 0601 KLV Parser Library"
  LANGUAGES C CXX
)

# Include sub-projects.
add_subdirectory (klvp)
add_subdirectory (ldsdb)

# Create an app, klv2xml, that reads KLV encode stream and outputs XML representation.
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

# Test cases
enable_testing()

add_subdirectory (tests)

add_test(NAME read_test 
  COMMAND klv2xml ${PROJECT_SOURCE_DIR}/sample/svt_testset_420_720p50_klved_4774.klv ${PROJECT_SOURCE_DIR}/data/klv.s3db
)
set_tests_properties(read_test
  PROPERTIES PASS_REGULAR_EXPRESSION "KLV count = 2503"
)