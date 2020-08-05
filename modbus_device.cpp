//
// Created by Alex on 8/5/2020.
//

#include "modbus_device.h"

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

//    if (modbus_rtu_set_serial_mode(mb, MODBUS_RTU_RS485) == -1) {
//        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
//    }

    if (modbus_connect(mb_) == -1) {
        fprintf(stderr, "Modbus connection failed for device %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }

    return 0;
}


int ModbusDevice::write_to_register(int location, int value)
{
    if (modbus_write_register(mb_, location, value) == -1)
    {
        fprintf(stderr, "Modbus Write Register fail for deivce %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }

    return 0;
}


ModbusDevice::~ModbusDevice() {
    if (mb_ != nullptr) {
        modbus_close(mb_);
        modbus_free(mb_);
    }
}
