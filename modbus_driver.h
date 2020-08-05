#ifndef MODBUS_DRIVER_MODBUS_DRIVER_H
#define MODBUS_DRIVER_MODBUS_DRIVER_H
#include <vector>
#include "modbus_device.h"

class ModbusDriver {
public:
    int initialize_device(ModbusDevice &device, const std::string &device_port, const std::string &device_name, int baud_rate = 9600, char parity = 'N', int data_bits = 8, int stop_bits = 1);
private:
    std::vector<ModbusDevice> devices_;
    int number_of_added_devices_ = 1;
    static constexpr int kNumberOfSupportedDevices = 10;
};


#endif //MODBUS_DRIVER_MODBUS_DRIVER_H
