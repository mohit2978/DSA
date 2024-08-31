#include <bits/stdc++.h>
using namespace std;


int solve(){
   int arr[]={0,3,2,1,3,3,0,2,2,1,1,2};
   int size=sizeof(arr)/sizeof(arr[0]);
   int pt0=-1;
   int pt1=0;
   int ptu=size-1;
   int pt2=size;
   while(pt1<=ptu){
   	if(arr[pt1]==0){
   		pt0++;
   		swap(arr[pt0],arr[pt1]);
   		pt1++;
   	}else if(arr[pt1]==1){
   		pt1++;
   	}else if(arr[pt1]==2){
   		swap(arr[ptu],arr[pt1]);
   		ptu--;
   	}else{
   		pt2--;
   		swap(arr[pt2],arr[pt1]);
   		if(pt2==ptu) ptu--;
   	}
   }

   for(int i=0;i<size;i++){
   	cout<<arr[i]<<" ";
   }
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif	
	solve();
	return 0;
}