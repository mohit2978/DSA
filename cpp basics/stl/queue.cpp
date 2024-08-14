#include <iostream>
#include <queue>

using namespace std;

int main() {
    // 1. Creating a queue of integers
    queue<int> q;

    // 2. Adding elements to the queue
    q.push(10);
    q.push(20);
    q.push(30);

    // 3. Displaying the front element
    cout << "Front element: " << q.front() << endl;

    // 4. Displaying the back element
    cout << "Back element: " << q.back() << endl;

    // 5. Removing an element from the queue
    q.pop();
    cout << "Front element after pop: " << q.front() << endl;

    // 6. Checking the size of the queue
    cout << "Size of the queue: " << q.size() << endl;

    // 7. Checking if the queue is empty
    if (q.empty()) {
        cout << "Queue is empty" << endl;
    } else {
        cout << "Queue is not empty" << endl;
    }

    // 8. Removing all elements from the queue
    while (!q.empty()) {
        q.pop();
    }
    cout << "Queue size after clearing: " << q.size() << endl;

    return 0;
}
