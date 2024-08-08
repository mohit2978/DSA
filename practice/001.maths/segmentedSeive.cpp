
#include<bits/stdc++.h>
using namespace std;
int size=(int)1e5;
bool seive[(int)1e5];
void fio()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
vector<int>prime;
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

    for(int i=2;i<size;i++){
        if(seive[i]==true) {
           prime.push_back(i);
        }
    }
}
void segmentedSeive(int m,int n){
    bool dummy[n-m+1];
    memset(dummy,true,n-m+1);
    if(m==1) dummy[0]=false;
    for(auto pr:prime){
        int firstMultiple=(m/pr)*pr;
        if(firstMultiple<m) firstMultiple+=pr;
        firstMultiple=max(firstMultiple,pr*pr);
        if(firstMultiple>n) break;
        for(int i=firstMultiple;i<=n;i+=pr){
            if(dummy[i-m]==true) dummy[i-m]=false;
        }
    }
    for(int i=m;i<=n;i++){
        if(dummy[i-m]==true){
            cout<<i<<endl;
        }
    }
}
void solve(){
    int tc;
    cin>>tc;
    seiveSol();
    for(int t=0;t<tc;t++){
        int l,r;
        cin>>l>>r;
        segmentedSeive(l,r);
        cout<<endl;
    }
}

int main(int argc, char const *argv[]) {
    fio();
    solve();
    return 0;
}
