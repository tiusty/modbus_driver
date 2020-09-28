#include <iostream>

#include "modbus_device.h"
#include <aqua_troll.h>

int main() {
    // Declare the devices
    ModbusDevice aqua_troll_500;
    ModbusDevice arduino;

    /* Initialize the desired devices */

    // Initialize the aqua troll
    if (aqua_troll_500.init("/dev/ttyS5", "Aqua Troll 500", 1, 19200, 'E', 8, 1) == -1) {
        std::cout << "Failed to initialize device, exiting" << std::endl;
        return -1;
    }

    // Initial the Arduino
    if (arduino.init("/dev/ttyS6", "Arduino", 1, 9600, 'N', 8, 1) == -1) {
        std::cout << "Failed to initialize device, exiting" << std::endl;
        return -1;
    }

    /* Logic to handle communication with the Aqua Troll */

    // Read parameters for temperature
    float temp_value = aqua_troll_500.read_float_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::temperature,
                                          aqua_troll::parameter_points::value));

    uint16_t temp_data_quality = aqua_troll_500.read_ushort_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::temperature,
                                          aqua_troll::parameter_points::data_quality));
    std::cout << "Temperature data quality is " << temp_data_quality << std::endl;

    uint16_t temp_units = aqua_troll_500.read_ushort_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::temperature,
                                          aqua_troll::parameter_points::units_id));
    std::string temp_units_str = temp_units == 1 ? "Celsius" : "Fahrenheit";
    std::cout << "Temperature value is: " << temp_value << " " << temp_units_str << std::endl;

    // Now change the units of temperature
    std::cout << "Changing Units of Temperature" << std::endl;
    uint16_t new_temp_units = 1;
    if (temp_units == 1)
    {
        new_temp_units = 2;
    }
    aqua_troll_500.write_to_registers(aqua_troll::calculate_address(aqua_troll::parameter_name::temperature,
                                                                    aqua_troll::parameter_points::units_id),
                                      new_temp_units);

    // read the values of temperature again
    temp_value = aqua_troll_500.read_float_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::temperature,
                                          aqua_troll::parameter_points::value));

    temp_units = aqua_troll_500.read_ushort_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::temperature,
                                          aqua_troll::parameter_points::units_id));
    temp_units_str = temp_units == 1 ? "Celsius" : "Fahrenheit";
    std::cout << "Temperature value is: " << temp_value << " " << temp_units_str << std::endl;

    // Read parameters for resistivity
    float resistivity_value = aqua_troll_500.read_float_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::resistivity,
                                          aqua_troll::parameter_points::value));
    std::cout << "Resistivity value is: " << resistivity_value << std::endl;

    uint16_t resistivity_data_quality = aqua_troll_500.read_ushort_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::resistivity,
                                          aqua_troll::parameter_points::data_quality));
    std::cout << "Resistivity data quality is " << resistivity_data_quality << std::endl;

    uint16_t resistivity_units_id = aqua_troll_500.read_ushort_from_register(
            aqua_troll::calculate_address(aqua_troll::parameter_name::resistivity,
                                          aqua_troll::parameter_points::units_id));
    std::cout << "Resistivity units id is: " << resistivity_units_id << std::endl;



    /* Logic to control communication with the Arduino */

    // Set value to 1 to turn on the LED
    arduino.write_to_register_function_06(0,1);

    return 0;
}



