cmake_minimum_required (VERSION 3.8)

project("math")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "mat.h"		"mat.hpp" 
							"trig.h"	"trig.cpp" 
							"vec.h"		"vec.hpp"  "vec.cpp" 
							"point.h"	"point.hpp")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
