#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include "book.h"
#include "Apparel.h"
#include "Electronics.h"
#include "Inventory.h"
#include "ShoppingCart.h"
#include "Exceptions.h"
#include "Utils.h"
#include "FileHandler.h"

using namespace std;
const string INVENTORY_FILENAME = "inventory_data.csv";

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

void addProductToInventory(Inventory& inventory) {
    cout << "\nSelect Product Type:\n";
    cout << "1. Book\n2. Electronics\n3. Apparel\n";
    cout << "Enter type: ";
    
    int type = InputUtils::getValidatedInt("");
    int id = InputUtils::getValidatedInt("Enter Product ID: ");
    string name = InputUtils::getStringInput("Enter Product Name: ");
    double price = InputUtils::getValidatedDouble("Enter Price: ");
    int stock = InputUtils::getValidatedInt("Enter Initial Stock: ");

    std::shared_ptr<Product> product = nullptr;

    try {
        if (type == 1) {
            string author = InputUtils::getStringInput("Enter Author Name: ");
            product = std::make_shared<Book>(id, name, price, author);
        } 
        else if (type == 2) {
            string brand = InputUtils::getStringInput("Enter Brand: ");
            int warranty = InputUtils::getValidatedInt("Enter Warranty (months): ");
            product = std::make_shared<Electronics>(id, name, price, brand, warranty);
        } 
        else if (type == 3) {
            string size = InputUtils::getStringInput("Enter Size: ");
            string color = InputUtils::getStringInput("Enter Color: ");
            product = std::make_shared<Apparel>(id, name, price, size, color);
        } 
        else {
            cout << "❌ Invalid product type!\n";
            return;
        }

        inventory.addProduct(product, stock);
        cout << "✅ Product added successfully!\n";
    } 
    catch (const exception& e) {
        cerr << "Error adding product: " << e.what() << endl;
    }
}

void viewAllProducts(Inventory& inventory) {
    auto products = inventory.getAllProducts();
    
    if (products.empty()) {
        cout << "No products available in inventory.\n";
    } else {
        cout << "\n=== Available Products ===\n";
        for (const auto& product : products) {
            product->displayDetails();
            cout << "Stock: " << inventory.getStockLevel(product->getId()) << endl;
            cout << "--------------------------\n";
        }
    }
}

void addProductToCart(Inventory& inventory, ShoppingCart& cart) {
    int id = InputUtils::getValidatedInt("Enter Product ID to add to cart: ");

    try {
        std::shared_ptr<Product> item = inventory.getProductById(id);
        
        inventory.processSale(id);
        
        cart.addItem(item);
        cout << "✅ Added to cart successfully!\n";
    } 
    catch (const ProductNotFoundException& e) {
        cerr << e.what() << endl;
    } 
    catch (const OutOfStockException& e) {
        cerr << e.what() << endl;
    }
}

int main() {
    Inventory store;
    ShoppingCart cart;

    cout << "Loading inventory...\n";
    try {
        FileHandler::loadInventory(store, INVENTORY_FILENAME);
        cout << "Inventory loaded successfully.\n";
    } catch (const std::exception& e) {
        cout << "No previous inventory found or load error. Starting empty.\n";
    }

    bool running = true;
    int choice;

    while (running) {
        showMenu();
        choice = InputUtils::getValidatedInt(""); 

        switch (choice) {
            case 1:
                addProductToInventory(store);
                break;

            case 2:
                viewAllProducts(store);
                break;

            case 3:
                addProductToCart(store, cart);
                break;

            case 4:
                cart.displayCart();
                break;

            case 5:
                cout << "\nFinal Cart Summary:\n";
                cart.displayCart();
                
                cout << "Saving inventory to " << INVENTORY_FILENAME << "...\n";
                FileHandler::saveInventory(store, INVENTORY_FILENAME);
                // ------------------------------
                
                cout << "Thank you for shopping with us!\n";
                running = false;
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
        }
    }

    return 0;
}