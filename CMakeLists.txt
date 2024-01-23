# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (klvp
	VERSION 0.1.0
	LANGUAGES C CXX
)

# Include sub-projects.
add_subdirectory (klvp)
add_subdirectory (ldsdb)

include_directories(../loki-lib/include)

add_executable(klvptest)

file(GLOB SRC_LIST
    src/*.cpp)
	
target_sources(klvptest PRIVATE ${SRC_LIST})

include(FetchContent)

FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.0.0"
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(GSL)

if(WIN32)
    list(APPEND EXTRA_LIBS Microsoft.GSL::GSL klvp ldsdb wsock32 ws2_32)
    target_link_libraries(klvptest PRIVATE ${EXTRA_LIBS})
else()
    list(APPEND EXTRA_LIBS Microsoft.GSL::GSL klvp ldsdb uuid)
    target_link_libraries(klvptest PRIVATE ${EXTRA_LIBS})
endif()