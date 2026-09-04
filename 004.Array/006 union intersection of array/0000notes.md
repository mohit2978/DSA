## Q1 Union of two sorted arrays

Given two sorted arrays **nums1** and **nums2**, return an array that contains the **union** of these two arrays. The elements in the union must be in ascending order.

The union of two arrays is an array where all values are distinct and are present in either the first array, the second array, or both.

**Examples:**

**Input:** `nums1 = [1, 2, 3, 4, 5], nums2 = [1, 2, 7]`  
**Output:** `[1, 2, 3, 4, 5, 7]`  
**Explanation:** The elements 1, 2 are common to both, 3, 4, 5 are from nums1 and 7 is from nums2

**Input:** `nums1 = [3, 4, 6, 7, 9, 9], nums2 = [1, 5, 7, 8, 8]`  
**Output:** `[1, 3, 4, 6, 7, 8, 9]`  
**Explanation:** The element 7 is common to both, 3, 4, 6, 9 are from nums1 and 1, 5, 8 is from nums2

**Input:** `nums1 = [3, 4, 4, 4], nums2 = [6, 7, 7]`  
**Output:** `[3, 4, 6, 7]`  

**Constraints:**
- `1 <= nums1.length, nums2.length <= 1000`
- `-10^4 <= nums1[i], nums2[i] <= 10^4`
- Both `nums1` and `nums2` are sorted in non-decreasing order



Merge procedure jaisa hai bilkul 
```cpp

class Solution {
public:
    vector<int> unionArray(vector<int>& nums1, vector<int>& nums2) {
        int i=0,j=0;
        vector<int> res;
        while(i<nums1.size() && j<nums2.size()){
            if(nums1[i]==nums2[j]){
                int val=nums1[i];
                res.push_back(val);
                while(nums1[i]==val) i++;
                while(nums2[j]==val) j++;
            }
            else if(nums1[i]<nums2[j]){
                int val=nums1[i];
                res.push_back(val);
                while(nums1[i]==val) i++;
            }else{
                 int val=nums2[j];
                res.push_back(val);
                while(nums2[j]==val) j++;
            }

        }

        while(i<nums1.size()){
           int val=nums1[i];
            res.push_back(val);
            while(nums1[i]==val) i++;
        }

        while(j<nums2.size()){
             int val=nums2[j];
            res.push_back(val);
            while(nums2[j]==val) j++;
        }

        return res;

    }
};
```
## Q2 Intersection of two sorted arrays

Given two sorted arrays, **nums1** and **nums2**, return an array containing the intersection of these two arrays. Each element in the result must appear as many times as it appears in both arrays.

The intersection of two arrays is an array where all values are present in both arrays.

**Examples:**

**Input:** `nums1 = [1, 2, 2, 3, 5], nums2 = [1, 2, 7]`  
**Output:** `[1, 2]`  
**Explanation:** The elements 1, 2 are the only elements present in both nums1 and nums2

**Input:** `nums1 = [1, 2, 2, 3, 3, 3], nums2 = [2, 3, 3, 4, 5, 7]`  
**Output:** `[2, 3, 3]`  
**Explanation:** The element 2 appears in both arrays only one time. The element 3 appears in both arrays two times so we add element 3 equal to its number of occurrences.

**Input:** `nums1 = [-45, -45, 0, 0, 2], nums2 = [-50, -45, 0, 0, 5, 7]`  
**Output:** `[-45, 0, 0]`  

**Constraints:**
- `1 <= nums1.length, nums2.length <= 1000`
- `-10^4 <= nums1[i], nums2[i] <= 10^4`
- Both `nums1` and `nums2` are sorted in non-decreasing order.


```cpp

class Solution {
public:
    vector<int> intersectionArray(vector<int>& nums1, vector<int>& nums2) {
        int i=0,j=0;
        vector<int> res;
        while(i<nums1.size() && j<nums2.size()){
            if(nums1[i]==nums2[j]){
                int val=nums1[i];
                res.push_back(val);
                i++;
                j++;
            }
            else if(nums1[i]<nums2[j]){
                int val=nums1[i];
                while(nums1[i]==val) i++;
            }else{
                 int val=nums2[j];
                while(nums2[j]==val) j++;
            }

        }
        return res;
    }
};

```





