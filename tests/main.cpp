#include <gtest/gtest.h>
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

// Google Test can be run manually from the main() function
// or, it can be linked to the gtest_main library for an already
// set-up main() function primed to accept Google Test test cases.
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
