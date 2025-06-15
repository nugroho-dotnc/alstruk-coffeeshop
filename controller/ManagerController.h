#pragma once
#include <iostream>
#include "../view/ManagerView.h"
#include "ProductController.h"
#include "UserController.h"
using namespace std;
class ManagerController{
  private:
      User* user;
      ProductController* productController;
      UserController* userController;
      KasirController* kasirController;
  public:
      ManagerController(User* user, ProductController* productController, UserController* userController, KasirController* kasirController) {
        this->user = user;
        this->productController = productController;
        this->userController = userController;
        this->kasirController = kasirController;
      }
      void run(){
        ManagerView view = ManagerView();
        bool status1  = false;
        while(!status1){
              int pilihan = view.menu(user->name);
              switch (pilihan)
              {
              case 1:
                  productController->run();
                  break;
              case 2:
                  userController->run();
                  break;
              case 3:
                  kasirController->displayTransaction();
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