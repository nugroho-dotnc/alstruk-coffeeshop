#include<string>
#include "../model/Queue.h"
#include "../model/Product.h"
using namespace std;


class QueueList {
    private :
        Queue* front;
        Queue* back;
        const int max = 8;
        int size = 0;
    public : 
        QueueList() {
            this->front = nullptr;
            this->back = nullptr;
        };

        bool isFull() {
            if(size >= 5) {
                return true;
            }
            return false;
        }

        bool isEmpty() {
            if(size == 0) {
                return true;
            } 
            return false;
        }


        void enqueue(string label) {
            if(isFull()) {
                cout << "Antrian sedang penuh";
                return;
            }

            Queue* newQueue = new Queue(label);
            if(isEmpty()) {
                front = back = newQueue;
            } else {
                back->next = newQueue;
                back = newQueue;
            }

            size++;
        }

        void showQueue() {
            if(isEmpty()) {
                cout << "Antrian kosong!";
                return;
            }

            Queue *tmp = front;
            for(int i = 0; i < size; i++) {
                cout << "Antrian " << i+1 << " : " << tmp->queueLabel << endl;
                tmp = tmp->next;
            }

            cout << "Antrian habis";
        }

        void showFront() {
            Queue *tmp = front;
            cout << front->queueLabel;
        }

};

int main() {
    QueueList q;
    q.enqueue("Nugroho");
    q.enqueue("Farrel");
    q.enqueue("Sello");
    q.showFront();
}