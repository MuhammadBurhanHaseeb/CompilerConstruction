#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    set<string> emailSet;

    emailSet.insert("john.doe@example.com");
    emailSet.insert("alice.smith@example.com");
    emailSet.insert("john.doe@example.com"); // Duplicate, will not be added
    emailSet.insert("bob.jones@example.com");

    // Display
    cout << "Unique email addresses: " << endl;
    for (const string& email : emailSet) {
        cout << email << endl;
    }

    string searchEmail = "alice.smith@example.com";
    if (emailSet.find(searchEmail) != emailSet.end()) {
        cout << searchEmail << " found in the set." << endl;
    } else {
        cout << searchEmail << " not found in the set." << endl;
    }

    // Delete 
    emailSet.erase("bob.jones@example.com");

    // Display again
    cout << "\nEmail addresses after deletion: " << endl;
    for (const string& email : emailSet) {
        cout << email << endl;
    }

    return 0;
}
