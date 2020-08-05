#include <iostream>

#include "modbus_device.h"
#include "modbus_driver.h"

int main() {
    // Declare the devices
    ModbusDevice arduino;
    ModbusDevice aqua_troll_500;

    // Declare the driver
    ModbusDriver driver;

    // Initialize the desired devices
    driver.initialize_device(arduino, "/dev/ttyS6", "Arudino");
//    driver.initialize_device(aqua_troll_500, "/dev/ttyS3", "Aqua Troll 500", 12000);

    // Write a value to the arduino
    driver.write(arduino, 0,0);
//    driver.write(aqua_troll_500, 0, 1);


    return 0;
}



