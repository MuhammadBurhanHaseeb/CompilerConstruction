#include <iostream>
#include <queue>
#include <string>
using namespace std;

class CinemaTicketingSystem {
private:
    queue<string> regularQueue;  
    queue<string> vipQueue;      

public:
    void joinQueue(const string& customerName) {
        regularQueue.push(customerName);
        cout << customerName << " has joined the regular queue." << endl;
    }

    void joinVipQueue(const string& vipName) {
        vipQueue.push(vipName);
        cout << vipName << " has joined the VIP queue." << endl;
    }

    void serveCustomer() {
        if (!vipQueue.empty()) {
            string served = vipQueue.front();  
            vipQueue.pop();                                                                                                     
            cout << "VIP customer " << served << " is being served." << endl;
        } else if (!regularQueue.empty()) {
            string served = regularQueue.front(); 
            regularQueue.pop();
            cout << "Regular customer " << served << " is being served." << endl;
        } else {
            cout << "No customers in queue to be served." << endl;
        }
    }

    void displayQueues() {
        cout << "\nCurrent Queue Status:" << endl;
        cout << "VIP Queue: ";
        displayQueue(vipQueue);

        cout << "Regular Queue: ";
        displayQueue(regularQueue);
        cout << endl;
    }

private:
    void displayQueue(queue<string> q) {
        if (q.empty()) {
            cout << "Empty" << endl;
            return;
        }

        while (!q.empty()) {
            cout << q.front() << " ";
            q.pop();
        }
        cout << endl;
    }
};

int main() {
    CinemaTicketingSystem cinema;

    cinema.joinQueue("Alice");
    cinema.joinQueue("Bob");

    cinema.joinVipQueue("Charlie");

    cinema.displayQueues();

    cinema.serveCustomer();  
    cinema.serveCustomer();  

    cinema.joinQueue("David");
    cinema.joinVipQueue("Eva");

    cinema.displayQueues();

    cinema.serveCustomer(); 
    cinema.serveCustomer();  
    cinema.serveCustomer();  

    cinema.serveCustomer();

    return 0;
}
