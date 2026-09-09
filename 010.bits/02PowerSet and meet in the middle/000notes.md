# Q1  Power set 

This can be acheieved by recusrion but let us see this way too

# Power Set Generation via Bitmasking

### 1. The Strategy: The Binary Checklist
Every subset is represented by a binary number between $0$ and $2^n - 1$.
- Imagine `nums = [10, 20, 30]`.
- We treat the bits of an integer `val` as a "Yes/No" checklist for each element.

| Decimal (`val`) | Binary (`i=2, 1, 0`) | Logic (Bits Set) | Resulting Subset |
| :--- | :--- | :--- | :--- |
| **0** | `0 0 0` | None | `[]` |
| **1** | `0 0 1` | 0th bit set | `[10]` |
| **3** | `0 1 1` | 0th & 1st bits set | `[10, 20]` |
| **7** | `1 1 1` | All bits set | `[10, 20, 30]` |

---

### 2. Code Breakdown

#### **A. The Total Count ($2^n$)**
`int count = (1 << n);`
- `1 << n` is the bitwise way to calculate $2^n$.
- This defines how many total subsets exist.

#### **B. The "Checklist" Loop**
`for(int val = 0; val < count; val++)`
- This loop generates every unique binary pattern from all zeros to all ones.

#### **C. The Bit Probe**
`if(val & (1 << i))`
- **The Mask:** `(1 << i)` creates a number with only the $i$-th bit set (e.g., $1, 2, 4, 8 \dots$).
- **The AND Operation:** `val & mask` results in a non-zero value only if `val` has the $i$-th bit turned on.

---

### 3. C++ vs. Java Observation
In your code, you noted:
> `if(val & (1 << i))` // In cpp this works but in java you need to put != 0

**The Physics of the Language:**
* **C++:** Interprets any **non-zero** integer as `true`. If the result of the bitwise AND is `4`, the `if` condition passes.
* **Java:** Requires a strict `boolean` (`true` or `false`). Since `val & mask` returns an `int`, Java will throw an error unless you explicitly compare it: `(val & (1 << i)) != 0`.

---

### 4. Complexity Analysis
* **Time Complexity:** $O(n \cdot 2^n)$
    - We iterate through $2^n$ combinations.
    - For each combination, we run an internal loop of $n$ to check bits.
* **Space Complexity:** $O(n \cdot 2^n)$
    - To store all subsets (if we are returning the answer).

---

### 5. Summary for Interviews
- **When to use:** When you need all possible combinations and $N$ is small (typically $N \le 20$).
- **Key Advantage:** It is iterative and avoids the overhead of recursion/backtracking.
- **Key Disadvantage:** It doesn't handle duplicate elements in the input array as easily as backtracking does.

### Cpp code

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    vector<vector<int>> powerSet(vector<int>& nums) {
        

        int n = nums.size();
    
        vector<vector<int>> ans;

        int count = (1 << n);
        

        for(int val = 0; val < count; val++) {
            

            vector<int> subset;
            
            for(int i=0; i < n; i++) {
                if(val & (1 << i)) {//In cpp this works but in java you need to put !=0
                    subset.push_back(nums[i]);
                }
            }

            ans.push_back(subset);
        }

        return ans;
    }
};
/*
In Java, the & operator performs a bitwise AND, but the result is still an int. Java expects a boolean expression inside an if statement, and:

i & (1 << j) returns an int, not a boolean

So this is a compilation error

so use if ((i & (1 << j)) != 0)  in java

In C/C++, it's fine to use just if (i & (1 << j)) because non-zero integers are treated as true, but Java is stricter and requires explicit boolean expressions.
*/

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol; 

    vector<vector<int>> ans = sol.powerSet(nums);
    
    sort(ans.begin(), ans.end());

    cout << "The power set for the given array is: " << endl;
    
    for(int i=0; i < ans.size(); i++) {
        for(int j=0; j < ans[i].size(); j++) {
            cout << ans[i][j] << " ";        
        }
        cout << endl;
    }
    
    return 0;
}

/*
Output:
1 
1 2 
1 2 3 
1 3 
2 
2 3 
3 
*/
```

### Java

```java
import java.util.*;
class PowerSetExample {
    static List<List<Integer>> powerSet(int[] nums) {
        List<List<Integer>> ans=new ArrayList<>();
        for(int val=0;val<(1<<nums.length);++val) {
            List<Integer> subset=new ArrayList<>();
            for(int i=0;i<nums.length;++i) if((val&(1<<i))!=0) subset.add(nums[i]);
            ans.add(subset);
        }
        return ans;
    }
    public static void main(String[] args) {
        List<List<Integer>> ans=powerSet(new int[]{1,2,3});
        ans.sort((a,b)->{
            int n=Math.min(a.size(),b.size());
            for(int i=0;i<n;++i) {
                int cmp=Integer.compare(a.get(i),b.get(i));
                if(cmp!=0) return cmp;
            }
            return Integer.compare(a.size(),b.size());
        });
        for(List<Integer> subset:ans) {
            for(int v:subset) System.out.print(v+" ");
            System.out.println();
        }
    }
}
```

# Bitwise Check: `if (val & (1 << i))`

### The Mechanics
1. **`1 << i` (The Mask):** Creates a number where only the $i$-th bit is 1. All other bits are 0.
2. **`&` (The Filter):** Performs a bitwise AND between the input `val` and the mask. 
3. **The Result:**
   - If the $i$-th bit of `val` is **1**: The result is $2^i$ (a non-zero number).
   - If the $i$-th bit of `val` is **0**: The result is $0$.

### Language Nuance
- **In C++:** `if (number)` passes if `number != 0`. Since $2^i$ is never zero, the `if` block executes when the bit is set.
- **In Java/C#:** You must write `if ((val & (1 << i)) != 0)` because these languages require an explicit boolean.

### Example (val = 13, i = 2)
- Binary `val`: `1101`
- Mask `1 << 2`: `0100`
- `1101 & 0100` = `0100` (4)
- **Result:** True (The 2nd bit is ON).

In context of power set we are checking that from range 0 to 2^n we have a value and in that value if 1 is set than we put that number in set

Every index is treated as an bit posistion in number

# The Bit-to-Index Mapping

### The Core Concept
Every index `i` in the input array `nums` is treated as the $i$-th bit position in a binary number.

1. **Outer Loop (`val`):** Iterates through every possible combination of $N$ bits (from $0$ to $2^N-1$).
2. **Inner Loop (`i`):** Scans through each bit position of the current `val`.
3. **The Decision:** If the $i$-th bit is "ON", it means the element at `nums[i]` is "invited" to join the current subset.

### Visual Example (nums = [A, B, C])
If `val = 6` (Binary `110`):
- Bit 0: `0` (Skip `nums[0]` / A) as bit 0 is 0
- Bit 1: `1` (Take `nums[1]` / B)
- Bit 2: `1` (Take `nums[2]` / C)
- **Resulting Subset:** `[B, C]`

### Java code

### C++

```cpp
#include <vector>
std::vector<std::vector<int>> powerSet(const std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    int limit=1<<nums.size();
    for(int i=0;i<limit;++i) {
        std::vector<int> subset;
        for(int j=0;j<(int)nums.size();++j) if((i&(1<<j))!=0) subset.push_back(nums[j]);
        res.push_back(subset);
    }
    return res;
}
```

### Java

```java

import java.util.*;
class Solution {
    public List<List<Integer>> powerSet(int[] nums) {
        int n=nums.length;
        List<List<Integer>> res = new ArrayList<>();
        int limit=(1<<n);//2 to power n no of susbsets

        for(int i=0;i<limit;i++){//iterating over 0 to 2^n
            List<Integer>subset=new ArrayList<>();
            for(int j=0;j<n;j++){//iterating over n bits as n bits for 2^n
                
                if((i &(1<<j))!=0){
                    subset.add(nums[j]);
                }
            }
            res.add(subset);
        }
     return res;
    }
    public static void main(String[] args) {
        int[] nums = {1,2,3,4};
        Solution sol = new Solution(); 
        List<List<Integer>>res=sol.powerSet(nums);
        System.out.println(res);
/*
Output:
[[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3], [4], [1, 4], [2, 4], [1, 2, 4], [3, 4], [1, 3, 4], [2, 3, 4], [1, 2, 3, 4]]
*/

    }
 
}
/*
tc->(n*(2^n)) two loops outer one of 2^n and inner one for n
sc->O((2^n)*n) 2^n subset and each size on avg we take as n for worst case
*/
/*
{1,2,3} n=3 so no of elements in set =2^n=8
000={}
001={3}
010={2}
011={2,3}
100={1}
101={1,3}
110={1,2}
111={1,2,3}

i loop iterates over 0 to <2^n

j loop over n bits as for subset of n number we need n bits to represent number between 
0 to 2^n

if bit is 1 then add that number else not
*/
```
## Question 2. Determine whether a subset reaches the target sum

# Meet in the middle

The Meet-in-the-Middle algorithm is a "Search Space Reduction" technique. It is essentially the "Divide and Conquer" of Brute Force.You use it when your search space is too big for a simple recursion ($O(2^n)$) but doesn't have the structure for Dynamic Programming.


## 1. The Physics: "Split and Merge"

- If you have $N$ elements and you try to find a subset sum, a normal Brute Force check is $O(2^N)$.

- If $N = 40$, $2^{40}$ is roughly 1 trillion operations (Way too slow for an interview).But if you split the array into two halves of $N=20$:$2^{20}$ is only 1 million operations (Very fast).

- The algorithm generates all possibilities for the first half, all for the second half, and then "meets in the middle" to find a combination that hits the target.



## 2. The Step-by-Step Logic

Divide: Split the array into two equal halves (Part A and Part B).

Generate: Create a list of all possible sums/results from Part A. Store them (usually in a sorted array or a HashMap).

Generate & Search: Generate each possible sum from Part B. For each sum sumB, calculate the "Required Value" from Part A: Needed = Target - sumB.

Find: Search for Needed in the stored results of Part A using Binary Search or a HashMap.

## 3. Comparison: Brute Force vs. Meet-in-the-Middle

| Feature | Brute Force ($2^n$) | Meet-in-the-Middle ($2^{n/2}$) |
| :--- | :--- | :--- |
| **Operations ($n=40$)** | $\approx 1.1 \times 10^{12}$ | $\approx 2.1 \times 10^6$ |
| **Time (Approx)** | Years | Milliseconds |
| **Time Complexity** | $O(2^n)$ | $O(2^{n/2} \cdot n)$ |
| **Space Complexity** | $O(1)$ or $O(n)$ | $O(2^{n/2})$ |
| **Primary Trade-off** | Slow, but memory efficient. | Extremely fast, but high memory usage. |

# Dp vs meet in middle 

for the standard Subset Sum problem, DP is usually the king. However, there is a "Physics" reason why DP isn't always possible, and that’s where Meet-in-the-Middle takes over.

The choice depends entirely on the Constraints of the input.

1. The DP Weakness: "Pseudo-Polynomial" TimeThe time complexity of Subset Sum using DP is $O(N \cdot \text{Target})$.

    - When DP is better: If the Target is small (e.g., $N=100$, $\text{Target}=10,000$), DP does $10^6$ operations. Fast!
    
    - When DP fails: If the Target is massive (e.g., $\text{Target} = 10^{12}$), DP would need a trillion-size array and a trillion operations. Crash!

2. The Meet-in-the-Middle Strength:"Target-Independent"

- Meet-in-the-Middle doesn't care how big the Target number is. It only cares about the number of elements ($N$).The Scenario: 

    - You have $N=40$ elements, and each element could be a huge number (like $10^{15}$), and the Target is also huge.
    
    - The Physics:DP: Fails because it can't create an array for $10^{15}$.Meet-in-the-Middle: Splits the 40 elements into two sets of 20. It calculates $2^{20}$ sums ($1$ million) and doesn't care how big the values are.

 3. Comparison Table

| Feature | Dynamic Programming (DP) | Meet-in-the-Middle |
| :--- | :--- | :--- |
| **Complexity** | $O(N \cdot \text{Target})$ | $O(2^{N/2} \cdot N)$ |
| **Dependent on...** | The Value of the Target. | The Count of Elements ($N$). |
| **Memory** | Needs an array of size **Target**. | Needs a list of size $2^{N/2}$. |
| **Best Case** | Large $N$, Small Target. | Small $N$ (up to 40), Huge Target. |

# DP vs. Meet-in-the-Middle

### 1. When to use DP
- Use when the **Target Sum** is small enough to fit in memory (usually up to $10^6$ or $10^7$).
- This is the "Standard" interview answer for most Subset Sum problems.

### 2. When to use Meet-in-the-Middle
- Use when the **Target Sum** is massive (e.g., $10^{12}$) but **N is small** (30-45).
- Use when the array elements are **Fractional** (Decimals) or huge integers.
- **Physics:** DP builds a table based on *values*; Meet-in-the-Middle builds a list based on *combinations*.

### 3. The Interview "Pro" Tip
If an interviewer gives you a Subset Sum problem, always ask: **"What is the range of the Target Sum?"**
- If they say 10,000: Say "I'll use DP."
- If they say $10^{15}$: Say "DP won't work due to space; I'll use Meet-in-the-Middle."

## Meet in middle for subset sum
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// Helper function to generate all possible subset sums for a given half
void generateSums(const vector<int>& arr, vector<ll>& sums) {
    int n = arr.size();
    // There are 2^n possible subsets
    for (int i = 0; i < (1 << n); i++) {
        ll currentSum = 0;
        for (int j = 0; j < n; j++) {
            // If the j-th bit is set, include arr[j] in the sum
            if (i & (1 << j)) {
                currentSum += arr[j];
            }
        }
        sums.push_back(currentSum);
    }
}

bool meetInTheMiddle(vector<int>& nums, ll target) {
    int n = nums.size();
    
    // 1. Split the array into two halves
    vector<int> leftHalf, rightHalf;
    for (int i = 0; i < n; i++) {
        if (i < n / 2) leftHalf.push_back(nums[i]);
        else rightHalf.push_back(nums[i]);
    }

    // 2. Generate all possible sums for both halves
    vector<ll> leftSums, rightSums;
    generateSums(leftHalf, leftSums);
    generateSums(rightHalf, rightSums);

    // 3. Sort the second half to enable Binary Search
    sort(rightSums.begin(), rightSums.end());

    // 4. For every sum in the first half, find the "Needed" value in the second
    for (ll s : leftSums) {
        ll needed = target - s;
        // Use binary search (binary_search returns true/false)
        if (binary_search(rightSums.begin(), rightSums.end(), needed)) {
            return true; 
        }
    }

    return false;
}

int main() {
    // Example: N=4 but imagine N=40. Target is huge.
    vector<int> nums = {10, 20, 30, 40};
    ll target = 50;

    if (meetInTheMiddle(nums, target)) {
        cout << "Target " << target << " can be formed!" << endl;
    } else {
        cout << "Target cannot be formed." << endl;
    }

    return 0;
}
```

### Java

```java
import java.util.*;
class MeetInTheMiddleExample {
    static List<Long> generateSums(int[] arr) {
        List<Long> sums=new ArrayList<>();
        for(int mask=0;mask<(1<<arr.length);++mask) {
            long sum=0;
            for(int j=0;j<arr.length;++j) if((mask&(1<<j))!=0) sum+=arr[j];
            sums.add(sum);
        }
        return sums;
    }
    static boolean meetInTheMiddle(int[] nums,long target) {
        int mid=nums.length/2;
        List<Long> left=generateSums(Arrays.copyOfRange(nums,0,mid));
        List<Long> right=generateSums(Arrays.copyOfRange(nums,mid,nums.length));
        Collections.sort(right);
        for(long s:left) if(Collections.binarySearch(right,target-s)>=0) return true;
        return false;
    }
    public static void main(String[] args) {
        long target=50;
        boolean found=meetInTheMiddle(new int[]{10,20,30,40},target);
        System.out.println(found ? "Target "+target+" can be formed!" : "Target cannot be formed.");
    }
}
```

# Meet-in-the-Middle Workflow

### Step 1: Divide
Split the array of size $N$ into two arrays of size $N/2$.

### Step 2: Generate (The "Small Hills")
Calculate all $2^{N/2}$ sums for both halves. 
*Complexity so far: $O(2^{N/2})$*

### Step 3: Sort
Sort the second list of sums so we can search it instantly.
*Complexity so far: $O(2^{N/2} \cdot \log(2^{N/2}))$*

### Step 4: The Handshake
For every sum in List A, Binary Search for `(Target - Sum)` in List B.
*Complexity: $O(2^{N/2} \cdot \frac{N}{2})$*

### Final Outcome
We solved a problem that usually takes $O(2^N)$ in roughly $O(N \cdot 2^{N/2})$. 
For $N=40$, this is the difference between **centuries** of waiting and **0.5 seconds** of execution.

























## Example and complexity clarifications

Power-set generation includes the empty subset. In the printed C++ example it appears as a blank output line before the nonempty subsets. With the code's indexing rule, bit 0 selects nums[0]. Thus [1,2,3] uses mask 001 for [1], 010 for [2], and 100 for [3]. A list written with array-index order left-to-right may display those bits in reverse order; the numerical masks below use the usual most-significant-bit-first display.

![All subsets: nums = [1, 2, 3]](svgs/power-set.svg)

The loops take O(n*2^n) time because each of 2^n masks checks n positions. Storing all subsets takes O(n*2^n) space; the temporary subset uses O(n). Sorting the finished collection for display is additional work beyond generation. The int mask expressions require small input sizes and valid shifts (n<31 for these signed-int loops).

For the meet-in-the-middle example [10,20,30,40] and target 50, split into [10,20] and [30,40]. Their subset sums are [0,10,20,30] and [0,30,40,70]. Searching complements finds 10+40=50 (and also 20+30=50).

![Meet in the middle: target = 50](svgs/meet-middle.svg)

For h=ceil(n/2), the shown bit-by-bit subset-sum generator takes O(h*2^h) time. Sorting and binary searching the sums also fit O(n*2^h). Space is O(2^h) for the two sum lists plus O(n) split arrays. Claims of O(2^h) generation alone require a different incremental subset-sum generator; the current nested loops have an h factor. Runtime examples in the existing prose are illustrative, not timing guarantees. Integer sums must fit in long long / long.
