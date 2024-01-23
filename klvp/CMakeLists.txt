cmake_minimum_required (VERSION 3.14)
project(klvp
    VERSION 1.0 
    DESCRIPTION "STANAG 4609 ST 0601 KLV parser library"
    LANGUAGES C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    set(CMAKE_INSTALL_LIBDIR $ENV{APPDATA})
endif()

include(FetchContent)

FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.0.0"
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(GSL)

include_directories(../../loki-lib/include)

add_library(klvp STATIC)

file(GLOB SRC_LIST
    src/*.cpp)

target_sources(klvp PRIVATE ${SRC_LIST})

set_property(TARGET klvp PROPERTY POSITION_INDEPENDENT_CODE ON)

if(WIN32)    
    target_link_libraries(klvp PRIVATE Microsoft.GSL::GSL wsock32 ws2_32)
else()    
    target_link_libraries(klvp PRIVATE Microsoft.GSL::GSL)    
endif()

target_include_directories(klvp
          PRIVATE src/klvp
		  PUBLIC include
          )

#file(GLOB LIB_INCLUDE_FILES "./*.h")

# install the target and create export-set
#install(TARGETS libklvp 
#    EXPORT libklvpTargets
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION lib
#    RUNTIME DESTINATION bin
#    INCLUDES DESTINATION include
#)

# install header file
#install(FILES ${LIB_INCLUDE_FILES} DESTINATION include)

# generate and install export file
#install(EXPORT libklvpTargets
#        FILE libklvpTargets.cmake
#        NAMESPACE lcss::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/lib/cmake/libklvp
#)