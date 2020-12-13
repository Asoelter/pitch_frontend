# CMakeList.txt : CMake project for pitch_frontend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pitch_frontend WIN32 "WinMain.cpp")
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

add_subdirectory(third_party/glad)
include_directories(third_party/glad/include)
include_directories(third_party/glad/src)
include_directories(third_party/glad)
include_directories(thid_party/glad/glad)
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} INTERFACE thir_party/glad)

include_directories(third_party/stb)

target_link_libraries(${PROJECT_NAME} Ws2_32.lib)

add_compile_definitions(WUI_SRC_DIR=\"${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/third_party/wui\")
