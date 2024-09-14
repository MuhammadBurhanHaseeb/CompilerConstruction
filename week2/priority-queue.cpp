#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Patient {
    string name;  
    int severity;  
};


struct CompareSeverity {
    bool operator()(const Patient& p1, const Patient& p2) {
        return p1.severity < p2.severity;  
    }
};

int main() {
    
    priority_queue<Patient, vector<Patient>, CompareSeverity> pq;

    // priority from higher no to lower no 
    pq.push({"John Doe", 5});   
    pq.push({"Jane Smith", 2}); 
    pq.push({"Alice Brown", 8}); 
    pq.push({"Bob Johnson", 3}); 

    // Treat the patients one by one
    while (!pq.empty()) {
        Patient p = pq.top();
        cout << "Attending to patient: " << p.name << " with severity: " << p.severity << endl;

        pq.pop();
    }

    return 0;
}
