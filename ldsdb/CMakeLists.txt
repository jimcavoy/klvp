cmake_minimum_required (VERSION 3.14)
project(ldsdb
    VERSION 0.1.0 
    DESCRIPTION "STANAG 4609 ST 0601 LDS Database library"
    LANGUAGES C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    set(CMAKE_INSTALL_LIBDIR $ENV{APPDATA})
	include_directories($ENV{ProgramFiles}/sqlite3/include)
else()
	include_directories(../../sqlite3-cmake/libs/include)
endif()

add_library(ldsdb STATIC)

file(GLOB SRC_LIST
    src/*.cpp)
	
target_sources(ldsdb PRIVATE ${SRC_LIST})

set_property(TARGET ldsdb PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(ldsdb
          PRIVATE src/ldsdb
		  PUBLIC include
          )

#file(GLOB LIB_INCLUDE_FILES "./*.h")

# install the target and create export-set
#install(TARGETS LibLdsDB 
#    EXPORT LibLdsDBTargets
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION lib
#    RUNTIME DESTINATION bin
#    INCLUDES DESTINATION include
#)

# install header file
#install(FILES ${LIB_INCLUDE_FILES} DESTINATION include)

# generate and install export file
#install(EXPORT LibLdsDBTargets
#        FILE LibLdsDBTargets.cmake
#        NAMESPACE lcss::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/lib/cmake/LibLdsDB
#)