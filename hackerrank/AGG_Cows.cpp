#include<bits/stdc++.h>
using namespace std;

#define ff              first
#define ss              second
#define ll             long long
#define lli 				long long int
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
int agressiveCows(){
    int n,c;
    cin>>n>>c;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    int lo=0,hi=arr[n-1]-arr[0];
    while(lo<=hi){
        int mid=(lo+hi)/2;
        int lastCowPlacedPos=arr[0];
        int cowPlaced=1;
        for(int i=1;i<n;i++){
            if(arr[i]-lastCowPlacedPos>=mid){
                cowPlaced++;
                lastCowPlacedPos=arr[i];
            }
            if(cowPlaced==c) break;
        }
        if(c==cowPlaced) lo=mid+1;
        else hi=mid-1;
    }
    return hi;
}
void solve(){
    int tc;
    cin>>tc;
    for(int i=0;i<tc;i++){
        cout<<agressiveCows()<<endl;
    }
}
int main(int argc, char const *argv[]) {
    fio();
    solve();
    return 0;
}
