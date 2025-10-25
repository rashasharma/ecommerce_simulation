#include "Apparel.h"
#include <iostream>

// Constructor: calls the base class constructor first
Apparel::Apparel(int id, std::string name, double price, const std::string& size, const std::string& color)
    : Product(id, name, price), size(size), color(color) {
    // Initialization list handles base and derived members
}

// Implementation of the overridden function
void Apparel::displayDetails() const {
    // Call the base class function to display common details
    Product::displayDetails();
    
    // Display Apparel-specific details
    std::cout << "Type: Apparel\n";
    std::cout << "Size: " << size << "\n";
    std::cout << "Color: " << color << "\n";
    std::cout << "---------------------------------\n";
}