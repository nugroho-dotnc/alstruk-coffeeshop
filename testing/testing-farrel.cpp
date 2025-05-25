#include<iostream>
#include<string>
#include "testing-farrel-linkedlist.h"
using namespace std;

struct QueueNode {
    string label;
    Order order;
    QueueNode *next;
};

class OrderQueue {
    private :
        QueueNode *front;
        QueueNode *back;
        int size;
    public :
        OrderQueue() {
            front = nullptr;
            back = nullptr;
            size = 0;
        }

        bool isEmpty() {
            return size == 0;
        }

        void enqueue() {
            QueueNode *q = new QueueNode();
            string qLabel;
            string orderMenu;
            int qty;
            float price;
            bool addMore = true;
            char addMoreChoice;
            cout << "Masukan nama pemesan : ";
            cin >> qLabel;

            while(addMore) {
                cout << "Masukan pesanan : ";
                cin >> orderMenu;
                cout << "Masukan jumlah : ";
                cin >> qty;
                cout << "Masukan harga : ";
                cin >> price;
                q->order.addOrder(orderMenu, qty, price);
                cout << "Apakah ada lagi? (Y/N) : ";
                cin >> addMoreChoice;
                (addMoreChoice == 'Y') ? addMore = true : addMore = false;
            }


            q->label = qLabel;
            if(isEmpty()) {
                front = back = q;
            } else {
                back->next = q;
                back = q;
            }

            size++;
        }

        void dequeue() {
            if(isEmpty()) {
                cout << "Antrian kosong" << endl;
                return;
            }

            QueueNode *temp = front;
            cout << "Antrian : " << front->label << " berhasil diselesaikan" << endl;
            front = front->next;
            delete temp;
            size--;

            if(front == nullptr) {
                back = nullptr;
            }

        } 

        void display() {
        if (isEmpty()) {
            cout << "Queue Kosong" << endl;
            return;
        }

        QueueNode* current = front;
        int index = 1;
        while (current != nullptr) {
            cout << "Antrian ke-" << index++ << " : " << current->label << endl;
            current->order.display();
            current = current->next;
        }
    }

        
};

int main() {
    OrderQueue q;

    q.enqueue();
    cout << endl;
    q.display();


}