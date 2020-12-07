cmake_minimum_required (VERSION 3.8)

project("core")

add_library (${PROJECT_NAME} INTERFACE)

function(addDirectory dir)
	add_subdirectory(${dir})
	include_directories(${dir})
	target_link_libraries(${PROJECT_NAME} INTERFACE ${dir})
	target_include_directories(${PROJECT_NAME} INTERFACE ${dir})
endfunction()

addDirectory(graphics)

