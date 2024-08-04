#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef vector<ll> vll;
const int MOD=1e9+7;
const int P=31;
const int N=1e5;
vll powerOfP(N+1,1);

ll polynomialHash(string &s){
    ll ans=0;
    for(int i=0;i<s.length();i++){
        ans=(ans+(s[i]-'a'+1)*powerOfP[i])%MOD;
    }
    return ans;
}
void solve(){
    string s;
    cin>>s;
    cout<<polynomialHash(s)<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for(int i=1;i<N+1;i++) powerOfP[i]=(powerOfP[i-1]*P)%MOD;
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}