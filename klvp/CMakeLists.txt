cmake_minimum_required (VERSION 3.26)

project(klvp
  VERSION 1.0.0
  DESCRIPTION "STANAG 4609 ST 0601 KLV parser library"
  LANGUAGES C CXX
)

include(GNUInstallDirs)

# set the postfix "d" for the resulting .so or .dll files when building the
# library in debug mode
set(CMAKE_DEBUG_POSTFIX d)

# include the module `ExternalProject`
include(ExternalProject)

# Add an external project from a downloaded source archive
ExternalProject_Add(loki-lib
  URL https://github.com/snaewe/loki-lib/archive/refs/tags/Release_0_1_5.tar.gz
  URL_HASH MD5=74e60c683f745dc15c6e772927349483
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

ExternalProject_Get_Property(loki-lib SOURCE_DIR)

set(LOKI_DIR "${SOURCE_DIR}")

find_package(Microsoft.GSL CONFIG REQUIRED)

add_library(klvp STATIC)

target_sources(klvp
  PRIVATE
    src/decode.cpp
    src/encode.cpp
    src/FpParser.cpp
    src/klvelmt.cpp
    src/klvelmtimpl.cpp
    src/klvelmtparse.cpp
    src/klvprsr.cpp
    src/KlvSizeVisitor.cpp
    src/klvsselmtimpl.cpp
    src/klvsselmtparse.cpp
    src/klvuselmtimpl.cpp
    src/util.cpp
    include/klvp/decode.h
    include/klvp/encode.h
    include/klvp/FpParser.h
    include/klvp/klvelmt.h
    include/klvp/klvelmtimpl.h
    include/klvp/klvprsr.h
    include/klvp/KlvSizeVisitor.h
    include/klvp/klvsselmtimpl.h
    include/klvp/klvuselmtimpl.h
    include/klvp/RawSerializedVisitor.h
    include/klvp/treenode.h
    include/klvp/util.h
)

set_property(TARGET klvp PROPERTY POSITION_INDEPENDENT_CODE ON)

add_dependencies(klvp loki-lib)

# specify the C++ standard
target_compile_features( klvp PUBLIC cxx_std_14)

target_link_libraries(klvp PUBLIC Microsoft.GSL::GSL)

if (WIN32)
target_link_libraries(klvp PRIVATE wsock32 ws2_32)
endif()

target_include_directories(klvp
  PRIVATE 
    src/klvp
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${LOKI_DIR}/include>
)

install (TARGETS klvp
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
  DESTINATION lib/cmake/klvp
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
  VERSION ${klvp_VERSION}
  # Package compatibility strategy. SameMajorVersion is essentially `semantic versioning`.
  COMPATIBILITY SameMajorVersion
)

# Install command for deploying Config-file package files into the target system. It must be present
# in the same directory as `klvp-config.cmake` file.
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/klvp-config-version.cmake"
  DESTINATION lib/cmake/klvp
)
