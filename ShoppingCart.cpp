#include "ShoppingCart.h"
#include <iostream>  
#include <iomanip>
#include <algorithm>

void ShoppingCart::addItem(std::shared_ptr<Product> item) {
    m_items.push_back(item);
}

double ShoppingCart::getTotalPrice() const {
    double total = 0.0;
    for (const auto& item : m_items) {
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

    for (const auto& item : m_items) {
        item->displayDetails();
    }
    
    std::cout << "-----------------" << std::endl;
    std::cout << "Total: ₹" << getTotalPrice() << std::endl;
    std::cout << "-----------------" << std::endl;
}

bool ShoppingCart::removeItem(int id) {
    auto itemToRemove = findItemById(m_items, id);
    
    if (itemToRemove != nullptr) {
        
        m_items.erase(
            std::remove_if(m_items.begin(), m_items.end(),
                [id](const std::shared_ptr<Product>& item) {
                    return item->getId() == id;
                }),
            m_items.end()
        );
        std::cout << "Item removed from cart.\n";
        return true;
    } else {
        std::cout << "Item not found in cart.\n";
        return false;
    }
}