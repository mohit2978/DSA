#include <bits/stdc++.h>
using namespace std;

class Test {
    private:
        static int x;
        
    public:
        //set private static integer x
        static void setX(int x) { Test::x = x; }
        
        //get private static integer x
        static int getX() { return x; }
};

//Initializer statement is valid
//even though variable is declared
//private
int Test::x = 1;

int main()
{
    Test::setX(5);
    cout << Test::getX();
    
    return 0;
}
