#include <iostream>
#include<vector>
using namespace std;
//https://codeforces.com/problemset/problem/1400/D
int solve(int arr[],int n) {
	int cnt=0;
	vector<pair<int,int>>left;
	for(int i=0;i<n;i++){
		for(int k=i+2;k<n;k++){
			if(arr[i]==arr[k]){
				left.push_back({i,k});
			}
		}
	}
	vector<pair<int,int>>right;
	for(int j=0;j<n;j++){
		for(int l=j+2;l<n;l++){
			if(arr[j]==arr[l]){
				right.push_back({j,l});
			}
		}
	}

	for(auto p1:left){
		for (auto p2:right){
			if(p1.first<p2.first && p2.first<p1.second && p1.second<p2.second)
				cnt++;
		}
	}
	return cnt;
}
int main(){
	freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int tc;
    cin>>tc;
    for(int t=0;t<tc;t++){
        int n;
        cin>>n;
        int arr[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        cout<<solve(arr,n)<<"\n";
    }
    return 0;
}