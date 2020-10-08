//
// Created by Alex on 9/27/2020.
//

#include "arduino.h"
#include "modbus_wrapper.h"

int run_arduino(const std::string& comm_port)
{
    ModbusWrapper arduino;

    // Initial the Arduino
    if (arduino.init(comm_port, "Arduino", 1, 9600, 'N', 8, 1) == -1) {
        std::cout << "Failed to initialize device, exiting" << std::endl;
        return -1;
    }

    /* Logic to control communication with the Arduino */

    // Set value to 1 to turn on the LED
    arduino.write_to_register(0, 1);

    return 0;
}

