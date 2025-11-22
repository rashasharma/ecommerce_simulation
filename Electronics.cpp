#include "Electronics.h"
#include <iostream>

Electronics::Electronics(int id, std::string name, double price, const std::string& brand, int warranty)
    : Product(id, name, price), brand(brand), warrantyPeriod(warranty) {}

void Electronics::displayDetails() const {
    std::cout << "ID: " << getId() << " | Electronics: " << getName() 
              << " | Brand: " << brand 
              << " | Warranty: " << warrantyPeriod << " months"
              << " | Price: " << getPrice() << std::endl;
}