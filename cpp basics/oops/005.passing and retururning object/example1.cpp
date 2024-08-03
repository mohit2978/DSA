#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;

    // Constructor to initialize the object
    Person(std::string n, int a) : name(n), age(a) {}

    // Method to display the object's current state
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }

    // Method to update the current object's attributes using another Person object
    void updateDetails(const Person& other) {
        name = other.name;
        age = other.age;
    }
};

int main() {
    // Creating two Person objects
    Person john("John Doe", 25);
    Person jane("Jane Smith", 30);

    // Displaying the initial state of 'john'
    std::cout << "Before modification:" << std::endl;
    john.display();  // Output: Name: John Doe, Age: 25

    // Modifying 'john' using 'jane's' details
    john.updateDetails(jane);

    // Displaying the modified state of 'john'
    std::cout << "After modification:" << std::endl;
    john.display();  // Output: Name: Jane Smith, Age: 30

    return 0;
}

// Output:
// Before modification:
// Name: John Doe, Age: 25
// After modification:
// Name: Jane Smith, Age: 30



