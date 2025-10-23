
#ifndef UTILS_H
#define UTILS_H

#include <vector>
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

#endif
