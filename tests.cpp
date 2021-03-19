// tests framework: https://github.com/google/googletest
#include "gtest/gtest.h"
#include "fridge.h"


TEST(FridgeAdd, addingProducts) {
    unsigned int n = 10;
    Fridge fridge = Fridge(n);
                                                                            // hash1 | hash2   | result
    fridge.add(Product("Молоко", "16.03.21", "23.03.21", 4239865327808));   // 4     | -       | 4
    fridge.add(Product("Хлеб",   "17.03.21", "18.03.21", 7702912383631));   // 4     | 5       | 5
    fridge.add(Product("Кефир",  "17.03.21", "23.03.21", 9108318280083));   // 1     | -       | 1
    fridge.add(Product("Курица", "12.03.21", "12.04.21", 7498792010213));   // 1     | 2       | 2
    fridge.add(Product("Чай",    "27.01.21", "27.01.22", 3348301015059));   // 9     | -       | 9
    fridge.add(Product("Вода",   "15.03.21", "15.06.21", 1835370248840));   // 4     | 5, 9, 8 | 8

    EXPECT_EQ(fridge.getTable()[1].product->name, "Кефир");
    EXPECT_EQ(fridge.getTable()[2].product->name, "Курица");
    EXPECT_EQ(fridge.getTable()[4].product->name, "Молоко");
    EXPECT_EQ(fridge.getTable()[5].product->name, "Хлеб");
    EXPECT_EQ(fridge.getTable()[8].product->name, "Вода");
    EXPECT_EQ(fridge.getTable()[9].product->name, "Чай");
}

TEST(FridgeAdd, addExitCodes) {
    unsigned int n = 5;

    Fridge fridge = Fridge(n);
    // adding 4 difference records
    EXPECT_EQ(fridge.add(Product("Молоко", "16.03.21", "23.03.21", 4239865327808)), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(Product("Хлеб",   "17.03.21", "18.03.21", 7702912383631)), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(Product("Кефир",  "17.03.21", "23.03.21", 9108318280083)), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(Product("Курица", "12.03.21", "12.04.21", 7498792010213)), Fridge::SUCCESS);
    // trying to add 4 existing records
    EXPECT_EQ(fridge.add(Product("Молоко", "16.03.21", "23.03.21", 4239865327808)), Fridge::FOUND_IDENTICAL);
    EXPECT_EQ(fridge.add(Product("Хлеб",   "17.03.21", "18.03.21", 7702912383631)), Fridge::FOUND_IDENTICAL);
    EXPECT_EQ(fridge.add(Product("Кефир",  "17.03.21", "23.03.21", 9108318280083)), Fridge::FOUND_IDENTICAL);
    EXPECT_EQ(fridge.add(Product("Курица", "12.03.21", "12.04.21", 7498792010213)), Fridge::FOUND_IDENTICAL);
    // filling in the table completely with new record
    EXPECT_EQ(fridge.add(Product("Чай",    "27.01.21", "27.01.22", 3348301015059)), Fridge::SUCCESS);
    // adding 1 new extra record
    EXPECT_EQ(fridge.add(Product("Вода",   "15.03.21", "15.06.21", 1835370248840)), Fridge::OVERFLOWED);
    // adding 1 existing extra record;
    EXPECT_EQ(fridge.add(Product("Молоко", "16.03.21", "23.03.21", 4239865327808)), Fridge::OVERFLOWED);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}