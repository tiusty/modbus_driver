#include <iostream>

#include <modbus/modbus.h>

int main() {
    modbus_t *mb;
    modbus_t *tb;
    uint16_t tab_reg[32];

    mb = modbus_new_rtu("/dev/ttyS6", 9600, 'N', 8, 1);
    if (mb == NULL) {
        fprintf(stderr, "Unable to create the libmodbus context\n");
        return -1;
    }
    tb = modbus_new_rtu("/dev/ttyS6", 9600, 'N', 8, 1);
    if (tb == NULL) {
        fprintf(stderr, "Unable to create the libmodbus context 2\n");
        return -1;
    }
    int rc = modbus_set_slave(mb, 1);
    std::cout << "Setting slave ID, status: " << rc << std::endl;
//    modbus_set_debug(mb, TRUE);

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

//        if (modbus_read_registers(mb, 0, 10, tab_reg) == -1) {
//            fprintf(stderr, "Read Register failed: %s\n", modbus_strerror(errno));
//        } else {
//            std::cout << "Register value is: " << tab_reg[0] << std::endl;

            if ( modbus_write_register(mb, 0, 1) == -1) {
                fprintf(stderr, "Write register failed: %s\n", modbus_strerror(errno));
            } else {
                if (modbus_read_registers(mb, 0, 10, tab_reg) == -1) {
                    fprintf(stderr, "Read Register failed: %s\n", modbus_strerror(errno));
                } else {
                    std::cout << "Register value is: " << tab_reg[0] << std::endl;
                }
            }
        }
//    }

    modbus_close(mb);
    modbus_free(mb);
    return 0;
}



