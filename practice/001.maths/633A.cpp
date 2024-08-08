#include<bits/stdc++.h>
using namespace std;
//https://codeforces.com/problemset/problem/633/A
void fio()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}

int main(int argc, char const *argv[]) {
    fio();
    int a,b,c;
    cin>>a>>b>>c;
    bool ans=false;
    for(int x=0;x<=c/a;x++){
        int k=(c-a*x);
        if(k%b==0){
            ans=true;
            break;
        }
    }
    if(ans==true) cout<<"Yes";
    else cout<<"No";
    return 0;
}
