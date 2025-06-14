#include "../controller/UserController.h"
#include <iostream>
using namespace std;

class UserView {
private:
  UserController controller;

public:
  void showMenu() {
    int choice;
    while (true) {
      cout <<endl << "\t\tUser Page" <<endl;
      cout << "==============================================" <<endl;
      cout << "1. Tambah User" <<endl;
      cout << "2. Edit User" <<endl;
      cout << "3. Hapus User" <<endl;
      cout << "4. Login" <<endl;
      cout << "5. Tampilkan Semua User" <<endl;
      cout << "6. Keluar" <<endl;
      cout << "==============================================" <<endl;
      cout << "Pilih menu: ";
      cin >> choice;
      cout << "==============================================" <<endl <<endl;

      switch (choice) {
        case 1:
          controller.addUser();
          break;
        case 2:
          controller.editUser();
          break;
        case 3:
          controller.deleteUser();
          break;
        case 4:
          controller.login();
          break;
        case 5:
          controller.displayAllUsers();
          break;
        case 6:
          cout << "Terima kasih!" <<endl;
          return;
        default:
          cout << "Pilihan tidak valid!" <<endl;
      }
    }
  }
};