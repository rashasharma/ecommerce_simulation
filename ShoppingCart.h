#pragma once
#include <vector>
#include <memory>
#include "Product.h"

class ShoppingCart {
private:
    std::vector<std::shared_ptr<Product>> m_items;

public:
    void addItem(std::shared_ptr<Product> item);

    double getTotalPrice() const;

    void displayCart() const;
    
    void removeItem(int id);
};