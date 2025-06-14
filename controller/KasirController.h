#pragma once
#include<iostream>
#include "../model/Queue.h"
#include "../model/Storage.h"
#include "../model/OrderedProduct.h"
#include "../data/ProductTree.h"
#include "../data/QueueList.h"
#include "../view/KasirView.h"
#include<vector>
using namespace std;

class KasirController {
    private :
        Storage *ps;
        ProductTree *productStorage = new ProductTree();
        QueueList *queueList;
        KasirView kasirView;
        User* user;
    public : 
        KasirController( Storage *productTree, User* user, QueueList* queueList) {
            this->ps = productTree;
            this->user = user;
            this->queueList = queueList;
        }

        void run() {
            system("cls");
            bool status = true;
            while (status)
            {
                int menuSelection = kasirView.menu(user->name);
                switch (menuSelection)
                {
                case 1:
                    this->addTransaction();
                    break;
                case 2:
                    this->displayTransaction();
                    break;
                case 3:
                    this->displayProducts();
                    break;
                case 0:
                    cout << "Terimakasih, Sampai Jumpa Kembali!" << endl;
                    status = false;
                    user = nullptr;
                    break;
                default:
                    cout<< "Input tidak valid, coba lagi!" << endl;
                    break;
                }
            }
            
        }
        
        void displayProducts() {
            system("cls");
            productStorage->printTree(ps);
            cout << "Klik enter untuk lanjut";
            cin.ignore();
            cin.get();
        }

        void addTransaction() {
            string customerName;
            Product *tempProduct;
            int qty;
            vector<OrderedProduct> orderedProductList;
            vector<float> subtotalList;
            float total = 0;
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
                    cout << "Masukan jumlah pembelian dari " + tempProduct->productName << " : ";
                    cin >> qty;
                    orderedProductList.push_back(OrderedProduct(tempProduct, qty));

                    char addMoreProducts;
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

            for(OrderedProduct product : orderedProductList) {
                cout << sequenceNumber++ << ". " << product.product->productName << " : Rp." << product.product->price << " x " << product.qty << " : Rp. " << product.product->price *  product.qty << endl;
                subtotalList.push_back(product.product->price * qty);
            }

            for(int i = 0; i < subtotalList.size(); i++) {
                total += subtotalList[i];
            }

            cout << "===================================" << endl;
            cout << "Total : Rp." <<total<< endl;
        
            char continueTransaction;
            cout << "Lanjutkan untuk pembayaran (y/n)";
            cin >> continueTransaction;
            cin.ignore();

            if (tolower(continueTransaction) != 'y') {
                cout << "Pesanan dibatalkan" << endl;
                return;
            }

            for(OrderedProduct orderedProduct : orderedProductList) {
                orderedProduct.product->stock = orderedProduct.product->stock - orderedProduct.qty;
            }

            queueList->enqueue(customerName, orderedProductList, total);
        }

        void displayTransaction() {
            char actionChoose;
            bool actionStatus = true;
            while(actionStatus) {
            queueList->display();
                cout << "Pilihan : " << endl;
                cout << "[D] Tandai pesanan terdepan selesai (dequeu)\n[B] Kembali ke menu utama\n[V] Lihat detail transaksi" << endl;
                cout << "Masukan pilihan : ";
                cin >> actionChoose;
                cin.ignore();
                if (tolower(actionChoose) == 'd') {
                    queueList->dequeue();
                } else if(tolower(actionChoose) == 'b') {
                    actionStatus = false;
                } else if(tolower(actionChoose) == 'v') {
                    string queueId;
                    cout << "Masukan ID dari antrean : ";
                    getline(cin, queueId);
                    queueList->displayQueueById(queueId);
                } else {
                    cout << "Menu tidak valid" << endl;
                }
            }
        }



};
