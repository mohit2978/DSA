

Given an array check if it represents a min-heap or not.
Print "Yes" if it represents a min-heap. Otherwise, print "No".

```cpp
#include <bits/stdc++.h>
using namespace std;
string solve(int* arr,int n,int i){
    int lidx=2*i+1;
    int ridx=2*i+2;
    string lres="Yes";
    string rres="Yes";
    if((lidx<n && arr[i]>arr[lidx]) || (ridx<n && arr[i]>arr[ridx])) return "No"; 
    
    if(lidx<n) lres=solve(arr,n,lidx);
    if(ridx<n) rres=solve(arr,n,ridx);
    
    if(lres=="No"|| rres=="No") return "No";
    return "Yes";
    
}
int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int arr[n];
        for(int i=0; i<n; i++)
        {
            cin>>arr[i];
        }
        cout<<solve(arr,n,0)<<"\n";
    }
}

```

Another way

```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Function to check if the given array is a min-heap
    bool isHeap(vector<int>& nums) {
        int n = nums.size(); // Size of the array
        
        // Iterate on the non-leaf nodes from the back
        for(int i = n/2 -1; i >= 0; i--) {
            int leftChildInd = 2*i + 1;
            int rightChildInd = 2*i + 2;
            
            // If left child has a smaller value than the parent
            if(leftChildInd < n && nums[leftChildInd] < nums[i])
                return false;
                
            // If right child has a smaller value than parent
            if(rightChildInd < n && nums[rightChildInd] < nums[i])
                return false;
        }
        
        return true;
    }
};

// Driver code
int main() {
    vector<int> nums = {10, 20, 30, 21, 23};
    
    cout << "Given Array: ";
    for(int x : nums) cout << x << " ";
    
    // Creating an object of the Solution class
    Solution sol;

    // Function call to check if the given array is a min-heap
    bool ans = sol.isHeap(nums); 
    
    if(ans) cout << "\nThe given array is a min-heap.";
    else cout << "\nThe given array is not a min-heap.";
    
    return 0;
}
```

Actually i have written recursive way and this is iterative way above.
