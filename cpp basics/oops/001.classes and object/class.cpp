#include <bits/stdc++.h>
using namespace std;
  
class Employee {  //Class Declaration
    public:
        string id, name;
        int years;  //experience (in years)
         
         //use this-> as this is a pointer
        Employee(string id, string name, int years) {
            this->id = id;
            this->name = name;
            this->years = years;
        }
        
        void work() {
            cout << "Employee: " << this->id << " is working\n";
        }
        //can do define a method here and declare later we have declared on line 23 need to use scope resolution (::) to define method
        void print();
};

void Employee::print(){
    cout<<"Id is"<<id<<" Name is"<<name;
}
  
int main()
{
    //Class Instantiation (Direct)
    Employee emp("GFG123", "John", 3);
    
    //Class Instantiation (Indirect)
    Employee *emp_ptr = new Employee("GFG456", "James", 4);
     
    cout << "Employee ID: " << emp.id << endl;
    cout << "Name: " << emp.name << endl;
    cout << "Experience (in years): " << emp.years << endl;
    
    emp.work();
    cout << endl;
    
    cout << "Employee ID: " << emp_ptr->id << endl;
    cout << "Name: " << emp_ptr->name << endl;
    cout << "Experience (in years): " << emp_ptr->years << endl;
    
    emp_ptr->work();
    emp_ptr->print();
    return 0;
}


// Output:
// Employee ID: GFG123
// Name: John
// Experience (in years): 3
// Employee: GFG123 is working

// Employee ID: GFG456
// Name: James
// Experience (in years): 4
// Employee: GFG456 is working
//Id isGFG456 Name isJames