#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Student {
    string name;
    float grade;
};


void displayRecords(const map<int, Student>& students) {
    cout << "\nStudent Records:\n";
    for (const auto& pair : students) {
        cout << "ID: " << pair.first << ", Name: " << pair.second.name << ", Grade: " << pair.second.grade << endl;
    }
}

int main() {
    map<int, Student> studentRecords;

    
    studentRecords[101] = {"Alice Smith", 89.5};
    studentRecords[102] = {"Bob Johnson", 75.2};
    studentRecords[103] = {"Charlie Brown", 92.3};

    
    displayRecords(studentRecords);

    
    int searchID = 102;
    if (studentRecords.find(searchID) != studentRecords.end()) {
        cout << "\nStudent found: " << studentRecords[searchID].name << ", Grade: " << studentRecords[searchID].grade << endl;
    } else {
        cout << "\nStudent with ID " << searchID << " not found.\n";
    }

    
    int deleteID = 103;
    studentRecords.erase(deleteID);

    
    cout << "\nAfter deletion of student with ID " << deleteID << ":\n";
    displayRecords(studentRecords);

    return 0;
}
