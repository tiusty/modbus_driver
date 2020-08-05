
#ifndef MODBUS_DRIVER_MODBUS_DEVICE_H
#define MODBUS_DRIVER_MODBUS_DEVICE_H

#include <modbus/modbus.h>
#include <string>

class ModbusDevice {
public:
    int init(const std::string &device_port, const std::string &device_name, int slave_number, int baud_rate = 9600, char parity = 'N', int data_bits = 8, int stop_bits = 1);
    void write_to_register(int location, int value);

    ~ModbusDevice();
private:
    std::string device_name_;
    modbus_t *mb_;
};


#endif //MODBUS_DRIVER_MODBUS_DEVICE_H
