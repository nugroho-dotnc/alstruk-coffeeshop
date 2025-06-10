#pragma once
#include "./Product.h"
#include <vector>
using namespace std;
class Storage{
    public:
    string label;
    Storage* parent;
    vector<Product*> products;
    vector<Storage*> children;
    Storage(const string& label){
        this->label = label;
        this->parent = nullptr;
    }
    Storage(const string& label, const vector<Product*> prods){
        this->label = label;
        this->products = prods;
    }
    Storage(){}
    ~Storage(){
        for(Storage* child : children){
            delete child;
        }
    }
};