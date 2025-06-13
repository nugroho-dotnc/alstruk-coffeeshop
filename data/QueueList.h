#pragma once
#include "../model/Queue.h"
#include <iostream>

class QueueList {
private:
    QueueNode* head;
    QueueNode* tail;
    int maxSize;

public:
    QueueList(int maxSize = 100) {
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
        QueueNode* current = head;
        while (current != nullptr) {
            total++;
            current = current->next;
        }
        return total;
    }

    void enqueue(Transaction trx) {
        if (isFull()) {
            std::cout << "Antrean penuh, tidak bisa menambahkan transaksi!\n";
            return;
        }

        QueueNode* newNode = new QueueNode{trx, nullptr};

        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        std::cout << "Transaksi " << trx.transactionId << " berhasil ditambahkan ke antrean.\n";
    }

    Transaction dequeue() {
        if (isEmpty()) {
            std::cout << "Antrean kosong!\n";
            return Transaction(); // Kembalikan objek kosong
        }

        QueueNode* temp = head;
        Transaction data = temp->data;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;

        std::cout << "Transaksi " << data.transactionId << " dikeluarkan dari antrean.\n";
        return data;
    }

    void display() {
        if (isEmpty()) {
            std::cout << "Antrean kosong!\n";
            return;
        }

        QueueNode* current = head;
        std::cout << "Daftar Transaksi dalam Antrean:\n";
        while (current != nullptr) {
            std::cout << "- Kode Transaksi: " << current->data.transactionId
                      << ", Total: " << current->data.totalAmount << "\n";
            current = current->next;
        }
    }

    void destroy() {
        while (!isEmpty()) {
            dequeue();
        }
        std::cout << "Semua transaksi dalam antrean telah dihapus.\n";
    }

    Transaction peek() {
    if (isEmpty()) {
        std::cout << "Antrean kosong!\n";
        return Transaction(); // atau throw exception
    }
    return head->data;
  }
};
