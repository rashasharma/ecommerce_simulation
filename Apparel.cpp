#include "Apparel.h"
#include <iostream>

Apparel::Apparel(int id, std::string name, double price, const std::string& size, const std::string& color)
    : Product(id, name, price), size(size), color(color) {}

void Apparel::displayDetails() const {
    std::cout << "ID: " << getId() << " | Apparel: " << getName() 
              << " | Size: " << size 
              << " | Color: " << color
              << " | Price: " << getPrice() << std::endl;
}
string Apparel::toCSV() const {
    return "Apparel," + std::to_string(getId()) + "," + getName() + "," + 
           std::to_string(getPrice()) + "," + size + "," + color;
}