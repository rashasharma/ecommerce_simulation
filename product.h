#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Product {
protected:
    int m_id;
    string m_name;
    double m_price;

public:
    Product(int id, const string& name, double price);
    virtual ~Product() = default;
    
    int getId() const { return m_id; }
    string getName() const { return m_name; }
    double getPrice() const { return m_price; }

    // Pure virtual function for polymorphism
    virtual void displayDetails() const = 0;
    virtual string toCSV() const = 0;
};

#endif // PRODUCT_H