#include <cstring>
#include "fridge.h"


Fridge::Fridge(unsigned int n) {
    this->size = n < 1 ? defaultSize : n;
    this->takenCells = 0;
    this->table = new TableCell[n];
}

Fridge::~Fridge() {
    for (int i = 0; i < size; ++i) {
        if (!table[i].hasNeverTaken) {
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

void Fridge::rehash() {
    std::string key;
    unsigned int index;
    unsigned int step;
    auto* newTable = new TableCell[size];

    for (int i = 0; i < size; ++i) {
        if (!table[i].hasNeverTaken) {
            if (table[i].isFree) {
                delete table[i].product;
            } else {
                key = getKey(*table[i].product);
                index = hash1(key);
                step = 1;
                while (!newTable[index].isFree) {
                    index = hash2(index, step++);
                }
                newTable[index].isFree = false;
                newTable[index].hasNeverTaken = false;
                newTable[index].product = table[i].product;
            }
        }
    }
    delete[] table;
    table = newTable;
}

std::string Fridge::getKey(const Product &product) {
    return product.name + product.purchaseDate;
}

TableCell* Fridge::getTable() {
    return table;
}

int Fridge::add(const Product &product) {
    if (takenCells == size) {
        return OVERFLOWED;
    }
    if (takenCells > 0 && find(product) > SUCCESS) {
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
    if (!table[index].hasNeverTaken) {
        delete table[index].product;
    }
    table[index].isFree = false;
    table[index].hasNeverTaken = false;
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
        rehash();
        return SUCCESS;
    }
}

long long Fridge::find(const Product& product) {
    if (takenCells == 0) {
        return NOT_FOUND;
    }
    unsigned int index;
    if (takenCells < size) {
        std::string key = getKey(product);
        unsigned int step = 1;
        index = hash1(key);
        while (!table[index].isFree && product != *table[index].product) {
            index = hash2(index, step++);
        }
        return (table[index].isFree ? NOT_FOUND : index);
    } else {
        index = 0;
        for (; index < size && product != *table[index].product; ++index);
        return (index == size ? NOT_FOUND : index);
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