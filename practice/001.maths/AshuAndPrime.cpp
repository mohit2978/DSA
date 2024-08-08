#include<bits/stdc++.h>
using namespace std;
//hackerearth
void fio()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
int sz=(int)1e6+1;
int spf[(int)1e6+1];
unordered_map<int,int>mp;
void calculateSPF(){
    for(int i=0;i<sz;i++) spf[i]=i;
    for(int i=2;i*i<sz;i++){
        if(spf[i]==i){
            mp[i]++;
            for(int j=i*i;j<=sz;j+=i){
                if(spf[j]==j){
                    spf[j]=i;
                    mp[i]++;
                }
            }
        }
    }
}
void solve(){
    int tc;
    cin>>tc;
    calculateSPF();
    for(int t=0;t<tc;t++){
        int x;
        cin>>x;
        int val=mp[x]==0?1:mp[x];
        cout<<val<<endl;
    }
}
int main(int argc, char const *argv[]) {
    fio();
    solve();
    return 0;
}
