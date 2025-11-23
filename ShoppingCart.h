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
    bool removeItem(int id);
    void clearCart() { m_items.clear(); }
    size_t getItemCount() const { return m_items.size(); }
};