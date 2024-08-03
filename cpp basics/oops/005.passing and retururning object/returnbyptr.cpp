#include <bits/stdc++.h>
class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}
};
MyClass* createDynamicObject() {
    MyClass* obj = new MyClass(50);
    return obj;
}

int main() {
    MyClass* dynObj = createDynamicObject();
    std::cout << "Dynamic object value: " << dynObj->value << std::endl;  // Output: 50
    delete dynObj;  // Don't forget to free the memory
    return 0;
}
