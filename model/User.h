#include <iostream>
using namespace std;
class User{
    private:
    string name;
    string username;
    string password;
    string role;
    public:
     User(string name, string username, string password, string role) {
        this->name = name;      
        this->username = username;
        this->password = password;
        this->role = role;
    }
    bool login(string username, string password){
        if(this->username == username && this->password == password){
            return true;
        }
        return false;
    }
    string getRole(){
        return this->role;
    }
    string getName() {
        return this->name;
    }
};