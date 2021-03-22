#ifndef HASH_TABLE_TABLEPRODUCTS_H
#define HASH_TABLE_TABLEPRODUCTS_H
#include "product.h"


class TableCell {
public:
    bool isFree = true;
    bool hasNeverTaken = true;
    Product* product {};
};


class Fridge {
private:
    static const unsigned int defaultSize = 50;
    unsigned int size;
    unsigned int takenCells;
    unsigned long long maxTries;
    TableCell* table;

    [[nodiscard]] unsigned int hash1(const std::string&) const;
    [[nodiscard]] unsigned int hash2(unsigned int, unsigned int) const;
    void rehash();
    static std::string getKey(const Product&);

public:
    explicit Fridge(unsigned int);
    ~Fridge();
    int add(const Product&);
    int remove(const Product&);
    long long find(const Product&);
    friend std::ostream &operator<<(std::ostream&, Fridge&);

    // method for tests
    TableCell* getTable();

    enum {
        SUCCESS = -1,
        OVERFLOWED = -2,
        HASH_ERROR = -3,
        FOUND_IDENTICAL = -4,
        NOT_FOUND = -5
    };
};


#endif






