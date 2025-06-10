#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Product {
    string productName;
    // string idProduct;
    float harga;
    int qty;
    Product(string name, float price, int quantity) : productName(name), harga(price), qty(quantity) {}

};

struct QueueNode {
    string label;
    QueueNode *next;
    vector<Product> transactions;
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
                cout << "Apakah ada lagi? (Y/N) : ";
                cin >> addMoreChoice;
                q->transactions.push_back(Product(orderMenu, price, qty));
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
                for(Product item : current->transactions) {
                    cout << "Item : " << item.productName << " | Rp." << item.harga << " | " << item.qty << " | " << item.harga * item.qty << endl;
                }
                current = current->next;
        }
    }

        
};

int main() {
    OrderQueue q;

    q.enqueue();
    q.enqueue();
    cout << endl;
    q.display();


}