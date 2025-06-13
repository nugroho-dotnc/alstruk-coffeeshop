#include <iostream>
#include "../view/ManagerView.h"
#include "ProductController.h"
using namespace std;
class ManagerController{
    private:
    User user;
    ProductController* productController;
    public:
    ManagerController(User& user, ProductController* productController){
      this->productController = productController;
      this->user = user;
    }
    void run(){
        ManagerView view = ManagerView();
        bool status1  = false;
        while(!status1){
             int pilihan = view.menu(user.getName());
             switch (pilihan)
             {
             case 1:
                productController->run();
                break;
             case 2:
                cout << "Fitur belum dibuat" << endl;
                break;
             case 0:
                cout << "Terimakasih, Samapai Jumpa Kembali!" << endl;
                status1 = true;
                break;
             default:
               cout<< "Input tidak valid, coba lagi!" << endl;
                  break;
               }
         }
      }
};