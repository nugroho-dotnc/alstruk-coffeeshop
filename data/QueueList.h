#pragma once
#include "../model/Queue.h"
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


    void enqueue(string label, vector<Product> products) {
        if (isFull()) {
            cout << "Antrean penuh, tidak bisa menambahkan transaksi!\n";
            return;
        }
        string numToString = to_string(countQueue);
        string queueId = "TR0" + numToString;
        Queue* newNode = new Queue(queueId, label, products);
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

        cout << "Transaksi \"" << removed->label << "\" dikeluarkan dari antrean.\n";
        return removed;
    }

    void display() {
        if (isEmpty()) {
            cout << "Antrean kosong!\n";
            return;
        }

        Queue* current = head;
        cout << "Daftar Transaksi dalam Antrean:\n";
        while (current != nullptr) {
            cout << "- Kode Transaksi: " << current->queueId << ", Total: " << current->label << "\n";
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

