#pragma once
#include <vector>
#include "Product.h"

class ShoppingCart {
private:
    std::vector<Product*> m_items;

public:
    void addItem(Product* item);

    double getTotalPrice() const;

    void displayCart() const;
    
    void removeItem(int id);
};