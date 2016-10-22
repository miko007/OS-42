### THIS IS JUST A STUB FOR CLion SYNTAX HIGHLIGHTING!
#   DO NOT! RUN CMAKE ON THIS ONE!!!

cmake_minimum_required(VERSION 3.5)
project(OS_42)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#project files to compile
file(GLOB_RECURSE project_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
		)
file(GLOB_RECURSE project_HDR
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
		)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/src/stdlib
)

add_executable(OS_42 ${project_SRC} ${project_HDR})