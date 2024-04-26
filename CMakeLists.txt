cmake_minimum_required(VERSION 3.15)

project(
	Tetrisxx
	LANGUAGES CXX
)
set(CMAKE_BUILD_TYPE "Debug")
aux_source_directory(src SRC)
add_executable(tetrisxx ${SRC})
target_include_directories(tetrisxx PUBLIC include)

add_definitions(-DTETRIS_GUI_COLOUR)
# add_definitions(-DDBG_MODE)

if(UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
	add_definitions(-DON_UNIX)
endif()
