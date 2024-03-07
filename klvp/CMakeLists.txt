cmake_minimum_required (VERSION 3.21)
project(klvp
    VERSION 1.0.0
    DESCRIPTION "STANAG 4609 ST 0601 KLV parser library"
    LANGUAGES C CXX)

include(GNUInstallDirs)

# This is the default install directory for config-file package cmake files
# It is relative to install prefix.
set(klvp_INSTALL_CMAKEDIR cmake CACHE PATH "Installation directory for config-file package cmake files")

# set the postfix "d" for the resulting .so or .dll files when building the
# library in debug mode
set(CMAKE_DEBUG_POSTFIX d)

# include the module `ExternalProject`
include(ExternalProject)

# Add an external project from a downloaded source archive
ExternalProject_Add(
  loki-lib
  URL https://github.com/snaewe/loki-lib/archive/refs/tags/Release_0_1_5.tar.gz
  URL_HASH MD5=74e60c683f745dc15c6e772927349483
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(loki-lib SOURCE_DIR)

set(LOKI_DIR "${SOURCE_DIR}")

include_directories(${LOKI_DIR}/include)

add_library(klvp STATIC)

file(GLOB SRC_LIST
    src/*.cpp)

target_sources(klvp PRIVATE ${SRC_LIST})

set_property(TARGET klvp PROPERTY POSITION_INDEPENDENT_CODE ON)

add_dependencies(klvp loki-lib)

# specify the C++ standard
target_compile_features(
    klvp
    PUBLIC cxx_std_14
)

if(WIN32)    
    set(WS wsock32 ws2_32)
endif()

target_link_libraries(klvp PRIVATE Microsoft.GSL::GSL ${WS})

target_include_directories(klvp
          PRIVATE src/klvp
          PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(TARGETS klvp
        EXPORT klvp_export
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install (
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install (EXPORT klvp_export
        FILE klvp-config.cmake
        NAMESPACE lcss::
        DESTINATION ${klvp_INSTALL_CMAKEDIR}
)

# Defines write_basic_package_version_file
include(CMakePackageConfigHelpers)

# Create a package version file for the package. This will allow consumers to specify
# version argument to select between several versions of the package via specifying VERSION argument
# to find_package().
# We're not explicitly specifying the VERSION parameter to allow `write_basic_package_version_file` to 
# get it from project(...) version (which is 1.0.0)
write_basic_package_version_file(
  "klvp-config-version.cmake"
  # Package compatibility strategy. SameMajorVersion is essentially `semantic versioning`.
  COMPATIBILITY SameMajorVersion
)

# Install command for deploying Config-file package files into the target system. It must be present
# in the same directory as `klvp-config.cmake` file.
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/klvp-config-version.cmake"
  DESTINATION "${klvp_INSTALL_CMAKEDIR}"
)
