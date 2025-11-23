#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <map>
#include "Book.h"
#include "Apparel.h"
#include "Electronics.h"
#include "Inventory.h"
#include "ShoppingCart.h"
#include "Exceptions.h"
#include "Utils.h"
#include "FileHandler.h"

using namespace std;

const string INVENTORY_FILENAME = "inventory_data.csv";

map<string, string> users; 
string currentUser = "";
string currentUserRole = "";
ShoppingCart currentUserCart;

void simulateLogin() {
    cout << "\n========== LOGIN ==========\n";
    cout << "Who are you? ";
    
    string username;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, username);
    
    username.erase(0, username.find_first_not_of(" \t\n\r\f\v")); 
    username.erase(username.find_last_not_of(" \t\n\r\f\v") + 1); 
    
    if (username.empty()) {
        cout << "❌ Invalid username! Username cannot be empty.\n";
        return;
    }
    if (users.find(username) == users.end()) {
        cout << "New user detected! Select your role:\n";
        cout << "1. Customer\n";
        cout << "2. Admin\n";
        cout << "Enter choice: ";
        int roleChoice = InputUtils::getValidatedInt("");
        
        if (roleChoice == 1) {
            users[username] = "customer";
        } else if (roleChoice == 2) {
            users[username] = "admin";
        } else {
            cout << "❌ Invalid choice! Defaulting to Customer.\n";
            users[username] = "customer";
        }
    }
    
    currentUser = username;
    currentUserRole = users[username];
    cout << "✅ Welcome " << username << " (" << currentUserRole << ")!\n";
}

void logout() {
    cout << "👋 Goodbye " << currentUser << "!\n";
    cout << "Saving inventory to " << INVENTORY_FILENAME << "...\n";
    
    currentUser = "";
    currentUserRole = "";
    currentUserCart = ShoppingCart(); 
}

void showMainMenu() {
    cout << "\n========== E-COMMERCE SYSTEM ==========\n";
    cout << "1. Login\n";
    cout << "2. Exit\n";
    cout << "======================================\n";
    cout << "Enter your choice: ";
}

void showCustomerMenu() {
    cout << "\n========== CUSTOMER MENU ==========\n";
    cout << "Welcome, " << currentUser << "!\n";
    cout << "1. View All Products\n";
    cout << "2. Add Product to Cart\n";
    cout << "3. View Cart\n";
    cout << "4. Remove Item from Cart\n";
    cout << "5. Checkout\n";
    cout << "6. Logout\n";
    cout << "===================================\n";
    cout << "Enter your choice: ";
}

void showAdminMenu() {
    cout << "\n========== ADMIN MENU ==========\n";
    cout << "Welcome, " << currentUser << "!\n";
    cout << "1. Add Product to Inventory\n";
    cout << "2. View All Products\n";
    cout << "3. View Stock Levels\n";
    cout << "4. Logout\n";
    cout << "================================\n";
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

    shared_ptr<Product> product = nullptr;

    try {
        if (type == 1) {
            string author = InputUtils::getStringInput("Enter Author Name: ");
            product = make_shared<Book>(id, name, price, author);
        } 
        else if (type == 2) {
            string brand = InputUtils::getStringInput("Enter Brand: ");
            int warranty = InputUtils::getValidatedInt("Enter Warranty (months): ");
            product = make_shared<Electronics>(id, name, price, brand, warranty);
        } 
        else if (type == 3) {
            string size = InputUtils::getStringInput("Enter Size: ");
            string color = InputUtils::getStringInput("Enter Color: ");
            product = make_shared<Apparel>(id, name, price, size, color);
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

void viewStockLevels(Inventory& inventory) {
    auto products = inventory.getAllProducts();
    
    if (products.empty()) {
        cout << "No products available in inventory.\n";
    } else {
        cout << "\n=== Stock Levels ===\n";
        for (const auto& product : products) {
            cout << "ID: " << product->getId() << " | " << product->getName();
            cout << " | Stock: " << inventory.getStockLevel(product->getId()) << endl;
        }
    }
}

void addProductToCart(Inventory& inventory) {
    int id = InputUtils::getValidatedInt("Enter Product ID to add to cart: ");

    try {
        shared_ptr<Product> item = inventory.getProductById(id);
        inventory.processSale(id);
        currentUserCart.addItem(item);
        cout << "✅ Added to cart successfully!\n";
    } 
    catch (const ProductNotFoundException& e) {
        cerr << e.what() << endl;
    } 
    catch (const OutOfStockException& e) {
        cerr << e.what() << endl;
    }
}

void removeFromCart() {
    int id = InputUtils::getValidatedInt("Enter Product ID to remove from cart: ");
    currentUserCart.removeItem(id);
}

void checkout() {
    cout << "\n=== Checkout Summary ===\n";
    currentUserCart.displayCart();
    cout << "Thank you for your purchase, " << currentUser << "!\n";
    currentUserCart = ShoppingCart(); 
}

void runCustomerMenu(Inventory& inventory) {
    bool inMenu = true;
    while (inMenu) {
        showCustomerMenu();
        int choice = InputUtils::getValidatedInt("");

        switch (choice) {
            case 1:
                viewAllProducts(inventory);
                break;
            case 2:
                addProductToCart(inventory);
                break;
            case 3:
                currentUserCart.displayCart();
                break;
            case 4:
                removeFromCart();
                break;
            case 5:
                checkout();
                break;
            case 6:
                FileHandler::saveInventory(inventory, INVENTORY_FILENAME);
                logout();
                inMenu = false;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

void runAdminMenu(Inventory& inventory) {
    bool inMenu = true;
    while (inMenu) {
        showAdminMenu();
        int choice = InputUtils::getValidatedInt("");

        switch (choice) {
            case 1:
                addProductToInventory(inventory);
                break;
            case 2:
                viewAllProducts(inventory);
                break;
            case 3:
                viewStockLevels(inventory);
                break;
            case 4:
                FileHandler::saveInventory(inventory, INVENTORY_FILENAME);
                logout();
                inMenu = false;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

int main() {
    Inventory store;

    cout << "Loading inventory...\n";
    try {
        FileHandler::loadInventory(store, INVENTORY_FILENAME);
        cout << "Inventory loaded successfully.\n";
    } catch (const exception& e) {
        cout << "No previous inventory found or load error. Starting empty.\n";
    }

    bool running = true;

    while (running) {
        if (currentUser.empty()) {
            showMainMenu();
            int choice = InputUtils::getValidatedInt("");

            switch (choice) {
                case 1:
                    simulateLogin();
                    break;
                case 2:
                    cout << "Thank you for using our system!\n";
                    running = false;
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } else {
            if (currentUserRole == "admin") {
                runAdminMenu(store);
            } else {
                runCustomerMenu(store);
            }
        }
    }

    return 0;
}