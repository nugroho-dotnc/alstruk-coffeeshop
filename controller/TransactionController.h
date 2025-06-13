#include<iostream>
#include "../model/Queue.h"
#include "../model/Storage.h"
#include "../data/ProductStorage.h"
#include "../data/QueueList.h"
using namespace std;

class TransactionController {
    private :
        Queue *q; 
        Storage *ps;
        ProductStorage *productStorage = new ProductStorage();
    public : 
        TransactionController(Queue *queue, Storage *ps) {
            this->q = queue;
            this->ps = ps;
            cout << "This is transaction controller";
        }

        void run() {
            productStorage->printTree(ps);
            // bool status = true;
            // while (status)
            // {
            //     int menuSelection = menu();
            //     switch (menuSelection)
            //     {
            //     case 1:
            //         /* code */
            //         break;
            //     case 2:
            //         /* code */
            //         break;
            //     case 3:
            //         productStorage->printTree(ps);
            //         // cout << "alsjf";
            //         break;
            //     default:
            //         break;
            //     }
            // }
            
        }
        
        int menu(){
            cout<< "===================================" << endl;
            cout<< "COFFEE SHOP MANAGEMENT SYSTEM" << endl;
            cout<< "===================================" << endl;
            // cout<< "Selamat datang, " << name <<"! (MANAJER)"<< endl;
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
