#include <string>

#ifndef MODBUS_DRIVER_AQUA_TROLL_H
#define MODBUS_DRIVER_AQUA_TROLL_H

/**
 * Entry function that runs the aqua troll functionality
 * @param comm_port The comm port the aqua troll is on
 * @return The error status code
 */
int run_aqua_troll_500(const std::string &comm_port);

#endif //MODBUS_DRIVER_AQUA_TROLL_H
