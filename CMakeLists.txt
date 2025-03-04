cmake_minimum_required(VERSION 3.13)  # CMake version check
project(todo-shell)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES main.c cJSON.c)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(todo-shell ${SOURCE_FILES})
target_include_directories(todo-shell PRIVATE ${CMAKE_SOURCE_DIR})
