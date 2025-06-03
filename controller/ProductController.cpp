#include "../model/Storage.h"
class ProductController{
    Storage* root;
    public:
     ProductController(){
        root = nullptr;
    }
    ~ProductController() {
        if (root != nullptr) {
            delete root; 
            root = nullptr;
        }
    }

    Storage* create(string rootLabel){
        if(root != nullptr){
            cout << "Tree sudah dibuat";
            return nullptr;
        }
        root = new Storage(rootLabel);
        cout << "Tree berhasil dibuat";
        return root;
    }

    Storage* insert(Storage*& parent, string label, vector<Product> prods = {}){
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

    void printTree(Storage* node, int indent = 0) const {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < indent; ++i) {
            cout << "  "; 
        }
        cout << "- " << node->label;
        if (!node->products.empty()) {
            cout << " (Produk: ";
            for (int i = 0; i < node->products.size(); ++i) {
                cout << node->products[i].productName;
                if (i < node->products.size() - 1) {
                    cout << ", ";
                }
            }
            cout << ")";
        }
        cout << endl;

        for (Storage* childNode : node->children) {
            printTree(childNode, indent + 1);
        }
    }
    Storage* _searchByLabel(Storage* currentNode, const string& targetLabel) const {
        if (currentNode == nullptr) {
            return nullptr; 
        }
        if (currentNode->label == targetLabel) {
            return currentNode; 
        }
        
        for (Storage* childNode : currentNode->children) {
            Storage* foundNode = _searchByLabel(childNode, targetLabel);
            if (foundNode != nullptr) {
                return foundNode; 
            }
        }
        
        return nullptr; 
    }
    Storage* searchByLabel(const string& targetLabel) const {
        if (root == nullptr) {
            cout << "Tree kosong. Tidak bisa mencari." << endl;
            return nullptr;
        }
        cout << "Mencari node dengan label '" << targetLabel << "'..." << endl;
        Storage* result = _searchByLabel(root, targetLabel);
        if (result != nullptr) {
            cout << "Node dengan label '" << targetLabel << "' ditemukan!" << endl;
        } else {
            cout << "Node dengan label '" << targetLabel << "' tidak ditemukan." << endl;
        }
        return result;
    }
    void addProduct(Storage*& parent, vector<Product> products){
        if(products.empty()){
            cout << "PRODUCT KOSONG" << endl;
            return;
        }
        for(Product prod: products){
            parent->products.push_back(prod);
        }
    }
    void addCategory(Storage*& parent, string label){
        Storage* newNode = new Storage(label);
        newNode->parent = parent;
        newNode->children = {};
        parent->children.push_back(newNode);
    }
};
int main(){
    ProductController productController;
    Storage* menuRoot = productController.create("menu");
    Storage* food = productController.insert(menuRoot, "food");
    productController.insert(food, "berat", {{ "kentang goreng", "ID001", 20000 }, { "nasi goreng", "ID002", 25000 }});
    Storage* drink = productController.insert(menuRoot, "drink");
    productController.printTree(menuRoot);
    Storage* found = productController.searchByLabel("berat");
    productController.addProduct(found,  {{ " goreng", "ID003", 40000 }, { "nasi goyang", "ID004", 30000 }});
    Storage* category_found = productController.searchByLabel("food");
    productController.addCategory(category_found, "ringan");
    productController.printTree(menuRoot);
    return 0;
}