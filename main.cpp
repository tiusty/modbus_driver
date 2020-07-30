#include <iostream>

#include <modbus/modbus.h>

int main() {
    modbus_t *mb;
    uint16_t tab_reg[32];

    mb = modbus_new_rtu("\\\\.\\COM5", 9600, 'N', 8, 1);
    int rc = modbus_set_slave(mb, 1);
    std::cout << "Setting slave ID " << rc << std::endl;
    if (modbus_connect(mb) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
    } else {
        std::cout << "Connected!" << std::endl;
        /* Read 5 registers from the address 0 */
        modbus_write_register(mb, 40001, 1);
        std::cout << "Wrote to register!" << std::endl;
    }

    modbus_close(mb);
    modbus_free(mb);
    return 0;
}



