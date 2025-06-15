#pragma once
#include <iostream>
using namespace std;

struct User {
    string name;
    string username;
    string password;
    string role;
};

const int TABLE_SIZE = 50;

// #pragma once
// #include <iostream>
// using namespace std;
// class User{
//     private:
//     string name;
//     string username;
//     string password;
//     string role;
//     public:
//      User(string name, string username, string password, string role) {
//         this->name = name;      
//         this->username = username;
//         this->password = password;
//         this->role = role;
//     }
//     // untuk inisiasi tanpa memasukkan parameter
//     User(){}
//     bool login(string username, string password){
//         if(this->username == username && this->password == password){
//             return true;
//         }
//         return false;
//     }
//     string getRole(){
//         return this->role;
//     }
//     string getName() {
//         return this->name;
//     }
// };