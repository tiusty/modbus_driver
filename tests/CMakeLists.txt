cmake_minimum_required(VERSION 3.10)

project(runTests
        VERSION 1.0
        LANGUAGES CXX)

# Find where gtest is installed
find_package(GTest REQUIRED)

# Include gtest
include_directories(${GTEST_INCLUDE_DIRS})

# Create the test executable
add_executable(${PROJECT_NAME} main.cpp)

# Link necessary libraries
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)