#include<iostream>
using namespace std;
int power(int a,int b){
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