# klvp 

Key-Length-Value (KLV) parser library (klvp) provides classes to allow client applications to parse or encode
a KLV encoded metadata stream based on the following STANAG 4609 standards:

- MISB ST 0601, UAS Datalink Local Set 
- MISB ST 0102, Security Metadata Universal and Local Sets for Motion Imagery Data

## Project Structure
The __klvp__ project consists of two static libraries and an example application.

### Static Libraries
The project builds two libraries:

- __klvp__ - KLV parser and encoder library
- __ldsdp__ - Local Dataset (LDS) database library 

### Example Application (klv2xml)
The example application, __klv2xml__, consumes the project's libraries to read a KLV encoded metadata stream and output an XML representation.

## How to Build

### Prerequisites
This project requires the following:

1. Install CMake, https://cmake.org/
2. Install vcpkg, https://github.com/microsoft/vcpkg, which is a packet management system.
3. Configure `VCPKG_ROOT` environment variable to the path where you installed __vcpkg__.
4. Add `VCPKG_ROOT` to the `PATH` environment variable.

### To Build and Install
In __klvp__ root directory, build and install this project using CMake with the following commands on a terminal:

#### 1. Generate the build environment

    cmake --preset=<windows-base|linux-base>

For Windows platform, use `window-base` and for Linux platform use `linux-base` preset.

#### 2. Build the library and test application

    cmake --build ./build 

#### 3. Install the KLV Parser library

    cmake --install ./build

Add additional CMake parameters as required depending on your host development environment. 

The `--install` command will install a CMake package so it can be imported into other CMake projects.

### Run Test
To run the projects build-in test, enter the following:

    ctest --test-dir ./build
