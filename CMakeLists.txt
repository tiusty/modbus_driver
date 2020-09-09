cmake_minimum_required(VERSION 3.10)
project(modbus_driver)

set(CMAKE_CXX_STANDARD 14)
set(ModbusDeviceLib modbusDevice)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        ${ModbusDeviceLib}
        )

add_library(${ModbusDeviceLib}
        modbus_device.cpp
        aqua_troll.h)

target_link_libraries(${ModbusDeviceLib}
        modbus
        )

target_include_directories(${ModbusDeviceLib}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

