#include "ShoppingCart.h"
#include <iostream>  
#include <iomanip> 
void ShoppingCart::addItem(Product* item) {
    m_items.push_back(item);
}

double ShoppingCart::getTotalPrice() const {
    double total = 0.0;
    for (Product* item : m_items) {
        total += item->getPrice();
    }
    return total;
}

void ShoppingCart::displayCart() const {
    if (m_items.empty()) {
        std::cout << "Your shopping cart is empty." << std::endl;
        return;
    }
    
    std::cout << "--- Your Cart ---" << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    for (Product* item : m_items) {
        item->displayDetails();
    }
    
    std::cout << "-----------------" << std::endl;
    std::cout << "Total: $" << getTotalPrice() << std::endl;
    std::cout << "-----------------" << std::endl;
}