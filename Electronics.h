#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"
#include <string>

class Electronics : public Product {
private:
    int warrantyPeriod; // in months
    std::string brand; // Added brand as per requirements

public:
    // Constructor
    Electronics(int id, std::string name, double price, const std::string& brand, int warranty);

    // Override the virtual function
    void displayDetails() const override;
};

#endif // ELECTRONICS_H