#ifndef HASHTABLE_PRODUCT_H
#define HASHTABLE_PRODUCT_H
#include <iostream>


class Product {
public:
    std::string name;
    std::string purchaseDate;
    std::string expirationDate;
    unsigned long barcode;

    Product(const std::string&, const std::string&, const std::string&, unsigned long);
    friend std::ostream &operator<<(std::ostream &out, const Product &product);
    friend bool operator==(const Product &a, const Product &b);
    friend bool operator!=(const Product &a, const Product &b);
};


#endif
