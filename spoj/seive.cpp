//https://www.spoj.com/problems/TDPRIMES/
#include<bits/stdc++.h>
using namespace std;
int size=(int)1e8;
bool seive[(int)1e8];
void fio()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
void seiveSol(){
   memset(seive,true,size);
    seive[0]=seive[1]=false;
    for(int i=2;i*i<=size;i++){
        if(seive[i]==true){
            for(int j=i*i;j<size;j+=i){
                seive[j]=false;
            }
        }
    }
    vector<int>prime;
    int cnt=1;
    for(int i=2;i<size;i++){
        if(seive[i]==true) {
            if(cnt%100==1){
                cout<<i<<endl;
            }
            cnt++;
        }
    }
}

int main(int argc, char const *argv[]) {
    fio();
    seiveSol();
    return 0;
}
