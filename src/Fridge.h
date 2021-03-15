#ifndef HASH_TABLE_TABLEPRODUCTS_H
#define HASH_TABLE_TABLEPRODUCTS_H
#include "product.h"


class TableCell {
public:
    bool isFree = true;
    bool isNeverTaken = true;
    Product* product {};
};


class Fridge {
private:
    static const unsigned int defaultSize = 50;
    unsigned int size;
    unsigned int takenCells;
    TableCell* table;

    [[nodiscard]] unsigned int hash1(const std::string&) const;
    [[nodiscard]] unsigned int hash2(unsigned int, unsigned int) const;
    static std::string getKey(const Product&);

public:
    explicit Fridge(unsigned int);
    ~Fridge();
    int add(const Product&);
    int remove(const Product&);
    long long find(const Product &product);
    friend std::ostream &operator<<(std::ostream&, Fridge&);

    enum {
        SUCCESS = -1,
        OVERFLOWED = -2,
        EMPTY = -3,
        FOUND_IDENTICAL = -4,
        FOUND = -5,
        NOT_FOUND = -6
    };
};


#endif






