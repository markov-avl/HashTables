#include "Fridge.h"

Fridge::Fridge(unsigned int n) {
    this->size = (n < 1 ? Fridge::defaultSize : n);
    this->count = 0;
    this->table = new Product[n];
}

Fridge::~Fridge() {
    delete[] this->table;
}