#include "modbus_device.h"
#include <cstring>

int ModbusDevice::init(const std::string &device_port, const std::string &device_name, int slave_number, int baud_rate, char parity, int data_bits, int stop_bits)
{
    std::cout << "Initialize " << device_name << " modbus protocol." << std::endl;

    // Set device name
    device_name_ = device_name;

    // Create the new modbus device
    mb_ = modbus_new_rtu(device_port.c_str(), baud_rate, parity, data_bits, stop_bits);
    if (mb_ == NULL) {
        fprintf(stderr, "Failed to create new rtu device for device %s: \n", device_name_.c_str());
        return -1;
    }

    // Set the slave ID
    modbus_set_slave(mb_, slave_number);

    // Establish a Modbus Connection
    if (modbus_connect(mb_) == -1) {
        fprintf(stderr, "Modbus connection failed for device %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }

    // Determine if modbus debug statements are going ot be printed
    set_debug_level();

    // This read register is just to wake up the Aqua Troll, the results can be ignored
    uint16_t tab_reg[1];
    modbus_read_registers(mb_, 1, 1, tab_reg);

    // Set the master timeout time
    modbus_set_response_timeout(mb_, 60, 0);

    std::cout << "Done initializing " << device_name << "." << std::endl;

    return 0;
}


int ModbusDevice::write_to_register(int location, int value)
{
    // Attempt to write the value at the register location
    if (modbus_write_register(mb_, location, value) == -1)
    {
        fprintf(stderr, "Modbus Write Register fail for deivce %s: %s\n", device_name_.c_str(),  modbus_strerror(errno));
        return -1;
    }

    return 0;
}


float ModbusDevice::read_float_from_register(int address)
{
    float f;
    uint32_t i;
    std::array<uint16_t , 2> tab_reg{0};

    std::cout << "Reading registers for " << device_name_ << "." << std::endl;
    int result = read_from_register(address, 2, tab_reg);
    std::cout << "Done reading registers for " << device_name_ << "." << std::endl;

    if (result == -1 )
    {
        return -1;
    }

    i = ((static_cast<uint32_t>(tab_reg[0])) << 16) + tab_reg[1];
    memcpy(&f, &i, sizeof(float));

    std::cout << f << std::endl;
    return f;
}



ModbusDevice::~ModbusDevice() {
    if (mb_ != nullptr) {
        modbus_close(mb_);
        modbus_free(mb_);
    }
}

void ModbusDevice::set_debug_level()
{
    if (mb_ == nullptr) {
        std::cout << "Please initialize Modbus Device before setting debug level" << std::endl;
    }

    // This can be uncommented if debug statements are desired for modbus,
    if (debug_statements)
    {
        modbus_set_debug(mb_, TRUE);
    } else {
        modbus_set_debug(mb_, FALSE);
    }
}
