#include <string>
#include<vector>
using namespace std;

struct Product 
{
    int id;
    float harga;
    string label;
};


class Queue {
    public :   
        Queue* next;
        string queueLabel;
        vector<Product> productList;

        Queue(string label, Queue* next, vector<Product> productList) {
            this->queueLabel = label;
            this->next = next;
            this->productList = productList;
        }


};