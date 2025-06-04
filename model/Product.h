#include <iostream>
using namespace std;
class Product{
    public:
    string productName;
    string idProduct;
    float harga;
    Product(){}
    Product(const string& name, const string& id, float price){
        productName = name;
        idProduct = id;
        harga = price;
    }
};
