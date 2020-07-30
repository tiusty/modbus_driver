cmake_minimum_required(VERSION 3.10)
project(modbus_driver)

set(CMAKE_CXX_STANDARD 14)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        modbus
        )

