#include "modbus_device.h"
#include <bitset>

int ModbusDevice::init(const std::string &device_port, const std::string &device_name, int slave_number, int baud_rate, char parity, int data_bits, int stop_bits)
{
    // Set device name
    device_name_ = device_name;

    // Create the new modbus device
    mb_ = modbus_new_rtu(device_port.c_str(), baud_rate, parity, data_bits, stop_bits);
    if (mb_ == NULL) {
        fprintf(stderr, "Failed to create new rtu device for device %s: \n", device_name_.c_str());
        return -1;
    }

    // Set the slave ID
    modbus_set_slave(mb_, slave_number);

    // Establish a Modbus Connection
    if (modbus_connect(mb_) == -1) {
        fprintf(stderr, "Modbus connection failed for device %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }


    // This read register is just to wake up the Aqua Troll, the results can be ignored
    uint16_t tab_reg[1];
    modbus_read_registers(mb_, 1, 1, tab_reg);

    modbus_set_debug(mb_, TRUE);

    uint32_t old_response_to_sec;
    uint32_t old_response_to_usec;

    // This code is for version 3.0.6
    modbus_get_response_timeout(mb_, &old_response_to_sec, &old_response_to_usec);
    std::cout << "Old Response. Seconds: " << old_response_to_sec << " msec : " << old_response_to_usec << std::endl;

    /* Define a new and too short timeout! */
    modbus_set_response_timeout(mb_, 120, 0);

    modbus_get_response_timeout(mb_, &old_response_to_sec, &old_response_to_usec);
    std::cout << "Old Response. Seconds: " << old_response_to_sec << " msec : " << old_response_to_usec << std::endl;

    return 0;
}


int ModbusDevice::write_to_register(int location, int value)
{
    // Attempt to write the value at the register location
    if (modbus_write_register(mb_, location, value) == -1)
    {
        fprintf(stderr, "Modbus Write Register fail for deivce %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }

    return 0;
}

int ModbusDevice::read_from_register(int address, int number_of_registers)
{
    uint16_t tab_reg[2];
    for (int i=0; i < 2; i++) {
        tab_reg[i] = 0;
    }

    int rc = modbus_read_registers(mb_, address, number_of_registers, tab_reg);

    if (rc == -1)
    {
        fprintf(stderr, "Modbus read register failed %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }

    for (int i=0; i < rc; i++) {
        printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
    }


    std::cout << "rc " << rc << std::endl;
    std::cout << "first: " << tab_reg[0] << std::endl;
    std::cout << "second: " << tab_reg[1] << std::endl;

    return 0;
}


ModbusDevice::~ModbusDevice() {
    if (mb_ != nullptr) {
        modbus_close(mb_);
        modbus_free(mb_);
    }
}
