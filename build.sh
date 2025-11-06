#!/bin/bash

conan install . -s build_type=Release -s compiler.cppstd=23
source build/Release/generators/conanbuild.sh
if [ $# -gt 0 -a "$1" == "dev" ]; then
  DEV=ON cmake --preset conan-release
else
  cmake --preset conan-release
fi
cmake --build --preset conan-release
