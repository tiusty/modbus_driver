#include <iostream>

#include <modbus/modbus.h>

int main() {
    modbus_t *mb;
    uint16_t tab_reg[32];

    mb = modbus_new_rtu("/dev/ttyS5", 9600, 'N', 8, 1);
    if (mb == NULL) {
        fprintf(stderr, "Unable to create the libmodbus context\n");
        return -1;
    }
    int rc = modbus_set_slave(mb, 1);
    std::cout << "Setting slave ID, status: " << rc << std::endl;
    modbus_set_debug(mb, TRUE);

    if (modbus_rtu_set_serial_mode(mb, MODBUS_RTU_RS485) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
    }
    int rc2 = modbus_rtu_get_serial_mode(mb);
    std::cout << rc2 << std::endl;
    if (modbus_connect(mb) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
    } else {
        std::cout << "Connected!" << std::endl;
        /* Read 5 registers from the address 0 */

        if ( modbus_write_register(mb, 0, 1) == -1) {
            fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        } else {
            std::cout << "Wrote to register!" << std::endl;
        }
    }

    modbus_close(mb);
    modbus_free(mb);
    return 0;
}



