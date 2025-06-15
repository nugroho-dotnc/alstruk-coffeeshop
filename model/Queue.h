#pragma once
#include <string>
#include <vector>
#include "OrderedProduct.h"
using namespace std;

class Queue {
public:
    string queueId;
    string label;
    float total;
    vector<OrderedProduct> products;
    Queue* next;

    Queue(string id, string label, vector<OrderedProduct> products, float total) {
        this->queueId = id;
        this->label = label;
        this->products = products;
        this->total = total; 
        this->next = nullptr;
    }
};
