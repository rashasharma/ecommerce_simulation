#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

class Product {
protected:
    int m_id;
    string m_name;
    double m_price;

public:
    Product(int id, const string& name, double price);
    virtual ~Product() = default;
    
    int getId() const { return m_id; }
    string getName() const { return m_name; }
    double getPrice() const { return m_price; }
    virtual void displayDetails() const = 0;
    virtual string toCSV() const = 0;
};

// Template function moved from Utils.h to Product.h
template <typename T>
shared_ptr<T> findItemById(const vector<shared_ptr<T>>& items, int id) {
    for (const auto& item : items) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}

template <typename T>
T* findItemById(const vector<T*>& items, int id) {
    for (T* item : items) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}

#endif 