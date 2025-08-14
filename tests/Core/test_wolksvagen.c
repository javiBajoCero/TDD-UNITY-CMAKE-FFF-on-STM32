#include "test_wolksvagen.h"

TEST_GROUP(Wolksvagen);

TEST_SETUP(Wolksvagen) {
}

TEST_TEAR_DOWN(Wolksvagen) {
}

TEST(Wolksvagen, test_always_passes) {
    TEST_ASSERT_TRUE(1);
}

TEST(Wolksvagen, test_always_passes_2) {
    TEST_ASSERT_TRUE(1);
}

TEST(Wolksvagen, test_fails) {
    TEST_ASSERT_TRUE(0);
}

TEST_GROUP_RUNNER(Wolksvagen) {
    RUN_TEST_CASE(Wolksvagen, test_always_passes);
    RUN_TEST_CASE(Wolksvagen, test_always_passes_2);
    RUN_TEST_CASE(Wolksvagen, test_fails);
}