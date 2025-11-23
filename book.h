#ifndef BOOK_H
#define BOOK_H

#include "Product.h"
#include <string>

class Book : public Product {
private:
    std::string author;

public:
    Book(int id, std::string name, double price, const std::string& author);
    void displayDetails() const override;
    string toCSV() const override;
};

#endif // BOOK_H
