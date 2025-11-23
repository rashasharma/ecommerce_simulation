#ifndef APPAREL_H
#define APPAREL_H

#include "Product.h"
#include <string>
using namespace std;

class Apparel : public Product {
private:
    string size;
    string color;

public:
    Apparel(int id, string name, double price, const string& size, const string& color);
    void displayDetails() const override;
    string toCSV() const override;
};

#endif // APPAREL_H