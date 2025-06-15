#include <iostream>
#include <vector>
#include "model/User.h"
#include "model/Queue.h"
#include "data/ProductTree.h"
#include "controller/ProductController.h"
#include "controller/ManagerController.h"
#include "controller/KasirController.h"
using namespace std;
vector<User> ListUser;
int main(){
    // INI LOGIN SEMENTARA, BUAT BAYANGAN GW AJA (NUGI)
    // ntar semisal udah ada versi fixnya (dari sello) bisa diganti logicnya

    // inisiasi data (Tree, Queue, dll)
    ProductTree* productStorage = new ProductTree();

    // deklarasi data
    Storage* menuRoot = nullptr;
    Queue* queue = nullptr;
    
    // inisialisasi data tree awal
    menuRoot = productStorage->create("menu");
    Storage* food = productStorage->insert(menuRoot, "food");
    productStorage->insert(food, "berat", {new Product("Ikan Goreng", "ID001", 12000, 10), new Product("Ikan Goreng Cipundung", "ID002", 10000, 10)});
    Storage* drink = productStorage->insert(menuRoot, "drink");

    // inisialisasi controller
    ProductController* productController = new ProductController(menuRoot, productStorage);

    User user1; 
    user1.name = "nugroho";
    user1.username = "manajer"; 
    user1.password = "manajer";
    user1.role =  "manajer";
    User user2;
    user2.name = "nugroho";
    user2.username = "kasir";
    user2.password = "kasir123";
    user2.role = "kasir";
        
    ListUser.assign({user1, user2});
    string username, password;
    bool status1 = false;
    while(!status1){
        bool loggedIn = false;
        cout << "LOGIN COFFEESHOP" << endl;
        cout << "Username: "; getline(cin, username);
        cout << "Password: "; getline(cin, password);
        for(User user : ListUser){
            if(user.username == username && user.password == password){
                loggedIn = true;
            }else{
                loggedIn = false;
            }
            if(loggedIn){
                cout<< "LOGIN BERHASIL!" <<endl;
                if(user.role == "manajer"){
                    ManagerController manager = ManagerController(user, productController);
                    manager.run();
                }else{
                    KasirController kasir = KasirController(queue, menuRoot);
                    kasir.run();
                }
            }
        }
    }
    return 0;
}

