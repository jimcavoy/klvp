cmake_minimum_required (VERSION 3.21)

project(ImapbTestProject
    DESCRIPTION "MISB ST 1201 IMAPB algorithm test"
    LANGUAGES CXX
)

add_executable(ImapbTest)

target_sources(ImapbTest PRIVATE src/main.cpp)

target_link_libraries(ImapbTest PRIVATE klvp)

# Test cases
add_test(NAME imapb_test
  COMMAND ImapbTest
)

set_tests_properties( imapb_test
  PROPERTIES PASS_REGULAR_EXPRESSION 
    "Encoding 13898.5463 => 0 0xd9 0x2a[\r\n\t ]*Decoding 0 0xd9 0x2a => 13898.5[\r\n\t ]*Decoded NaN successfully[\r\n\t ]*Decoded Infinity successfully"
)