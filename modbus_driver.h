#ifndef MODBUS_DRIVER_MODBUS_DRIVER_H
#define MODBUS_DRIVER_MODBUS_DRIVER_H
#include <vector>

enum class ModbusDevices {
    kArduino = 0,
    kAquaTroll500,
};

class ModbusDriver {
public:
    std::vector<>
private:
    static constexpr int kNumberOfSupportedDevices = 10;
};


#endif //MODBUS_DRIVER_MODBUS_DRIVER_H
