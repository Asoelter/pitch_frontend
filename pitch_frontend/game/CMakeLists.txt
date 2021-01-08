cmake_minimum_required (VERSION 3.8)

project("game")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "card.h"			"card.cpp" 
							"start_menu.h"		"start_menu.cpp" 
							"socket_thread.h"	"socket_thread.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ../)
include_directories(../pitch_common)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

#This seems like a hack to get glad in, but it works for now
include_directories(../third_party/glad/include)
include_directories(../third_party/glad/src)
include_directories(../third_party/glad)

include_directories(../third_party/glfw)
include_directories(../third_party/glfw/include)

#This also feels like a hack
include_directories(../third_party/imgui)
target_link_libraries(${PROJECT_NAME} imgui)
target_include_directories(${PROJECT_NAME} INTERFACE ../thir_party/imgui)
