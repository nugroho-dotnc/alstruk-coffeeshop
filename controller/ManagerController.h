#pragma once
#include <iostream>
#include "../view/ManagerView.h"
#include "ProductController.h"
#include "UserController.h"
#include "KasirController.h"
using namespace std;
class ManagerController{
  private:
      User* user;
      ProductController* productController;
      UserController* userController;
      QueueList* queueList;
  public:
      ManagerController(User* user, ProductController* productController, UserController* userController, QueueList* queueList) {
        this->user = user;
        this->productController = productController;
        this->userController = userController;
        this->queueList = queueList;
      }
      void run(){
       
        ManagerView view = ManagerView();
        bool status1  = false;
        while(!status1){
              system("cls");
              int pilihan = view.menu(user->name);
              switch (pilihan)
              {
              case 1:
                system("cls");
                  productController->run();
                  break;
              case 2:
                system("cls");
                  userController->run();
                  break;
              case 3:
                system("cls");
                  queueList->display();
                  break;
              case 0:
                system("cls");
                  cout << "Terimakasih, Sampai Jumpa Kembali!" << endl;
                  status1 = true;
                  user = nullptr;
                  break;
              default:
              cout<< "Input tidak valid, coba lagi!" << endl;
                  break;
              }
        }
      }
};