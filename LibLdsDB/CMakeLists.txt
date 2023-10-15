cmake_minimum_required (VERSION 3.14)
project("LibLdsDB"
    VERSION 1.0 
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

file(GLOB SRC_LIST
    *.h
    *.cpp)
add_library(LibLdsDB STATIC ${SRC_LIST})
set_property(TARGET LibLdsDB PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(LibLdsDB
          PUBLIC 
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
          "$<INSTALL_INTERFACE:include>"
          )

file(GLOB LIB_INCLUDE_FILES "./*.h")

# install the target and create export-set
install(TARGETS LibLdsDB 
    EXPORT LibLdsDBTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# install header file
install(FILES ${LIB_INCLUDE_FILES} DESTINATION include)

# generate and install export file
#install(EXPORT LibLdsDBTargets
#        FILE LibLdsDBTargets.cmake
#        NAMESPACE lcss::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/lib/cmake/LibLdsDB
#)