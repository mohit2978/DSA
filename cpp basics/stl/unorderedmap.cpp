#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    // 1. Creating an unordered map
    unordered_map<int, string> unorderedMap;

    // 2. Inserting elements into the unordered map
    unorderedMap[3] = "Three";
    unorderedMap[1] = "One";
    unorderedMap[2] = "Two";

    // 3. Displaying elements using an iterator
    cout << "Unordered Map Elements:" << endl;
    for (unordered_map<int, string>::iterator it = unorderedMap.begin(); it != unorderedMap.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    // 4. Accessing elements
    cout << "Element with key 2: " << unorderedMap[2] << endl;

    // 5. Checking if a key exists
    if (unorderedMap.find(4) != unorderedMap.end()) {
        cout << "Key 4 found" << endl;
    } else {
        cout << "Key 4 not found" << endl;
    }

    // 6. Removing an element
    unorderedMap.erase(2);
    cout << "Unordered Map after removing key 2:" << endl;
    for (auto& pair : unorderedMap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 7. Checking the size of the unordered map
    cout << "Size of the unordered map: " << unorderedMap.size() << endl;

    return 0;
}
