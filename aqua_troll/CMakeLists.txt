cmake_minimum_required(VERSION 3.10)

project(aqua_troll
        VERSION 1.0
        LANGUAGES CXX)

add_library(${PROJECT_NAME}
        aqua_troll.cpp aqua_troll_private.h aqua_troll.h
        )

target_link_libraries(${PROJECT_NAME}
        ${ModbusDeviceLib}
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

