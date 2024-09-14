#include<iostream>
#include<deque>
using namespace std;
#include <vector>
#include <stack>

class studentData {
    public :
        string name ;
        float cgpa;
        char grade;
   
};
class Tasks {

    public :
    int priority ;
    string tasks ; 

};

void addTaskAtStart(deque<Tasks> deqq)
{
    
}
void addTaskAtEnd()
{

}
void deleteTaskAtStart()
{

}
void deleteTaskAtEnd()
{
    
}

struct node 
{
    int data;
    node *prev;
    node *next;

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

node* delHead(node *head) {

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

void printDeque(deque<Tasks>& deqq  )
{
     for (int i = 0 ; i < deqq.size() ; i++ )
    {
        cout <<"Priority : " << deqq[i].priority << " tasks :" << deqq[i].tasks << endl;     
    }

}

bool checkStringExpression(const string& s)
{

    stack<char> stk;

    for (char ch : s) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stk.push(ch);
        }
        else {
            if (!stk.empty()) {
                char top = stk.top();
                stk.pop();  

                if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[')) {
                    return false;  
                }
            } else {
                return false; 
            }
        }

}
return stk.empty();
};




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

    

// task 3 

    Tasks t1;
    deque<Tasks> deqq ;

    t1.tasks = "hello ";
    t1.priority = 1;

    Tasks t2;
    t2.tasks = "hello ";
    t2.priority = 2;

    Tasks t3;
    t3.tasks = "hello ";
    t3.priority = 3;

    Tasks t4;
    t4.tasks = "hello ";
    t4.priority = 4;


    deqq.push_front(t1);
    deqq.push_front(t4);
    deqq.push_back(t3);
    deqq.push_back(t2);



    printDeque(deqq);

    // for (int i = 0 ; i < deqq.size() ; i++ )
    // {
    //     cout <<"StudentName : " << deqq[i].priority << " CGPA :" << deqq[i].tasks << endl;     
    // }


    cout<<"the expression balancing "<<endl;
    string exp = "{({})}";
    bool res = checkStringExpression(exp);
    cout<<" The expression is valid : " << res <<endl;

}
