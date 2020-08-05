#include <iostream>

#include "modbus_device.h"
#include "modbus_driver.h"

int main() {
    // Declare the evices
    ModbusDevice arudino;
    ModbusDevice aqua_troll_500;

    // Declare the driver
    ModbusDriver driver;

    // Initialize the desired devices
//    driver.initialize_device(AquaTroll500, "/dev/ttyS3", "Aqua Troll 500", 12000);
    driver.initialize_device(arudino, "/dev/ttyS6", "Arudino");

    // Write a value to the arduino
    driver.write(arudino, 0,0);


    return 0;
}



