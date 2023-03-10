#!/bin/sh

rm -rf build # we clear up the build folder if it exists
mkdir build
conan install . -if build --build missing
cmake . -B build
make -C build
