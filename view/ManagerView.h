#include<iostream>
using namespace std;
class ManagerView{
    public:
    int menu(string name){
            cout<< "===================================" << endl;
            cout<< "COFFEE SHOP MANAGEMENT SYSTEM" << endl;
            cout<< "===================================" << endl;
            cout<< "Selamat datang, " << name <<"! (MANAJER)"<< endl;
            cout<< "Pilihan Menu:" << endl;
            cout<< "[1] Kelola Produk" << endl;
            cout<< "[2] Lihat Antrean Pesanan" << endl;
            cout<< "[0] Logout" << endl;
            cout << "Masukkan Pilihan Anda: ";
            int pilihan;
            cin >> pilihan;
            cin.ignore();
            return pilihan;
    }
};