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

## Cross-Compile ARM64
This section describes how to cross-compile ARM64 (aarch64-linux-gnu) on a Linux x86_64 host machine.

### 1. Install the Cross-Compiler
Install the `aarch64` toolchain on your host Linux machine.

```
sudo apt update
sudo apt install gcc-linux-gnu g++-aarch64-linux-gnu
```

### 2. Generate Build System
Use `aarch64-toolchain.cmake` file to generate a cross-compile build system.  At the root of the project directory entry the following commands.

```
cmake -B build-arm64 -S . -DCMAKE_TOOLCHAIN_FILE=aarch64-toolchain.cmake
```

CMake will report `Configuring incomplete, errors occurred!`.  Ignore this warning and enter this following command to complete the configuration and to download ARM64 packages from vcpkg.

```
cmake -B build-arm64 -S . -DCMAKE_TOOLCHAIN_FILE=aarch64-toolchain.cmake -DVCPKG_TARGET_TRIPLET=arm64-linux
```

### 3. Build Project
To build all the binaries in this project, enter the following command.

```
cmake --build ./build-arm64
```
### 4. Verify Binaries
Once the build completes, confirm that the generated binaries are compiled for the correct architecture using the `file` utility.

```
file build-arm64\klv2xml
```

#### Expected Output:

```
klv2xml: ELF 64-bit LSB pie executable, ARM aarch64, version 1 (GNU/Linux), dynamically linked, interpreter /lib/ld-linux-aarch64.so.1, BuildID[sha1]=11759c0fccd318bf203ffee294c8ef36d31ecc1e, for GNU/Linux 3.7.0, not stripped
```

### 5. Install the KLV Parser Library
For other cross-compiled projects that need to link to this library, enter the following command:

```
sudo cmake --install ./build-arm64 --prefix /usr/aarch64-linux-gnu
```


