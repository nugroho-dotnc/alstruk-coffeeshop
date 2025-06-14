#pragma once
#include <string>
#include <vector>
#include "Product.h"
using namespace std;

class Queue {
public:
    string queueId;
    string label;
    vector<Product> products;
    Queue* next;

    Queue(string id, string label, vector<Product> products) {
        this->queueId = id;
        this->label = label;
        this->products = products;
        this->next = nullptr;
    }
};
