cmake_minimum_required(VERSION 3.13)

message(STATUS ${MY_VAR})

project(
	openGL_wrapper
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g3")

if (APPLE)
		set(GLFW_DIR
				"glfw-3.3.8"
		)
		set(ASSIMP_DIR
				"assimp"
		)
		set(GLAD_DIR
				"include/glad_mac"
		)
		add_subdirectory(
				${GLFW_DIR}
		)
		add_subdirectory(
				${ASSIMP_DIR}
		)
elseif(WIN32)
		set(GLAD_DIR
				"include/glad_windows"
		)
else ()
		set(GLAD_DIR
				"include/glad_linux"
		)
endif (APPLE)


if (APPLE)
		set(SOURCE_FILES
				source/glad/glad_mac.c
				source/main.cpp
		)
elseif(WIN32)
		set(SOURCE_FILES
				source/glad/glad_windows.c
				source/main.cpp
		)
else ()
		set(SOURCE_FILES
				source/glad/glad_linux.c
				source/main.cpp
		)
endif (APPLE)

add_executable(${MY_VAR}
		${SOURCE_FILES}
)

target_include_directories(${MY_VAR}
		PUBLIC
		include
		${GLAD_DIR}
		${GLFW_DIR}/include
		${ASSIMP_DIR}/include
)

if (APPLE)
		target_link_libraries(${MY_VAR}
				glfw
		)
		target_link_libraries(${MY_VAR}
				assimp
		)
else ()
		target_link_libraries(${MY_VAR}
				glfw ${CMAKE_DL_LIBS}
		)
endif (APPLE)

target_compile_definitions(${MY_VAR}
		PRIVATE
		ROOT_PATH="${CMAKE_SOURCE_DIR}"
)
