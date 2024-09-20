#include<iostream>
using namespace std;
/*Example 1:
Input : x = 2.0000 , n = 10

Output : 1024.0000

Explanation : Answer = 2^10 => 1024.

Example 2
Input : x = 2.0000 , n = -2

Output : 0.2500

Explanation : Answer = 2^(-2) = 1/4 => 0.25.

Constraints:
-100.0 <= x <= 100.0
-231 <= n <= 231 - 1
-104 <= xn <= 104
Either x is not zero or n>0.
n is an integer.
Note:
In output print 6 digits places after decimal point.
*/
int power(int a,int b){
     if(b==0) return 1;
        if(b<0){
            b=-b;
            a=1/a;
        }
    int res=1;
    while(b){
        if((b&1)==1){
            res*=a;
        }
        a=a*a;
        b=b>>1;
    }
    return res;
}
int main(){
    int a,b;
    a=5;
    b=5;
    cout<<power(a,b);
    return 0;
}