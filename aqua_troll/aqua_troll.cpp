//
// Created by Alex on 9/27/2020.
//
#include "modbus_wrapper.h"
#include <aqua_troll_private.h>
#include <functional>
#include <thread>
#include <chrono>

void timer_start(std::function<int(const std::string &)> func, unsigned int interval, const std::string &comm_port);
int print_data_values(const std::string &comm_port);

void run_aqua_troll_500(const std::string &comm_port) {
    // Start a timer function that runs on the specified frequency
    timer_start(print_data_values, 1000, comm_port);

    // Runs forever
    while (true)
        ;
}

void timer_start(std::function<int(const std::string &)> func, unsigned int interval, const std::string &comm_port) {
    /**
     * Runs the desired function on a specified interval
     * The interval must be shorter than the time it takes to run the function
     *  Otherwise the function will continuously run
     *
     *  @param func: The function that will run on the specified interval
     *  @param interval: The interval in milliseconds that the function should run on
     *  @param comm_port: The comm port that the device is on
     */
    std::thread([func, interval, comm_port]() {
                    while (true) {
                        // Determine the end time of the interval before the function is run, so the function
                        //  run time doesn't affect when the function will run next
                        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);

                        // Run the Aqua Troll Function
//                        func(comm_port);

                        // Sleep until the interval is over
                        std::this_thread::sleep_until(x);
                    }
                }
    ).detach();
}

int print_data_values(const std::string &comm_port) {
    /**
     * An example Aqua Troll function that can be run
     */
    // Declare the Modbus Device
    ModbusWrapper aqua_troll_500;

    /* Initialize the desired device */

    // Initialize the aqua troll
    if (aqua_troll_500.init(comm_port, "Aqua Troll 500", 1, 19200, 'E', 8, 1) == -1) {
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
    std::array<uint16_t, 1> new_temp_units = {1};
    if (temp_units == 1) {
        new_temp_units.at(0) = 2;
    }
    aqua_troll_500.write_to_registers(aqua_troll::calculate_address(aqua_troll::parameter_name::temperature,
                                                                    aqua_troll::parameter_points::units_id),
                                      1,
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

    return 0;

}
