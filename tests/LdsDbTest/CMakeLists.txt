cmake_minimum_required (VERSION 3.21)

project(LdsDbTestProject
    DESCRIPTION "LDS Database test"
    LANGUAGES CXX
)

add_executable(LdsDbTest)

target_sources(LdsDbTest PRIVATE src/main.cpp)

target_link_libraries(LdsDbTest PRIVATE ldsdb)

# Test cases
add_test(NAME LdsDatabase_test
  COMMAND LdsDbTest ${PROJECT_SOURCE_DIR}/../../data/klv.s3db
)

set_tests_properties( LdsDatabase_test
  PROPERTIES PASS_REGULAR_EXPRESSION "fetch\\(\\) passed
fetch_security\\(\\) passed
fetch_list\\(\\) passed
fetch_security_list\\(\\) passed
fetch_security_elements_validvalues\\(\\) passed
fetch_list_rights\\(\\) passed
fetch_security_list_rights\\(\\) passed"
)