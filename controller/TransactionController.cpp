#include<iostream>
#include "../model/Queue.h"
using namespace std;

class TransactionController {
    private :
        QueueNode *q; 
        
    public : 
        TransactionController(QueueNode *queue) {
            this->q = queue;
            cout << "This is transaction controller";
        }

        void addTransaction() {
            
        }
};

int main() {
    cout << "hello world";
}