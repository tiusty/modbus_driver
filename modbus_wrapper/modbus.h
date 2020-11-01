//
// Created by Alex on 10/31/2020.
//

#ifndef MODBUS_DRIVER_MODBUS_H
#define MODBUS_DRIVER_MODBUS_H
#include "modbus_interface.h"
#include <modbus/modbus.h>

class Modbus : public ModbusInterface {
public:
    virtual int set_debug(modbus_t *ctx, int flag) override;
};


#endif //MODBUS_DRIVER_MODBUS_H
