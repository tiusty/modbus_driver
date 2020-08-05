#include <iostream>

#include "modbus_device.h"
#include "modbus_driver.h"

int main() {
    ModbusDevice Arudino;
    ModbusDriver driver;
    driver.initialize_device(Arudino, "/dev/ttyS6", "Arudino");
    driver.write(Arudino, 0,0);


    return 0;
}



