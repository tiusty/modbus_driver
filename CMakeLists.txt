cmake_minimum_required(VERSION 3.10)
project(modbus_driver
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Added desired devices
add_subdirectory(modbus_wrapper)
add_subdirectory(aqua_troll)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        modbus_wrapper
        aqua_troll
        )
