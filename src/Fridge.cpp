#include <cstring>
#include "fridge.h"


Fridge::Fridge(unsigned int n) {
    this->size = n < 1 ? defaultSize : n;
    this->takenCells = 0;
    this->table = new TableCell[n];
}

Fridge::~Fridge() {
    for (int i = 0; i < size; ++i) {
        if (!table[i].isNeverTaken) {
            delete table[i].product;
        }
    }
    delete[] table;
}

unsigned int Fridge::hash1(const std::string &key) const {
    unsigned int hash;
    for (char i : key) {
        hash += i;
    }
    return hash % size;
}

unsigned int Fridge::hash2(unsigned int hash, unsigned int step) const {
    return (hash + step * step) % size;
}

std::string Fridge::getKey(const Product &product) {
    return product.name + product.purchaseDate;
}

int Fridge::add(const Product &product) {
    if (takenCells == size) {
        return OVERFLOWED;
    }
    if (find(product) > SUCCESS) {
        return FOUND_IDENTICAL;
    }
    // находим индекс с помощью хеширования
    std::string key = getKey(product);
    unsigned int index = hash1(key);
    unsigned int step = 1;
    while (!table[index].isFree) {
        index = hash2(index, step++);
    }
    // добавляем запись
    ++takenCells;
    if (!table[index].isNeverTaken) {
        delete table[index].product;
    }
    table[index].isFree = false;
    table[index].isNeverTaken = false;
    table[index].product = new Product(product.name, product.purchaseDate, product.expirationDate, product.barcode);
    return SUCCESS;
}

int Fridge::remove(const Product& product) {
    if (takenCells == 0) {
        return EMPTY;
    }
    long long index = find(product);
    if (index == NOT_FOUND) {
        return NOT_FOUND;
    } else {
        --takenCells;
        table[index].isFree = true;
        return SUCCESS;
    }
}

long long Fridge::find(const Product& product) {
    if (takenCells == 0) {
        return EMPTY;
    } else {
        std::string key = getKey(product);
        unsigned int index = hash1(key);
        unsigned int step = 1;
        while (!table[index].isFree && product != *table[index].product) {
            index = hash2(index, step++);
        }
        if (table[index].isFree) {
            return NOT_FOUND;
        } else {
            return index;
        }
    }
}

std::ostream &operator<<(std::ostream &out, Fridge& fridge) {
    if (fridge.size == 0) {
        out << "The fridge is empty" << std::endl;
    } else {
        unsigned int k = 1;
        for (unsigned int i = 0; i < fridge.size; ++i) {
            if (!fridge.table[i].isFree) {
                out << k++ << '.' << std::endl << *fridge.table[i].product << std::endl;
            }
        }
    }
    return out;
}