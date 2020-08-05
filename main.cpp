#include <iostream>

#include "modbus_device.h"

int main() {
    ModbusDevice Arudino;
    Arudino.init("/dev/ttyS6", 1, "Arudino");
    Arudino.write(1,0);


    return 0;
}



