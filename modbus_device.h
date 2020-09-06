
#ifndef MODBUS_DRIVER_MODBUS_DEVICE_H
#define MODBUS_DRIVER_MODBUS_DEVICE_H

#include <modbus/modbus.h>
#include <string>
#include <iostream>
#include <array>

class ModbusDevice {
    /**
     * Class stores information associated with one Modbus Device slave device. Each device should
     *  have a new instance of the class instantiated.
     *  Example:
     *      // Define various Modbus slave devices
     *      ModbusDevice arduino;
     *      ModbusDevice aqua_troll_500;
     *
     *      // Initialize the devices by setting the appropriate configuration
     *      arduino.init("/dev/ttyS5", "Arduino", 1);
     *      aqua_troll_500.init("/dev/ttyS6, "Aqua Troll 500", 2);
     *
     *      // Now the devices can be written to/read from etc
     *      arduino.write_to_register(0,0);
     *      aqua_troll_500.write_to_register(2,5);
     */
public:
    /**
     * Initializes the modbus device on the modbus rtu network
     * @param device_port The port the device is connected to
     * @param device_name The device name. Used for printing logging messages
     * @param slave_number The slave ID of the modbus device
     * @param baud_rate The baud rate of the device
     * @param parity Determines the type of parity used
     * @param data_bits The number of data bits
     * @param stop_bits The number of stop bits
     * @return 0 if success, -1 otherwise
     */
    int init(const std::string &device_port, const std::string &device_name, int slave_number, int baud_rate = 9600, char parity = 'N', int data_bits = 8, int stop_bits = 1);

    /**
     * Writes a value to the desired location
     * @param location The location to write to
     * @param value The value to write
     * @return 0 if success, -1 otherwise
     */
    int write_to_register(int location, int value);

    template <size_t N>
    int read_from_register(int address, int number_of_registers, std::array<uint16_t, N> &tab_reg)
    {
        // Read the registers from the device
        int rc = modbus_read_registers(mb_, address, number_of_registers, tab_reg.data());

        // Determine the error code of the read command
        if (rc == -1)
        {
            fprintf(stderr, "Modbus read register failed %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
            return -1;
        }

        // Display the results
        for (int i=0; i < rc; i++) {
            printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
        }

        return 0;

    }

    float read_float_from_register(int address);

    /**
     * Defined destructor to free memory when program terminates
     */
    ~ModbusDevice();
private:
    /**
     * Stores the name of the device
     */
    std::string device_name_;
    /**
     * Pointer to modbus structure
     */
    modbus_t *mb_;
};


#endif //MODBUS_DRIVER_MODBUS_DEVICE_H
