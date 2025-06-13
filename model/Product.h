#pragma once
#include <iostream>
using namespace std;
class Product{
    public:
        string productName;
        string idProduct;
        float price;
        Product(const string& name, const string& id, float harga){
            productName = name;
            idProduct = id;
            price = harga;
        }
        // untuk inisiasi tanpa memasukkan parameter
        Product(){}
};
