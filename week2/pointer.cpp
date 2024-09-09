#include<iostream>
using namespace std;
#include <vector>

class studentData {
    public :
        string name ;
        float cgpa;
        char grade;

    // void deleteStudent(string name )
    // {
    //     for(int i = 0 ; i < )
    //     {

    //     }

    // }    
};

struct node 
{
    int data;
    struct node *prev;
    struct node *next;

};

void forwardTraversal(node* head) {
  
    node* curr = head;

    while (curr != nullptr) {
      
        cout << curr->data << " ";

        curr = curr->next;
    }

    cout << endl;
};

void backwardTraversal(node* tail) {
  
    node* curr = tail;

    while (curr != nullptr) {
      
        cout << curr->data << " ";
        curr = curr->prev;
    }
    cout << endl;
};

node* insertBegin(node* head, int data) {
    
    node* new_node = new node();
    new_node->data = data;
    
    new_node->next = head;
    
    if (head->prev == NULL) {
        head->prev = new_node;
    }
    
    return new_node;
}

node *delHead(node *head) {

    if (head == nullptr)
        return nullptr;

    node *temp = head;

    head = head->next;

    if (head != nullptr)
        head->prev = nullptr;

    delete temp;
    return head;
}

void printLinkedList(node* head) {
    node* curr = head;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
      cout << "\n";
}






 void deleteStudent(  vector<studentData>& myVector , const string& name )
    {
        for (auto it = myVector.begin(); it != myVector.end(); ++it) {
        if (it->name == name) {
            myVector.erase(it);
            cout << "Deleted student: " << name << endl;
            return;  // Exit after deleting the student
        }
    }
    cout << "Student not found: " <<  name <<  endl;

    };


int main()
{
    studentData s1;
    s1.name = "Burhan";
    s1.cgpa = 3.12;
    s1.grade = 'B';

    studentData s2;
    s2.name = "Naseeb";
    s2.cgpa = 4.12;
    s2.grade = 'A';
    vector<studentData> myVector;

    myVector.push_back(s1); // push 
    myVector.push_back(s2);


 /// retrieve 
    for (int i = 0 ; i < myVector.size() ; i++ )
    {
        cout <<"StudentName : " << myVector[i].name << " CGPA :" << myVector[i].cgpa << " Grades :" << myVector[i].grade << endl;     
    }

 // delete 
    deleteStudent(myVector ,"Burhan");


    // to check student del or not 

// check 
      for (int i = 0 ; i < myVector.size() ; i++ )
    {
        cout <<"StudentName : " << myVector[i].name << " CGPA :" << myVector[i].cgpa << " Grades :" << myVector[i].grade << endl;     
    }

    // double linked list

 
    node* head_node = new node();
    node* firstNode = new node();
    node* secondNode = new node();
    node* thirdNode = new node();


    head_node->data = 1 ; 
    head_node->prev = NULL;
    head_node->next = firstNode;

    firstNode->data = 2;
    firstNode->prev = head_node;
    firstNode->next = secondNode;


    secondNode->data = 3;
    secondNode->prev = firstNode;
    secondNode->next = thirdNode;

    thirdNode->data = 4;
    thirdNode->prev = secondNode;


    cout << "Forward Traversal:" << endl;
    forwardTraversal(head_node);

    cout << "Backward Traversal:" << endl;
    backwardTraversal(thirdNode);

   
    cout << "Add  a node at the start  " << endl;
    node* head = new node();
    head = insertBegin(head_node , 7 );
    printLinkedList(head);


    cout << "Delete a node at the start " << endl;
    node* headNew = new node();
    headNew = delHead(head);
    printLinkedList(headNew);

    




}
