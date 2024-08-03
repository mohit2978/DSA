//  Protected: The protected access modifier is similar to the private access modifier
//   in the sense that it can’t be accessed outside of its class unless with the help of a friend class. 
//   The difference is that the class members declared as Protected can be accessed by any 
//   subclass (derived class) of that class as well. 

// Note: This access through inheritance can alter the access modifier of the elements of base
//  class in derived class depending on the mode of Inheritance.


// C++ program to demonstrate 
// protected access modifier 
#include <bits/stdc++.h> 
using namespace std; 

// base class 
class Parent 
{ 
	// protected data members 
	protected: 
	int id_protected; 
	
}; 

// sub class or derived class from public base class 
class Child : public Parent 
{ 
	public: 
	void setId(int id) 
	{ 
		
		// Child class is able to access the inherited 
		// protected data members of base class 
		
		id_protected = id; 
		
	} 
	
	void displayId() 
	{ 
		cout << "id_protected is: " << id_protected << endl; 
	} 
}; 

// main function 
int main() { 
	
	Child obj1; 
	
	// member function of the derived class can 
	// access the protected data members of the base class 
	
	obj1.setId(81); 
	obj1.displayId(); 
	return 0; 
} 

// Output: 

// id_protected is: 81