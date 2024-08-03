// Private: The class members declared as private can be accessed only by the member functions inside the class. 
// They are not allowed to be accessed directly by any object or function outside the class. 
// Only the member functions or the friend functions are allowed to access the private data members of the class. 
// C++ program to demonstrate private 
// access modifier 

#include<iostream> 
using namespace std; 

class Circle 
{ 
	// private data member 
	private: 
		double radius; 
	
	// public member function	 
	public:	 
		double compute_area() 
		{ // member function can access private 
			// data member radius 
			return 3.14*radius*radius; 
		} 
	
}; 

// main function 
int main() 
{ 
	// creating object of the class 
	Circle obj; 
	
	// trying to access private data member 
	// directly outside the class 
	obj.radius = 1.5; 
	
	cout << "Area is:" << obj.compute_area(); 
	return 0; 
} 


// Output: 

//  In function 'int main()':
// 11:16: error: 'double Circle::radius' is private
//          double radius;
//                 ^
// 31:9: error: within this context
//      obj.radius = 1.5;

// The output of the above program is a compile time error because we are not allowed to access the private data
//  members of a class directly from outside the class. Yet an access to obj.radius is attempted, but radius being a private data member, we obtained the above compilation error. 

// However, we can access the private data members of a class indirectly using the public member functions of the class. 