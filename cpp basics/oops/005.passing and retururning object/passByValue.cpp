#include <bits/stdc++.h>
class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}
};

void modifyObject(MyClass obj) {
    obj.value = 20;  // Changes only the copy
}

int main() {
    MyClass original(10);
    modifyObject(original);
    std::cout << "Original value: " << original.value << std::endl;  // Output: 10
    return 0;
}
