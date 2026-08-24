# Q1 Add a node to BST

![alt text](Scanned_20260208-1843-03.jpg)
## My code 1

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==nullptr) return root;
        if(root->left==nullptr && root->right==nullptr){
            if(val>root->data) root->right=new TreeNode(val);
            else root->left=new TreeNode(val);
            return root;
        }
        if(root->right==nullptr && val>root->data){
            root->right=new TreeNode(val);
            return root;
        }
        
        if(root->left==nullptr && val<root->data){
            root->left=new TreeNode(val);
            return root;
        }
        if(val>root->data) insertIntoBST(root->right,val);
        else insertIntoBST(root->left,val);
        return root;
    }
};
```
## Perfect code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
// 1. Base Case: We reached the correct insertion point
        if (root == nullptr) {
            return new TreeNode(val);
        }

        // 2. Navigation: Choose left or right
        if (val > root->data) {
            // Re-assign right child to catch the newly created node
            root->right = insertIntoBST(root->right, val);
        } else {
            // Re-assign left child to catch the newly created node
            root->left = insertIntoBST(root->left, val);
        }

        // 3. Return: Return the original root back up the stack
        return root;
    }
};
```
# Q2 Deletion of node in BST 
 
 ![alt text](Scanned_20260208-1843-04.jpg)
  ![alt text](Scanned_20260208-1843-05.jpg)
 Ai given idea i just written code

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==nullptr) return root;
        if(root->data==key){
            if(root->left==nullptr) return root->right;
            if(root->right==nullptr) return root->left;
            TreeNode *leftnode=root->left;
            TreeNode *rnode=root->right;
            TreeNode * lnode=leftnode;
            while(lnode->right!=nullptr){
                lnode=lnode->right;
            }
            lnode->right=rnode;
            return leftnode;
        }
        if(key>root->data) root->right=deleteNode(root->right,key);
        else root->left=deleteNode(root->left,key);
        return root;
    }
};
```
# Q3 target sum or Two sum in BST

### Problem Statement
Given the root of a binary search tree and an integer `k`. Return `true` if there exist two elements in the BST such that their sum is equal to `k` otherwise `false`.

### Examples

**Example 1:**
```text
Input: root = [5, 3, 6, 2, 4, null, 7] , k = 9
Output: true
Explanation: The BST contains multiple pair of nodes that sum up to k.
3 + 6 => 9.
5 + 4 => 9.
2 + 7 => 9.
```

### Constraints
- $1 \leq \text{Number of Nodes} \leq 10^4$
- $-10^4 \leq \text{Node.val} \leq 10^4$
- $-10^5 \leq k \leq 10^5$

Brute be like for every node try to find  node hvaing data (tar-node->data) this is O($n^2$)

Better be get inorder and then apply 2 sum!!O(n)

For next approach see `BST itrator` in 001 notes

So here we use that approach 

My approach 
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/
class BSTIterator {
    stack<TreeNode*> stk1;
    stack<TreeNode*> stk2;

   public:
    BSTIterator(TreeNode* root) {
        TreeNode* curr = root;
        while (curr != nullptr) {
            stk1.push(curr);
            curr = curr->left;
        }
        curr = root;
        while (curr != nullptr) {
            stk2.push(curr);
            curr = curr->right;
        }
    }

    bool hasNext() {
        if (!stk1.empty()) return true;
        return false;
    }
    bool hasPrev() {
        if (!stk2.empty()) return true;
        return false;
    }

    TreeNode * next() {
        if (stk1.empty()) return nullptr;
        TreeNode* node = stk1.top();
        stk1.pop();
        TreeNode* curr = node->right;
        while (curr != nullptr) {
            stk1.push(curr);
            curr = curr->left;
        }
        return node;
    }

    TreeNode * prev() {
        if (stk2.empty()) return nullptr;;
        TreeNode* node = stk2.top();
        stk2.pop();
        TreeNode* curr = node->left;
        while (curr != nullptr) {
            stk2.push(curr);
            curr = curr->right;
        }
        return node;
    }
};
class Solution {
   public:
    bool twoSumBST(TreeNode* root, int k) {
        if(root->left==nullptr && root->right==nullptr) return false;
        BSTIterator it(root);
        TreeNode * v1=it.next();
        TreeNode * v2=it.prev();
        while(v1->data+v2->data!=k){
            if(v1->data +v2->data <k ) v1=it.next();
            else v2=it.prev();
            if(v1==v2) return false;
        }
        return true;
    }
};
```
Approach given 

```cpp
#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// BST Iterator to iterate in the inorder and reverse inorder manner
class BSTIterator {
    stack<TreeNode*> st;
    bool reverse;
    
    // Helper function to push all left or right nodes
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            node = (reverse) ? node->right : node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root, bool isReverse) : reverse(isReverse) {
        pushAll(root);
    }
    
    // Check if there are more elements in the BST
    bool hasNext() {
        return !st.empty();
    }
    
    // Get the next element in the inorder or reverse inorder traversal
    int next() {
        TreeNode* node = st.top();
        st.pop();
        if (!reverse) pushAll(node->right);
        else pushAll(node->left);
        return node->data;
    }
};

class Solution {
public:
    bool twoSumBST(TreeNode* root, int k) {
        if (!root) return false;
        
        // Initialize two iterators
        BSTIterator l(root, false); // normal inorder
        BSTIterator r(root, true);  // reverse inorder
        
        int i = l.next();
        int j = r.next();
        
        while (i < j) {
            if (i + j == k) return true;
            else if (i + j < k) i = l.next();
            else j = r.next();
        }
        return false;
    }
};

int main() {
    // Create the tree
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(7);

    // Create solution instance
    Solution solution;
    int k = 9;
    
    // Check if there exist two elements in the BST such that their sum is equal to k
    bool result = solution.twoSumBST(root, k);
    cout << (result ? "True" : "False") << endl;
    return 0;
}

```
Me: Compare both

AI :
You are comparing a **"Monolithic"** approach (Solution 1) vs. a **"Modular/Flag-based"** approach (Solution 2).

**Solution 2 is significantly better.** It is the standard, "Senior Engineer" implementation that you would be expected to write in an interview at Google, Meta, or Amazon.

Here is the deep dive into why Solution 1 is dangerous and why Solution 2 is the correct pattern.

### 1. The Critical Crash Risk in Solution 1
Look at your `while` loop in Solution 1:

```cpp
TreeNode * v1 = it.next();
TreeNode * v2 = it.prev();

// DANGER ZONE
while(v1->data + v2->data != k) {  // <--- SEGFAULT WAITING TO HAPPEN
    if(v1->data + v2->data < k) v1 = it.next();
    else v2 = it.prev();
    
    if(v1 == v2) return false; 
}
```
### The Bug
* **The Bug:** If `it.next()` runs out of nodes (or `it.prev()` does), it returns `nullptr`.
* The very next line `while(v1->data ...)` tries to access `data` on a `nullptr`.
* **Result:** Runtime Error (Segmentation Fault).
* Even if logic dictates they should meet, relying on that without a `nullptr` check is bad engineering practice.

### 2. Design Pattern: "Separation of Concerns"
* **Solution 1 (Bad):** You jammed two different logic flows (Forward and Backward) into a single class with two stacks.
    * **Memory Waste:** If I only need a forward iterator, I still carry the code/overhead for the backward stack logic.
    * **Complexity:** The class is harder to read. You have duplicated logic (`curr = curr->left` vs `curr = curr->right`) hardcoded in multiple places.
* **Solution 2 (Good):** It uses a single class `BSTIterator` that behaves differently based on a `reverse` flag.
    * **Reusability:** You create two instances: `l` (Forward) and `r` (Backward).
    * **Cleanliness:** The `pushAll` helper function removes code duplication.

### 3. The "Two Pointer" Logic
* **Solution 1:** uses `TreeNode*` pointers.
    * Comparing `v1 == v2` checks memory addresses. This works, but it's brittle.
* **Solution 2:** uses `int` values (data).
    * It uses `next()` to get the integer directly.
    * It maintains the iterator state internally.
    * The loop `while (i < j)` is standard Two Sum logic and much easier to reason about than pointer comparisons.

### Verdict: Adopt Solution 2
* Solution 2 is the canonical "Next Element" iterator pattern.

### Ai code

```cpp
class BSTIterator {
    stack<TreeNode*> st;
    // 'reverse' = true means we are doing "Right -> Root -> Left" (Decreasing order)
    // 'reverse' = false means we are doing "Left -> Root -> Right" (Increasing order)
    bool reverse; 

public:
    BSTIterator(TreeNode* root, bool isReverse) {
        reverse = isReverse;
        pushAll(root);
    }

    bool hasNext() {
        return !st.empty();
    }

    int next() {
        TreeNode* node = st.top();
        st.pop();
        
        // If we are going forward (!reverse), we went Left, processed Root, now go Right.
        // If we are going backward (reverse), we went Right, processed Root, now go Left.
        if (!reverse) pushAll(node->right);
        else pushAll(node->left);
        
        return node->data;
    }

private:
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            // Logic Flip:
            // If reverse is true, we want biggest first, so we keep going Right.
            // If reverse is false, we want smallest first, so we keep going Left.
            if (reverse) node = node->right;
            else node = node->left;
        }
    }
};

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;

        // 1. Initialize Left Iterator (Smallest -> Largest)
        BSTIterator l(root, false);
        // 2. Initialize Right Iterator (Largest -> Smallest)
        BSTIterator r(root, true);

        int i = l.next(); // Smallest value
        int j = r.next(); // Largest value

        // 3. Standard Two Sum Loop
        // We compare values (i < j) because BST contains sorted distinct values (usually).
        // Note: If duplicates exist, this logic still holds for sum finding.
        while (i < j) {
            if (i + j == k) return true;
            
            if (i + j < k) {
                // Sum is too small? Need larger number. Move Left Iterator forward.
                if (!l.hasNext()) break; 
                i = l.next();
            } else {
                // Sum is too big? Need smaller number. Move Right Iterator backward.
                if (!r.hasNext()) break;
                j = r.next();
            }
        }
        return false;
    }
};
```
### Interview Tip
When the interviewer asks **"What is the Time and Space Complexity?"**

* **Time:** $O(N)$.
    * *Wait, isn't next() doing a while loop?* Yes, but mostly `next()` is $O(1)$.
    * **Amortized Analysis:** Each node is pushed onto the stack exactly once and popped exactly once. So for $N$ nodes, total operations are $2N$. Average per `next()` is $O(1)$.

* **Space:** $O(H)$ (Height of the tree).
    * We store the path from root to leaf in the stack. $O(\log N)$ for balanced, $O(N)$ for skewed.

>Note: We can use BST iterator in many questions remember!!!

# Q4 Floor and Ceil in a BST



### **Problem Statement**
Given a binary search tree (BST) and a key, find the **floor** and **ceil** values of that key in the BST.

- **Floor Value:** The largest value in the BST that is smaller than or equal to the key.
- **Ceil Value:** The smallest value in the BST that is greater than or equal to the key.

If either the floor or ceil value does not exist, return -1 for that specific value.

---

### **Example 1**
**Input:** `root = [10, 5, 15, 2, 6]`, `key = 7`  
**Output:** `Floor: 6, Ceil: 10`  
**Explanation:** - The values in the BST are `{2, 5, 6, 10, 15}`.
- The largest value $\le 7$ is 6.
- The smallest value $\ge 7$ is 10.

### **Example 2**
**Input:** `root = [10, 5, 15, 2, 6]`, `key = 1`  
**Output:** `Floor: -1, Ceil: 2`  
**Explanation:** - There is no value $\le 1$ in the BST, so Floor is -1.
- The smallest value $\ge 1$ is 2.

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 10^5]`.
- `1 <= Node.val <= 10^9`
- `1 <= key <= 10^9`

---

![alt text](Scanned_20260208-1843-01.jpg) ![alt text](Scanned_20260208-1843-02.jpg)

Two pass solution
```cpp
/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution{	
    int floorval=-1;
    int ceilval=1e7+1;
    void getFloor(TreeNode* root,int val){
        if(root==nullptr){
            return;
        }
        if(root->data==val){
            floorval=val;
            return;
        }
        else if(root->data<val){
            floorval=max(floorval,root->data);
            getFloor(root->right,val);
        }else getFloor(root->left,val);
    }
      void getCeil(TreeNode* root,int val){
        if(root==nullptr){
            return;
        }
        if(root->data==val){
            ceilval=val;
            return;
        }
        else if(root->data>val){
            ceilval=min(ceilval,root->data);
            getCeil(root->left,val);
        }else getCeil(root->right,val);
    }
	
	public:
		vector<int> floorCeilOfBST(TreeNode* root,int key){
			getFloor(root,key);
            getCeil(root,key);
			ceilval=(ceilval==1e7+1)?-1:ceilval;
            return {floorval,ceilval};
		}
};
```

One pass solution

```cpp
/**
 * Definition for a binary tree node.
 * class TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution{	
    int floorval=-1;
    int ceilval=1e7+1;
      void getCeil(TreeNode* root,int val){
        if(root==nullptr){
            return;
        }
        if(root->data==val){
            ceilval=val;
			floorval=val;
            return;
        }
        else if(root->data>val){
            ceilval=min(ceilval,root->data);
            getCeil(root->left,val);
        }else {
			floorval=max(floorval,root->data);
			getCeil(root->right,val);
		}
    }
	
	public:
		vector<int> floorCeilOfBST(TreeNode* root,int key){
			//getFloor(root,key);
            getCeil(root,key);
			ceilval=(ceilval==1e7+1)?-1:ceilval;
            return {floorval,ceilval};
		}
};
```
# Q5 Inorder Successor and Predecessor in BST



---

### **Problem Statement**
Given a binary search tree (BST) and a key, find the **Inorder Successor** and **Inorder Predecessor** of the given key in the BST.

- **Inorder Predecessor:** The node with the largest value that is strictly smaller than the key.
- **Inorder Successor:** The node with the smallest value that is strictly greater than the key.

If either the predecessor or successor does not exist, return -1 for that specific value.

---

### **Example 1**
**Input:** `root = [10, 5, 15, 2, 6, 12, 20]`, `key = 10`  
**Output:** `Predecessor: 6, Successor: 12`  
**Explanation:** - Inorder traversal: `[2, 5, 6, 10, 12, 15, 20]`
- Node before 10 is 6.
- Node after 10 is 12.

### **Example 2**
**Input:** `root = [10, 5, 15, 2, 6, 12, 20]`, `key = 2`  
**Output:** `Predecessor: -1, Successor: 5`  
**Explanation:** - Inorder traversal: `[2, 5, 6, 10, 12, 15, 20]`
- 2 is the first node, so Predecessor is -1.
- Node after 2 is 5.

---

### **Constraints**
- The number of nodes in the tree is in the range `[1, 10^5]`.
- `1 <= Node.val <= 10^9`
- `1 <= key <= 10^9`

---
Brute--> get inorder get inorder succesor and predecessor

Better--> 3 traversals 

See in morris traversal it is morris predecessor which we use, there we need to go from bottom left to next up!! But here we using general predecessor 

if we have child then normal morris predecessor 

if not then our parent is our predecesoor if we are on right of our parent ,and if we are on left than parent is our succesor

```cpp

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/

class Solution {
    TreeNode* ancpred = nullptr;
    TreeNode* ancsucc = nullptr;
    TreeNode* inorderPred(TreeNode* node) {
        if (node->left == nullptr) return nullptr;
        TreeNode* curr = node->left;
        while (curr->right != nullptr) curr = curr->right;
        return curr;
    }
    TreeNode* inorderSucc(TreeNode* node) {
        if (node->right == nullptr) return nullptr;
        TreeNode* curr = node->right;
        while (curr->left != nullptr) curr = curr->left;
        return curr;
    }
    TreeNode* find(TreeNode* root, int val) {
        if (root == nullptr) return root;
        if (val == root->data) return root;
        if (val > root->data) {
            ancpred = root;
            return find(root->right, val);
        } else {
            ancsucc = root;
            return find(root->left, val);
        }
    }

   public:
    vector<int> succPredBST(TreeNode* root, int key) {
        TreeNode* node = find(root, key);
        vector<int> res(2, -1);
		if(node==nullptr) return res;
        TreeNode* pred = inorderPred(node);
        TreeNode* succ = inorderSucc(node);
        if (pred != nullptr)
            res[0] = pred->data;
        else if (ancpred != nullptr)
            res[0] = ancpred->data;
        if (succ != nullptr)
            res[1] = succ->data;
        else if (ancsucc != nullptr)
            res[1] = ancsucc->data;
        return res;
    }
};
```

# Q6 kth smallest and kth largest in BST 

Brute --> find inorder and find kth smallest and largest 


Optimal--> use BST iterator


```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/
 class BSTIterator {
    stack<TreeNode*> st;
    bool reverse;
    
    // Helper function to push all left or right nodes
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            node = (reverse) ? node->right : node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root, bool isReverse) {
		this->reverse=isReverse;
        pushAll(root);
    }
    
    // Check if there are more elements in the BST
    bool hasNext() {
        return !st.empty();
    }
    
    // Get the next element in the inorder or reverse inorder traversal
    int next() {
        TreeNode* node = st.top();
        st.pop();
        if (!reverse) pushAll(node->right);
        else pushAll(node->left);
        return node->data;
    }
};


class Solution {
public:
	vector<int> kLargesSmall(TreeNode* root,int k){
		vector<int>res;
		BSTIterator it1=BSTIterator(root,false);
		BSTIterator it2=BSTIterator(root,true);
		while(k>0){
			int v1=it1.next();
			int v2=it2.next();
			if(k==1){
				res.push_back(v1);
				res.push_back(v2);
			}
			k--;
		}
		return res;

	}
};
```
## Striver sol

```cpp
#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
  struct TreeNode {
      int data;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
 };
 
class Solution {
public:
    // Function to find the kth smallest element
    int kthSmallest(TreeNode* root, int k) {
        this->k = k;
        this->result = -1;
        inorder(root);
        return result;
    }

    // Function to find the kth largest element
    int kthLargest(TreeNode* root, int k) {
        this->k = k;
        this->result = -1;
        reverse_inorder(root);
        return result;
    }

    // Function to return kth smallest and kth largest elements
    vector<int> kLargesSmall(TreeNode* root, int k) {
        return {kthSmallest(root, k), kthLargest(root, k)};
    }

private:
    int k;
    int result;

    // Helper function for inorder traversal
    void inorder(TreeNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            if (--k == 0) {
                result = node->data;
                return;
            }
            inorder(node->right);
        }
    }

    // Helper function for reverse inorder traversal
    void reverse_inorder(TreeNode* node) {
        if (node != nullptr) {
            reverse_inorder(node->right);
            if (--k == 0) {
                result = node->data;
                return;
            }
            reverse_inorder(node->left);
        }
    }
};

// Main method to demonstrate the function
int main() {
    // Constructing the tree: [3, 1, 4, nullptr, 2]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    root->right = new TreeNode(4);
    
    Solution solution;
    int k = 1;
    vector<int> result = solution.kLargesSmall(root, k);
    
    // Output the result
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [1, 4]
    
    return 0;
}

```

## Ai review


Here sol2 is BST iterator and sol1 is above one !!


This is another classic comparison between **"Competitive Programming Style"** (Solution 1) and **"Software Engineering Style"** (Solution 2).

### **Verdict:** Solution 2 (Iterator Approach) is the winner for Senior Interviews.

Here is the detailed breakdown of why Solution 2 is better, despite Solution 1 being shorter.

### 1. The "State" Trap (Solution 1's Weakness)
Look at how Solution 1 works:

```cpp
// Solution 1
private:
    int k;       // <--- GLOBAL STATE
    int result;  // <--- GLOBAL STATE

    void inorder(...) {
        if (--k == 0) ... // Modifying global state deep in recursion
    }
 ```

* **The Problem:** The class is **Stateful**.
* **Concurrency Risk:** If two threads call `kthSmallest` on the same Solution object at the same time, the `this->k` variable will be overwritten by both, leading to garbage results.
* **Reusability:** You cannot easily pause the traversal. You have to run the recursion from start to finish every time.

### 2. The Power of Abstraction (Solution 2's Strength)
Solution 2 separates the **"Logic of Traversal"** from the **"Business Logic."**

* **The Iterator (The Tool):** Handles the complex stack logic to move through the tree. It doesn't care *why* you are traversing, just *how*.
* **The Solution (The User):** Just asks for `next()`. It doesn't care *how* the tree is traversed, just that it gets the next value.

**Why Interviewers Love This:**
* It shows you know how to build **Reusable Components**.
    * Need to solve "Two Sum BST"? **Use the Iterator.**
    * Need "Flatten BST to List"? **Use the Iterator.**
    * Need "K-th Smallest"? **Use the Iterator.**
* You wrote the Iterator **once**, and now you can solve 10 different LeetCode problems with it. Solution 1 only solves one problem.

### 3. Efficiency & Control
* **Solution 1:** Calls `kthSmallest` (recurses depth $K$), then calls `kthLargest` (recurses depth $K$ again). It effectively does the setup and teardown twice.
* **Solution 2:**

```cpp
while(k > 0) {
    int v1 = it1.next(); // Step forward from left
    int v2 = it2.next(); // Step backward from right
    if (k == 1) res = {v1, v2};
    k--;
}
```

It traverses both ends simultaneously in a single loop. It is cleaner and easier to reason about the runtime.

### Comparison Summary

| Feature | Solution 1 (Recursive) | Solution 2 (Iterator) |
| :--- | :--- | :--- |
| **Code Style** | Scripting / CP Style | Production / Library Style |
| **Thread Safety** | **Unsafe** (Uses shared class variables) | **Safe** (State is encapsulated in local iterator objects) |
| **Flexibility** | **Low** (Hardcoded to find K-th) | **High** (Can pause, resume, or stop anytime) |
| **Memory** | $O(H)$ (Recursion Stack) | $O(H)$ (Explicit Stack) |
| **Verdict** | Good for "Easy" questions. | Required for "System Design" or "Hard" questions. |

### Suggestion for the Interview
If you are asked this question:
1.  Start by mentioning **Solution 2**: *"I can solve this using a custom BST Iterator. This allows us to traverse the tree inorder and reverse-inorder simultaneously, which is cleaner and thread-safe."*
2.  Write the **Iterator Class**.
3.  Implement the logic.

This proves you aren't just memorizing recursive algorithms, but actually designing data structures. **Solution 2 is the way to go.**


### Here is the breakdown of the Time and Space complexity for both approaches.

There is a hidden performance trap in Solution 1 that makes Solution 2 strictly superior.

#### 1. Solution 1: Recursive (DFS)
* **Time Complexity:** $O(N)$ (Linear)
    * **The Trap:** Your recursive code does not stop when it finds the $k$-th element.
    * The line `if (--k == 0) return;` only exits the current function call.
    * The recursion unwinds to the parent, which then proceeds to visit the right subtree.
    * Since `k` is now 0 (or negative), the remaining calls continue to run until the entire tree is visited.
    * **Best Case (Optimized Code):** If you added complex logic to "hard stop" the recursion immediately (e.g., checking `k < 0` at the start of every call), it could be $O(k)$. But as written, it is $O(N)$.
    * **Total Operations:** $2 \times N$ (Once for `kthSmallest`, once for `kthLargest`).

* **Space Complexity:** $O(H)$
    * $H$ is the height of the tree ($\log N$ for balanced, $N$ for skewed).
    * This is the cost of the Recursion Stack stored in memory.

#### 2. Solution 2: Iterator (Stack-based)
* **Time Complexity:** $O(H + k)$
    * **Initialization ($O(H)$):** The constructor goes straight to the leftmost/rightmost node, pushing $H$ nodes onto the stack.
    * **Traversal ($O(k)$):** You call `next()` exactly $k$ times.
    * Each `next()` operation is **Amortized** $O(1)$. (Each node is pushed and popped exactly once).
    * **Why it wins:** It is **"Lazy."** It only does the exact amount of work needed to find the $k$-th element and then stops immediately. It never touches the rest of the tree ($N - k$ nodes are ignored).

* **Space Complexity:** $O(H)$
    * We use an Explicit Stack to simulate recursion.
    * In the worst case (skewed tree), the stack holds $N$ nodes. In a balanced tree, it holds $\log N$.
    * Since you create two iterators, it is technically $2 \times H$, which simplifies to $O(H)$.

### Comparison Summary

| Metric | Solution 1 (Recursive) | Solution 2 (Iterator) | Winner |
| :--- | :--- | :--- | :--- |
| **Time** | $O(N)$ (Visits entire tree) | $O(H + k)$ (Visits only needed nodes) | **Solution 2** |
| **Space** | $O(H)$ (System Stack) | $O(H)$ (Heap Stack) | **Tie** |
| **Control** | Hard to stop early | Easy to pause/stop | **Solution 2** |

### The "Senior Engineer" Insight
If an interviewer asks: **"Can we optimize Solution 1 to be O(k)?"**

You answer: *"Yes, we can add a check `if (k <= 0) return;` at the very top of the recursion to force an early exit. However, Solution 2 (Iterator) achieves this naturally without cluttering the logic with global flags."*


# Q7 Correct BST with two nodes swapped

### Problem Statement
Given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake.

Recover the tree without changing its structure.

### Examples

**Example 1**
```text
Input : root = [1, 3, null, null, 2]
Output : [3, 1, null, null, 2]
Explanation :
3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

```

### Constraints
- $1 \leq \text{Number of Nodes} \leq 10^4$
- $-2^{31} \leq \text{Node.val} \leq 2^{31} - 1$


## Mysol

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/
class BSTIterator {
    stack<TreeNode*> st;
    bool reverse;

    // Helper function to push all left or right nodes
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            node = (reverse) ? node->right : node->left;
        }
    }

   public:
    BSTIterator(TreeNode* root, bool isReverse) {
        this->reverse = isReverse;
        pushAll(root);
    }

    // Check if there are more elements in the BST
    bool hasNext() { return !st.empty(); }

    // Get the next element in the inorder or reverse inorder traversal
    TreeNode* next() {
        if(st.empty()) return nullptr;
        TreeNode* node = st.top();
        st.pop();
        if (!reverse)
            pushAll(node->right);
        else
            pushAll(node->left);
        return node;
    }
};

class Solution {
   public:
    void recoverTree(TreeNode* root) {
        if (root == nullptr) return;
        BSTIterator it = BSTIterator(root, false);
        TreeNode* prev = it.next();

        TreeNode* curr = nullptr;
        TreeNode* first = nullptr;
        TreeNode* second = nullptr;
        while (it.hasNext()) {
            curr = it.next();
            if (prev->data > curr->data) {
                if (first == nullptr) {
                    first = prev;
                    second = curr;
                } else {
                    second = curr;
                    break;
                }
            }
            prev = curr;
            
        }
        if(first && second) swap(first->data, second->data); // swpa if both exists
    }
};
```

### This code is Correct and Interview-Ready.

You have successfully implemented the Morris Traversal logic (using a Stack Iterator instead of threads) to solve the problem in $O(N)$ time and $O(H)$ space.

### Why this is a "Strong Hire" Solution:

* **Modular Design:** You reused your `BSTIterator` class. This shows you write clean, maintainable code rather than a monolithic script.
* **Correct Violation Logic:**
    * You correctly identified that `first` is set only on the first violation.
    * You correctly identified that `second` is updated on every violation (which handles both the adjacent and non-adjacent swap cases).
    * You included the break optimization when the second violation is found.
* **Safety Checks:** You added `if (st.empty()) return nullptr;` in `next()`, which prevents the crash we discussed earlier.


## Striver solution

```cpp
#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *first = nullptr, *middle = nullptr, *last = nullptr, *prev = nullptr;

        // Helper function for inorder traversal
        function<void(TreeNode*)> inorder = [&](TreeNode* node) {
            if (!node) return;

            // Traverse the left subtree
            inorder(node->left);

            // Identify the nodes that are out of order
            if (prev && prev->data > node->data) {
                if (!first) {
                    first = prev;  // First out-of-order node
                    middle = node; // Middle node in case nodes are adjacent
                } else {
                    last = node;   // Last out-of-order node
                }
            }

            prev = node; // Update prev node to the current node
            inorder(node->right); // Traverse the right subtree
        };

        inorder(root); // Perform the inorder traversal to find the two nodes

        // Correct the BST by swapping the misplaced nodes
        if (first && last) {
            swap(first->data, last->data); // Non-adjacent nodes
        } else if (first && middle) {
            swap(first->data, middle->data); // Adjacent nodes
        }
    }
};

// Helper function to insert nodes in the tree for testing purposes
TreeNode* insertLevelOrder(vector<int>& arr, int i) {
    if (i >= arr.size() || arr[i] == -1) return nullptr;
    TreeNode* root = new TreeNode(arr[i]);
    root->left = insertLevelOrder(arr, 2 * i + 1);
    root->right = insertLevelOrder(arr, 2 * i + 2);
    return root;
}

// Helper function to print inorder traversal of the tree
void inorderPrint(TreeNode* root) {
    if (root) {
        inorderPrint(root->left);
        cout << root->data << " ";
        inorderPrint(root->right);
    }
}

int main() {
    // Example input tree: [1, 3, -1, -1, 2]
    vector<int> nodes = {1, 3, -1, -1, 2};
    TreeNode* root = insertLevelOrder(nodes, 0);

    // Solution instance
    Solution sol;
    sol.recoverTree(root);

    // Print corrected tree
    inorderPrint(root);

    return 0;
}

```

Sol2-->BST iterator 
sol1--> striver one

## Ai review

Both solutions are correct and will pass, but **Solution 2 is the superior "Engineering" solution.**

Here is the comparison of why Solution 2 (the Iterator approach) is better for interviews, specifically focusing on the variable logic.

### 1. Variable Logic: The "Middle" vs "Second"
* **Solution 1 (Recursive)** uses three variables: `first`, `middle`, and `last`.
    * It treats "Adjacent Swaps" and "Non-Adjacent Swaps" as two different cases.
    * It requires a complex final check: `if (first && last) swap(...) else if (first && middle) swap(...)`.
* **Solution 2 (Iterator)** uses only two variables: `first` and `second`.
    * It unifies both cases.
    * **Logic:** When we find the first violation, `second` is set to the current node. If we find a second violation later, we just update `second` to the new node.
    * This removes the need for `middle` and the complex `else if` check at the end. It's cleaner logic.

### 2. Stack Depth & Safety
* **Solution 1:** Uses **System Stack (Recursion)**.
    * If the tree is skewed ($N=100,000$), this will crash (**Stack Overflow**) on production systems with limited stack size.
* **Solution 2:** Uses **Heap Memory (Explicit Stack)**.
    * This is robust. It will never cause a Stack Overflow.
    * It allows you to pause the recovery process if needed (e.g., "process 100 nodes, then yield").

### 3. Modularity
* **Solution 1:** The logic is hard-coded into the inorder lambda. You cannot reuse this traversal logic for other problems (like "Kth Smallest").
* **Solution 2:** The `BSTIterator` is a reusable tool. You wrote it once, and now you can use it for Recovery, Search, Kth-Smallest, etc. This shows **Software Design** skills.

### Final Verdict
**Solution 2 is the winner.**

It demonstrates that you can:
* Write modular, reusable code.
* Manage memory explicitly (avoiding recursion depth issues).
* Simplify logic (using 2 pointers instead of 3).

### Interview Tip
If an interviewer asks, **"Why did you use an Iterator instead of simple recursion?"**

You say: *"Recursion is risky for deep trees due to Stack Overflow. The Iterator approach moves the storage to the Heap, which is safer. Also, unifies the logic for adjacent and non-adjacent swaps into a single `second` pointer update, making the code cleaner."*




# Q8 Largest BST in Binary Tree

### Problem Statement
Given a root of Binary Tree, where the nodes have integer values. Return the size of the largest subtree of the binary tree which is also a BST.

A binary search tree (BST) is a binary tree data structure which has the following properties:
* The left subtree of a node contains only nodes with data less than the node's data.
* The right subtree of a node contains only nodes with data greater than the node's data.
* Both the left and right subtrees must also be binary search trees.

### Examples

**Example 1:**
```text
Input: root = [2, 1, 3]
Output: 3
Explanation: The given complete binary tree is a BST consisting of 3 nodes.

```

### Constraints
- $1 \leq \text{Number of Nodes} \leq 10^4$
- $1 \leq \text{Node.val} \leq 10^5$

Q--> why not 4 length include 50 too10,30,40,50. why it output is 3??


This is the most common confusion with this problem!
The reason you cannot include 50 is due to the strict definition of a "Subtree."

### 1. The Definition of "Largest BST Subtree"
In this problem, a "Subtree" is defined as a node and **ALL** of its descendants. You cannot pick and choose which children to keep. It is an **"All or Nothing"** deal.
* If you include Node 50, you **MUST** include both its Left Child (30 and its kids) **AND** its Right Child (20).

### 2. The "Killer" Node: 20
Let's look at the tree rooted at 50:

```text
      50  <-- Root
     /  \
   30    20  <-- The Problem
  /  \
10    40
```
* **BST Rule:** For any node, the Right Child must be **GREATER** than the Root.
* **The Check:** Is 20 > 50?
* **The Result:** **NO**. (20 is smaller than 50).

### 3. The Verdict
Because the Right Child (20) violates the BST rule, the entire triangle rooted at 50 is declared **"Invalid."**
Even though the left side (10, 30, 40) is perfect, and even though 50 is larger than 40, the presence of that single "bad" node (20) on the right ruins the validity for the top root.

**Therefore:**
* **Tree rooted at 50:** **INVALID** (Size 0 for contest purposes).
* **Tree rooted at 30:** **VALID** (10 < 30 < 40). Size = 3.
* **Tree rooted at 20:** **VALID** (Leaf). Size = 1.

**Winner:** Subtree rooted at 30 (Size 3).

Q--> can we use inorder here??

### No
### 1. The "Information Dependency" (Why Preorder/Inorder Fail)
To decide if Node 50 is the root of a valid BST, you need to know:
* Is the Left Child a BST?
* Is the Right Child a BST?
* What is the Max of the Left?
* What is the Min of the Right?

**Inorder Traversal Order:** Left -> Root -> Right
* When you are at the Root, you know about the Left child.
* **BUT**, you haven't visited the Right child yet!
* You cannot make a decision about the Root until you have processed the Right child.

**Post-Order Traversal Order:** Left -> Right -> Root
* When you are at the Root, you have already finished visiting Left **AND** Right.
* You have all the data you need. This is why Post-Order is the only efficient ($O(N)$) way to solve this.

### 2. Can we brute force it with Inorder?
Technically, yes, but it is slow ($O(N^2)$).
* You could write a function `isValidBST(node)` that uses Inorder traversal.
* Then you call this function on every single node in the tree.
* **Result:** $O(N^2)$ Time Complexity. (Too slow for interviews).

### Summary Table

| Traversal | Information Flow | Suitability for "Largest BST Subtree" |
| :--- | :--- | :--- |
| **Inorder** | Left -> Root -> Right | **Fails.** Parent doesn't know about Right child yet. Flattens structure. |
| **Preorder** | Root -> Left -> Right | **Fails.** Parent knows nothing about children yet. |
| **Post-Order** | Left -> Right -> Root | **Perfect.** Children report status to Parent before Parent processes. |
| **Morris** | (Complex Threading) | **Fails.** Modifies tree structure, making it impossible to calculate subtree sizes accurately. |

### Rule of Thumb:
* If the problem asks about **"Subtrees"** (Sum, Average, Count, Largest BST), always use **Post-Order Traversal (DP)**.
* If the problem asks about **"Sequence"** (Kth Smallest, Validate Global BST), use **Inorder**.


```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int data;
 *     TreeNode *left;
 *     TreeNode *right;
 *      TreeNode(int val) : data(val) , left(nullptr) , right(nullptr) {}
 * };
 **/
class NodeValue {
public:
    int maxNode, minNode, maxSize;
    
    NodeValue(int minNode, int maxNode, int maxSize) {
        this->maxNode = maxNode;
        this->minNode = minNode;
        this->maxSize = maxSize;
    }
};
class Solution{
	NodeValue helper(TreeNode* node) {
       
        if (!node) {
            return NodeValue(INT_MAX, INT_MIN, 0);
        }
        
        // Post-Order Traversal: Get info from children first
        auto left = helper(node->left);
        auto right = helper(node->right);
        
        // Logic: Am I a valid BST root?
        // 1. My value must be greater than max of left subtree
        // 2. My value must be smaller than min of right subtree
        if (left.maxNode < node->data && node->data < right.minNode) {
            
            // If valid, I combine the sizes + 1 (myself)
            // My new min is left.min (or myself if left is empty)
            // My new max is right.max (or myself if right is empty)
            return NodeValue(
                min(node->data, left.minNode), 
                max(node->data, right.maxNode), 
                left.maxSize + right.maxSize + 1
            );
        }
        
        // If INVALID, we return a "garbage" range (INT_MIN, INT_MAX)
        // This ensures my parent can NEVER be a valid BST.
        // We propagate the largest size found so far in children.
        return NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
    }
	public:
		int largestBST(TreeNode* root){
			return helper(root).maxSize;
		}
};
```

Q--> is it dp on treees??

YES, this is a classic example of **"DP on Trees"** (Dynamic Programming on Trees).

Specifically, it falls under the category of **Post-Order Traversal DP** (or Bottom-Up DP).

### Why is this considered DP?
In Dynamic Programming, we solve a problem by combining the solutions of its sub-problems.
* **The State:** The `NodeValue` object `{minNode, maxNode, maxSize}` represents the "DP State" for the current subtree.
* **Optimal Substructure:** To know if the tree rooted at `Node` is a valid BST, we strictly depend on the answers from `Node->left` and `Node->right`.
* **Bottom-Up Computation:** We calculate the answer for the leaves first, then pass that information up to the parents.

### How this DP works (The Logic Breakdown)
This code is an optimized $O(N)$ solution that replaces the brute-force $O(N^2)$ approach.

#### State Definition (`NodeValue`):
Each node returns a "Report Card" to its parent containing:
* `minNode`: The smallest value in my entire subtree.
* `maxNode`: The largest value in my entire subtree.
* `maxSize`: The size of the largest BST found inside my subtree.

#### Transitions (The `if` condition):
A node can only extend a BST if three conditions are met:
1. The **Left Child** is a valid BST (implied by the range check).
2. The **Right Child** is a valid BST (implied by the range check).
3. $Left.Max < Current.Value < Right.Min$.

#### The "Clever" Trick (Using Infinity as a Flag):
Instead of adding a boolean `isBST` variable, this code uses `INT_MIN` and `INT_MAX` as "poison."
* If a subtree is **Invalid**, it returns `{INT_MIN, INT_MAX, size}`.
* When the parent checks `left.maxNode < node->data`, it sees `INT_MAX < node->data`, which is **False**.
* The parent immediately knows *"My child is broken, so I am broken too."*

### Complexity Analysis
* **Time Complexity:** $O(N)$. We visit every node exactly once. This is the hallmark of Tree DP.
* **Space Complexity:** $O(H)$. The recursion stack depth.

### Summary
You have correctly identified this as DP on Trees. It is a very common interview pattern. Other problems that use this exact same pattern include:
* **Binary Tree Maximum Path Sum** (LeetCode 124)
* **Diameter of Binary Tree** (LeetCode 543)
* **Balanced Binary Tree** (LeetCode 110)




