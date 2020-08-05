cmake_minimum_required(VERSION 3.10)
project(modbus_driver)

set(CMAKE_CXX_STANDARD 14)
set(ModbusDeviceLib modbusDevice)
set(ModbusDriverLib modbusDriver)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        ${ModbusDriverLib}
        )

add_library(${ModbusDeviceLib}
        modbus_device.cpp
        )

add_library(${ModbusDriverLib}
        modbus_driver.cpp
        )

target_link_libraries(${ModbusDeviceLib}
        modbus
        )

target_link_libraries(${ModbusDriverLib}
        modbus
        ${ModbusDeviceLib}
        )


target_include_directories(${ModbusDeviceLib}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_include_directories(${ModbusDriverLib}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )

