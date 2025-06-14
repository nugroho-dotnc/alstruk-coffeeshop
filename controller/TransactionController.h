#pragma once
#include<iostream>
#include "../model/Queue.h"
#include "../model/Storage.h"
#include "../data/ProductTree.h"
#include "../data/QueueList.h"
#include<vector>
using namespace std;

class TransactionController {
    private :
        Queue *q; 
        Storage *ps;
        ProductTree *productStorage = new ProductTree();
        QueueList *queueList = new QueueList();
    public : 
        TransactionController(Queue *queue, Storage *productTree) {
            this->q = queue;
            this->ps = productTree;
        }

        void run() {
            system("cls");
            bool status = true;
            while (status)
            {
                int menuSelection = menu();
                switch (menuSelection)
                {
                case 1:
                    this->addTransaction();
                    break;
                case 2:
                    queueList->display();
                    break;
                case 3:
                    productStorage->printTree(ps);
                    // cout << "alsjf";
                    break;
                default:
                    break;
                }
            }
            
        }

        void addTransaction() {
            string customerName;
            Product *tempProduct;
            vector<Product> orderedProductList;
            bool addTransactionProductsStatus = true;


            system("cls");

            cout << "Masukan nama pemesan :";
            getline(cin, customerName);

            system("cls");

            while(addTransactionProductsStatus) {
                cout << "Pesanan atas nama : " << customerName << endl;
                cout<< "===================================" << endl;
                cout << "LIST MENU" << endl;
                cout<< "===================================" << endl;
                productStorage->printTree(ps);
                tempProduct = productStorage->getProductById(ps); 
                if(tempProduct != nullptr) {
                    char addMoreProducts;
                    orderedProductList.push_back(*tempProduct);
                    cout << "Berhasil menambahkan produk ke dalam transaksi, apakah anda ingin menambahkan produk lagi? (y/n)";
                    cin >> addMoreProducts;
                    cin.ignore();
                    if (tolower(addMoreProducts) != 'y') {
                        addTransactionProductsStatus = false;
                    }
                    system("cls");
                } else {
                    cout << "Produk tidak ditemukan" << endl;
                }
            }

            system("cls");
            int sequenceNumber = 1;
            cout << "Pesanan atas nama : " << customerName << endl;
            cout << "===================================" << endl;
            cout << "List Pesanan : " << endl;

            for(Product product : orderedProductList) {
                cout << sequenceNumber++ << ". " << product.productName << " : Rp." << product.price << endl;
            }
        
            char continueTransaction;
            cout << "Lanjutkan untuk pembayaran (y/n)";
            cin >> continueTransaction;
            cin.ignore();

            if (tolower(continueTransaction) != 'y') {
                cout << "Pesanan dibatalkan" << endl;
                return;
            }

            queueList->enqueue(customerName, orderedProductList);
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
