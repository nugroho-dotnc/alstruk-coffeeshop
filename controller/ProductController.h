#include <iostream>
#include "../view/ProductView.h"
#include <vector>
using namespace std;
class ProductController{
    private:
    ProductStorage productStorage;
    ProductView productView;
    Storage* menuRoot;
    public:
    ProductController(){
        menuRoot = productStorage.create("menu");
        Storage* food = productStorage.insert(menuRoot, "food");
        productStorage.insert(food, "berat", {{ "kentang goreng", "ID001", 20000 }, { "nasi goreng", "ID002", 25000 }});
        Storage* drink = productStorage.insert(menuRoot, "drink");
        productStorage.printTree(menuRoot);
    }
    void run(){
        bool status = false;
        while(!status){
            int opsi = productView.menu(productStorage, menuRoot);
            switch (opsi)
            {
            case 1:
                addProduct();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 0:
                break;
            default:
                break;
            }
        }
    }
    void addProduct(){
        vector<Product> ListProduct;
        string kategori;
        cout << "==============" << endl;
        cout << "TAMBAH PRODUK" << endl;
        cout << "==============" << endl;
        cout << "Kategori produk yang akan ditambahkan: ";
        getline(cin, kategori);
        Storage* category = productStorage.searchByLabel(kategori);
        if(category == nullptr){
            cout << "Kategori " << kategori << " tidak ditemukan! "<<endl;
            return;
        }
        bool status = false;
        while(!status){
        Product product;
        cout << "Id Product : ";
        getline(cin, product.idProduct);
        cout << "Nama Produk : ";
        getline(cin, product.productName);
        string harga;
        while (true) {
            cout << "Harga Product: ";
            getline(cin, harga);
            try {
                product.harga = stof(harga);
                break;
            } catch (...) {
                cout << "Harga tidak valid! Ulangi." << endl;
            }
        }
        ListProduct.push_back({product.productName, product.idProduct, product.harga});
        string opsi;
        cout << "Tambah produk lagi? (Y/N)";
        getline(cin, opsi);
        cout << endl;
        if(!(opsi == "Y" || opsi == "y")){
            status = true;
        }
        }
        productStorage.addProduct(category, ListProduct);
    }
};