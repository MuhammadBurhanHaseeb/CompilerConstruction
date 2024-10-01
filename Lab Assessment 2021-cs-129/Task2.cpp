// Section-C  2021-cs-129 Muhammad Burhan 

#include<iostream>
#include <deque>
#include<string>
using namespace std ;

deque<string> taskQueue;

void addTask(string task , bool isHighPriority )
{
    if(isHighPriority)
    {
        taskQueue.push_front(task);
        cout <<"Added Task" << task << " to the front of the queue "<<endl; 
    }
    else
    {
        taskQueue.push_back(task);
        cout <<"Added Task" << task << "  to the back of the queue "<<endl;
    }

}

void processTask()
{
    if (!taskQueue.empty())
    {
        cout << "Processing Task ::  " << taskQueue.front() << endl;
        taskQueue.pop_front();
    }
    else
    {
        cout<<"Queue is Empty "<< endl ;
    }
}

void Display()
{
    if (taskQueue.empty())
    {
        cout<<"No Tasks " <<endl;
    }
    else
    {
        cout<<"Current Taks  " <<endl;
        for (size_t i = 0 ; i<taskQueue.size() ; i++ )
        {
            cout<< i + 1 << ". " << taskQueue[i] << endl;

        }
    }
}

int main()
{

    addTask ("Task 1" , false);
    addTask ("Urgent Task" , true);
    addTask("Task 2" , false);


    processTask();

    Display();

    return 0 ; 


}
