#include "Book.h"
#include <iostream>

Book::Book(int id, std::string name, double price, const std::string& author)
    : Product(id, name, price), author(author) {}

void Book::displayDetails() const {
    std::cout << "ID: " << getId() << " | Book: " << getName() 
              << " | Author: " << author 
              << " | Price: " << getPrice() << std::endl;
}
string Book::toCSV() const {
    return "Book," + std::to_string(getId()) + "," + getName() + "," + 
           std::to_string(getPrice()) + "," + author;
}