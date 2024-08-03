#include <bits/stdc++.h>
class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}
};

MyClass createObject() {
    MyClass obj(30);
    return obj;  // Returns a copy of obj
}

int main() {
    MyClass newObj = createObject();
    std::cout << "New object value: " << newObj.value << std::endl;  // Output: 30
    return 0;
}
