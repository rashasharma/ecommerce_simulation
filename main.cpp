#include <iostream>
#include <limits>
#include "book.h"
#include "Apparel.h"
#include "Electronics.h"
#include "Inventory.h"
#include "ShoppingCart.h"
#include "Exceptions.h"
#include "Utils.h"

using namespace std;

void showMenu() {
    cout << "\n========== SHOPPING SYSTEM ==========\n";
    cout << "1. Add Product to Inventory\n";
    cout << "2. View All Products\n";
    cout << "3. Add Product to Cart\n";
    cout << "4. View Cart\n";
    cout << "5. Checkout & Exit\n";
    cout << "=====================================\n";
    cout << "Enter your choice: ";
}

int main() {
    Inventory store;
    ShoppingCart cart;

    bool running = true;
    int choice;

    while (running) {
        showMenu();
        cin >> choice;

        switch (choice) {
            // ---------------------------------------------------
            case 1: { // Add Product to Inventory
                cout << "\nSelect Product Type:\n";
                cout << "1. Book\n2. Electronics\n3. Apparel\n";
                cout << "Enter type: ";
                int type;
                cin >> type;

                int id, stock;
                string name;
                double price;

                cout << "Enter Product ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Product Name: ";
                getline(cin, name);
                cout << "Enter Price: ";
                cin >> price;
                cout << "Enter Initial Stock: ";
                cin >> stock;

                Product* p = nullptr;

                if (type == 1) {
                    string author;
                    cin.ignore();
                    cout << "Enter Author Name: ";
                    getline(cin, author);
                    p = new Book(id, name, price, author);
                } 
                else if (type == 2) {
                    string brand;
                    int warranty;
                    cin.ignore();
                    cout << "Enter Brand: ";
                    getline(cin, brand);
                    cout << "Enter Warranty (months): ";
                    cin >> warranty;
                    p = new Electronics(id, name, price, brand, warranty);
                } 
                else if (type == 3) {
                    string size, color;
                    cin.ignore();
                    cout << "Enter Size: ";
                    getline(cin, size);
                    cout << "Enter Color: ";
                    getline(cin, color);
                    p = new Apparel(id, name, price, size, color);
                } 
                else {
                    cout << "❌ Invalid product type!\n";
                    break;
                }

                store.addProduct(p, stock);
                cout << "✅ Product added successfully!\n";
                break;
            }

            // ---------------------------------------------------
            case 2: { // View Products
                auto products = store.getAllProducts();
                if (products.empty()) {
                    cout << "No products available in inventory.\n";
                } else {
                    cout << "\n=== Available Products ===\n";
                    for (auto* p : products) {
                        p->displayDetails();
                        cout << "--------------------------\n";
                    }
                }
                break;
            }

            // ---------------------------------------------------
            case 3: { // Add Product to Cart
                cout << "Enter Product ID to add to cart: ";
                int id;
                cin >> id;

                try {
                    Product* item = store.getProductById(id);
                    store.processSale(id);
                    cart.addItem(item);
                    cout << "✅ Added to cart successfully!\n";
                } 
                catch (const ProductNotFoundException& e) {
                    cerr << e.what() << endl;
                } 
                catch (const OutOfStockException& e) {
                    cerr << e.what() << endl;
                }
                break;
            }

            // ---------------------------------------------------
            case 4:
                cart.displayCart();
                break;

            // ---------------------------------------------------
            case 5:
                cout << "\nFinal Cart Summary:\n";
                cart.displayCart();
                cout << "Thank you for shopping with us!\n";
                running = false;
                break;

            // ---------------------------------------------------
            default:
                cout << "Invalid choice! Please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
