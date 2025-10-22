#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Product {
protected:
    int id;
    string name;
    double price;

public:
    Product(int id, const std::string& name, double price);
    virtual ~Product() = default;

    int getId() const;
    string getName() const;
    double getPrice() const;


    virtual void displayDetails() const = 0;
};

#endif 
