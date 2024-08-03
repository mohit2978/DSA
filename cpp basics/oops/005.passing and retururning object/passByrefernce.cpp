#include <bits/stdc++.h>
class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}
};

void modifyObject(MyClass& obj) {
    obj.value = 20;  // Modifies the original object
}

int main() {
    MyClass original(10);
    modifyObject(original);
    std::cout << "Original value: " << original.value << std::endl;  // Output: 20
    return 0;
}

// Output:
// Original value: 20