#include <iostream>

#include "modbus_device.h"
#include "modbus_driver.h"

int main() {
    ModbusDevice Arudino;
    ModbusDriver driver;
    driver.initialize_device(Arudino, "/dev/ttyS6", "Arudino");
    Arudino.write(1,0);


    return 0;
}



