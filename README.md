# klvp
STANAG 4609 ST 0601 Key-Length-Value (KLV) parser library

## To Build and Install
In __klvp__ root directory, build and install this project using CMake with the following commmands on a terminal:

### 1. Generate the build envirnoment
    cmake -S . -B ./build 
### 2. Build the library and test application
    cmake --build ./build 
### 3. Install the KLV Parser library
    cmake --install ./build

Add additional CMake parameters as required depending on your host development envirnoment.

The `--install` command will install a CMake package so it can be imported into other CMake projects.

## Run Test
To run the projects build-in test, enter the following:

    ctest --test-dir ./build
