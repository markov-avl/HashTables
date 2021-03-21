// tests framework: https://github.com/google/googletest
#include <iostream>
#include "gtest/gtest.h"
#include "fridge.h"


// here some products that will be used in the tests
Product product0 = Product("Молоко", "16.03.21", "23.03.21", 4239865327808);
Product product1 = Product("Хлеб",   "17.03.21", "18.03.21", 7702912383631);
Product product2 = Product("Кефир",  "17.03.21", "23.03.21", 9108318280083);
Product product3 = Product("Курица", "12.03.21", "12.04.21", 7498792010213);
Product product4 = Product("Чай",    "27.01.21", "27.01.22", 3348301015059);
Product product5 = Product("Вода",   "15.03.21", "15.06.21", 1835370248840);
Product product6 = Product("Творог", "13.03.21", "27.03.21", 2846104742535);
Product product7 = Product("Сыр",    "19.03.21", "19.04.21", 1090583553288);
Product product8 = Product("Сахар",  "21.03.21", "21.03.22", 9994289019376);
Product product9 = Product("Кетчуп", "16.02.21", "16.08.22", 6388319002832);


TEST(FridgeAdd, AddingProducts) {
    unsigned int n = 10;
    auto fridge = Fridge(n);

    // adding first 5 products    hash1 | hash2   | result
    fridge.add(product0);      // 4     | -       | 4
    fridge.add(product1);      // 4     | 5       | 5
    fridge.add(product2);      // 1     | -       | 1
    fridge.add(product3);      // 1     | 2       | 2
    fridge.add(product4);      // 9     | -       | 9

    // checking that first 5 products added correctly
    EXPECT_EQ(*fridge.getTable()[4].product, product0);
    EXPECT_EQ(*fridge.getTable()[5].product, product1);
    EXPECT_EQ(*fridge.getTable()[1].product, product2);
    EXPECT_EQ(*fridge.getTable()[2].product, product3);
    EXPECT_EQ(*fridge.getTable()[9].product, product4);

    // adding left 5 products     hash1 | hash2                           | result
    fridge.add(product5);      // 4     | 5, 9, 8                         | 8
    fridge.add(product6);      // 0     | -                               | 0
    fridge.add(product7);      // 0     | 1, 5, 4, 0, 5, 1, 0, 4, 5, 5, 6 | 6
    fridge.add(product8);      // 1     | 2, 6, 5, 1, 6, 2, 1, 5, 6, 6, 7 | 7
    fridge.add(product9);      // 9     | 0, 4, 3                         | 3

    // checking that last 5 products added correctly
    EXPECT_EQ(*fridge.getTable()[8].product, product5);
    EXPECT_EQ(*fridge.getTable()[0].product, product6);
    EXPECT_EQ(*fridge.getTable()[6].product, product7);
    EXPECT_EQ(*fridge.getTable()[7].product, product8);
    EXPECT_EQ(*fridge.getTable()[3].product, product9);
}

TEST(FridgeAdd, AddExitCodes) {
    unsigned int n = 5;
    auto fridge = Fridge(n);

    // adding 4 different products
    EXPECT_EQ(fridge.add(product0), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(product1), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(product2), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(product3), Fridge::SUCCESS);

    // trying to add 4 existing product
    EXPECT_EQ(fridge.add(product0), Fridge::FOUND_IDENTICAL);
    EXPECT_EQ(fridge.add(product1), Fridge::FOUND_IDENTICAL);
    EXPECT_EQ(fridge.add(product2), Fridge::FOUND_IDENTICAL);
    EXPECT_EQ(fridge.add(product3), Fridge::FOUND_IDENTICAL);

    // filling in the table completely with new product
    EXPECT_EQ(fridge.add(product4), Fridge::SUCCESS);

    // adding 1 new extra product
    EXPECT_EQ(fridge.add(product5), Fridge::OVERFLOWED);

    // adding 1 existing extra product
    EXPECT_EQ(fridge.add(product0), Fridge::OVERFLOWED);
}


TEST(FridgeRemove, RemoveProducts) {
    unsigned int n = 5;
    auto fridge = Fridge(n);

    // checking that all cells are free
    EXPECT_TRUE(fridge.getTable()[0].isFree);
    EXPECT_TRUE(fridge.getTable()[1].isFree);
    EXPECT_TRUE(fridge.getTable()[2].isFree);
    EXPECT_TRUE(fridge.getTable()[3].isFree);
    EXPECT_TRUE(fridge.getTable()[4].isFree);

    // adding test products     hash1 | hash2   | result
    fridge.add(product0);    // 4     | -       | 4
    fridge.add(product1);    // 4     | 0       | 0
    fridge.add(product2);    // 1     | -       | 1
    fridge.add(product3);    // 1     | 2       | 2
    fridge.add(product4);    // 4     | 0, 4, 3 | 3

    // checking that all cells are taken
    EXPECT_FALSE(fridge.getTable()[0].isFree);
    EXPECT_FALSE(fridge.getTable()[1].isFree);
    EXPECT_FALSE(fridge.getTable()[2].isFree);
    EXPECT_FALSE(fridge.getTable()[3].isFree);
    EXPECT_FALSE(fridge.getTable()[4].isFree);

    // removing 2 products: first and last
    fridge.remove(product0);
    // rehashing occurs after each removing:
    // -------------------------------------
    // product  | hash1 | hash2   | result
    // product1 | 4     | -       | 4
    // product2 | 1     | -       | 1
    // product3 | 1     | 2       | 2
    // product4 | 4     | 0, 4, 3 | 3
    fridge.remove(product4);
    // rehashing occurs after each removing:
    // -------------------------------------
    // product  | hash1 | hash2   | result
    // product1 | 4     | -       | 4
    // product2 | 1     | -       | 1
    // product3 | 1     | 2       | 2

    // checking that only removed cells are free -> 0 and 3
    EXPECT_TRUE (fridge.getTable()[0].isFree);
    EXPECT_FALSE(fridge.getTable()[1].isFree);
    EXPECT_FALSE(fridge.getTable()[2].isFree);
    EXPECT_TRUE (fridge.getTable()[3].isFree);
    EXPECT_FALSE(fridge.getTable()[4].isFree);

    // removing left products
    fridge.remove(product1);
    fridge.remove(product2);
    fridge.remove(product3);

    // checking that all cells are free again
    EXPECT_TRUE(fridge.getTable()[0].isFree);
    EXPECT_TRUE(fridge.getTable()[1].isFree);
    EXPECT_TRUE(fridge.getTable()[2].isFree);
    EXPECT_TRUE(fridge.getTable()[3].isFree);
    EXPECT_TRUE(fridge.getTable()[4].isFree);
}


TEST(FridgeRemove, RemoveExitCodes) {
    unsigned int n = 5;
    auto fridge = Fridge(n);

    // trying to remove something from fridge when it's empty
    EXPECT_EQ(fridge.remove(product0), Fridge::EMPTY);

    // adding 5 different products
    fridge.add(product0);
    fridge.add(product1);
    fridge.add(product2);
    fridge.add(product3);
    fridge.add(product4);

    // trying to remove 2 not existing products
    EXPECT_EQ(fridge.remove(product5), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.remove(product6), Fridge::NOT_FOUND);

    // trying to remove exising product when fridge is full
    EXPECT_EQ(fridge.remove(product0), Fridge::SUCCESS);

    // checking that removed product couldn't be found
    EXPECT_EQ(fridge.remove(product0), Fridge::NOT_FOUND);

    // removing 3 products
    EXPECT_EQ(fridge.remove(product1), Fridge::SUCCESS);
    EXPECT_EQ(fridge.remove(product2), Fridge::SUCCESS);
    EXPECT_EQ(fridge.remove(product3), Fridge::SUCCESS);

    // checking that removed products couldn't be found
    EXPECT_EQ(fridge.remove(product1), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.remove(product2), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.remove(product3), Fridge::NOT_FOUND);

    // removing last product
    EXPECT_EQ(fridge.remove(product4), Fridge::SUCCESS);

    // checking that fridge is empty again
    EXPECT_EQ(fridge.remove(product4), Fridge::EMPTY);

    // checking that after removing we can add products again
    EXPECT_EQ(fridge.add(product1), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(product2), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(product3), Fridge::SUCCESS);
    EXPECT_EQ(fridge.add(product4), Fridge::SUCCESS);
}

TEST(FridgeFind, FindProductsAndExitCodes) {
    unsigned int n = 10;
    auto fridge = Fridge(n);

    // adding first 5 products    hash1 | hash2   | result
    fridge.add(product0);      // 4     | -       | 4
    fridge.add(product1);      // 4     | 5       | 5
    fridge.add(product2);      // 1     | -       | 1
    fridge.add(product3);      // 1     | 2       | 2
    fridge.add(product4);      // 9     | -       | 9

    // checking that first 5 products added correctly
    EXPECT_EQ(fridge.find(product0), 4);
    EXPECT_EQ(fridge.find(product1), 5);
    EXPECT_EQ(fridge.find(product2), 1);
    EXPECT_EQ(fridge.find(product3), 2);
    EXPECT_EQ(fridge.find(product4), 9);

    // checking that not existing products couldn't be found
    EXPECT_EQ(fridge.find(product5), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.find(product9), Fridge::NOT_FOUND);

    // adding left 5 products     hash1 | hash2                           | result
    fridge.add(product5);      // 4     | 5, 9, 8                         | 8
    fridge.add(product6);      // 0     | -                               | 0
    fridge.add(product7);      // 0     | 1, 5, 4, 0, 5, 1, 0, 4, 5, 5, 6 | 6
    fridge.add(product8);      // 1     | 2, 6, 5, 1, 6, 2, 1, 5, 6, 6, 7 | 7
    fridge.add(product9);      // 9     | 0, 4, 3                         | 3

    // checking that last 5 products added correctly and could be found when fridge is full
    EXPECT_EQ(fridge.find(product5), 8);
    EXPECT_EQ(fridge.find(product6), 0);
    EXPECT_EQ(fridge.find(product7), 6);
    EXPECT_EQ(fridge.find(product8), 7);
    EXPECT_EQ(fridge.find(product9), 3);

    // removing every second product
    fridge.remove(product0);
    fridge.remove(product2);
    fridge.remove(product4);
    fridge.remove(product6);
    fridge.remove(product8);
    // the last rehash should be like this:
    // ------------------------------------
    // product  | hash1 | hash2   | result
    // product1 | 4     | -       | 4
    // product3 | 1     | -       | 1
    // product5 | 4     | 5       | 5
    // product7 | 0     | -       | 0
    // product9 | 9     | -       | 9

    // checking that left products could be found
    EXPECT_EQ(fridge.find(product1), 4);
    EXPECT_EQ(fridge.find(product3), 1);
    EXPECT_EQ(fridge.find(product5), 5);
    EXPECT_EQ(fridge.find(product7), 0);
    EXPECT_EQ(fridge.find(product9), 9);

    // checking that every second removed product couldn't be found
    EXPECT_EQ(fridge.find(product0), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.find(product2), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.find(product4), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.find(product6), Fridge::NOT_FOUND);
    EXPECT_EQ(fridge.find(product8), Fridge::NOT_FOUND);
}

TEST(FridgePrint, PrintProducts) {
    unsigned int n = 3;
    auto fridge = Fridge(n);

    // checking that new fridge is really empty
    testing::internal::CaptureStdout();
    std::cout << fridge;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "The fridge is empty");

    // adding product and checking that it appeared in the fridge
    fridge.add(product0);
    testing::internal::CaptureStdout();
    std::cout << fridge;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1.\n"
                                                      "Name            | " + product0.name + "\n"
                                                      "Purchase date   | " + product0.purchaseDate + "\n"
                                                      "Expiration date | " + product0.expirationDate + "\n"
                                                      "Barcode         | " + std::to_string(product0.barcode)  + "\n");

    // adding 2 more products
    fridge.add(product1);
    fridge.add(product2);
    // after adding indexes should be like this:
    // -----------------------------------------
    // product  | index
    // product0 | 2
    // product1 | 0
    // product2 | 1

    // checking that 2 last products appeared in the fridge
    testing::internal::CaptureStdout();
    std::cout << fridge;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1.\n"
                                                      "Name            | " + product1.name + "\n"
                                                      "Purchase date   | " + product1.purchaseDate + "\n"
                                                      "Expiration date | " + product1.expirationDate + "\n"
                                                      "Barcode         | " + std::to_string(product1.barcode)  + "\n"
                                                      "\n"
                                                      "2.\n"
                                                      "Name            | " + product2.name + "\n"
                                                      "Purchase date   | " + product2.purchaseDate + "\n"
                                                      "Expiration date | " + product2.expirationDate + "\n"
                                                      "Barcode         | " + std::to_string(product2.barcode)  + "\n"
                                                      "\n"
                                                      "3.\n"
                                                      "Name            | " + product0.name + "\n"
                                                      "Purchase date   | " + product0.purchaseDate + "\n"
                                                      "Expiration date | " + product0.expirationDate + "\n"
                                                      "Barcode         | " + std::to_string(product0.barcode)  + "\n");

    // removing 2 first products and checking that only product2 left in the fridge
    fridge.remove(product0);
    fridge.remove(product1);
    testing::internal::CaptureStdout();
    std::cout << fridge;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "1.\n"
                                                      "Name            | " + product2.name + "\n"
                                                      "Purchase date   | " + product2.purchaseDate + "\n"
                                                      "Expiration date | " + product2.expirationDate + "\n"
                                                      "Barcode         | " + std::to_string(product2.barcode)  + "\n");

    // removing last product and checking that the fridge is empty again
    fridge.remove(product2);
    testing::internal::CaptureStdout();
    std::cout << fridge;
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "The fridge is empty");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}