
## Q1. Rotate Array

### Question

Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative. The rotation must be performed in-place using `O(1)` extra space.

**Example 1**

```text
Input:  nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]

After 1 step: [7,1,2,3,4,5,6]
After 2 steps: [6,7,1,2,3,4,5]
After 3 steps: [5,6,7,1,2,3,4]
```

**Example 2**

```text
Input:  nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
```

**Constraints**

- `1 <= nums.length <= 100000`
- `-2^31 <= nums[i] <= 2^31 - 1`
- `0 <= k <= 100000`

### Explanation

A positive `k` means rotate right; a negative rotation count would mean rotate left. Normalize the count with `k = ((k % n) + n) % n`, so it always lies in `[0, n - 1]`. Adding or subtracting `n` has no effect because a full rotation returns the array to its original state.

For a right rotation, reverse the complete array, reverse the first `k` elements, and finally reverse the remaining `n-k` elements. Reversal is used because directly shifting every element would either require extra memory or repeated movement.

![Dry run for rotating an array](<q1_rotate_array_dry_run.svg>)

### C++ Implementation

```cpp
class Solution {
    void reverseRange(vector<int>& nums, int left, int right) {
        while (left < right) {
            swap(nums[left++], nums[right--]);
        }
    }

public:
    void rotate(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        k = ((k % n) + n) % n;

        reverseRange(nums, 0, n - 1);
        reverseRange(nums, 0, k - 1);
        reverseRange(nums, k, n - 1);
    }
};
```

### Java Implementation

```java
class Solution {
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    private void reverse(int[] nums, int left, int right) {
        while (left < right) {
            swap(nums, left++, right--);
        }
    }

    public void rotate(int[] nums, int k) {
        int n = nums.length;
        k = ((k % n) + n) % n;

        reverse(nums, 0, n - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, n - 1);
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q2. Segregate Negative and Non-Negative Elements

### Question

Given an integer array `arr`, rearrange it in-place so that every negative element appears before every non-negative element. The relative order within either group does not have to be preserved. Treat zero as non-negative.

**Example 1**

```text
Input:  arr = [4,-3,7,-1,0,-6,2]
Output: [-3,-1,-6,4,0,7,2]
```

Any arrangement in which all negative values precede all non-negative values is valid.

**Constraints**

- `1 <= arr.length <= 100000`
- `-10^9 <= arr[i] <= 10^9`

### Explanation

Maintain `boundary`, the last position occupied by a negative value, and scan from left to right. Whenever `arr[scan]` is negative, increment `boundary` and swap that value into the negative region. This is the same in-place partition idea later reused for sorting arrays containing only `0` and `1`.

![Dry run for segregating negative values](<q2_positive_negative_dry_run.svg>)

### C++ Implementation

```cpp
class Solution {
public:
    void segregateNegative(vector<int>& arr) {
        int boundary = -1;

        for (int scan = 0; scan < static_cast<int>(arr.size()); ++scan) {
            if (arr[scan] < 0) {
                swap(arr[++boundary], arr[scan]);
            }
        }
    }
};
```

### Java Implementation

```java
class Solution {
    public void segregateNegative(int[] arr) {
        int boundary = -1;

        for (int scan = 0; scan < arr.length; scan++) {
            if (arr[scan] < 0) {
                boundary++;
                int temp = arr[boundary];
                arr[boundary] = arr[scan];
                arr[scan] = temp;
            }
        }
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q3. Segregate 0s and 1s

### Question

Given a binary array `arr` containing only `0` and `1`, rearrange it in-place so that all `0`s occur before all `1`s.

**Example 1**

```text
Input:  arr = [1,0,1,0,1,1,0]
Output: [0,0,0,1,1,1,1]
```

**Constraints**

- `1 <= arr.length <= 100000`
- `arr[i]` is either `0` or `1`

### Explanation

`nextZero` points to the position where the next encountered `0` belongs. Scan the entire array. When a `0` is found, swap it with `arr[nextZero]`, then advance `nextZero`. Ones need no direct action: they are naturally pushed to the right by later swaps.

![Dry run for sorting 0s and 1s](<q3_sort_01_dry_run.svg>)

### C++ Implementation

```cpp
class Solution {
public:
    void segregateZeroAndOne(vector<int>& arr) {
        int nextZero = 0;

        for (int scan = 0; scan < static_cast<int>(arr.size()); ++scan) {
            if (arr[scan] == 0) {
                swap(arr[nextZero++], arr[scan]);
            }
        }
    }
};
```

### Java Implementation

```java
class Solution {
    public void segregateZeroAndOne(int[] arr) {
        int nextZero = 0;

        for (int scan = 0; scan < arr.length; scan++) {
            if (arr[scan] == 0) {
                int temp = arr[nextZero];
                arr[nextZero] = arr[scan];
                arr[scan] = temp;
                nextZero++;
            }
        }
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q4. Segregate 0s, 1s and 2s

### Question

Given an array `arr` containing only `0`, `1`, and `2`, sort it in-place without using a library sorting function.

**Example 1**

```text
Input:  arr = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
```

**Constraints**

- `1 <= arr.length <= 100000`
- `arr[i]` is `0`, `1`, or `2`

### Explanation

Use the Dutch National Flag partition with three pointers:

- `[0, low - 1]` contains `0`s.
- `[low, mid - 1]` contains `1`s.
- `[mid, high]` is unknown.
- `[high + 1, n - 1]` contains `2`s.

If `arr[mid]` is `0`, swap it with `arr[low]` and advance both pointers. If it is `1`, advance `mid`. If it is `2`, swap it with `arr[high]` and decrease `high`; do not advance `mid`, because the incoming value has not been classified.

![Dry run for sorting 0s, 1s and 2s](<q4_sort_012_dry_run.svg>)

### C++ Implementation

```cpp
class Solution {
public:
    void sortZeroOneTwo(vector<int>& arr) {
        int low = 0;
        int mid = 0;
        int high = static_cast<int>(arr.size()) - 1;

        while (mid <= high) {
            if (arr[mid] == 0) {
                swap(arr[low++], arr[mid++]);
            } else if (arr[mid] == 1) {
                mid++;
            } else {
                swap(arr[mid], arr[high--]);
            }
        }
    }
};
```

### Java Implementation

```java
class Solution {
    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public void sortZeroOneTwo(int[] arr) {
        int low = 0;
        int mid = 0;
        int high = arr.length - 1;

        while (mid <= high) {
            if (arr[mid] == 0) {
                swap(arr, low++, mid++);
            } else if (arr[mid] == 1) {
                mid++;
            } else {
                swap(arr, mid, high--);
            }
        }
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q5. Segregate 0s, 1s, 2s and 3s

### Question

Given an array `arr` containing only `0`, `1`, `2`, and `3`, sort it in-place in one traversal so that equal values form four consecutive regions in ascending order.

**Example 1**

```text
Input:  arr = [0,3,2,1,3,3,0,2,2,1,1,2]
Output: [0,0,1,1,1,2,2,2,2,3,3,3]
```

**Example 2**

```text
Input:  arr = [3,2,1,0]
Output: [0,1,2,3]
```

**Constraints**

- `1 <= arr.length <= 100000`
- `arr[i]` is `0`, `1`, `2`, or `3`
- The rearrangement must be in-place.

### Explanation

This extends the Dutch National Flag idea to five regions: known `0`s, known `1`s, unknown values, known `2`s, and known `3`s.

- `p0` is the last index of the `0` region.
- `scan` is the first unclassified index from the left.
- `unknownEnd` is the final unclassified index from the right.
- `p3` is the first index of the `3` region.

On `0`, expand the zero region and advance `scan`. On `1`, only advance `scan`. On `2`, swap with `unknownEnd` and shrink the unknown region. On `3`, expand the three region from the right. The value swapped into `scan` after handling a `2` or `3` must be examined again.

The special `if (p3 == unknownEnd) unknownEnd--;` handles the moment at which the `3` boundary collides with the unknown boundary. It prevents a position already fixed as `3` from remaining classified as unknown.

![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(11).jpg>)
 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(12).jpg>) 
 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(13).jpg>) 
 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(14).jpg>) 
 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(15).jpg>) 
 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(16).jpg>)

---

#### sort array 0,1,2

```cpp
class Solution {
public:
    void sortZeroOneTwo(vector<int>& nums) {
        int n=nums.size();
        int i=0,j=0;
        int k=n-1;
        while(i<=k){
            if(nums[i]==0){
                swap(nums[i],nums[j]);
                i++;
                j++;
            }else if(nums[i]==1){
                i++;
            }else{
                swap(nums[i],nums[k]);
                k--;
            }
        }
    }
};
```

#### segregate 0,1,2,3

```cpp
#include <bits/stdc++.h>
using namespace std;


void solve(){
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


```




---
### C++ Implementation

```cpp
class Solution {
public:
    void sortZeroOneTwoThree(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        int p0 = -1;
        int scan = 0;
        int unknownEnd = n - 1;
        int p3 = n;

        while (scan <= unknownEnd) {
            if (arr[scan] == 0) {
                swap(arr[++p0], arr[scan]);
                scan++;
            } else if (arr[scan] == 1) {
                scan++;
            } else if (arr[scan] == 2) {
                swap(arr[scan], arr[unknownEnd--]);
            } else {
                swap(arr[scan], arr[--p3]);
                if (p3 == unknownEnd) {
                    unknownEnd--;
                }
            }
        }
    }
};
```

### Java Implementation

```java
class Solution {
    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public void sortZeroOneTwoThree(int[] arr) {
        int n = arr.length;
        int p0 = -1;
        int scan = 0;
        int unknownEnd = n - 1;
        int p3 = n;

        while (scan <= unknownEnd) {
            if (arr[scan] == 0) {
                p0++;
                swap(arr, p0, scan);
                scan++;
            } else if (arr[scan] == 1) {
                scan++;
            } else if (arr[scan] == 2) {
                swap(arr, scan, unknownEnd);
                unknownEnd--;
            } else {
                p3--;
                swap(arr, scan, p3);
                if (p3 == unknownEnd) {
                    unknownEnd--;
                }
            }
        }
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`; every operation permanently shrinks the unknown region or advances `scan`.
- **Auxiliary space:** `O(1)`

---

## Q6. Maximum Sum in the Configuration

### Question

Given a zero-indexed array `A` of length `N`, find the maximum possible value of:

```text
0 × A[0] + 1 × A[1] + ... + (N - 1) × A[N - 1]
```

You may rotate the array clockwise or counter-clockwise any number of times.

**Example 1**

```text
Input:  N = 4, A = [8,3,1,2]
Output: 29

Rotations and scores:
[8,3,1,2] -> 8×0 + 3×1 + 1×2 + 2×3 = 11
[3,1,2,8] -> 3×0 + 1×1 + 2×2 + 8×3 = 29
[1,2,8,3] -> 1×0 + 2×1 + 8×2 + 3×3 = 27
[2,8,3,1] -> 2×0 + 8×1 + 3×2 + 1×3 = 17
```

**Constraints**

- `1 <= N <= 10000`
- `1 <= A[i] < 1000`

### Explanation

Recomputing the complete weighted sum for every rotation takes `O(n^2)`. Instead, first calculate the total array sum `S` and the initial weighted sum `R0`.

For consecutive left rotations, the next score is:

```text
Ri = R(i - 1) - S + N × A[i - 1]
```

All values lose one from their index contribution, which subtracts `S`. The element moved from the front to the back gains `N` index positions relative to that subtraction, so add `N × A[i - 1]`. Thus each new rotation score takes constant time.


 ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(17).jpg>) ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(18).jpg>)
 
 
  ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(19).jpg>) 


### C++ Implementation

```cpp
class Solution {
public:
    long long maxSum(const vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        long long sum = 0;
        long long weighted = 0;

        for (int i = 0; i < n; ++i) {
            sum += arr[i];
            weighted += 1LL * i * arr[i];
        }

        long long answer = weighted;
        for (int i = 1; i < n; ++i) {
            weighted = weighted - sum + 1LL * n * arr[i - 1];
            answer = max(answer, weighted);
        }

        return answer;
    }
};
```

### Java Implementation

```java
class Solution {
    public long maxSum(int[] arr) {
        int n = arr.length;
        long sum = 0;
        long weighted = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];
            weighted += (long) i * arr[i];
        }

        long answer = weighted;
        for (int i = 1; i < n; i++) {
            weighted = weighted - sum + (long) n * arr[i - 1];
            answer = Math.max(answer, weighted);
        }

        return answer;
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`

---

## Q7. Container With Most Water

### Question

You are given an integer array `height` of length `n`. There are `n` vertical lines; the endpoints of the line at index `i` are `(i, 0)` and `(i, height[i])`.

Choose two lines that, together with the x-axis, form a container holding the maximum possible amount of water. Return that maximum area. The container's sides may not be slanted.

**Example 1**

```text
Input:  height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: Lines at indices 1 and 8 give width 7 and height min(8,7) = 7.
             Area = 7 × 7 = 49.
```

**Example 2**

```text
Input:  height = [1,1]
Output: 1
```

**Constraints**

- `n == height.length`
- `2 <= n <= 100000`
- `0 <= height[i] <= 10000`

### Explanation

Start with one pointer at each end, giving the maximum possible width. The water held by the two selected lines is:

```text
area = (right - left) × min(height[left], height[right])
```

After calculating the area, move the pointer at the shorter line. Moving the taller line cannot improve the height limit because the shorter line would remain, while the width would decrease. Moving the shorter line is the only move that might find a taller limiting side and compensate for the smaller width. If both heights are equal, either pointer may move.


  ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(20).jpg>) 
  ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(21).jpg>)
   ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(22).jpg>) 
   ![alt text](<001basic ques segregate 0123 conatiner most wtr_231123_170649(23).jpg>)


### C++ Implementation

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int best = 0;

        while (left < right) {
            int width = right - left;

            if (height[left] < height[right]) {
                best = max(best, height[left] * width);
                left++;
            } else {
                best = max(best, height[right] * width);
                right--;
            }
        }

        return best;
    }
};
```

### Java Implementation

```java
class Solution {
    public int maxArea(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int best = 0;

        while (left < right) {
            int width = right - left;

            if (height[left] < height[right]) {
                best = Math.max(best, height[left] * width);
                left++;
            } else {
                best = Math.max(best, height[right] * width);
                right--;
            }
        }

        return best;
    }
}
```

### Time and Space Complexity

- **Time:** `O(n)`
- **Auxiliary space:** `O(1)`
