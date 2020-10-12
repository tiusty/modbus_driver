#include "arduino.h"
#include "modbus_wrapper.h"

/**
 * Device parameters
 */
namespace device {
    constexpr char name[] = "Arduino";
    constexpr int slave_number = 1;
    constexpr int baud_rate = 9600;
    constexpr char parity = 'N';
    constexpr int data_bits = 8;
    constexpr int stop_bits = 1;
}

int run_arduino(const std::string &comm_port) {
    ModbusWrapper arduino;

    // Initial the Arduino
    if (arduino.init(comm_port, device::name, device::slave_number, device::baud_rate, device::parity,
                     device::data_bits, device::stop_bits) == -1) {
        std::cout << "Failed to initialize device " << device::name << ", exiting" << std::endl;
        return -1;
    }

    /* Logic to control communication with the Arduino */

    // Set value to 1 to turn on the LED
    arduino.write_to_register(0, 1);

    return 0;
}

