#pragma once
#include "../model/Storage.h"
#include <vector>

class ProductStorage{
    Storage* root;
    public:
     ProductStorage(){
        root = nullptr;
    }
    ~ProductStorage() {
        if (root != nullptr) {
            delete root; 
            root = nullptr;
        }
    }

    Storage* create(string rootLabel){
        if(root != nullptr){
            cout << "Tree sudah dibuat" << endl;
            return nullptr;
        }
        root = new Storage(rootLabel);
        cout << "Tree berhasil dibuat" << endl;
        return root;
    }

    Storage* insert(Storage*& parent, string label, vector<Product*> prods = {}){
        Storage* newStorage;
        if(!prods.empty()){
            newStorage = new Storage(label, prods);
        }else{
            newStorage = new Storage(label);
        }
        newStorage->parent = parent;
        parent->children.push_back(newStorage);
        return newStorage;
    }

    void printTree(Storage* parent, int indent = 0) const {
            Storage* node = new Storage();
            node = parent;
            if (node == nullptr) {
                return;
            }
            for (int i = 0; i < indent; ++i) {
                cout << "  "; 
            }
            cout << "- " << node->label << ":" << endl;
            if (!node->products.empty()) {
                for (Product* p: node->products) {
                    for (int i = 0; i < indent + 2; ++i) {
                        cout << "  "; 
                    }
                    cout << p->idProduct << " - " << p->productName << " - " << p->price << endl;
                }
            }
            for (Storage* childNode : node->children) {
                printTree(childNode, indent + 1);
            }
        }
    
    void printPath(vector<string> path){
        cout << "Path: menu -> ";
        for (const string& s : path) {
            cout << s << " -> ";
        }
        cout << endl;
    }
    Storage* clusterSearch(Storage* currentNode) {
        vector<string> path;
        Storage* foundStorage = nullptr;
        bool searchActive = true;
        while (searchActive) {
            string label;
            cout << "Masukkan kategori: ";
            getline(cin, label);
            
            foundStorage = searchInParent(currentNode, label);
            if (foundStorage != nullptr) {
                path.push_back(foundStorage->label);
                currentNode = foundStorage;
                printPath(path);
                if (!currentNode->children.empty()) {
                    char lanjut;
                    cout << "Apakah ingin mencari subkategori dari \"" << currentNode->label << "\"? (y/n): ";
                    cin >> lanjut;
                    cin.ignore(); // Buang newline dari buffer

                    if (tolower(lanjut) != 'y') {
                        searchActive = false;
                    }
                } else {
                    cout << "Kategori ditemukan, Tidak ada subkategori dari \"" << currentNode->label << "\".\n";
                    searchActive = false;
                }
            } else {
                cout << "Kategori \"" << label << "\" tidak ditemukan di level ini. Coba lagi.\n";
            }
        }

        return foundStorage;
    }

    Storage* searchInParent(Storage* currentNode,  string targetLabel){
        if(currentNode == nullptr){
            return nullptr;
        }
        if (currentNode->label == targetLabel) {
            return currentNode; 
        }
        for (Storage* childNode : currentNode->children) {
            if (childNode->label == targetLabel) {
                return childNode; 
            }
        }
        return nullptr; 
    }
    void addProduct(Storage* parent, vector<Product*> products){
        if(products.empty()){
            cout << "PRODUCT KOSONG" << endl;
            return;
        }
        for(Product* prod: products){
            bool found = false;
            for(Product* existedProd: parent->products){
                if(prod->idProduct == existedProd->idProduct){
                    found = true;
                    break;
                }
            }
            if(!found){
                parent->products.push_back(prod);
                cout << "produk dengan id " << prod->idProduct << " berhasil ditambahkan!" << endl;
            }else{
                cout << "produk dengan id " << prod->idProduct << " sudah ada!" << endl;
            }
            
        }
    }
    void addCategory(Storage* parent, string label){
        Storage* newNode = new Storage(label);
        newNode->parent = parent;
        newNode->children = {};
        parent->children.push_back(newNode);
    }

    void deleteCategory(string label, Storage* tempNode){
        int position = 0;
        bool found = false;
        for(Storage* storage : tempNode->children){
            if(storage->label == label){
                found = true;
                break;
            }
            position++;
        }
        if(found){
            tempNode->children.erase(tempNode->children.begin() + position);
            cout << "Kategori dengan nama: " << label << " Berhasil dihapus!" << endl; 
        }
    }
    
    void deleteProduct(Storage* parentNode, string idProduct){
        if(parentNode->products.empty()){
            cout << "Product Kosong!" << endl;
            return;
        }
        int position = 0;
        bool found = false;
        for(Product* product : parentNode->products){
            if(product->idProduct == idProduct){
                found = true;
                break;
            }
            position++;
        }
        if(found){
            parentNode->products.erase(parentNode->products.begin() + position);
            cout << "product dengan id "  << idProduct << " berhasil dihapus!" << endl;
        }else{
             cout << "product dengan id "  << idProduct << " tidak ditemukan!" << endl;
        }
    }
};

// contoh penggunaan
// int main(){
//     vector<Product> listProduct = {};
//     listProduct.push_back({ "anu goreng", "ID003", 40000 });
//     listProduct.push_back({"babang goreng", "ID005", 40000});
//     ProductStorage ProductStorage;
//     Storage* menuRoot = ProductStorage.create("menu");
//     Storage* food = ProductStorage.insert(menuRoot, "food");
//     ProductStorage.insert(food, "berat", {{ "kentang goreng", "ID001", 20000 }, { "nasi goreng", "ID002", 25000 }});
//     Storage* drink = ProductStorage.insert(menuRoot, "drink");
//     ProductStorage.printTree(menuRoot);
//     Storage* found = ProductStorage.searchByLabel("berat");
//     ProductStorage.addProduct(found,  listProduct);
//     Storage* category_found = ProductStorage.searchByLabel("food");
//     ProductStorage.addCategory(category_found, "ringan");
//     ProductStorage.printTree(menuRoot);
//     ProductStorage.deleteProduct(found, "ID004");
//     ProductStorage.deleteCategory("drink");
//     ProductStorage.printTree(menuRoot);
//     return 0;
// }