#include <iostream>
#include <map>

using namespace std;

int main() {
    // 1. Creating an ordered map
    map<int, string> orderedMap;

    // 2. Inserting elements into the map
    orderedMap[1] = "One";
    orderedMap[2] = "Two";
    orderedMap[3] = "Three";

    // 3. Displaying elements using an iterator
    cout << "Ordered Map Elements:" << endl;
    for (map<int, string>::iterator it = orderedMap.begin(); it != orderedMap.end(); ++it) {
        cout << it->first << ": " << it->second << endl;
    }

    // 4. Accessing elements
    cout << "Element with key 2: " << orderedMap[2] << endl;

    // 5. Checking if a key exists
    if (orderedMap.find(4) != orderedMap.end()) {
        cout << "Key 4 found" << endl;
    } else {
        cout << "Key 4 not found" << endl;
    }

    // 6. Removing an element
    orderedMap.erase(2);
    cout << "Ordered Map after removing key 2:" << endl;
    for (auto& pair : orderedMap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // 7. Checking the size of the map
    cout << "Size of the ordered map: " << orderedMap.size() << endl;

    return 0;
}
