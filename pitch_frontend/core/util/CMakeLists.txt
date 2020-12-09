cmake_minimum_required (VERSION 3.8)

project("util")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "file_io.h" "file_io.cpp"  "algorithm.h" "algorithm.hpp")

include_directories(../../third_party/stb)
