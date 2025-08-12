#include "unity.h"
#include "fff.h"

DEFINE_FFF_GLOBALS;

void setUp(void) {}
void tearDown(void) {}

void test_truth(void) {
    TEST_ASSERT_TRUE(1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_truth);
    return UNITY_END();
}
