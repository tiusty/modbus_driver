cmake_minimum_required(VERSION 3.10)
project(modbus_driver
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(ModbusDeviceLib modbusDevice)
set(Aqua_troll_500 aqua_troll)

add_subdirectory(aqua_troll)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        ${ModbusDeviceLib}
        ${Aqua_troll_500}
        )

 # Modbus Library
add_library(${ModbusDeviceLib}
        modbus_device.cpp
        aqua_troll/aqua_troll_private.h)

target_link_libraries(${ModbusDeviceLib}
        modbus
        )

target_include_directories(${ModbusDeviceLib}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

