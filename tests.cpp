// tests framework: https://github.com/google/googletest

#include "gtest/gtest.h"


TEST(functionName, testName) {

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}