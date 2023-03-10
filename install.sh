#!/bin/sh

rm -rf build # we clear up the build folder if it exists
mkdir build
conan install . -if build
cmake . -B build
make -C build
