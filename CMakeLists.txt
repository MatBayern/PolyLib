# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set specific compiler paths
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-14")

# Project name and language
project(PolynomialProject CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-format-style=.clang-format;-config-file=../.clang-tidy")


# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Find all source files in src directory and its subdirectories
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.hpp"
)

# Print the found source files (optional, for debugging)
message(STATUS "Found source files: ${SOURCES}")

# Add executable with all source files
add_executable(polynomial_app ${SOURCES})

# Include directories
target_include_directories(polynomial_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pol
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interpolate
)