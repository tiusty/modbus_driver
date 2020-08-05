
#ifndef MODBUS_DRIVER_MODBUS_DEVICE_H
#define MODBUS_DRIVER_MODBUS_DEVICE_H

#include <modbus/modbus.h>
#include <string>

class ModbusDevice {
public:
    int init(const std::string &device_port, int slave_number, std::string &device_name, int baud_rate = 9600, char parity = 'N', int data_bits = 8, int stop_bits = 1);
    ~ModbusDevice();
private:
    modbus_t *mb_;
    std::string device_name_;
};


#endif //MODBUS_DRIVER_MODBUS_DEVICE_H