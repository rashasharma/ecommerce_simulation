#include "Inventory.h"
#include <vector> 



void Inventory::addProduct(std::shared_ptr<Product> product, int initialStock) {
     int id = product->getId(); 
     m_productCatalog[id] = product; 
     m_stockLevel[id] = initialStock;
}

std::shared_ptr<Product> Inventory::getProductById(int id) {
    if (m_productCatalog.find(id) == m_productCatalog.end()) {
        throw ProductNotFoundException();
    }
    return m_productCatalog.at(id);
}

int Inventory::getStockLevel(int id)const{
    if (m_stockLevel.find(id) != m_stockLevel.end()) {
        return m_stockLevel.at(id);
    }
    return 0;
}

void Inventory::processSale(int id) {
    if (m_stockLevel.at(id) <= 0) {
        throw OutOfStockException();
    }
    m_stockLevel[id]--;
}

void Inventory::restock(int id, int quantity) {
    if (m_stockLevel.find(id) != m_stockLevel.end()) {
        m_stockLevel[id] += quantity;
    }
}

std::vector<std::shared_ptr<Product>> Inventory::getAllProducts() const {
    std::vector<std::shared_ptr<Product>> allProducts;
    for (auto const& pair : m_productCatalog) {
        allProducts.push_back(pair.second);
    }
    return allProducts;
}