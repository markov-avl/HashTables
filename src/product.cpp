#include "product.h"


Product::Product(const std::string& name, const std::string& purchaseDate, const std::string& expirationDate,
                 const unsigned long barcode) {
    this->name = name;
    this->purchaseDate = purchaseDate;
    this->expirationDate = expirationDate;
    this->barcode = barcode;
}

std::ostream &operator<<(std::ostream &out, const Product &product) {
    out << "Name            | " << product.name << std::endl
        << "Purchase date   | " << product.purchaseDate << std::endl
        << "Expiration date | " << product.expirationDate << std::endl
        << "Barcode         | " << product.barcode << std::endl;
    return out;
}

bool operator==(const Product &a, const Product &b) {
    return a.name == b.name && a.purchaseDate == b.purchaseDate && a.expirationDate == b.expirationDate &&
           a.barcode == b.barcode;
}

bool operator!=(const Product &a, const Product &b) {
    return a.name != b.name || a.purchaseDate != b.purchaseDate || a.expirationDate != b.expirationDate ||
           a.barcode != b.barcode;
}