#include <iostream>
#include <array>

#include "modbus_device.h"

int main() {
    // Declare the devices
    ModbusDevice aqua_troll_500;

    // Initialize the desired devices
    aqua_troll_500.init("/dev/ttyS5", "Aqua Troll 500", 1, 19200, 'E', 8, 1);

    // Write a value to the devices
    if (aqua_troll_500.read_float_from_register(5450) == -1)
    {
        std::cout << "Error reading float from register" << std::endl;
    }


    return 0;
}



