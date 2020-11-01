#ifndef MODBUS_DRIVER_MODBUS_INTERFACE_H
#define MODBUS_DRIVER_MODBUS_INTERFACE_H
#include <modbus/modbus.h>

class ModbusInterface {
public:
    virtual int set_debug(modbus_t *ctx, int flag) = 0;
};


#endif //MODBUS_DRIVER_MODBUS_INTERFACE_H
