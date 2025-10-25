#ifndef BOOK_H
#define BOOK_H

#include "Product.h"
#include <string>

class Book : public Product {
private:
    std::string author;
    // Note: Kept 'publisher' optional and simplified for this core task,
    // focusing on 'author' as the primary unique attribute.

public:
    // Constructor
    Book(int id, std::string name, double price, const std::string& author);

    // Override the virtual function to display specific book details
    void displayDetails() const override;
};

#endif // BOOK_H
