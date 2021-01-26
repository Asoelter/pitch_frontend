cmake_minimum_required (VERSION 3.8)

project("pitch_imgui")

# Add source to this project's executable.
add_library(${PROJECT_NAME} "imgui.h" "imgui.cpp"
							"imgui_demo.cpp"
                            "imgui_draw.cpp"
                            "imgui_widgets.cpp"
                            "imgui_tables.cpp"
							"imgui_impl_glfw.h" "imgui_impl_glfw.cpp"
                            "imgui_impl_opengl3.h" "imgui_impl_opengl3.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ../../third_party)

#This seems like a hack to get glfw in, but it works for now
include_directories(../glfw)
include_directories(../glfw/include)
