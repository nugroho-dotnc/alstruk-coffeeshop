#pragma once
#include <iostream>
using namespace std;
class ProductView{
    public:
    void menu(){
        cout << "===================" << endl;
        cout << "MENU KELOLA PRODUK" << endl;
        cout << "===================" << endl;
        cout << "[1] Tambah Produk" << endl;
        cout << "[2] Edit Produk" << endl;
        cout << "[3] Hapus produk" << endl;
        cout << "[4] Tambah Kategori" << endl;
        cout << "[5] Hapus Kategori" << endl;
        cout << "[0] Keluar" << endl;
    };
    Product addProductView() {
        Product product;
        cout << "==============" << endl;
        cout << "TAMBAH PRODUK" << endl;
        cout << "==============" << endl;
        cout << "Id Product : ";
        getline(cin, product.idProduct);
        cout << "Nama Produk : ";
        getline(cin, product.productName);
        cout << "Harga Product: ";
        string harga;
        getline(cin, harga);

        try {
            product.price = stof(harga);
        } catch (...) {
            cout << "Harga tidak valid!" << endl;
            product.price = 0;
        }

        return product;
    }
    string TextBox(string label) {
        cout << label;
        string input;
        getline(cin, input);
        return input;
    }
};