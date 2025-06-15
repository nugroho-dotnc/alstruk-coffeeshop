#include <iostream>
#include <vector>
#include "model/User.h"
#include "model/Queue.h"
#include "data/ProductTree.h"
#include "controller/ProductController.h"
#include "controller/ManagerController.h"
#include "controller/KasirController.h"
#include "controller/UserController.h"
using namespace std;
vector<User> ListUser;
int main(){
    // INI LOGIN SEMENTARA, BUAT BAYANGAN GW AJA (NUGI)
    // ntar semisal udah ada versi fixnya (dari sello) bisa diganti logicnya

    // inisiasi data (Tree, Queue, dll)
    ProductTree* productStorage = new ProductTree();
    QueueList* queueList = new QueueList();

    // deklarasi data
    Storage* menuRoot = nullptr;
    User* table[TABLE_SIZE];
    
    // inisialisasi data tree awal
    menuRoot = productStorage->create("menu");
    Storage* food = productStorage->insert(menuRoot, "food");
    productStorage->insert(food, "berat", {new Product("Ikan Goreng", "ID001", 12000, 10), new Product("Ikan Goreng Cipundung", "ID002", 10000, 10)});
    Storage* drink = productStorage->insert(menuRoot, "drink");

    
    // inisialisasi controller
    ProductController* productController = new ProductController(menuRoot, productStorage);
    UserController* userController = new UserController();


    string username, password;
    bool status1 = false;
    while(!status1){
        system("cls");
        User* user;
        cout << "==============================================" <<endl;
        cout << "\t\tLogin Page" <<endl;
        cout << "==============================================" <<endl;
        string username, password;
        cout << "Masukkan username: ";
        getline(cin, username);
        cout << "Masukkan password: ";
        getline(cin, password);
        user = userController->login(username, password);
        if(user != nullptr){
            if(user->role == "admin"){
                ManagerController manager = ManagerController(user, productController, userController, queueList);
                manager.run();
            } else{
                KasirController kasir = KasirController( menuRoot, user, queueList);
                kasir.run();
            }
        } else {
            cout << "==============================================" <<endl;
            cout << "Username atau password salah!" <<endl;
            cout << "==============================================" <<endl;
          }
    }
    return 0;
}