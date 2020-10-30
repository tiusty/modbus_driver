#ifndef MODBUS_DRIVER_AQUA_TROLL_PRIVATE_H
#define MODBUS_DRIVER_AQUA_TROLL_PRIVATE_H

/**
 * This namespace contains the register information for the aqua troll.
 *
 * This is meant to be used with the ModbusWrapper class. This namespace provides an easy way
 *  to access register location for each parameter/sensor
 */
namespace aqua_troll {

    /**
     * Device parameters for the aqua troll 500
     *  Values are specified from the documentation
     */
    namespace device {
        // This is just a user friendly name for logging
        //  this is not from the documentation
        constexpr char name[] = "Aqua Troll 500";
        constexpr int slave_number = 1;
        constexpr int baud_rate = 19200;
        constexpr char parity = 'E';
        constexpr int data_bits = 8;
        constexpr int stop_bits = 1;
    }

    /**
     * The parameters points are the 7 registers associated with each parameter.
     * These are taken from page 37 of the aqua troll 500 manual
     *
     * NOte: When writing to Aqua Troll values, must use function code 16 (write to registers)
     *  I.e don't use the write_to_register function, use the write_to_registers function with array size 1
     *
     * value (R) (float) -> The measured value from the sensor
     * data_quality (R) (ushort) -> 0 means no error, otherwise check the system specs for the error
     * units_id (R/W)  (ushort) -> Unit id for the measured value. Table on page 57 of aqua troll manual
     * parameter_id (R) (ushort) -> The ID of the parameter for this location
     * offline_sentinel_value (R/W) (float) -> The value that's return on error or if the parameter is not available
     */
    namespace parameter_points {
        constexpr int value = 0;
        constexpr int data_quality = 2;
        constexpr int units_id = 3;
        constexpr int parameter_id = 5;
        constexpr int offline_sentinel_value = 5;
    }

    /**
     * The different parameters that could be available depending on the installed sensors
     *
     * Units depend on what they are set to and can be read from the parameter point units_id
     * These values are from page 55 of the aqua troll manual
     * https://in-situ.com/pub/media/support/documents/at500-manual.pdf
     *
     * Not all the parameters are added since the list would get long. As sensors are added,
     *  the corresponding parameter_id can be added below
     */
    namespace parameter_name {
        constexpr int temperature = 1;
        constexpr int pressure = 2;
        constexpr int depth = 3;
        constexpr int level_depth_to_water = 4;
        constexpr int level_surface_elevation = 5;
        constexpr int actual_conductivity = 9;
        constexpr int specific_conductivity = 10;
        constexpr int resistivity = 11;
        constexpr int salinity = 12;
    }

    /**
     * Given a parameter_id, calculate the starting register for that parameter. Each parameter
     *  has 7 registers associated with it starting at the starting_register.
     *
     *  Usually the calculate_address function should be used, not this function
     * @param parameter_id The desired parameter id
     * @return The starting register address
     */
    constexpr int starting_register(int parameter_id) {
        return (parameter_id - 1) * 7 + 5451;
    }

    /**
     * Calculates the address for a parameter point for a specific parameter id.
     *
     * This should be the go to function that will determine the desired register depending
     *  on the parameter desired and the parameter point of that parameter, i.e value, units_id etc
     * @param parameter_name The desired parameter id
     * @param parameter_point The desired parameter point for the parameter id
     * @return The address for that parameter point for the parameter id
     *
     *
     * Example usage:
     *
     * This gets the address for the measured temperature value
     * aqua_troll::calculate_address(aqua_troll::parameter_name::temperature, aqua_troll::parameter_points::value)
     */
    constexpr int calculate_address(int parameter_id, int parameter_point) {
        // Modbus requires subtracting one because of the way it calculates the holding register
        return starting_register(parameter_id) + parameter_point - 1;
    }
}

#endif //MODBUS_DRIVER_AQUA_TROLL_PRIVATE_H
