#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

struct product {
    string productName;
    string idProduct;
    float harga;

    product(const string& name, const string& id, float price){
        productName = name;
        idProduct = id;
        harga = price;
    }
};

struct TreeStorage {
    string label;                   
    vector<product> products;     
    TreeStorage* parent;            
    vector<TreeStorage*> children; 

    TreeStorage(const string& lbl){
        label = lbl;
        parent = nullptr;
    }

    TreeStorage(const string& lbl, const vector<product>& prods){
        label = lbl;
        products = prods;
    }

    ~TreeStorage() {
        for (TreeStorage* childNode : children) {
            delete childNode; 
        }
    }
};

class Storage {
public:
    TreeStorage* root; 

    Storage(){
        root = nullptr;
    }

    ~Storage() {
        if (root != nullptr) {
            delete root; 
            root = nullptr;
        }
    }

    TreeStorage* createRoot(const string& label, const vector<product>& products = {}) {
        if (root != nullptr) {
            cout << "Tree sudah berhasil dibuat. Tidak bisa membuat ulang root." << endl;
            return nullptr;
        }
        if (!products.empty()) {
            root = new TreeStorage(label, products);
        } else {
            root = new TreeStorage(label);
        }
        cout << "Root tree berhasil dibuat dengan label: " << label << endl;
        return root;
    }
    
    TreeStorage* add(TreeStorage* parentNode, const string& label, const vector<product>& products = {}) {
        if (root == nullptr) {
            cout << "Tree belum ada. Buat root tree terlebih dahulu." << endl;
            return nullptr;
        }
        if (parentNode == nullptr) {
            cout << "Node parent tidak valid (nullptr)." << endl;
            return nullptr;
        }

        TreeStorage* newNode;
        if (!products.empty()) {
            newNode = new TreeStorage(label, products);
        } else {
            newNode = new TreeStorage(label);
        }
        
        newNode->parent = parentNode;
        parentNode->children.push_back(newNode);
        
        cout << "Node '" << label << "' berhasil ditambahkan sebagai anak dari '" << parentNode->label << "'" << endl;
        return newNode;
    }

    TreeStorage* _searchByLabel(TreeStorage* currentNode, const string& targetLabel) const {
        if (currentNode == nullptr) {
            return nullptr; 
        }
        if (currentNode->label == targetLabel) {
            return currentNode; 
        }
        
        for (TreeStorage* childNode : currentNode->children) {
            TreeStorage* foundNode = _searchByLabel(childNode, targetLabel);
            if (foundNode != nullptr) {
                return foundNode; 
            }
        }
        
        return nullptr; 
    }

    TreeStorage* searchByLabel(const string& targetLabel) const {
        if (root == nullptr) {
            cout << "Tree kosong. Tidak bisa mencari." << endl;
            return nullptr;
        }
        cout << "Mencari node dengan label '" << targetLabel << "'..." << endl;
        TreeStorage* result = _searchByLabel(root, targetLabel);
        if (result != nullptr) {
            cout << "Node dengan label '" << targetLabel << "' ditemukan!" << endl;
        } else {
            cout << "Node dengan label '" << targetLabel << "' tidak ditemukan." << endl;
        }
        return result;
    }

    void deleteNode(TreeStorage* nodeToDelete) {
        if (root == nullptr) {
            cout << "Tree kosong. Tidak ada yang bisa dihapus." << endl;
            return;
        }
        if (nodeToDelete == nullptr) {
            cout << "Node yang ingin dihapus tidak valid (nullptr)." << endl;
            return;
        }

        if (nodeToDelete == root) {
            delete root; 
            root = nullptr;
            cout << "Seluruh tree berhasil dihapus." << endl;
            return;
        }

        if (nodeToDelete->parent != nullptr) {
            TreeStorage* parentNode = nodeToDelete->parent;
            parentNode->children.erase(
                std::remove(parentNode->children.begin(), parentNode->children.end(), nodeToDelete),
                parentNode->children.end()
            );
            nodeToDelete->parent = nullptr; 
        }
        
        delete nodeToDelete;
        cout << "Node dan sub-tree berhasil dihapus." << endl;
    }

    void printTree(TreeStorage* node, int indent = 0) const {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < indent; ++i) {
            cout << "  "; 
        }
        cout << "- " << node->label;
        if (!node->products.empty()) {
            cout << " (Produk: ";
            for (size_t i = 0; i < node->products.size(); ++i) {
                cout << node->products[i].productName;
                if (i < node->products.size() - 1) {
                    cout << ", ";
                }
            }
            cout << ")";
        }
        cout << endl;

        for (TreeStorage* childNode : node->children) {
            printTree(childNode, indent + 1);
        }
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void clear() {
        if (root == nullptr) {
            cout << "Tree sudah kosong!" << endl;
            return;
        }
        delete root; 
        root = nullptr;
        cout << "Tree berhasil dikosongkan!" << endl;
    }
};

int main() {
    Storage treeStorage;

    TreeStorage* menuRoot = treeStorage.createRoot("Menu");

    TreeStorage* foodNode = treeStorage.add(menuRoot, "Food");

    vector<product> foodProducts = {
        product("Nasi Goreng", "F001", 25000.0f),
        product("Mie Ayam", "F002", 20000.0f),
        product("Sate Ayam", "F003", 30000.0f)
    };
    treeStorage.add(foodNode, "Daftar Makanan", foodProducts);

    TreeStorage* drinkNode = treeStorage.add(menuRoot, "Drink");

    TreeStorage* nonCoffeeNode = treeStorage.add(drinkNode, "Non-Coffee");

    vector<product> nonCoffeeProducts = {
        product("Es Teh", "DNC001", 8000.0f),
        product("Jus Jeruk", "DNC002", 15000.0f)
    };
    treeStorage.add(nonCoffeeNode, "Daftar Non-Coffee", nonCoffeeProducts);

    TreeStorage* coffeeNode = treeStorage.add(drinkNode, "Coffee");

    vector<product> coffeeProducts = {
        product("Espresso", "DC001", 18000.0f),
        product("Cappuccino", "DC002", 22000.0f),
        product("Latte", "DC003", 23000.0f)
    };
    treeStorage.add(coffeeNode, "Daftar Coffee", coffeeProducts);

    cout << "\n--- Struktur Tree Awal ---" << endl;
    treeStorage.printTree(treeStorage.root);

    cout << "\n--- Operasi Pencarian ---" << endl;
    TreeStorage* foundFoodNode = treeStorage.searchByLabel("Food");
    if (foundFoodNode) {
        cout << "Ditemukan node: " << foundFoodNode->label << endl;
    }

    TreeStorage* foundLatteList = treeStorage.searchByLabel("Daftar Coffee");
    if (foundLatteList) {
        cout << "Ditemukan node: " << foundLatteList->label << " dengan produk: ";
        for (const auto& p : foundLatteList->products) {
            cout << p.productName << " ";
        }
        cout << endl;
    }

    TreeStorage* notFound = treeStorage.searchByLabel("Dessert");
    if (notFound) {
    }

    cout << "\n--- Operasi Penghapusan ---" << endl;
    TreeStorage* nodeToDelete = treeStorage.searchByLabel("Non-Coffee");
    if (nodeToDelete) {
        treeStorage.deleteNode(nodeToDelete);
    }

    cout << "\n--- Struktur Tree Setelah Penghapusan Non-Coffee ---" << endl;
    treeStorage.printTree(treeStorage.root);

    cout << "\n--- Menghapus Seluruh Tree ---" << endl;
    treeStorage.deleteNode(menuRoot);   

    cout << "Tree kosong? " << (treeStorage.isEmpty() ? "Ya" : "Tidak") << endl;

    return 0;
}
