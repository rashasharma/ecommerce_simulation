#pragma once
#include <vector>
#include "Product.h"
using namespace std;

class ShoppingCart {
private:
    vector<shared_ptr<Product>> m_items;

public:
    void addItem(shared_ptr<Product> item);

    double getTotalPrice() const;

    void displayCart() const;

    void removeItem(int id);
};