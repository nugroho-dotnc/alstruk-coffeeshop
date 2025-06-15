#include<iostream>
using namespace std; 

class KasirView {
    public :
        int menu(string name) {
            system("cls");
            cout<< "===================================" << endl;
            cout<< "COFFEE SHOP MANAGEMENT SYSTEM" << endl;
            cout<< "===================================" << endl;
            cout<< "Selamat datang, " << name <<"! (KASIR)"<< endl;
            cout<< "Pilihan Menu:" << endl;
            cout<< "[1] Buat Pesanan Baru" << endl;
            cout<< "[2] Lihat Antrean Pesanan" << endl;
            cout<< "[3] Lihat Daftar Produk" << endl;
            cout<< "[0] Logout" << endl;
            cout << "Masukkan Pilihan Anda: ";
            int pilihan;
            cin >> pilihan;
            cin.ignore();
            return pilihan;
        }
};