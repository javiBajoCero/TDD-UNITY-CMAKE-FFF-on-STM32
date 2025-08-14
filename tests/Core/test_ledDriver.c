#include "unity.h"
#include "unity_fixture.h"

#include "LedDriver.h"

TEST_GROUP(LEDDriver);

TEST_SETUP(LEDDriver) {
}

TEST_TEAR_DOWN(LEDDriver) {
}

TEST(LEDDriver, test_led_on) {
    TEST_ASSERT_TRUE(1);
}


TEST_GROUP_RUNNER(LEDDriver) {
    RUN_TEST_CASE(LEDDriver, test_led_on);
}