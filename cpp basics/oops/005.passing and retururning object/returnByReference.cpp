#include <bits/stdc++.h>
class MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}
};
MyClass& modifyAndReturnObject(MyClass& obj) {
    obj.value = 40;
    return obj;
}

int main() {
    MyClass original(10);
    MyClass& refObj = modifyAndReturnObject(original);
    std::cout << "Reference object value: " << refObj.value << std::endl;  // Output: 40
    return 0;
}
