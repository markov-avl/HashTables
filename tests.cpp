// tests framework: https://github.com/google/googletest
#include "gtest/gtest.h"
#include "fridge.h"


TEST(FridgeAdd, addingProducts) {
    unsigned int n = 10;
    Fridge fridge = Fridge(n);                                              // hash1 | hash2   | result

    fridge.add(Product("Молоко", "16.03.21", "23.03.21", 4239865327808));   // 5     | -       | 5
    fridge.add(Product("Хлеб",   "17.03.21", "18.03.21", 7702912383631));   // 1     | -       | 1
    fridge.add(Product("Кефир",  "17.03.21", "23.03.21", 9108318280083));   // 5     | 6       | 6
    fridge.add(Product("Курица", "12.03.21", "12.04.21", 7498792010213));   // 0     | -       | 0
    fridge.add(Product("Чай",    "27.01.21", "27.01.22", 3348301015059));   // 8     | -       | 8
    fridge.add(Product("Вода",   "15.03.21", "15.06.21", 1835370248840));   // 5     | 6, 0, 9 | 9

    EXPECT_EQ(fridge.getTable()[0].product->name, "Курица");
    EXPECT_EQ(fridge.getTable()[1].product->name, "Хлеб");
    EXPECT_EQ(fridge.getTable()[5].product->name, "Молоко");
    EXPECT_EQ(fridge.getTable()[6].product->name, "Кефир");
    EXPECT_EQ(fridge.getTable()[8].product->name, "Чай");
    EXPECT_EQ(fridge.getTable()[9].product->name, "Вода");

    fridge.~Fridge();
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

    fridge.~Fridge();
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}