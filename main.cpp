#include <iostream>
#include <vector>
#include "model/User.h"
#include "model/Queue.h"
#include "data/ProductTree.h"
#include "controller/ProductController.h"
#include "controller/ManagerController.h"
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
    productStorage->insert(food, "berat", {new Product("Ikan Goreng", "ID001", 12000), new Product("Ikan Goreng Cipundung", "ID002", 10000)});
    Storage* drink = productStorage->insert(menuRoot, "drink");

    // inisialisasi controller
    ProductController* productController = new ProductController(menuRoot, productStorage);

    User user1 = User("nugroho", "manajer", "manajer", "manajer");
    User user2 = User("farrel", "kasir", "kasir123", "kasir");
    ListUser.assign({user1, user2});
    string username, password;
    bool status1 = false;
    while(!status1){
        bool loggedIn = false;
        cout << "LOGIN COFFEESHOP" << endl;
        cout << "Username: "; getline(cin, username);
        cout << "Password: "; getline(cin, password);
        for(User user : ListUser){
            loggedIn = user.login(username, password);
            if(loggedIn){
                cout<< "LOGIN BERHASIL!" <<endl;
                if(user.getRole() == "manajer"){
                    ManagerController manager = ManagerController(user, productController);
                    manager.run();
                }else{
                    cout << "GWEJ GA NGURUS YANG NI, WAHAHAHHA"<<endl;
                }
            }
        }
    }
    return 0;
}

// int main() {
//     ProductStorage* ps = new ProductStorage();
//     Queue* queue = nullptr;
//     Storage* menuRoot = ps->create("menu");
//     Storage* food = ps->insert(menuRoot, "food");
//     ps->insert(food, "berat", {new Product("Ikan Goreng", "ID001", 12000)});
//     Storage* drink = ps->insert(menuRoot, "drink");

//     // ProductController* productController = new ProductController(ps, menuRoot);
//     TransactionController* transactionController = new TransactionController(queue, menuRoot);

//     // ps->printTree(menuRoot);
//     transactionController->run();

    
//     // dst...
//     return 0;
// }
