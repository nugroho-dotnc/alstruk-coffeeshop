#pragma once
#include "Product.h"
class OrderedProduct: public Product
{
    public:
        int qty;
        OrderedProduct(const string& name, const string& id, float harga, int qty) {
            productName = name;
            idProduct = id;
            price = harga;
            this->qty = qty;
        }
};
