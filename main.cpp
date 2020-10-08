#include <thread>
#include "aqua_troll/aqua_troll.h"
#include "arduino/arduino.h"

int main() {
    std::thread aqua_troll {run_aqua_troll_500, "/dev/ttyS5"};
    std::thread arduino {run_arduino, "/dev/ttyS6"};

    aqua_troll.join();
    arduino.join();

    return 0;
}



