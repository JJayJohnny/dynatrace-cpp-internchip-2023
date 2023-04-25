#!/bin/sh

if [ "$TEST" = true ]
then
# Compiling for tests
rm -rf test/out/*
#compile functions to be tested
g++ -I/opt/vcpkg/installed/x64-linux/include -std=c++17 -c src/internship.cpp -o test/out/internship
#create library of functions to be tested
ar r test/out/testlib test/out/internship
#compile testing function
g++ -I/opt/vcpkg/installed/x64-linux/include -std=c++17 -c test/test.cpp -o test/out/test
#link library and gtest to testing funcion
g++ -I/opt/vcpkg/installed/x64-linux/include -L/opt/vcpkg/installed/x64-linux/lib test/out/test test/out/internship -o test/out/result -lgtest
sh -c "test/out/result"
else
# Create build directory
mkdir -p build
# Clean up the build directory
rm -rf build/*
# Use GCC to compile the main.cpp and internship.cpp source files with include path to VCPKG installer libraries
g++ -I/opt/vcpkg/installed/x64-linux/include -std=c++17 -O2 -o build/internship src/*.cpp
# Run the application
sh -c "build/internship ${DATA_JSON} ${COUNT}"
fi
