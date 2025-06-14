#pragma once
#include "../model/Queue.h"
#include "../model/OrderedProduct.h"
#include <iostream>
using namespace std; 

class QueueList {
private:
    Queue* head;
    Queue* tail;
    int maxSize;
    int countQueue = 1;

public:
    QueueList(int maxSize = 8) {
        this->head = nullptr;
        this->tail = nullptr;
        this->maxSize = maxSize;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    bool isFull() {
        return count() >= maxSize;
    }

    int count() {
        int total = 0;
        Queue* current = head;
        while (current != nullptr) {
            total++;
            current = current->next;
        }
        return total;
    }


    void enqueue(string label, vector<OrderedProduct> products, float total) {
        if (isFull()) {
            cout << "Antrean penuh, tidak bisa menambahkan transaksi!\n";
            return;
        }
        string numToString = to_string(countQueue);
        string queueId = "TR0" + numToString;
        Queue* newNode = new Queue(queueId, label, products, total);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        cout << "Transaksi \"" << label << "\" berhasil ditambahkan ke antrean.\n";
        countQueue++;
    }

    Queue* dequeue() {
        if (isEmpty()) {
            cout << "Antrean kosong!\n";
            return nullptr;
        }

        Queue* removed = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }

        cout << "Transaksi \"" << removed->queueId << "\" telah selesai.\n";
        return removed;
    }

    void displayQueueById(string queueId) {
        Queue *current = head;
        float total;
        while(current != nullptr) {
            if(current->queueId == queueId) {
                system("cls");
                cout << "Pesanan atas nama " << current->label << endl;
                cout << "List order : " << endl;
                int countItem = 1;
                for(OrderedProduct orderList : current->products) {
                    cout << countItem << ". " << orderList.productName << " - Rp." << orderList.price << " x " << orderList.qty << " : " << orderList.price * orderList.qty << endl;
                    total = orderList.price * orderList.qty;
                    countItem++;
                }
                cout<< "===================================" << endl;
                cout << "Total : Rp." << total << endl;
                cout<< "===================================" << endl;
                cout << "Klik enter untuk lanjut";
                cin.ignore();
                cin.get();
                return;
            } else {
                current = current->next;
            }
        }
        system("cls");
        cout << "Antrean tidak ditemukan" << endl;
        cout << "Klik enter untuk lanjut";
        cin.ignore();
        cin.get();
    }

    void display() {
        system("cls");
        int counter = 1;
        if (isEmpty()) {
            cout << "Antrean kosong!\n";
            return;
        }

        Queue* current = head;
        cout<< "===================================" << endl;
        cout<< "ANTREAN PESANAN" << endl;
        cout<< "===================================" << endl;
        while (current != nullptr) {
            cout << counter << ". " << "Pesanan " << current->queueId << " - Total Rp." << current->total <<endl;
            counter++;
            current = current->next;
        }
    }

    void destroy() {
        while (!isEmpty()) {
            Queue* temp = dequeue();
            delete temp;
        }
        cout << "Semua transaksi dalam antrean telah dihapus.\n";
    }

    Queue* peek() {
        if (isEmpty()) {
            cout << "Antrean kosong!\n";
            return nullptr;
        }
        return head;
    }
};

