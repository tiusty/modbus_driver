cmake_minimum_required(VERSION 3.10)
project(modbus_driver
        VERSION 1.0
        LANGUAGES CXX)

# Set standard to c++17
set(CMAKE_CXX_STANDARD 17)

# Add the modbus wrapper
add_subdirectory(modbus_wrapper)

# Added desired devices
add_subdirectory(aqua_troll)

# Create the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link the necessary devices/wrapper
target_link_libraries(${PROJECT_NAME}
        modbus_wrapper
        aqua_troll
        )
