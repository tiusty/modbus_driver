cmake_minimum_required(VERSION 3.10)

project(modbus_wrapper
        VERSION 1.0
        LANGUAGES CXX)

# Create the modbus wrapper library
add_library(${PROJECT_NAME}
        modbus_wrapper.cpp modbus_wrapper.h
        )

# Link the necessary libraries
target_link_libraries(${PROJECT_NAME}
        modbus
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

