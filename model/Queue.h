#include <string>
#include<vector>
#include "Product.h"
using namespace std;

class Queue {
    public :   
        Queue* next;
        string queueLabel;
        vector<Product> productList;

        Queue(string label) {
            this->queueLabel = label;
            this->next = nullptr;
            // this->productList = productList;
        }
};