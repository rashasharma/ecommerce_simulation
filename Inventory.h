
#pragma once
#include <map>
#include <string>
#include <vector>
#include<memory>
#include "Product.h"     
#include "Exceptions.h" 
using namespace std;
 
class Inventory {
private:
    map<int, shared_ptr<Product>> m_productCatalog;
    map<int, int> m_stockLevel;

public:
    void addProduct(shared_ptr<Product> product, int initialStock);
    void restock(int id, int quantity);
    shared_ptr<Product> getProductById(int id);
    vector<shared_ptr<Product>> getAllProducts() const;
    int getStockLevel(int id) const;
    void processSale(int id);
};