//
// Created by Alex on 9/9/2020.
//

#ifndef MODBUS_DRIVER_AQUA_TROLL_H
#define MODBUS_DRIVER_AQUA_TROLL_H

namespace aqua_troll {
    namespace parameter_name {
        constexpr int temperature = 1;
        constexpr int pressure = 2;
        constexpr int depth = 3;
        constexpr int level_depth_to_water = 4;
        constexpr int level_surface_elevation = 5;
    }
    namespace parameter_points {
        constexpr int value = 0;
        constexpr int data_quality = 2;
        constexpr int units_id = 3;
        constexpr int parameter_id = 4;
        constexpr int offline_sentinel_value = 5;
    }

    constexpr int starting_register(int parameter_id)
    {
        return (parameter_id - 1) * 7 + 5451;
    }

    constexpr int calculate_address(int parameter_name, int parameter_point)
    {
        return starting_register(parameter_name) + parameter_point - 1;
    }
}

#endif //MODBUS_DRIVER_AQUA_TROLL_H
