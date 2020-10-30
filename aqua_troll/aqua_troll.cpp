#include <modbus_wrapper.h>
#include <aqua_troll_private.h>
#include <functional>
#include <thread>
#include <chrono>
#include <mutex>

// Mutex to protect critical sections of code
// Every function that is running should acquire the lock
//  to prevent race conditions.
std::mutex mtx;

// Specify that the namespace is using aqua troll
using namespace aqua_troll;

// Function declarations
void
timer_start(const std::function<int(const std::string &)> &func, unsigned int interval, const std::string &comm_port);

int change_temperature_units(const std::string &comm_port);

int print_temperature_values(const std::string &comm_port);

int print_resistivity_values(const std::string &comm_port);




/**
 * Various file_names to store values to
 */
namespace file_names {
    constexpr char temperature_units[] = "temperature_units.txt";
    constexpr char temperature_value[] = "temperature_values.txt";
    constexpr char resistivity_value[] = "resistivity_values.txt";
}


void run_aqua_troll_500(const std::string &comm_port) {
    /**
     * The entry function for the aqua troll functionality
     *  All aqua troll functionality should be called here
     *
     *  @param comm_port: THe comm port for the aqua troll
     */
    // Change the temperature units of the Aqua Troll every 10 seconds
    timer_start(change_temperature_units, 10000, comm_port);

    // Print out and store the temperature every 5 seconds
    timer_start(print_temperature_values, 5000, comm_port);

    // Print out and store the resistivity values every 15 seconds
    timer_start(print_resistivity_values, 15000, comm_port);

    // Runs forever
    while (true);
}

void
timer_start(const std::function<int(const std::string &)> &func, unsigned int interval, const std::string &comm_port) {
    /**
     * Runs the desired function on a specified interval
     * The interval must be shorter than the time it takes to run the function
     *  Otherwise the function will continuously run
     *
     *  Note: This timer function acquires the mutex as part of the timer function
     *      so the functions that use the timer should not try to attempt to
     *      acquire the lock as well, otherwise it will cause a deadlock since
     *      it already acquired the lock
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

                        // These curly braces are essential to make sure the mutex
                        //  goes out of scope when the function finishes executing
                        //  thus releasing the lock
                        {
                            // The first step every iteration is to acquire the mutex
                            // to prevent against race conditions of two or more threads trying to read/write to
                            // the aqua troll at the same time
                            std::unique_lock<std::mutex> lck(mtx);

                            // Run the Aqua Troll Function
                            func(comm_port);
                        }

                        // Sleep until the interval is over
                        std::this_thread::sleep_until(x);
                    }
                }
    ).detach();
}

int print_temperature_values(const std::string &comm_port) {
    /**
     * An example Aqua Troll function that can be run
     * Prints out the temperature values of the Aqua Troll 500
     *  Stores the result to a file
     *
     * @param comm_port: The comm port for the aqua troll
     */
    /* Initialize the desired device */

    // Declare the Modbus Device
    ModbusWrapper aqua_troll_500;

    // Initialize the aqua troll
    if (aqua_troll_500.init(comm_port, device::name, device::slave_number, device::baud_rate, device::parity,
                            device::data_bits, device::stop_bits) == -1) {
        std::cout << "Failed to initialize device " << device::name << ", exiting" << std::endl;
        return -1;
    }

    /* Logic to handle communication with the Aqua Troll */

    // Read parameters for temperature
    float temp_value = aqua_troll_500.read_float_from_register(
            calculate_address(parameter_name::temperature,
                                          parameter_points::value));

    uint16_t temp_data_quality = aqua_troll_500.read_ushort_from_register(
            calculate_address(parameter_name::temperature,
                                          parameter_points::data_quality));
    std::cout << "Temperature data quality is " << temp_data_quality << std::endl;

    uint16_t temp_units = aqua_troll_500.read_ushort_from_register(
            calculate_address(parameter_name::temperature,
                                          parameter_points::units_id));
    std::string temp_units_str = temp_units == 1 ? "Celsius" : "Fahrenheit";
    std::cout << "Temperature value is: " << temp_value << " " << temp_units_str << std::endl;

    // Store the new temperature value in a file
    aqua_troll_500.save_to_file(temp_value, file_names::temperature_value);


    return 0;
}

int change_temperature_units(const std::string &comm_port) {
    /**
     * An example Aqua Troll function that can be run
     * Changes the temperature units of the Aqua Troll 500
     *  Stores the result to a file
     *
     * @param comm_port: The comm port for the aqua troll
     */

    /* Initialize the desired device */

    // Declare the Modbus Device
    ModbusWrapper aqua_troll_500;

    // Initialize the aqua troll
    if (aqua_troll_500.init(comm_port, device::name, device::slave_number, device::baud_rate, device::parity,
                            device::data_bits, device::stop_bits) == -1) {
        std::cout << "Failed to initialize device " << device::name << ", exiting" << std::endl;
        return -1;
    }

    /* Logic to handle communication with the Aqua Troll */

    // Read temperature units
    uint16_t temp_units = aqua_troll_500.read_ushort_from_register(
            calculate_address(parameter_name::temperature,
                                          parameter_points::units_id));

    // Now change the units of temperature
    std::array<uint16_t, 1> new_temp_units = {1};
    if (temp_units == 1) {
        new_temp_units.at(0) = 2;
    }
    aqua_troll_500.write_to_registers(calculate_address(parameter_name::temperature,
                                                                    parameter_points::units_id),
                                      1,
                                      new_temp_units);

    temp_units = aqua_troll_500.read_ushort_from_register(
            calculate_address(parameter_name::temperature,
                                          parameter_points::units_id));
    std::string temp_units_str = temp_units == 1 ? "Celsius" : "Fahrenheit";

    // Print out the new units of temperature
    std::cout << "Temperature units are now in " << temp_units_str << std::endl;\

    // Store the the new unit in the desired file
    aqua_troll_500.save_to_file(temp_units, file_names::temperature_units);

    return 0;

}

int print_resistivity_values(const std::string &comm_port) {
    /**
     * An example Aqua Troll function that can be run
     * Prints out the resistivity values from the Aqua Troll 500
     * @param comm_port: The comm port for the aqua troll
     */
    // Declare the Modbus Device
    ModbusWrapper aqua_troll_500;

    /* Initialize the desired device */

    // Initialize the aqua troll
    if (aqua_troll_500.init(comm_port, device::name, device::slave_number, device::baud_rate, device::parity,
                            device::data_bits, device::stop_bits) == -1) {
        std::cout << "Failed to initialize device " << device::name << ", exiting" << std::endl;
        return -1;
    }

    /* Logic to handle communication with the Aqua Troll */

    // Read parameters for resistivity
    float resistivity_value = aqua_troll_500.read_float_from_register(
            calculate_address(parameter_name::resistivity,
                                          parameter_points::value));
    std::cout << "Resistivity value is: " << resistivity_value << std::endl;

    uint16_t resistivity_data_quality = aqua_troll_500.read_ushort_from_register(
            calculate_address(parameter_name::resistivity,
                                          parameter_points::data_quality));
    std::cout << "Resistivity data quality is " << resistivity_data_quality << std::endl;

    uint16_t resistivity_units_id = aqua_troll_500.read_ushort_from_register(
            calculate_address(parameter_name::resistivity,
                                          parameter_points::units_id));
    std::cout << "Resistivity units id is: " << resistivity_units_id << std::endl;

    // Store the the new value in the desired file
    aqua_troll_500.save_to_file(resistivity_value, file_names::resistivity_value);

    return 0;
}
