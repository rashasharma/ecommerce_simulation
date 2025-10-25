#include "Electronics.h"
#include <iostream>

// Constructor: calls the base class constructor first
Electronics::Electronics(int id, std::string name, double price, const std::string& brand, int warranty)
    : Product(id, name, price), brand(brand), warrantyPeriod(warranty) {
    // Initialization list handles base and derived members
}

// Implementation of the overridden function
void Electronics::displayDetails() const {
    // Call the base class function to display common details
    Product::displayDetails();
    
    // Display Electronics-specific details
    std::cout << "Type: Electronics\n";
    std::cout << "Brand: " << brand << "\n";
    std::cout << "Warranty: " << warrantyPeriod << " months\n";
    std::cout << "---------------------------------\n";
}