cmake_minimum_required(VERSION 3.13)

project(
	openGL_wrapper
)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_DIR
	"glfw-3.3.8"
)

set(SOURCE_FILES
	source/glad.c
	source/main.cpp
)

add_executable(HelloWrapper
	${SOURCE_FILES}
)

add_subdirectory(
	${GLFW_DIR}
)

target_include_directories(HelloWrapper
	PUBLIC
    include
	${GLFW_DIR}/include
)

target_link_libraries(HelloWrapper
	glfw
)

target_compile_definitions(HelloWrapper
	PRIVATE
    ROOT_PATH="${CMAKE_SOURCE_DIR}"
)