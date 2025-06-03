#include <iostream>
#include "../view/ManagerView.h"
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
        }
    }
};