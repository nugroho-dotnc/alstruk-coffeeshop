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
        productStorage.insert(food, "berat", {new Product("Ikan Goreng", "ID001", 12000), new Product("Ikan Goreng Cipundung", "ID002", 10000)});
        Storage* drink = productStorage.insert(menuRoot, "drink");
        productStorage.printTree(menuRoot);
    }
    void run(){
        bool status = false;
        while(!status){
             cout << "DATA PRODUCT:" << endl;
             productStorage.printTree(menuRoot); 
             productView.menu();
            int opsi;
            cout << "Pilihan Anda: "; cin >> opsi;
            cin.ignore();
            cout << endl;
            switch (opsi)
            {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                addCategory();
                break;
            case 5:
                deleteCategory();
                break;
            case 0:
                status = true;
                break;
            default:
                break;
            }
        }
    }
    void addProduct(){
        vector<Product*> ListProduct;
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
        Product* product  = new Product();
        cout << "Id Product : ";
        getline(cin, product->idProduct);
        cout << "Nama Produk : ";
        getline(cin, product->productName);
        string harga;
        while (true) {
            cout << "Harga Product: ";
            getline(cin, harga);
            try {
                product->price = stof(harga);
                break;
            } catch (...) {
                cout << "Harga tidak valid! Ulangi." << endl;
            }
        }
        ListProduct.push_back(product);
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
    void editProduct(){
        string kategori, idProduct;
        cout << "==============" << endl;
        cout << "EDIT PRODUK" << endl;
        cout << "==============" << endl;
        cout << "Kategori produk yang akan di edit: ";
        getline(cin, kategori);

        Storage* category = productStorage.searchByLabel(kategori);
        if(category == nullptr){
            cout << "Kategori " << kategori << " tidak ditemukan! "<<endl;
            return;
        }

        cout << "Id Produk yang akan diedit: ";
        getline(cin, idProduct);

        for(Product* p: category->products){
            if(p->idProduct == idProduct){
                cout << "Nama Produk lama : " << p->productName << endl;
                cout << "Nama Produk baru (Enter untuk tidak mengubah): ";
                string namaProduk;
                getline(cin, namaProduk);
                if(!namaProduk.empty()){
                    p->productName = namaProduk;
                }

                cout << "Harga lama : " << p->price << endl;
                cout << "Harga baru (Enter untuk tidak mengubah): ";
                string hargaInput;
                getline(cin, hargaInput);
                if(!hargaInput.empty()){
                    try {
                        p->price = stof(hargaInput);
                    } catch (...) {
                        cout << "Input harga tidak valid. Harga tidak diubah." << endl;
                    }
                }

                cout << "Produk berhasil diperbarui!" << endl;
                return;
            }
        }

        cout << "Produk dengan ID " << idProduct << " tidak ditemukan!" << endl;
    }
    void deleteProduct(){
        string kategori, idProduct;
        cout << "==============" << endl;
        cout << "DELETE PRODUK" << endl;
        cout << "==============" << endl;
        cout << "Kategori produk yang akan di hapus: ";
        getline(cin, kategori);

        Storage* category = productStorage.searchByLabel(kategori);
        if(category == nullptr){
            cout << "Kategori " << kategori << " tidak ditemukan! "<<endl;
            return;
        }
        cout << "Id Produk yang akan dihapus: ";
        getline(cin, idProduct);
        productStorage.deleteProduct(category, idProduct);
    }
    void addCategory() {
        string parentCategoryLabel = productView.TextBox("Parent Kategori: ");
        Storage* parentCategory = productStorage.searchByLabel(parentCategoryLabel);
        if(parentCategory == nullptr){
            cout << "parent kategori tidak ditemukan!" << endl;
            return;
        }
        string newCategory = productView.TextBox("Kategori Baru: ");
        Storage* storage =  productStorage.searchByLabel(newCategory);
        if(!(storage == nullptr)){
            cout << "Kategori dengan nama " << newCategory << " sudah ada!" <<endl;
            return;
        }
        productStorage.addCategory(parentCategory, newCategory);
    }
    void deleteCategory(){
        string category = productView.TextBox("kategori yang mau dihapus: ");
        productStorage.deleteCategory(category);
    }
};