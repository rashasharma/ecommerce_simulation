#ifndef APPAREL_H
#define APPAREL_H

#include "Product.h"
#include <string>

class Apparel : public Product {
private:
    std::string size;
    std::string color;

public:
    // Constructor
    Apparel(int id, std::string name, double price, const std::string& size, const std::string& color);

    // Override the virtual function
    void displayDetails() const override;
};

#endif // APPAREL_H