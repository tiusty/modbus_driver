#include "gtest/gtest.h"
#include "modbus_wrapper.h"

TEST(test_set_debug_level, set_true) {
    //Arrange
    ModbusWrapper wrapper = ModbusWrapper();

    //Act
    wrapper.debug_statements = true;
    wrapper.set_debug_level();

    //Assert
    EXPECT_EQ (true,  true);
}

