 ## Q Search in Rotated Sorted Array I

Given an integer array `nums`, sorted in ascending order (with distinct values) and a target value `k`. The array is rotated at some pivot point that is unknown.

Find the index at which `k` is present, and if `k` is not present, return `-1`.

## Examples

**Example 1:**
- **Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 0`
- **Output:** `4`
- **Explanation:** The target `0` is present at index 4 in the array.

**Example 2:**
- **Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 3`
- **Output:** `-1`
- **Explanation:** The target `3` is not present in the given array.

## Constraints

* `1 <= nums.length <= 10^4`
* `-10^4 <= nums[i] <= 10^4`
* All values of `nums` are unique.
* `nums` is an ascending array that is possibly rotated.
* `-10^4 <= k <= 10^4`

***

![alt text](<003rotated array_240105_131613(1).jpg>) ![alt text](<003rotated array_240105_131613(2).jpg>) ![alt text](<003rotated array_240105_131613(3).jpg>) ![alt text](<003rotated array_240105_131613(4).jpg>) ![alt text](<003rotated array_240105_131613(5).jpg>) 
 
 


```cpp
class Solution {

    int bs(vector<int> &nums, int target,int low ,int high){
        int n=nums.size();
        while(low<=high){
            int mid=(low+high)/2;
            if(nums[mid]==target) return mid;
            // Check if the left part is sorted
            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    // Target exists in the left sorted part
                    high = mid - 1 ;
                } else {
                    // Target does not exist in the left sorted part
                    low = mid + 1;
                }
            } else {
                // Check if the right part is sorted
                if (nums[mid] <= target && target <= nums[high]) {
                    // Target exists in the right sorted part
                    low = mid + 1;
                } else {
                    // Target does not exist in the right sorted part
                    high = mid - 1;
                }
        }
        }
        return -1;
    }
public:
    int search(vector<int> &nums, int k) {
       return bs(nums,k,0,nums.size()-1);
    }
};

```


seee

```cpp
            if (nums[low] <= nums[mid]) {///condition 1
                
            } else {//condition 2 nums[lo]>nums[mid]
               
        }
        }
``` 

![alt text](image.png)


![alt text](image-1.png)

![alt text](image-2.png)

![alt text](image-3.png)
 
 ![alt text](<003rotated array_240105_131613(6).jpg>) ![alt text](<003rotated array_240105_131613(7).jpg>) ![alt text](<003rotated array_240105_131613(8).jpg>)

![alt text](<003rotated array_240105_131613(9).jpg>) 

![alt text](<003rotated array_240105_131613(10).jpg>) 


```cpp

class Solution {
        int bs(vector<int> &nums, int target,int low ,int high){
        int n=nums.size();
        while(low<=high){
            int mid=(low+high)/2;
            if(nums[mid]==target ||target==nums[low]) return true;
            // Check if the left part is sorted
            if (nums[low] < nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    // Target exists in the left sorted part
                    high = mid - 1 ;
                } else {
                    // Target does not exist in the left sorted part
                    low = mid + 1;
                }
            } else if (nums[mid] < nums[high]) {
                // Check if the right part is sorted
                if (nums[mid] <= target && target <= nums[high]) {
                    // Target exists in the right sorted part
                    low = mid + 1;
                } else {
                    // Target does not exist in the right sorted part
                    high = mid - 1;
                }
        } else low++;
        }
        return false;
    }
public:
    bool searchInARotatedSortedArrayII(vector<int> &nums, int k)  {
      return bs(nums,k,0,nums.size()-1);
    }
};
```
![alt text](image-4.png)

## Q Find min in rotated sorted array

Given an integer array nums of size N, sorted in ascending order with distinct values, and then rotated an unknown number of times (between 1 and N), find the minimum element in the array.

---
Example 1

Input : nums = [4, 5, 6, 7, 0, 1, 2, 3]

Output: 0

Explanation: Here, the element 0 is the minimum element in the array.

---
Example 2

Input : nums = [3, 4, 5, 1, 2]

Output: 1

Explanation:Here, the element 1 is the minimum element in the array.

---
Example 3

Input : nums = [4, 5, 6, 7, -7, 1, 2, 3]

Output:

-7

---
Constraints

n == nums.length

 1 <= n <= $10^4$

 -$10^4$ <= nums[i] <= $10^4$

 All the integers of nums are unique.
 nums is sorted and rotated between 1 and n times.

![alt text](image-5.png)

![alt text](image-6.png)
![alt text](<003rotated array_240105_131613(12).jpg>)

### The Logic: "Maybe" vs. "Definitely Not"

When we look at `nums[mid]`, we compare it to `nums[high]` (the end of the range) to determine which side holds the minimum.

---

### Case A: `nums[mid] > nums[high]`
* **Meaning:** The left side is "high up" on the cliff, and the right side is "down low." The drop (and thus the minimum) **MUST** be to the right of `mid`.
* **Action:** Since `nums[mid]` is larger than `nums[high]`, `mid` itself cannot be the minimum. We can safely discard it.
* **Code:** `lo = mid + 1` (Standard Template 2 logic).

---

### Case B: `nums[mid] < nums[high]` (or equal, if no duplicates)
* **Meaning:** The slope from `mid` to `high` is normal (increasing). The cliff is not on the right side.
* **Crucial Insight:** Since the right side is normal, the minimum must be at `mid` **OR** somewhere to the left of `mid`.
* **Action:** `mid` could potentially be the minimum (e.g., `[4, 5, 1, 2, 3]`, where `mid` is `1`). We cannot discard it.
* **Code:** `hi = mid` (We keep `mid` in the search space).

---

### Summary Table

| Comparison | Location of Min | Decision | Update |
| :--- | :--- | :--- | :--- |
| `mid > high` | To the Right | `mid` is **definitely not** min | `lo = mid + 1` |
| `mid < high` | At `mid` or Left | `mid` **could be** the min | `hi = mid` |







```cpp
class Solution {

public:
    int findMin(vector<int> &arr)  {
      int si=0;
      int ei=arr.size()-1;
       int ans = INT_MAX;  
      while(si<=ei){
        int mid=(si+ei)/2;
        if(arr[mid]>=arr[si]){//si to mid is sorted and min is si
            ans = min(ans, arr[si]);  
            si=mid+1;
        }else{//arr[mid]<arr[si] so arr[si] is not min and si to mid we have a j which is min or mid is that j so need to go on left
            ans = min(ans, arr[mid]);  
            ei=mid-1;
        }
      }
      return ans;
    }
};
```
### Your Code = "Exhaust and Harvest"

Your code uses the **Template 1** skeleton to scan the entire relevant search space. 

* **Goal:** Find the minimum value in the array.
* **Action:** Unlike a standard search, we **never** return inside the loop.
* **Logic:** We "harvest" the potential answer (`ans = min(ans, nums[mid])`) and then **Keep Going** until the search space is absolutely exhausted ($si > ei$).

---

### Why this works safely (The "Safety Net")

The biggest danger of using **Template 1** (`hi = mid - 1`) for finding a minimum is that you might accidentally **discard the answer**.

Imagine the following scenario:
1.  Your code looks at `nums[mid]`.
2.  `nums[mid]` happens to be the **actual minimum** of the entire array.
3.  The logic then executes `ei = mid - 1`.

**The Risk:** You just threw the answer out of your search range! 

**The Safety Net:** Because you "harvested" the value into your `ans` variable *before* updating the pointers, it doesn't matter if you discard `mid`. The answer is already safely stored in your "pocket" (the `ans` variable).

---

### Comparison: Harvesting vs. Shrinking

| Feature | Your "Harvest" Approach | Standard Template 2 |
| :--- | :--- | :--- |
| **Pointers** | `ei = mid - 1` (Discard `mid`) | `ei = mid` (Keep `mid`) |
| **Storage** | Uses an external `ans` variable. | The answer is the final `lo` pointer. |
| **Loop Type** | `while (si <= ei)` | `while (lo < hi)` |
| **Strategy** | Scan everything; remember the best. | Narrow the range until only the best remains. |

---

### Summary
Your approach is very robust. By updating `ans` at every step, you turn the Binary Search into a "Smart Probe" that remembers the best thing it has seen, allowing you to use the simpler `si <= ei` template without fear of losing the minimum.

### The One "Gotcha" (Be Ready for This)

Some strict interviewers expect the **Template 2** solution (converging to a single index without an `ans` variable) because it is considered the "Classical" solution to this specific problem.

If you write your "Exhaust and Harvest" solution, they might ask:
> "Can you do this without the extra `ans` variable, just by narrowing the index?"

---

### How to handle that
You don't have to panic. You can stick to your guns by explaining **why** you chose your approach. You can say:

> "I prefer using the explicit `ans` variable because it allows me to use the standard `lo <= hi` template. This eliminates the risk of **off-by-one errors** or **infinite loops** that are common when trying to narrow down to a single index. It achieves the same $O(\log N)$ Time and $O(1)$ Space complexity while being more robust."

---

### Why this is a "Power Move"
Most interviewers will accept that answer immediately because it shows **engineering maturity**. You are demonstrating that you:
1.  Understand the underlying mechanics of the templates.
2.  Prioritize **readable, bug-free code** over "clever" pointer manipulation.
3.  Are aware of the trade-offs in different implementations.

---

### Summary Table: Engineering Trade-offs

| Feature | Your Approach (Harvest) | Classical Approach (Converge) |
| :--- | :--- | :--- |
| **Safety** | High (Hard to loop infinitely) | Medium (Requires precise updates) |
| **Clarity** | Very Clear (Logic is explicit) | Concise (Elegant but subtle) |
| **Memory** | $O(1)$ | $O(1)$ |
| **Performance** | Identical | Identical |

Would you like to see how the **Classical (Converge)** version looks in code just so you can recognize it if an interviewer brings it up?

When using `while(lo <= hi)`, the loop always terminates with:
$$lo = hi + 1$$

Here is the mathematical proof using the **"Last Man Standing"** scenario.

---

### The Final Step (When `lo == hi`)
Eventually, the search narrows down to a single element. Let's say `lo` and `hi` both point to index **5**.
* `lo = 5`
* `hi = 5`
* `mid = 5`

Now, the code executes one of two paths:

#### Path A: You go Right (`lo = mid + 1`)
* Code executes: `lo = 5 + 1 = 6`.
* `hi` stays at **5**.
* **Result:** `lo (6) > hi (5)`.
* **Gap:** `lo` is exactly `hi + 1`.

#### Path B: You go Left (`hi = mid - 1`)
* Code executes: `hi = 5 - 1 = 4`.
* `lo` stays at **5**.
* **Result:** `lo (5) > hi (4)`.
* **Gap:** `lo` is exactly `hi + 1`.

---

### Why is this useful?
This property is why this template is so powerful for finding **Insert Positions** or **Boundaries**. At the moment the loop breaks:

* **`lo`** ends up pointing to the first element **GREATER** than the target (the correct position to insert the target).
* **`hi`** ends up pointing to the last element **SMALLER** than the target.

---

### Summary
Because the pointers "cross" by exactly one unit, you have a perfect snapshot of the boundary where the target would belong. 


 ![alt text](<003rotated array_240105_131613(14).jpg>) ![alt text](<003rotated array_240105_131613(15).jpg>) 
 
 ![alt text](<003rotated array_240105_131613(16).jpg>)

 ![alt text](image-7.png)
 
 ![alt text](image-8.png)
 ```cpp
 class Solution {
public:
    int findMin(vector<int>& arr) {
            int si=0;
      int ei=arr.size()-1;
       int ans = INT_MAX;  
      while(si<=ei){
        int mid=(si+ei)/2;
        if (arr[si] == arr[mid] && arr[mid] == arr[ei]) {
                ans = min(ans, arr[si]);
                si++;
                ei--;
                continue; // Skip the rest of the loop logic
            }
        if(arr[mid]>=arr[si]){//si to mid is sorted and min is si
            ans = min(ans, arr[si]);  
            si=mid+1;
        }else{//arr[mid]<arr[si] so arr[si] is not min and si to mid we have a j which is min or mid is that j so need to go on left
            ans = min(ans, arr[mid]);  
            ei=mid-1;
        }
      }
      return ans;
    }
};
```
 ### Why we need `continue`

When we execute `si++` and `ei--`, the boundaries of our search space change. We immediately want to **restart the loop** to recalculate `mid` using these new boundaries. 

We use `continue` to prevent the code from executing the rest of the binary search logic (the `mid` comparisons) with stale or invalid logic states. It ensures that the very next thing the program does is re-check the `while` condition and compute a fresh, accurate `mid`.

---

### Complexity Analysis

* **Average Case: $O(\log N)$**
    * In most scenarios, the array will still allow us to discard half of the search space in each step, behaving like a standard binary search.

* **Worst Case: $O(N)$**
    * **Example:** `[1, 1, 1, 1, 1, 1, 1]` or `[1, 1, 1, 0, 1, 1, 1]`.
    * If the `si`, `mid`, and `ei` elements are all identical, we cannot mathematically determine which half is sorted. We are forced to shrink the range step-by-step (`si++` and `ei--`). 
    * This linear time complexity is **unavoidable** for rotated arrays containing duplicates.

---

### Summary Table

| Case | Complexity | Condition |
| :--- | :--- | :--- |
| **Best Case** | $O(1)$ | Target found at the first `mid`. |
| **Average Case** | $O(\log N)$ | Distinct elements or clear rotation point. |
| **Worst Case** | $O(N)$ | Many duplicates making `nums[si] == nums[mid] == nums[ei]`. |


solution by rajneesh is also worst case O(n) solution !! Both are same!!


 
  ![alt text](<003rotated array_240105_131613(17).jpg>) ![alt text](<003rotated array_240105_131613(18).jpg>) 
![alt text](<003rotated array_240105_131613(19).jpg>)

```java
class Solution {
    public int peakIndexInMountainArray(int[] arr) {
         int n=arr.length;
        int lo=0;
        int hi=n-1;
        while(lo<hi){
            int mid=(lo+hi)/2;

            if(mid>0&&mid<n){
                if(arr[mid]>arr[mid-1]&& arr[mid]>arr[mid+1]) return mid;
                else if(arr[mid]<arr[mid-1] && arr[mid]>arr[mid+1]) hi=mid-1; 
                else lo=mid+1;
            }
            else   if(mid==0){
                return arr[0]>arr[1]?0:1;
            }
            else if(mid==n-2){//this is not required as covered by mid>0 &&mid<n 1st if iske bina bhi submit hora
                return arr[n-1]>arr[n-2]?n-1:n-2;
            }
   
        }
        return lo;
      }
}
```

Complexity Analysis: 
Time Complexity:O(logN), N is size of the given array. As binary search is being used to find the minimum.

Space Complexity: As no additional space is used, so the Space Complexity is O(1).

 ![alt text](<003rotated array_240105_131613(20).jpg>) 
![alt text](<003rotated array_240105_131613(21).jpg>)




## QFind how many time array is rotated

Given an integer array nums of size n, sorted in ascending order with distinct values. The array has been right rotated an unknown number of times, between 0 and n-1 (including). Determine the number of rotations performed on the array.

---

Example 1

Input : nums = [4, 5, 6, 7, 0, 1, 2, 3]

Output: 4

Explanation: The original array should be [0, 1, 2, 3, 4, 5, 6, 7]. So, we can notice that the array has been rotated 4 times.

---

Example 2

Input: nums = [3, 4, 5, 1, 2]

Output: 3

Explanation: The original array should be [1, 2, 3, 4, 5]. So, we can notice that the array has been rotated 3 times.

---

Example 3

Input: nums = [4, 5, 1, 2]

Output:

2

----

Constraints

 - n == nums.length
 - 1 <= n <= $10^4$
 - -$10^4$ <= nums[i] <= $10^4$
 - All the integers of nums are unique.


```cpp
class Solution {
public:
    int findKRotation(vector<int> &arr)  {
        int si=0;
      int ei=arr.size()-1;
       int ans = INT_MAX;  
       int index=-1;
      while(si<=ei){
        int mid=(si+ei)/2;
        if(arr[mid]>=arr[si]){
            if(arr[si]<ans){
                ans=arr[si];
                index=si;
            }
            si=mid+1;
        }else{
            if(arr[mid]<ans){
                ans=arr[mid];
                index=mid;
            }
            ei=mid-1;
        }
      }
      return index;
    }
};
```
