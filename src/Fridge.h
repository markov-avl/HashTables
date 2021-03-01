#ifndef HASHTABLES_FRIDGE_H
#define HASHTABLES_FRIDGE_H
#include <iostream>


struct Product {
    std::string data;
    bool isFree = true;
};


class Fridge {
private:
    static const int defaultSize = 256;
    unsigned int size;
    unsigned int count;
    Product* table;
    unsigned int hash1(Product product);
    unsigned int hash2(unsigned int address);
public:
    explicit Fridge(unsigned int n = Fridge::defaultSize);
    ~Fridge();
    int add(Product product);
    int del(Product product);
    int search(Product product);
};


std::ostream& operator<<(std::ostream& out, Fridge& fridge);


#endif
