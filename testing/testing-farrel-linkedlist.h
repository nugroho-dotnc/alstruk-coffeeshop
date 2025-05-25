#include<iostream>
using namespace std;

struct OrderList {
    int idList;
    string label;
    float subTotal;
    int qty;
    OrderList *next;
};

class Order {
    private : 
        OrderList *head;
    public :
        Order() {
            head = nullptr;
        }

        void addOrder(string label, int quantity, float subTotal) {

            OrderList *order = new OrderList;
            OrderList *last = new OrderList;
            int tempId = 1;
            order->label = label;
            order->qty = quantity;
            order->subTotal = subTotal;

            if (head == nullptr) {
                order->idList = 1;
                order->next = nullptr;
                head = order;
                return;
            } 

            last->next = head;
            while(last->next != nullptr) {
                tempId +=  1;
                last = last->next;
            }   
            order->idList = tempId;
            last->next = order;

        }

        void display() {
            OrderList *temp;
            temp = head;
            while(temp != nullptr) {
                cout << "Item " << temp->idList << " : " << temp->label << " | " << temp->qty << " | " << "Rp." << temp->subTotal << " | " << "Rp." << temp->qty * temp->subTotal << endl;
                temp = temp->next;
            }
        }

        
};


