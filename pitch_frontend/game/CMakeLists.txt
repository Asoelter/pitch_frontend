cmake_minimum_required (VERSION 3.8)

project("game")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "card.h" "card.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ../)
