class MyClass {
public:
    static int staticVar;
    int nonStaticVar;

    static void staticFunction() {
        // Can access static member directly
        staticVar = 10;

        // Cannot access non-static member directly
        // nonStaticVar = 20; // Error: non-static member 'nonStaticVar' cannot be accessed in a static member function

        // To access non-static members, need to pass an object
    }

    void nonStaticFunction() {
        // Can access both static and non-static members
        staticVar = 15;
        nonStaticVar = 25;
    }
};

// Definition of static member
int MyClass::staticVar = 0;

int main() {
    MyClass::staticFunction(); // Access static function without an object

    MyClass obj;
    obj.nonStaticVar = 5;
    obj.nonStaticFunction(); // Access non-static function with an object

    return 0;
}
