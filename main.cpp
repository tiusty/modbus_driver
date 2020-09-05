#include <iostream>

#include "modbus_device.h"

int main() {
    // Declare the devices
//    ModbusDevice arduino;
    ModbusDevice aqua_troll_500;

    // Initialize the desired devices
//    arduino.init("/dev/ttyS6", "Arudino", 1);
    aqua_troll_500.init("/dev/ttyS6", "Aqua Troll 500", 1, 19200, 'E', 8, 1);
//    aqua_troll_500.init("/dev/ttyS5", "Aqua Troll 500", 2);

    // Write a value to the devices
//    aqua_troll_500.write_to_register(5451,0);
    aqua_troll_500.read_from_register(45451, 2);
//    aqua_troll_500.write_to_register(0,0);


    return 0;
}



