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

add_executable(klvptest)

target_sources(klvptest PRIVATE
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

if(WIN32)
    list(APPEND EXTRA_LIBS klvp ldsdb wsock32 ws2_32)
else()
    list(APPEND EXTRA_LIBS klvp ldsdb uuid)
endif()

target_link_libraries(klvptest PRIVATE ${EXTRA_LIBS})

target_link_libraries(klvptest INTERFACE Microsoft.GSL::GSL)

# Test cases
enable_testing()

set(args ${PROJECT_SOURCE_DIR}/sample/svt_testset_420_720p50_klved_4774.klv ${PROJECT_SOURCE_DIR}/data/klv.s3db)
add_test(NAME read_test 
    COMMAND klvptest ${args}
)
set_tests_properties(read_test
    PROPERTIES PASS_REGULAR_EXPRESSION "KLV count = 2503")