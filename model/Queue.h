#pragma once
#include <string>
#include <vector>
#include "Product.h"
using namespace std;

class Queue {
public:
    string label;
    vector<Product*> products;
    Queue* next;

    Queue(string label, vector<Product*> products) {
        this->label = label;
        this->products = products;
        this->next = nullptr;
    }
};
