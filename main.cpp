#include <iostream>
#include <vector>
#include "model/User.h"
#include "controller/ManagerController.h"
#include "data/ProductStorage.h"
using namespace std;
vector<User> ListUser;
int main(){
    // INI LOGIN SEMENTARA, BUAT BAYANGAN GW AJA (NUGI)
    // ntar semisal udah ada versi fixnya (dari sello) bisa diganti logicnya

    // deklarasi data baru
    Storage* menuRoot = nullptr;
   

    // inisialisasi controller
    ProductController* productController = new ProductController( menuRoot);


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
                    cout << "KASIR BUKAN GWEJ YG NGURUS, WUAHAHAHAH" << endl;
                }
            }
        }
    }
    return 0;
}