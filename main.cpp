#include <iostream>
#include <vector>
#include "model/User.h"
#include "model/Queue.h"
#include "controller/ManagerController.h"
#include "data/ProductStorage.h"
#include "controller/TransactionController.h"
using namespace std;
vector<User> ListUser;
int main(){
    // INI LOGIN SEMENTARA, BUAT BAYANGAN GW AJA (NUGI)
    // ntar semisal udah ada versi fixnya (dari sello) bisa diganti logicnya

    // deklarasi data baru
    Storage *menuRoot = nullptr;
    Queue* queue = nullptr;
    ProductStorage *ps; 

    // inisialisasi controller
    ProductController* productController = new ProductController(menuRoot);

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
                    ps->printTree(menuRoot);
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
