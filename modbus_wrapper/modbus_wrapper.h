#ifndef MODBUS_DRIVER_MODBUS_WRAPPER_H
#define MODBUS_DRIVER_MODBUS_WRAPPER_H

#include <modbus/modbus.h>
#include <string>
#include <iostream>
#include <array>

class ModbusWrapper {
    /**
     * Class stores information associated with one Modbus Device slave device. Each device should
     *  have a new instance of the class instantiated.
     *  Example:
     *      // Define various Modbus slave devices
     *      ModbusWrapper arduino;
     *      ModbusWrapper aqua_troll_500;
     *
     *      // Initialize the devices by setting the appropriate configuration
     *      arduino.init("/dev/ttyS5", "Arduino", 1);
     *      aqua_troll_500.init("/dev/ttyS6, "Aqua Troll 500", 2);
     *
     *      // Now the devices can be written to/read from etc
     *      arduino.write_to_registers(0,0);
     *      aqua_troll_500.write_to_registers(2,5);
     */
public:
    /**
     * Initializes the modbus_wrapper device on the modbus_wrapper rtu network
     * @param device_port The port the device is connected to
     * @param device_name The device name. Used for printing logging messages
     * @param slave_number The slave ID of the modbus_wrapper device
     * @param baud_rate The baud rate of the device
     * @param parity Determines the type of parity used
     * @param data_bits The number of data bits
     * @param stop_bits The number of stop bits
     * @return 0 if success, -1 otherwise
     */
    int init(const std::string &device_port, const std::string &device_name, int slave_number, int baud_rate = 9600,
             char parity = 'N', int data_bits = 8, int stop_bits = 1);

    /**
     * Writes a value to the desired location
     *  This performs a Modbus function code 16 (Write to registers)
     * @param location The location to write to
     * @param value The value to write
     * @return 0 if success, -1 otherwise
     */
    template<size_t N>
    int write_to_registers(int location, int number_of_registers, std::array<uint16_t, N> tab_reg) {
        // Simple check to make sure the user does not want to write values than the array size
        if (number_of_registers > tab_reg.size()) {
            std::cout << "Number of registers should be less than or equal to the length of the array" << std::endl;
            return -1;
        }

        // Attempt to write the value at the register location
        if (modbus_write_registers(mb_, location, number_of_registers, tab_reg.data()) == -1) {
            fprintf(stderr, "Modbus Write Register fail for device %s: %s\n", device_name_.c_str(),
                    modbus_strerror(errno));
            return -1;
        }

        return 0;

    }

    /**
     * Writes a value to the desired location
     *  This performs a Modbus function code 6 (WRite to register)
     * @param location The location to write to
     * @param value The value to write
     * @return 0 if success, -1 otherwise
     */
    int write_to_register(int location, uint16_t value);

    /**
     * Reads a sequential list of registers starting at the desired address. The number of registers can be
     *  specified though the array should be long enough to support the desire amount of registers
     * @tparam N The size of the passed in array
     * @param address The start address of where to start reading registers from
     * @param number_of_registers The number of registers to read
     * @param tab_reg The array that will store the results from the read registers
     * @return 0 if success, -1 if fail
     */
    template<size_t N>
    int read_from_register(int address, int number_of_registers, std::array<uint16_t, N> &tab_reg) {
        // Simple check to make sure the array can hold the amount of desired registers
        if (number_of_registers > tab_reg.size()) {
            std::cout << "Number of registers should be less than or equal to the length of the array" << std::endl;
            return -1;
        }

        // Read the registers from the device
        int rc = modbus_read_registers(mb_, address, number_of_registers, tab_reg.data());

        // Determine the error code of the read command
        if (rc == -1) {
            fprintf(stderr, "Modbus read register failed %s: %s\n", device_name_.c_str(), modbus_strerror(errno));
            return -1;
        }

        // Useful print statement to print out hex values of the registers
        if (debug_statements) {
            for (int i = 0; i < rc; i++) {
                printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
            }
        }

        return 0;

    }

    /**
     * This function is used when a 32bit float register is desired to be read
     * @param address The first 16bit register address
     * @return The float value which is composed of the addressed 16bit register and the one following it
     */
    float read_float_from_register(int address);

    /**
     * This function is used to read a ushort (usigned 16 bit) register
     * @param address The address to read from
     * @return The ushort value
     */
    uint32_t read_ushort_from_register(int address);

    /**
     * Create the default constructor
     */
    ModbusWrapper() = default;

    /**
     * Defined destructor to free memory when program terminates
     */
    ~ModbusWrapper();

private:
    /**
     * Stores the name of the device
     */
    std::string device_name_;
    /**
     * Pointer to modbus_wrapper structure
     */
    modbus_t *mb_ = nullptr;

    /**
     * Determines if modbus_wrapper debug statements are printed
     */
    bool debug_statements = false;

    /**
     * Sets the debug level based on the debug_statment boolean value
     */
    void set_debug_level();
};


#endif //MODBUS_DRIVER_MODBUS_WRAPPER_H
