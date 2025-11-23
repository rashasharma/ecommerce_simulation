#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"
#include <string>

class Electronics : public Product {
private:
    int warrantyPeriod; // in months
    std::string brand;

public:
    Electronics(int id, std::string name, double price, const std::string& brand, int warranty);
    void displayDetails() const override;
    string toCSV() const override;
};

#endif // ELECTRONICS_H