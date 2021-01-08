# CMakeList.txt : CMake project for pitch_frontend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pitch_frontend WIN32 "WinMain.cpp" )#"pitch_common/messages.h" "pitch_common/messages.cpp" "core/container/locked_message_queue.h" "core/container/locked_message_queue.hpp" "pitch_common/card_enums.h" "game/player.h" "game/player_hand.h")

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

add_subdirectory(third_party/covid)
include_directories(third_party/covid)
target_link_libraries(${PROJECT_NAME} covid)
target_include_directories(${PROJECT_NAME} PUBLIC thir_party/covid)

add_subdirectory(third_party/glfw)
include_directories(third_party/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PUBLIC thir_party/glfw)

add_subdirectory(core)
include_directories(core)
target_link_libraries(${PROJECT_NAME} core)
target_include_directories(${PROJECT_NAME} PUBLIC core)

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
