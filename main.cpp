#include <iostream>
#include <array>

#include "modbus_device.h"
#include <aqua_troll.h>

int main() {
    // Declare the devices
    ModbusDevice aqua_troll_500;

    // Initialize the desired devices
    if (aqua_troll_500.init("/dev/ttyS5", "Aqua Troll 500", 1, 19200, 'E', 8, 1) == -1)
    {
        std::cout << "Failed to initialize device, exiting" << std::endl;
        return -1;
    }

    // Read parameters for temperature
    float temp_value = aqua_troll_500.read_float_from_register(aqua_troll::calculate_address(aqua_troll::parameter_name::temperature, aqua_troll::parameter_points::value));
    std::cout << "Temperature value is: " << temp_value << " celcius" << std::endl;

    uint16_t temp_data_quality = aqua_troll_500.read_ushort_from_register(aqua_troll::calculate_address(aqua_troll::parameter_name::temperature, aqua_troll::parameter_points::data_quality));
    std::cout << "Temperature data quality is " << temp_data_quality << std::endl;

    uint16_t  temp_units = aqua_troll_500.read_ushort_from_register(aqua_troll::calculate_address(aqua_troll::parameter_name::temperature, aqua_troll::parameter_points::units_id));
    std::cout << "Temperature units id is " << temp_units << std::endl;

    // Read parameters for resistivity
    float resistivity_value = aqua_troll_500.read_float_from_register(aqua_troll::calculate_address(aqua_troll::parameter_name::resistivity, aqua_troll::parameter_points::value));
    std::cout << "Resistivity value is: " << resistivity_value << std::endl;

    uint16_t resistivity_data_quality = aqua_troll_500.read_ushort_from_register(aqua_troll::calculate_address(aqua_troll::parameter_name::resistivity, aqua_troll::parameter_points::data_quality));
    std::cout << "Resistivity data quality is " << resistivity_data_quality << std::endl;

    uint16_t resistivity_units_id = aqua_troll_500.read_ushort_from_register(aqua_troll::calculate_address(aqua_troll::parameter_name::resistivity, aqua_troll::parameter_points::units_id));
    std::cout << "Resistivity units id is: " << resistivity_units_id << std::endl;

    return 0;
}



