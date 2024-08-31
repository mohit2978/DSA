#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define f first
#define s second
#define vi vector<int>
#define vvi vector<vector<int>>
int mod=1e9+7;
ll lmod=1e18;
//Ctrl+B to run
//https://www.codechef.com/problems/BROKPHON?tab=statement
int solve(){
	int n;
	cin>>n;
	int arr[n];
	int count=0;
	cin>>arr[0];
	int prevVal=arr[0];
	int lidx=-1;
	for(int i=1;i<n;i++){
		cin>>arr[i];
		if(prevVal!=arr[i] ){
			count+=2;
			if(lidx==i-1) count--;
			lidx=i;
		}
		prevVal=arr[i];

	}
	return count;;
}
int main(){
	#ifndef ONLINE_JUDGE
    	freopen("input.txt","r",stdin);
    	freopen("output.txt","w",stdout);
    #endif	
    int testCases;
    cin>>testCases;
    for(int t=0;t<testCases;t++){
    	cout<<solve()<<"\n";
    }
    
	return 0;
}