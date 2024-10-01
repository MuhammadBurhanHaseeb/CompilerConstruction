// Section-C  2021-cs-129 Muhammad Burhan  

#include<iostream>
#include <map>
#include<string>
using namespace std ;
struct Employee
{
    int id ;
    string name;
    string department;
    double  salary;
};

map<int, Employee> employees;

void addEmployee( int id ,  string name , string department , double salary  )
{
    employees[id].name = name;
    employees[id].department = department;
    employees[id].salary = salary;
    cout<<"Added Employee  ";
     cout<<"Id :" << id << "  Name : " <<name << "  Department : " << department << "  Salary :" << salary << endl; 



}

void updateSalary(int id , double newSalary)
{
    if(employees.find(id) != employees.end())
    {
        employees[id].salary  = newSalary;
        cout<<"Updtaed employee  : Id" << id << "  New Salary : Saary " << newSalary << endl;
    }
    else
    {
        cout<<"Employee With Id : " << id << "Not Found ";
    }
}

void removeEmployee(int id )
{
    if(employees.erase(id))
    {
        cout << "Employe Removed " << id <<endl; 
    }
    else
    {
        cout <<"Employe not removed "<<endl;
    }
}


void displayEmployee()
{
    if(employees.empty())
    {
        cout<<"No Employeee To map "<<endl;
    }
    else{
        cout<<"Current  Employeee  "<<endl;
        for (const auto& emp : employees)
        {
            cout<<"Id :" << emp.first << "  Name : " << emp.second.name << " Department : " << emp.second.department << "  Salary :" << emp.second.salary << endl; 

        }

    }

}

int main()
{

    addEmployee(101 , "Alice" , "HR" , 50000);
    addEmployee(102 , "Bob" , "Eng" , 60000);


    updateSalary(101 , 55000);

    removeEmployee(102);

    displayEmployee();


    return 0 ;
}

