#pragma once
// #include "../controller/UserController.h"
#include <iostream>
using namespace std;

class UserView {
public:
  int showMenu() {
    int choice;
    while (true) {
      cout <<endl << "\t\tUser Page" <<endl;
      cout << "==============================================" <<endl;
      cout << "1. Tambah User" <<endl;
      cout << "2. Edit User" <<endl;
      cout << "3. Hapus User" <<endl;
      cout << "4. Tampilkan Semua User" <<endl;
      cout << "5. Keluar" <<endl;
      cout << "==============================================" <<endl;
      cout << "Pilih menu: ";
      cin >> choice;
      cout << "==============================================" <<endl <<endl;
      cin.ignore();
      return choice;
    }
  }
};