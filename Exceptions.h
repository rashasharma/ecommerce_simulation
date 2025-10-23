#pragma once
#include <exception> 

class ProductNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "ERROR: Product ID not found.";
    }
};

class OutOfStockException : public std::exception {
public:
    const char* what() const noexcept override {
        return "ERROR: Item is out of stock.";
    }
};