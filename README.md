# klvp
STANAG 4609 ST 0601 Key-Length-Value (KLV) parser library and test application, __klv2xml__, 
which reads in KLV encoded stream and writes out an XML representation.

## Prerequisites
This project requires the following to be installed:

1. CMake, https://cmake.org/
2. Microsoft Guidelines Support Library (GSL), https://github.com/microsoft/GSL 
3. SQLite3, https://github.com/sqlite/sqlite

It is recommended to use a package managment system such as [vcpkg](https://github.com/microsoft/vcpkg) to download and install __GSL__ and __SQLite3__.

## To Build and Install
In __klvp__ root directory, build and install this project using CMake with the following commmands on a terminal:

### 1. Generate the build environment
    cmake -S . -B ./build 
    
If you installed __GSL__ and __SQLite3__ using __vcpkg__, you may need to add `-DCMAKE_PREFIX_PATH=[vcpkg root]/installed/[target]` as an argument to the above command. 
The `[target]` is the target machine architecture such as `x64-windows` or `x64-linux`.

### 2. Build the library and test application
    cmake --build ./build 
### 3. Install the KLV Parser library
    cmake --install ./build

Add additional CMake parameters as required depending on your host development envirnoment. 

The `--install` command will install a CMake package so it can be imported into other CMake projects.

## Run Test
To run the projects build-in test, enter the following:

    ctest --test-dir ./build
