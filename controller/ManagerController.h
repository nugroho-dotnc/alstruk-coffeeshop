#include <iostream>
#include "../view/ManagerView.h"
#include "ProductController.h"
using namespace std;
class ManagerController{
    private:
    string name;
    public:
    ManagerController(string name){
        this->name = name;
    }
    void run(){
        ManagerView view = ManagerView();
        bool status1  = false;
        while(!status1){
             int pilihan = view.menu(name);
             switch (pilihan)
             {
             case 1:
                
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