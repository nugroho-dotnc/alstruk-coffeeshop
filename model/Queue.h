#pragma once
#include <string>
#include <vector>
#include "Product.h"

// Menyimpan data produk + quantity dalam satu pesanan
struct ProductOrder {
    Product* product;
    int quantity;
};

// Menyimpan transaksi pelanggan
struct Transaction {
    std::string transactionId;
    time_t timestamp;
    std::vector<ProductOrder> productList;
    double totalAmount;
};

// Node antrian (linked list)
struct QueueNode {
    Transaction data;
    QueueNode* next;
};
