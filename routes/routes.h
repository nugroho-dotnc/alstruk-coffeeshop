#include<iostream>
#include "../controller/ProductController.h"
#include "../controller/TransactionController.h"
using namespace std;

void route() {
    int choice;
    cout << "SELAMAT DATANG DI SISTEM INFORMASI COFFEE SHOP XYZ" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "1. Order" << endl;
    cout << "2. Produk" << endl;
    cout << "3. Logout" << endl;
    cout << "Masukan menu yang ingin anda pilih : ";
    cin >> choice;
    switch(choice) {
        case 1 : {
            TransactionController transactionController;        
            break;
        }
        case 2 : {
            ProductController productController;
            break;
        }
    }
}