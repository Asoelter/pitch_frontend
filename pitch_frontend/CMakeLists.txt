# CMakeList.txt : CMake project for pitch_frontend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (pitch_frontend WIN32 "WinMain.cpp" )
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_subdirectory(third_party/covid)
include_directories(third_party/covid)
target_link_libraries(${PROJECT_NAME} covid)
target_include_directories(${PROJECT_NAME} PUBLIC thir_party/covid)

target_link_libraries(${PROJECT_NAME} Ws2_32.lib)