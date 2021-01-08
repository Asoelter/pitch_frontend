# CMakeList.txt : CMake project for pitch_frontend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pitch_frontend WIN32 "WinMain.cpp" )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(DEBUG=1)
	add_compile_definitions(RELEASE=0)
else()
	add_compile_definitions(DEBUG=0)
	add_compile_definitions(RELEASE=1)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

add_compile_definitions(PITCH_SHADER_DIRECTORY="${PROJECT_SOURCE_DIR}/pitch_frontend/res/shaders")
add_compile_definitions(PITCH_TEXTURE_DIRECTORY="${PROJECT_SOURCE_DIR}/pitch_frontend/res/textures")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

function(addDirectory dir)
	add_subdirectory(${dir})
	include_directories(${dir})
	target_link_libraries(${PROJECT_NAME} ${dir})
	target_include_directories(${PROJECT_NAME} PUBLIC ${dir})
endfunction()

function(addThirdParty dir)
	add_subdirectory(third_party/${dir})
	include_directories(third_party/${dir})
	target_link_libraries(${PROJECT_NAME} ${dir})
	target_include_directories(${PROJECT_NAME} PUBLIC thir_party/${dir})
endfunction()

addThirdParty(covid)
addThirdParty(glfw)

addDirectory(core)

add_subdirectory(game)
include_directories(game)
target_link_libraries(${PROJECT_NAME} game)
target_include_directories(${PROJECT_NAME} PUBLIC game)

add_subdirectory(pitch_common)
include_directories(pitch_common)
target_link_libraries(${PROJECT_NAME} pitch_common)
target_include_directories(${PROJECT_NAME} PUBLIC pitch_common)

add_subdirectory(third_party/glad)
include_directories(third_party/glad/include)
include_directories(third_party/glad/src)
include_directories(third_party/glad)
include_directories(thid_party/glad/glad)
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} INTERFACE thir_party/glad)

include_directories(third_party/stb)

add_subdirectory(third_party/imgui)
include_directories(third_party/imgui)
target_link_libraries(${PROJECT_NAME} imgui)
target_include_directories(${PROJECT_NAME} PUBLIC thir_party/imgui)

target_link_libraries(${PROJECT_NAME} Ws2_32.lib)
