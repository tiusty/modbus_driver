#include <iostream>
#include "modbus_device.h"
#include "aqua_troll/aqua_troll.h"

int main() {
    run_aqua_troll_500();

    ModbusDevice arduino;

    // Initial the Arduino
    if (arduino.init("/dev/ttyS6", "Arduino", 1, 9600, 'N', 8, 1) == -1) {
        std::cout << "Failed to initialize device, exiting" << std::endl;
        return -1;
    }

    /* Logic to control communication with the Arduino */

    // Set value to 1 to turn on the LED
    arduino.write_to_register(0, 1);


    return 0;
}



