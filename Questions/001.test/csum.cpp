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
void compute(vector<int>&nums,vector<int>&presum,int n){
    presum[0]=nums[0];
    for(int i=1;i<n;i++){
        presum[i]=presum[i-1]+nums[i];
    }
}
int csum(vector<int>&presum,int l,int r,int n){
    if(l!=0) return presum[r]-presum[l-1];
    else return presum[r];
}
//Ctrl+B to run
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    vi nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    vi presum(n);
    compute(nums,presum,n);
    int q;
    cin>>q;
    while(q-->0){
        int l,r;
        cin>>l>>r;
        cout<<csum(presum,l,r,n)<<"\n";
    }
    
	return 0;
}