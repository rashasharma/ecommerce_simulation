
#pragma once
#include <map>
#include <string>
#include <vector>
#include "Product.h"     
#include "Exceptions.h"  
class Inventory {
private:
    std::map<int, Product*> m_productCatalog;
    std::map<int, int> m_stockLevel;

public:
    ~Inventory();
    void addProduct(Product* product, int initialStock);
    Product* getProductById(int id);
    int getStockLevel(int id);
    void processSale(int id);
    std::vector<Product*> getAllProducts() const;
};