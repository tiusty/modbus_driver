#include "modbus_wrapper.h"
#include <cstring>

int ModbusWrapper::init(const std::string &device_port, const std::string &device_name, int slave_number, int baud_rate,
                        char parity, int data_bits, int stop_bits) {

    if (debug_statements) {
        std::cout << "Initialize " << device_name << " modbus_wrapper protocol." << std::endl;
    }

    // Set device name
    device_name_ = device_name;

    // Create the new modbus_wrapper device
    mb_ = modbus_new_rtu(device_port.c_str(), baud_rate, parity, data_bits, stop_bits);
    if (mb_ == nullptr) {
        fprintf(stderr, "Failed to create new rtu device for device %s: \n", device_name_.c_str());
        return -1;
    }

    // Set the slave ID
    modbus_set_slave(mb_, slave_number);

    // Establish a Modbus Connection
    if (modbus_connect(mb_) == -1) {
        fprintf(stderr, "Modbus connection failed for device %s: %s\n", device_name_.c_str(), modbus_strerror(errno));
        return -1;
    }

    // Determine if modbus_wrapper debug statements are going ot be printed
    set_debug_level();

    // This read register is just to wake up the Aqua Troll, the results can be ignored
    uint16_t tab_reg[1];
    modbus_read_registers(mb_, 1, 1, tab_reg);

    // Set the master timeout time
    modbus_set_response_timeout(mb_, 60, 0);

    if (debug_statements) {
        std::cout << "Done initializing " << device_name << "." << std::endl;
    }

    return 0;
}

int ModbusWrapper::write_to_register(int location, uint16_t value) {
    // Attempt to write the value at the register location
    if (modbus_write_register(mb_, location, value) == -1) {
        fprintf(stderr, "Modbus Write Register fail for device %s: %s\n", device_name_.c_str(), modbus_strerror(errno));
        return -1;
    }

    return 0;
}


float ModbusWrapper::read_float_from_register(int address) {
    float f;
    uint32_t i;
    std::array<uint16_t, 2> tab_reg{0};

    if (read_from_register(address, 2, tab_reg) == -1) {
        return -1;
    }

    // Convert the 2 uint16 values to a float
    i = ((static_cast<uint32_t>(tab_reg[0])) << 16) + tab_reg[1];
    memcpy(&f, &i, sizeof(float));

    return f;
}

uint32_t ModbusWrapper::read_ushort_from_register(int address) {
    std::array<uint16_t, 1> tab_reg{0};

    if (read_from_register(address, 1, tab_reg) == -1) {
        return -1;
    }

    return tab_reg[0];
}

ModbusWrapper::~ModbusWrapper() {
    // Free memory if it is activated
    if (mb_ != nullptr) {
        modbus_close(mb_);
        modbus_free(mb_);
    }
}

void ModbusWrapper::set_debug_level() {
    if (mb_ == nullptr) {
        std::cout << "Please initialize Modbus Device before setting debug level" << std::endl;
    }

    // This can be uncommented if debug statements are desired for modbus_wrapper,
    if (debug_statements) {
        modbus_set_debug(mb_, TRUE);
    } else {
        modbus_set_debug(mb_, FALSE);
    }
}
