#include <iostream>
#include "../view/ManagerView.h"
#include "ProductController.h"
using namespace std;
class ManagerController{
    private:
    User user;
    public:
    ManagerController(User& user){
      this->user = user;
    }
    void run(){
        ManagerView view = ManagerView();
        ProductController productController;
        bool status1  = false;
        while(!status1){
             int pilihan = view.menu(user.getName());
             switch (pilihan)
             {
             case 1:
                productController.run();
                break;
             case 2:
                break;
             case 3:
                break;
             case 4:
                break;
             default:
                break;
             }
        }
    }
};