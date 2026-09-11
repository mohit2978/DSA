### Sorting is the "Backbone" of 90% of Greedy Problems.

Greedy algorithms work by making the **best local choice** at every step. Sorting is the tool that lines up these "best choices" right in front of you.

However, it's not *always* just `std::sort`. Here are the three main flavors of Greedy:

#### 1. Static Sorting (The Classic)
You sort the entire input **once** at the beginning, then iterate linearly to pick the best items.
* **Activity Selection / Non-overlapping Intervals:** Sort by **End Time** (Ascending).
* **Job Sequencing:** Sort by **Profit** (Descending).
* **Fractional Knapsack:** Sort by **Value/Weight Ratio** (Descending).
* **Kruskal’s MST:** Sort edges by **Weight** (Ascending).

#### 2. Dynamic Sorting (Priority Queue / Heap)
Sometimes, picking an item **changes** the "goodness" of the remaining items, or you only need the "best" one repeatedly without sorting everything fully.
* **Huffman Coding:** You combine the two smallest frequencies, create a new node, and push it back. You need a **Min-Heap**.
* **Prim’s MST:** You constantly look for the cheapest edge connected to your *current* tree.
* **Dijkstra’s Algorithm:** You always expand the node with the shortest current distance.

#### 3. Linear Scan (No Explicit Sort)
Sometimes the "Greedy Choice" is based on position or a simple max/min tracking.
* **Jump Game:** You don't sort. You just iterate `i` from 0 to N and track `maxReach = max(maxReach, i + nums[i])`.
* **Buy and Sell Stock II:** You just sum up every positive difference (`price[i] - price[i-1]`).

### The "Sorting Trap" (When Greedy Fails)
Just because you *can* sort doesn't mean Greedy works.
* **0/1 Knapsack:** If you sort by value/weight, it fails because you can't break items. You might leave a tiny empty space that could have been filled by a "less efficient" but "perfectly fitting" item. **(Requires DP)**.
* **Coin Change (General):** If coins are `{1, 3, 4}` and you want `6`.
    * **Greedy (Sort Descending):** Pick 4, then 1, then 1 $\rightarrow$ **3 coins**.
    * **Actual Optimal:** Pick 3, then 3 $\rightarrow$ **2 coins**.
    * **(Requires DP)**.

### Summary Rule of Thumb
1.  **Can I define a strict criteria** (like "earliest finish time" or "highest profit") that *always* makes sense regardless of future choices?
    * **Yes:** Sort it $\rightarrow$ Greedy.
2.  **Does picking item A potentially "ruin" the fit for item B in a complex way?**
    * **Yes:** Do not Sort $\rightarrow$ DP.

## Q1 Assign cookies

Input : Student = [1, 2, 3] , Cookie = [1, 1]

Output :1

Explanation : You have 3 students and 2 cookies.

The minimum size of cookies required for students are 1 , 2 ,3.

You have 2 cookies both of size 1, So you can assign the cookie only to student having minimum cookie size 1.

So your answer is 1.

Input : Student = [1, 2] , Cookie = [1, 2, 3]

Output : 2

Explanation : You have 2 students and 3 cookies.

The minimum size of cookies required for students are 1 , 2.

You have 3 cookies and their sizes are big enough to assign cookies to all students.

So your answer is 2.

Mysolution

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution{    
    public:
    int findMaximumCookieStudents(vector<int>& Student, vector<int>& Cookie){
        sort(Student.begin(),Student.end());
        sort(Cookie.begin(),Cookie.end());
        //if min student >max of cookies then no student will get cookie
        if(Student[0]>Cookie[Cookie.size()-1]) return 0;
        int res=0;
        int j=0;
        for(int i=0;i<Student.size();i++){
            int val=Student[i];
            while(j<Cookie.size() && Cookie[j]<val) j++;
            if(j==Cookie.size()) return res;
            res++;
            j++;
        }
        return res;
    }
};

int main() {
    // Example input
    vector<int> Student = {1, 2};
    vector<int> Cookie = {1, 2, 3};

    // Create a Solution object
    Solution solution;

    // Call the findMaximumCookieStudents function
    int result = solution.findMaximumCookieStudents(Student, Cookie);

    // Output the result
    cout << "Number of students satisfied: " << result << endl;

    return 0;
}
```

Given solution
```cpp

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    
    int findMaximumCookieStudents(vector<int>& Student, vector<int>& Cookie) {
        int n = Student.size();
        int m = Cookie.size();
        // Pointers
        int l = 0, r = 0;
        // Sorting of vectors
        sort(Student.begin(), Student.end());
        sort(Cookie.begin(), Cookie.end());

        // Traverse through both arrays
        while (l < n && r < m) {
            /*If the current cookie can satisfy 
            the current student, move to the 
            next student*/
            if (Cookie[r] >= Student[l]) {
                l++;
            }
            // Move to next cookie
            r++;
        }
        // Return the number of students who got cookies
        return l; 
    }
};
int main() {
    // Example input
    vector<int> Student = {1, 2};
    vector<int> Cookie = {1, 2, 3};

    // Create a Solution object
    Solution solution;

    // Call the findMaximumCookieStudents function
    int result = solution.findMaximumCookieStudents(Student, Cookie);

    // Output the result
    cout << "Number of students satisfied: " << result << endl;

    return 0;
}

```

## Q2 lemonade change


At a lemonade stand, each lemonade costs **$5**.

Customers are standing in a queue to buy from you and order one at a time (in the order specified by the input array `bills`). Each customer will only buy one lemonade and pay with either a **$5**, **$10**, or **$20** bill.

You must provide the correct change to each customer so that the net transaction is that the customer pays **$5**. Note that you do not have any change in hand at first.

Given an integer array `bills` where `bills[i]` is the bill the $i^{th}$ customer pays, return `true` if you can successfully provide correct change to all customers, or `false` otherwise.

### Examples

**Example 1:**

Input: bills = [5,5,5,10,20] Output: true Explanation:

- The first three customers pay $5 each. We collect three $5 bills.

- The fourth customer pays $10. We give back one $5 bill. We now have two $5 bills and one $10 bill.

- The fifth customer pays $20. We need $15 in change. We give back one $10 bill and one $5 bill. We now have one $5 bill and zero $10 bills. All customers received correct change.


**Example 2:**
Input: bills = [5,5,10,10,20] Output: false Explanation:

- The first two customers pay $5 each. We collect two $5 bills.

- The third customer pays $10. We give back one $5 bill. We now have one $5 bill and one $10 bill.

- The fourth customer pays $10. We give back one $5 bill. We now have zero $5 bills and two $10 bills.

- The fifth customer pays $20. We need $15 in change. We must give $10 + $5 or three $5s. We only have two $10s and zero $5s. We cannot provide the change. The answer is false.


### Constraints

* `1 <= bills.length <= 10^4`
* `bills[i]` is either `5`, `10`, or `20`.

### My solution

let us count 5,10,20 but 20 cnt is not needed as we do not provide 20 to anyone

then for 5 and 10 we use cnt.

for 5 simply increase frequency of 5

for 10 we only have one case to provide 5 as return so check if we have 5 or not else return false.

for 20 we have 2 cases 

case 1 either return 10,5 

case 2 return 5,5,5

we choose greedily so we first try to return 10,5 as 5 we will need later and 10 if we need to return we can make by 5's

we check case-1 first and then case-2 

```cpp
class Solution{    
  public:    
    bool lemonadeChange(vector<int>& bills){
        int cnt5=0;
        int cnt10=0;
        for(int bill:bills){
          if(bill==5){
            cnt5++;
          }else if(bill==10){
            cnt10++;
            if(cnt5>0) cnt5--;
            else return false;
          }else if(bill==20){
            if(cnt10>0 && cnt5>0){
              cnt10--;
              cnt5--;
            }else if(cnt5>=3){
              cnt5-=3;
            }else return false;
          }
        }
        return true;
    }
};
```

Time Complexity:The time complexity is O(n) because the code iterates through the bills vector once.

Space Complexity:The space complexity is O(1) because the code uses a fixed number of variables (cnt5, cnt10) regardless of the input size.

## Q3 Jump game-1

Given an array of integers nums, each element in the array represents the maximum jump length at that position. Initially starting at the first index of the array, determine if it is possible to reach the last index. Return true if the last index can be reached, otherwise return false.


Examples:

---
Input : [2, 3, 1, 1, 4]



Output : true



Explanation : We can simply take Jump of 1 step at each index to reach the last index.

---

Input : [3, 2, 1, 0, 4]



Output : false



Explanation : No matter how you make jumps you will always reach the third index (0 base) of the array.

The maximum jump of index three is 0, So you can never reach the last index of array.


### Solution

```cpp
class Solution {
public:
    // To determine if last index is reachable
    bool canJump(vector<int>& nums) {
        
        int maxIndex = 0;


        for (int i = 0; i < nums.size(); i++) {

            if (i > maxIndex) {
                return false;
            }

            maxIndex = max(maxIndex, i + nums[i]);
        }

        return true;
    }
};
```