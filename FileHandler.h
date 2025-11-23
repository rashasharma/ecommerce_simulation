#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include "Inventory.h"
#include "Book.h"
#include "Electronics.h"
#include "Apparel.h"

class FileHandler {
public:
    static void saveInventory(const Inventory& inv, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for saving.\n";
            return;
        }

        for (const auto& product : inv.getAllProducts()) {
            int currentStock = inv.getAllProducts().empty() ? 0 : inv.getStockLevel(product->getId());
            
            file << product->toCSV() << "," << currentStock << "\n";
        }
        file.close();
        std::cout << "Inventory saved to " << filename << "\n";
    }

    static void loadInventory(Inventory& inv, const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for loading.");
        }

        std::string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> tokens;

            while (getline(ss, segment, ',')) {
                tokens.push_back(segment);
            }
            if (tokens.size() < 4) continue;

            std::string type = tokens[0];
            
            try {
                std::shared_ptr<Product> product = nullptr;
                int id = std::stoi(tokens[1]);
                std::string name = tokens[2];
                double price = std::stod(tokens[3]);
                
                int stockIndex = -1;
                int stock = 0;

                if (type == "Book") {
                    if (tokens.size() < 5) continue;
                    std::string author = tokens[4];
                    product = std::make_shared<Book>(id, name, price, author);
                    stockIndex = 5;
                } 
                else if (type == "Electronics") {
                    if (tokens.size() < 6) continue;
                    std::string brand = tokens[4];
                    int warranty = std::stoi(tokens[5]);
                    product = std::make_shared<Electronics>(id, name, price, brand, warranty);
                    stockIndex = 6;
                } 
                else if (type == "Apparel") {
                    if (tokens.size() < 6) continue;
                    std::string size = tokens[4];
                    std::string color = tokens[5];
                    product = std::make_shared<Apparel>(id, name, price, size, color);
                    stockIndex = 6;
                }
                if (stockIndex != -1 && tokens.size() > stockIndex) {
                    stock = std::stoi(tokens[stockIndex]);
                } else {
                    stock = 5; 
                }

                if (product) {
                    inv.addProduct(product, stock);
                }
            } catch (const std::exception& e) {
                std::cerr << "Skipping corrupt line: " << line << " (" << e.what() << ")\n";
            }
        }
        file.close();
    }
};

#endif