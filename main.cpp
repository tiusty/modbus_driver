#include <iostream>

#include "modbus_device.h"
#include "modbus_driver.h"

int main() {
    // Declare the devices
    ModbusDevice arduino;
    ModbusDevice aqua_troll_500;

    // Initialize the desired devices
    arduino.init("/dev/ttyS6", "Arudino", 1);
//    aqua_troll_500.init("/dev/ttyS5", "Aqua Troll 500", 2);

    // Write a value to the devices
    arduino.write_to_register(0,1);
//    aqua_troll_500.write_to_register(0,0);


    return 0;
}



