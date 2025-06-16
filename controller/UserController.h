#pragma once
#include "../model/User.h"
#include "../view/UserView.h"
#include <iostream>
#include <string>

class UserController {
private:
    User* table[TABLE_SIZE];

public:
  UserController() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
      table[i] = nullptr;
    }
    insert("Admin Coffeeshop", "admin", "admin123", "admin");
    insert("Kasir Coffeeshop", "kasir", "kasir123", "kasir");
  }

  bool isValidRole(const string& role) {
  return (role == "admin" || role == "kasir");
  }

  int hashFunction(string username) {
    int hashValue = 0;
    for (char c : username) {
      hashValue += c;
    }
    return hashValue % TABLE_SIZE;
  }

    bool isUsernameExists(const string& username) {
    return search(username) != nullptr;
  }

  void insert(string name, string username, string password, string role) {
    int index = hashFunction(username);
    User* newUser = new User{name, username, password, role};

    while (table[index] != nullptr) {
      index = (index + 1) % TABLE_SIZE;
    }
    table[index] = newUser;
  }

  User* search(string username) {
    int index = hashFunction(username);

    while (table[index] != nullptr) {
      if (table[index]->username == username) {
        return table[index];
      }
      index = (index + 1) % TABLE_SIZE;
    }
    return nullptr;
  }

  void remove(string username) {
    int index = hashFunction(username);

    while (table[index] != nullptr) {
      if (table[index]->username == username) {
        delete table[index];
        table[index] = nullptr;
        return;
      }
      index = (index + 1) % TABLE_SIZE;
    }
  }

  void displayAllUsers() {
    cout << "==============================================" <<endl;
    cout << "\t\t Data Users" <<endl;
    for (int i = 0; i < TABLE_SIZE; ++i) {
      if (table[i] != nullptr) {
        cout << "==============================================" <<endl;
        cout << "Nama: " << table[i]->name <<endl;
        cout << "Username: " << table[i]->username <<endl;
        cout << "Role: " << table[i]->role <<endl;
      }
    }
    cout << "==============================================" <<endl;
  }

  void addUser() {
    cout << "==============================================" <<endl;
    cout << "\t\t Tambah User" <<endl;
    string name, username, password, role;

    cout << "==============================================" <<endl;
    cout << "Masukkan Nama Lengkap: ";
    getline(cin, name);
    cout << "Masukkan Username: ";
    getline(cin, username);

    if (isUsernameExists(username)) {
      cout << "Username sudah digunakan. Silakan pilih username lain." << endl;
      return;
    }

    cout << "Masukkan Password: ";
    getline(cin, password);
    
    while (true) {
      cout << "Masukkan Role (Admin/Kasir): ";
      cin >> role;
      if (isValidRole(role)) {
        break;
      } else {
          cout << "Role tidak valid! Hanya admin atau kasir yang diperbolehkan." <<endl;
        }
    }

    insert(name, username, password, role);
    cout << "==============================================" <<endl;
    cout << "User berhasil ditambahkan!" <<endl;
    cout << "==============================================" <<endl;
  }

  void editUser() {
    string oldUsername, newUsername, password, role, name;
    cout << "==============================================" <<endl;
    cout << "\t\t Edit User" <<endl;
    cout << "==============================================" <<endl;
    cout << "Masukkan username yang akan diedit: ";
    cin >> oldUsername;
    cout << "==============================================" <<endl;
    cout << "Note: kosongkan jika tidak ingin mengubah" <<endl;
    cout << "==============================================" <<endl;

    User* user = search(oldUsername);
    if (user != nullptr) {
      cin.ignore();
      cout << "Masukkan nama baru: ";
      getline(cin, name);
      if (name.empty()) {
        name = user->name;
      }

      cout << "Masukkan username baru: ";
      getline(cin, newUsername);
      if (newUsername.empty()) {
        newUsername = user->username;
      } else {
          if (search(newUsername) != nullptr) {
            cout << "Username baru sudah digunakan. Silakan coba username lain." <<endl;
            return;
          }
        }

      cout << "Masukkan password baru: ";
      getline(cin, password);
      if (password.empty()) {
        password = user->password;
      }

      cout << "Masukkan role baru (admin/kasir): ";
      getline(cin, role);
      if (role.empty()) {
        role = user->role;
      }

      remove(oldUsername);
      insert(name, newUsername, password, role);
      cout << "==============================================" <<endl;
      cout << "User berhasil diperbarui!" <<endl;
      cout << "==============================================" <<endl;
    } else {
        cout << "==============================================" <<endl;
        cout << "User tidak ditemukan!" <<endl;
        cout << "==============================================" <<endl;
      }
  }

  void deleteUser() {
    cout << "==============================================" <<endl;
    cout << "\t\tHapus User" <<endl;
    cout << "==============================================" <<endl;
    string username;
    cout << "Masukkan username yang akan dihapus: ";
    cin >> username;
    int index = hashFunction(username);
    int startIdx = index;

    while (table[index] != nullptr) {
      if (table[index]->username == username) {
        delete table[index];
        table[index] = nullptr;

        int nextIndex = (index + 1) % TABLE_SIZE;
        while (table[nextIndex] != nullptr) {
          User* temp = table[nextIndex];
          table[nextIndex] = nullptr;
          insert(temp->name, temp->username, temp->password, temp->role);
          delete temp;
          nextIndex = (nextIndex + 1) % TABLE_SIZE;
        }
        cout << "==============================================" <<endl;
        cout << "User " << username << " berhasil dihapus" <<endl;
        cout << "==============================================" <<endl;
        return;
      }
      index = (index + 1) % TABLE_SIZE;
      if (index == startIdx) break;
    }
    cout << "==============================================" <<endl;
    cout << "User " << username << " tidak ditemukan." <<endl;
    cout << "==============================================" <<endl;
  }

  void run() {
    UserView userChoice;
    while (true) {
      int choice = userChoice.showMenu();
      switch (choice) {
        case 1:
          addUser();
          break;
        case 2:
          editUser();
          break;
        case 3:
          deleteUser();
          break;
        case 4:
          displayAllUsers();
          break;
        case 5:
          cout << "Terima kasih!" <<endl;
          return;
        default:
          cout << "Pilihan tidak valid!" <<endl;
      }
    }
  }

  User* login(string username, string password) {
    User* user = search(username);
    if (user != nullptr && user->password == password) {
      cout << "==============================================" <<endl;
      cout << "Login berhasil!" << endl;
      cout << "==============================================" <<endl;
      return user;
    }
    return nullptr;
  }
};