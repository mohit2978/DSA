#include<bits/stdc++.h>
using namespace std;
//scanline algorithm
#define ff              first
#define ss              second
#define lo             long long
#define ll 				long long int
#define pb              push_back
#define mp              make_pair
#define pii             pair<int,int>
#define vi              vector<int>
#define mii             map<int,int>
#define umii			unordered_map<int, int>
#define pq_max          priority_queue<int>
#define pq_min          priority_queue<int,vi,greater<int> >
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define mod             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define mid(s,e)         (s+(e-s)/2)
#define mk(arr,n,type)  type *arr=new type[n];
#define w(t)            int t; cin>>t; while(t--)
#define DEBUG(x) 		cout << '>' << #x << ':' << x << endl;
#define REP(i,n) 		for(int i=0;i<(n);i++)
#define FOR(i,a,b) 		for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) 	for(int i=(a);i>=(b);i--)

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
    int n,k;
    cin>>n>>k;
    int arr[k+1]={0};
    for(int i=0;i<n;i++){
        int illumination,pos;
        cin>>pos>>illumination;
        int l=pos-illumination<0?0:pos-illumination;
        int r=pos+illumination>k?k:pos+illumination;
        arr[l]++;
        arr[r+1]--;
    }
    int res=0,len=0;
    int scan=0;
    for(int i=0;i<k+1;i++){
        scan+=arr[i];
        if(scan!=1) len++;
        else len=0;
        if(len>res) res=len;
    }
    cout<<res;
    return 0;
}
