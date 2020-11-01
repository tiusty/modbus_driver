//
// Created by Alex on 10/31/2020.
//
#include "modbus.h"
int Modbus::set_debug(modbus_t *ctx, int flag)
{
    return modbus_set_debug(ctx, flag);
}
