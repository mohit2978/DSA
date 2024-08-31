#include <bits/stdc++.h>
using namespace std;

int solve1(){
	int n;
	cin>>n;
	int max=-1;
	if(n==1||n==2||n==3) return 1;
	for(int i=2;i<=n;i++){
		for(int j=2;j*j<=i;j++){
			if(i%j==0){
				if(j>max) max=j;
				if(i/j!=j){
					if(i/j>max) max=i/j;
				}
			}
		}
	}
	return max;
}

int solve(){
	int n;
	cin>>n;
	if(n==1||n==2||n==3) return 1;
	if(n%2==0) return n/2;
	else return (n-1)/2;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif	
	int tc;
	cin>>tc;
	for(int t=0;t<tc;t++){
		cout<<solve()<<endl;
	}
	return 0;
}