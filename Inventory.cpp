
#include "Inventory.h"
#include <vector> 
Inventory::~Inventory() {
    for (auto const& pair : m_productCatalog) {
        delete pair.second; 
    }
}
void Inventory::addProduct(Product* product, int initialStock) {
     int id = product->getId(); 
     m_productCatalog[id] = product;
       
    m_stockLevel[id] = initialStock;
}
Product* Inventory::getProductById(int id) {
    if (m_productCatalog.find(id) == m_productCatalog.end()) {
        throw ProductNotFoundException();
    }
    return m_productCatalog.at(id);
}
int Inventory::getStockLevel(int id) {
    if (m_stockLevel.find(id) != m_stockLevel.end()) {
        return m_stockLevel[id];
    }
    return 0;
}
void Inventory::processSale(int id) {
    if (m_stockLevel.at(id) <= 0) {
        throw OutOfStockException();
    }
    
    m_stockLevel[id]--;
}

std::vector<Product*> Inventory::getAllProducts() const {
    std::vector<Product*> allProducts;
    for (auto const& pair : m_productCatalog) {
        allProducts.push_back(pair.second);
    }

    return allProducts;
}