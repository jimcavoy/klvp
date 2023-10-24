# CMakeList.txt : CMake project for klvp, include source and define
# project specific logic here.
#

include(FetchContent)

FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.0.0"
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(GSL)

include_directories(../../loki-lib/include)

# Add source to this project's executable.
file(GLOB SRC_LIST
    *.h
    *.cpp)
add_executable (klvp ${SRC_LIST})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET klvp PROPERTY CXX_STANDARD 14)
endif()

if(WIN32)
    list(APPEND EXTRA_LIBS Microsoft.GSL::GSL libklvp LibLdsDB wsock32 ws2_32)
    target_link_libraries(klvp PRIVATE ${EXTRA_LIBS})
else()
    list(APPEND EXTRA_LIBS Microsoft.GSL::GSL libklvp LibLdsDB uuid)
    target_link_libraries(klvp PRIVATE ${EXTRA_LIBS})
endif()

# TODO: Add tests and install targets if needed.
