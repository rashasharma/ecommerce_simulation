#include "Book.h"
#include <iostream>

// Constructor: calls the base class constructor first
Book::Book(int id, std::string name, double price, const std::string& author)
    : Product(id, name, price), author(author) {
    // Initialization list handles base and derived members
}

// Implementation of the overridden function
void Book::displayDetails() const {
    // Call the base class function to display common details
    Product::displayDetails();
    
    // Display Book-specific details
    std::cout << "Type: Book\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "---------------------------------\n";
}