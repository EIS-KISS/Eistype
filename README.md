# eistype

eistype is a shared library (libeisgenerator.so) and CLI application that allows one to operate on kiss files and datatypes.

eistype's development and target platform is UNIX, but it should compile on nigh on any platform

## Compile/Install

### Requirements

* git
* c++20 capable compiler (GCC, CLANG)
* cmake 3.20 or later

### Procedure (UNIX)

In a console do:

* git clone https://github.com/EIS-KISS/Eistype.git
* cd eistype
* mkdir build
* cd build
* cmake ..
* make
* sudo make install

### Cross-compile for windows on UNIX

* Have the mingw cross-compile toolchain installed
* git clone https://github.com/EIS-KISS/Eistype.git
* cd build
* mkdir build
* cd build
* cmake -DCMAKE_TOOLCHAIN_FILE=./crossW64.cmake ..
* make
