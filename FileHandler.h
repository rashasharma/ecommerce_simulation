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
           file << product->toCSV() << "\n";
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

            if (tokens.empty()) continue;

            std::string type = tokens[0];
            
            try {
                std::shared_ptr<Product> product = nullptr;
                int id = std::stoi(tokens[1]);
                std::string name = tokens[2];
                double price = std::stod(tokens[3]);
                int stock = 5; 
                if (type == "Book") {
                    std::string author = tokens[4];
                    product = std::make_shared<Book>(id, name, price, author);
                } 
                else if (type == "Electronics") {
                    std::string brand = tokens[4];
                    int warranty = std::stoi(tokens[5]);
                    product = std::make_shared<Electronics>(id, name, price, brand, warranty);
                } 
                else if (type == "Apparel") {
                    std::string size = tokens[4];
                    std::string color = tokens[5];
                    product = std::make_shared<Apparel>(id, name, price, size, color);
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