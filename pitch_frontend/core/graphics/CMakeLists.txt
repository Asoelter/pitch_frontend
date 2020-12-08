cmake_minimum_required (VERSION 3.8)

project("graphics")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "vertex_array_object.h"		"vertex_array_object.cpp" 
							"vertex_buffer_object.h"	"vertex_buffer_object.cpp" 
							"window.h"					"window.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ../../third_party)

#This seems like a hack to get glad in, but it works for now
include_directories(../../third_party/glad/include)
include_directories(../../third_party/glad/src)
include_directories(../../third_party/glad)

include_directories(../../third_party/glfw)
include_directories(../../third_party/glfw/include)
