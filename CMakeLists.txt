cmake_minimum_required(VERSION 3.13)
project(demo)

# Get all files in the source directory recursively
file(GLOB_RECURSE SRC "cli/*.cpp" "demo/*.cpp" )

# Create an executable using those source file
add_executable(${PROJECT_NAME} ${SRC})

# Specify that the C++ version to use for the executable is C++20
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE "cli/")