#include "modbus_device.h"
#include <bitset>
#include <cstring>

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


float ModbusDevice::read_float_from_register(int address)
{
    float f;
    uint32_t i;
    std::array<uint16_t , 2> tab_reg{0};

    int result = read_from_register(address, 2, tab_reg);

    if (result == -1 )
    {
        return -1;
    }

    i = (((uint32_t)tab_reg[0]) << 16) + tab_reg[1];
    memcpy(&f, &i, sizeof(float));

    std::cout << f << std::endl;
    return f;
}

ModbusDevice::~ModbusDevice() {
    if (mb_ != nullptr) {
        modbus_close(mb_);
        modbus_free(mb_);
    }
}
