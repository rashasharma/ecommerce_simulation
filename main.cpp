// main.cpp
#include <iostream>
#include <vector>
#include "Product.h"
#include "Utils.h"
#include "ShoppingCart.h"
#include "Inventory.h"
#include "Exceptions.h"
using namespace std;

int main() {
    Inventory inventory;
    ShoppingCart cart;

    // (Later your teammate will implement Inventory and ShoppingCart)

    int choice;
    do {
        cout << "\n=== E-Commerce Simulator ===";
        cout << "\n1. View Products";
        cout << "\n2. Add to Cart";
        cout << "\n3. View Cart";
        cout << "\n4. Checkout";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    inventory.displayAllProducts();
                    break;
                case 2: {
                    int id;
                    cout << "Enter product ID to add: ";
                    cin >> id;
                    Product* p = inventory.getProductById(id);
                    if (p)
                        cart.addProduct(p);
                    else
                        throw ProductNotFoundException();
                    break;
                }
                case 3:
                    cart.displayCart();
                    break;
                case 4:
                    cart.checkout();
                    break;
                case 0:
                    cout << "Exiting... Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}
