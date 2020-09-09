//
// Created by Alex on 9/9/2020.
//

#ifndef MODBUS_DRIVER_AQUA_TROLL_H
#define MODBUS_DRIVER_AQUA_TROLL_H

namespace aqua_troll {
    /**
     * The parameters points are the 7 registers associated with each parameter.
     * These are taken from page 37 of the aqua troll 500 manual
     *
     * value (float) -> The measured value from the sensor
     * data_quality (ushort) -> 0 means no error, otherwise check the system specs for the error
     * units_id (ushort) -> Unit id for the measured value. Table on page 57 of aqua troll manual
     * parameter_id (ushort) -> The ID of the parameter for this location
     * offline_sentinel_value (float) -> The value that's return on error or if the parameter is not available
     */
    namespace parameter_points {
        constexpr int value = 0;
        constexpr int data_quality = 2;
        constexpr int units_id = 3;
        constexpr int parameter_id = 4;
        constexpr int offline_sentinel_value = 5;
    }

    /**
     * The different parameters that could be available depending on the installed sensors
     *
     * Units depend on what they are set to and can be read from the parameter point units_id
     */
    namespace parameter_name {
        constexpr int temperature = 1;
        constexpr int pressure = 2;
        constexpr int depth = 3;
        constexpr int level_depth_to_water = 4;
        constexpr int level_surface_elevation = 5;
    }

    /**
     * Given a paramtere_id, calcaulte the starting reigster for that parameter. Each parameter
     *  has 7 registers associated with it starting at the starting_register.
     *
     *  Usually calculate_address should be used, not this one
     * @param parameter_id The desired parameter id
     * @return The starting register address
     */
    constexpr int starting_register(int parameter_id)
    {
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
    constexpr int calculate_address(int parameter_id, int parameter_point)
    {
        // Modbus requires subtracting one because of the way it calculates the holding register
        return starting_register(parameter_id) + parameter_point - 1;
    }
}

#endif //MODBUS_DRIVER_AQUA_TROLL_H
