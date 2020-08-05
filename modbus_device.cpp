//
// Created by Alex on 8/5/2020.
//

#include "modbus_device.h"

ModbusDevice::~ModbusDevice() {
    if (mb_ != nullptr) {
        modbus_close(mb_);
        modbus_free(mb_);
    }
}
