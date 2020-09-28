cmake_minimum_required(VERSION 3.10)

project(arduino
        VERSION 1.0
        LANGUAGES CXX)

# Create the Aqua Troll Library
add_library(${PROJECT_NAME}
        arduino.cpp arduino.h
        )

# Link the necessary libraries
target_link_libraries(${PROJECT_NAME}
        modbus_wrapper
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

