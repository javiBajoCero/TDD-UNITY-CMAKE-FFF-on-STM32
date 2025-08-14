#include "unity.h"
#include "unity_fixture.h"

#include "main.h"
#include "ledDriver.h"

TEST_GROUP(LEDDriver);

TEST_SETUP(LEDDriver) {
    ledDriver_Init(GREEN_LED_Pin, GREEN_LED_GPIO_Port);
}

TEST_TEAR_DOWN(LEDDriver) {
}

TEST(LEDDriver, test_is_initially_off) {
    TEST_ASSERT_TRUE(HAL_GPIO_ReadPin(GREEN_LED_GPIO_Port, GREEN_LED_Pin) == GPIO_PIN_RESET);
}

TEST(LEDDriver, test_led_on) {
    ledDriver_ledOn();
    TEST_ASSERT_TRUE(HAL_GPIO_ReadPin(GREEN_LED_GPIO_Port, GREEN_LED_Pin) == GPIO_PIN_SET);
}

TEST(LEDDriver, test_led_off) {
    ledDriver_ledOff();
    TEST_ASSERT_TRUE(HAL_GPIO_ReadPin(GREEN_LED_GPIO_Port, GREEN_LED_Pin) == GPIO_PIN_RESET);
}

TEST(LEDDriver, test_led_toggle) {
    ledDriver_ledOn();
    TEST_ASSERT_TRUE(HAL_GPIO_ReadPin(GREEN_LED_GPIO_Port, GREEN_LED_Pin) == GPIO_PIN_SET);
    ledDriver_ledOff();
    TEST_ASSERT_TRUE(HAL_GPIO_ReadPin(GREEN_LED_GPIO_Port, GREEN_LED_Pin) == GPIO_PIN_RESET);
    ledDriver_ledOn();
    TEST_ASSERT_TRUE(HAL_GPIO_ReadPin(GREEN_LED_GPIO_Port, GREEN_LED_Pin) == GPIO_PIN_SET);
    ledDriver_ledOff();
    TEST_ASSERT_TRUE(HAL_GPIO_ReadPin(GREEN_LED_GPIO_Port, GREEN_LED_Pin) == GPIO_PIN_RESET);
}


TEST_GROUP_RUNNER(LEDDriver) {
    RUN_TEST_CASE(LEDDriver, test_is_initially_off);
    RUN_TEST_CASE(LEDDriver, test_led_on);
    RUN_TEST_CASE(LEDDriver, test_led_off);
    RUN_TEST_CASE(LEDDriver, test_led_toggle);
}