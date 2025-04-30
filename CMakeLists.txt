cmake_minimum_required(VERSION 3.14)
project(PongThreading)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

#-- Fetch gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

#-- Fetch glfw
#Remove comments here and add comments to
#local system implementation if GLFW not downloaded locally

#FetchContent_Declare(
#	glfw
#	GIT_REPOSITORY https://github.com/glfw/glfw.git
# 	GIT_TAG latest
#)

#-- Use GLFW from local system (comment out if not used)
set(GLFW_DIR "C:/Users/Zak/glfw-3.4") # Change to desired filepath
add_subdirectory(${GLFW_DIR} ${CMAKE_BINARY_DIR}/glfw_build)

find_package(OpenGL REQUIRED)
# -- Make gtest and glfw available on test
FetchContent_MakeAvailable(googletest) # If fetching glfw, add parameter here


#-- Add test executables
add_executable(runTests
	test_test.cpp
	ball_test.cpp
	PongThreading/ball.cpp
	PongThreading/game.cpp 
	PongThreading/paddle.cpp
	PongThreading/main.cpp
)

#-- Define static GLFW_STATIC
target_compile_definitions(runTests PRIVATE UNIT_TEST)

# Link needed libraries
target_link_libraries(runTests
	glfw
	OpenGL::GL
	gtest
	gtest_main
)

enable_testing()

add_test(NAME PongTests COMMAND runTests)