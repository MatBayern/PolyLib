# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Set specific compiler paths

message(STATUS "compiler: " ${CMAKE_CXX_COMPILER_ID})
# Project name and language
project(PolynomialProject CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Configure clang-tidy for our project files only
#set(CMAKE_CXX_CLANG_TIDY clang-tidy;
#  -header-filter=.;
#  -format-style=.clang-format;
#  -config-file=../.clang-tidy;
#)

# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -O0")

# Find TBB package (only need to do this once)
find_package(TBB REQUIRED)

# Find all source files in src directory and its subdirectories
file(GLOB_RECURSE SOURCES
  "src/*.cpp"
  "src/*.hpp"
)

# Exclude test files from the main application build
list(FILTER SOURCES EXCLUDE REGEX ".*_test\\.cpp$")

# Print the found source files (optional, for debugging)
message(STATUS "Found source files: ${SOURCES}")

# Add executable with all source files
add_executable(polynomial_app ${SOURCES})

# Link TBB library to the main app
target_link_libraries(polynomial_app PRIVATE TBB::tbb)

# Include directories
target_include_directories(polynomial_app PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pol
  ${CMAKE_CURRENT_SOURCE_DIR}/src/interpolate
)

# Temporarily disable clang-tidy for GoogleTest
set(OLD_CMAKE_CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
set(CMAKE_CXX_CLANG_TIDY "")

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0  # Specify a version tag for stability
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Find all test files
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp" "src/*_test.cpp")
message(STATUS "Found test files: ${TEST_SOURCES}")

# Create test executable
add_executable(polynomial_tests ${TEST_SOURCES})

# Make src files available to tests (excluding main.cpp)
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp" "src/*.hpp")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*main\\.cpp$")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*test\\.cpp$")
target_sources(polynomial_tests PRIVATE ${LIB_SOURCES})

# Link TBB library to the test executable as well
target_link_libraries(polynomial_tests PRIVATE TBB::tbb)

# Add include directories for tests
target_include_directories(polynomial_tests PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pol
  ${CMAKE_CURRENT_SOURCE_DIR}/src/interpolate
  ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

# Link test executable with GoogleTest
target_link_libraries(polynomial_tests PRIVATE 
  GTest::gtest_main  # This includes a main() function
  GTest::gtest 
  GTest::gmock
)

# Restore clang-tidy setting for our test executable (but not for the GoogleTest libraries)
set_target_properties(polynomial_tests PROPERTIES CXX_CLANG_TIDY "${OLD_CMAKE_CXX_CLANG_TIDY}")

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(polynomial_tests)