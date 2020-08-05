
#ifndef MODBUS_DRIVER_MODBUS_DEVICE_H
#define MODBUS_DRIVER_MODBUS_DEVICE_H

#include <modbus/modbus.h>
#include <string>

class ModbusDevice {
public:
    std::string device_name_;
    modbus_t *mb_;
    ~ModbusDevice();
};


#endif //MODBUS_DRIVER_MODBUS_DEVICE_H
