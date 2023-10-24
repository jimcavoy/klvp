cmake_minimum_required (VERSION 3.14)
project("libklvp"
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

file(GLOB SRC_LIST
    *.h
    *.cpp)
add_library(libklvp STATIC ${SRC_LIST})
set_property(TARGET libklvp PROPERTY POSITION_INDEPENDENT_CODE ON)

if(WIN32)    
    target_link_libraries(libklvp PRIVATE Microsoft.GSL::GSL wsock32 ws2_32)
else()    
    target_link_libraries(libklvp PRIVATE Microsoft.GSL::GSL)
    set_target_properties(libklvp 
        PROPERTIES
        OUTPUT_NAME klvp)
endif()

target_include_directories(libklvp
          PUBLIC 
          "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
          "$<INSTALL_INTERFACE:include>"
          )

file(GLOB LIB_INCLUDE_FILES "./*.h")

# install the target and create export-set
install(TARGETS libklvp 
    EXPORT libklvpTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# install header file
install(FILES ${LIB_INCLUDE_FILES} DESTINATION include)

# generate and install export file
#install(EXPORT libklvpTargets
#        FILE libklvpTargets.cmake
#        NAMESPACE lcss::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/lib/cmake/libklvp
#)