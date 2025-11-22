#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include "Product.h"

template <typename T>
T* findItemById(const std::vector<T*>& items, int id) {
    for (T* item : items) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}
class InputUtils {
public:
    static int getValidatedInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                return value;
            } else {
                std::cout << "Invalid input. Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    static double getValidatedDouble(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                return value;
            } else {
                std::cout << "Invalid input. Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    static std::string getStringInput(const std::string& prompt) {
        std::cout << prompt;
        std::string value;
        std::cin >> value;
        return value;
    }
};

#endif