#pragma once
#include "Product.h"
class OrderedProduct
{
    public:
        int qty;
        Product *product;
        // OrderedProduct(const string& name, const string& id, float harga, int qty) {
        //     productName = name;
        //     idProduct = id;
        //     price = harga;
        //     this->qty = qty;
        // }
        OrderedProduct(Product *product, int qty) {
            this->qty = qty;
            this->product = product;
        }
};
