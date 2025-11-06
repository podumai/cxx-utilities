#!/bin/bash

conan build . -s:a build_type=Release -s:a compiler.cppstd=23
source build/Release/generators/conanbuild.sh
