//
// Created by Alex on 8/5/2020.
//

#include "modbus_driver.h"

int ModbusDriver::initialize_device(ModbusDevice &device, const std::string &device_port, const std::string &device_name, int baud_rate, char parity, int data_bits, int stop_bits)
{
    // Set device name
    device.device_name_ = device_name;

    // Create the new modbus device
    device.mb_ = modbus_new_rtu(device_port.c_str(), baud_rate, parity, data_bits, stop_bits);
    if (device.mb_ == NULL) {
        fprintf(stderr, "Failed to create new rtu device for device %s: \n", device.device_name_.c_str());
        return -1;
    }

    // Set the slave ID
    modbus_set_slave(device.mb_, number_of_added_devices_);

//    if (modbus_rtu_set_serial_mode(mb, MODBUS_RTU_RS485) == -1) {
//        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
//    }

    if (modbus_connect(device.mb_) == -1) {
        fprintf(stderr, "Modbus connection failed for device %s: %s\n", device.device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }

    number_of_added_devices_++;
    return 0;
}
