#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 1. Creating a vector of integers
    vector<int> vec;

    // 2. Adding elements to the vector
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // 3. Displaying elements using a range-based for loop
    cout << "Vector elements: ";
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;

    // 4. Accessing elements using index
    cout << "Element at index 1: " << vec[1] << endl;

    // 5. Modifying an element
    vec[1] = 25;
    cout << "Modified element at index 1: " << vec[1] << endl;

    // 6. Iterating using an iterator
    cout << "Vector elements using iterator: ";
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 7. Inserting an element at a specific position
    vec.insert(vec.begin() + 1, 15);
    cout << "After inserting 15 at index 1: ";
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;

    // 8. Removing an element
    vec.erase(vec.begin() + 2);
    cout << "After removing element at index 2: ";
    for (int i : vec) {
        cout << i << " ";
    }
    cout << endl;

    // 9. Getting the size of the vector
    cout << "The size of the vector is: " << vec.size() << endl;

    // 10. Clearing the vector
    vec.clear();
    cout << "Vector size after clearing: " << vec.size() << endl;

    // 11. Checking if the vector is empty
    if (vec.empty()) {
        cout << "Vector is empty" << endl;
    } else {
        cout << "Vector is not empty" << endl;
    }

    return 0;
}
