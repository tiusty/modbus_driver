#include <thread>
#include "aqua_troll/aqua_troll.h"
#include "arduino/arduino.h"

/**
 * Main function that defines the comm ports and starts the execution of the
 *  various sensors
 * @return
 */
int main() {
    // Run each sensor in it's own thread
    std::thread aqua_troll {run_aqua_troll_500, "/dev/ttyS5"};
    std::thread arduino {run_arduino, "/dev/ttyS6"};

    // Wait for all the devices to finish before exiting
    aqua_troll.join();
    arduino.join();

    return 0;
}



