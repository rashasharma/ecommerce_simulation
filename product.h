// Product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product {
protected:
    int id;
    string name;
    double price;

public:
    Product(int id, string name, double price)
        : id(id), name(name), price(price) {}

    virtual ~Product() {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }

    // Pure virtual function
    virtual void displayDetails() const = 0;
};

#endif
