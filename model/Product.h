#pragma once
#include <iostream>
using namespace std;
class Product{
    public:
        string productName;
        string idProduct;
        float price;
        int stock;
        Product(const string& name, const string& id, float harga, int stock){
            productName = name;
            idProduct = id;
            price = harga;
            this->stock = stock;
        }
        // untuk inisiasi tanpa memasukkan parameter
        Product(){}
};
