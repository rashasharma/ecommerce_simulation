#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include "Product.h"
using namespace std;

template <typename T>
T* findItemById(const vector<T*>& items, int id) {
    for (T* item : items) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}
class InputUtils {
public:
    static int getValidatedInt(const string& prompt) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                return value;
            } else {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    static double getValidatedDouble(const string& prompt) {
        double value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                return value;
            } else {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    static string getStringInput(const string& prompt) {
        cout << prompt;
        string value;
        if (cin.peek() == '\n') cin.ignore(); 
        getline(cin, value);
        return value;
    }
};

#endif