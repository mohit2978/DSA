# Notes
![alt text](002_3_hard_traversal_ques.jpg)

![alt text](002_3_hard_traversal_ques(1).jpg) ![alt text](002_3_hard_traversal_ques(2).jpg) ![alt text](002_3_hard_traversal_ques(3).jpg) ![alt text](002_3_hard_traversal_ques(4).jpg) ![alt text](002_3_hard_traversal_ques(5).jpg) ![alt text](002_3_hard_traversal_ques(6).jpg) ![alt text](002_3_hard_traversal_ques(7).jpg) 

## Java code

```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    class pair{
        TreeNode node;
        int h;
        int v;
        pair(TreeNode node,int h,int v){
            this.node=node;
            this.h=h;
            this.v=v;
        }
    }
    public List<List<Integer>> verticalTraversal(TreeNode root) {
        LinkedList<pair>q=new LinkedList<>();
        q.addLast(new pair(root,0,0));

        Map<Integer,PriorityQueue<pair>>mp=new HashMap<>();

        int lmv=0,rmv=0;
        while(q.size()>0){
            pair temp=q.removeFirst();
            if(temp.v<lmv) lmv=temp.v;
            if(temp.v>rmv) rmv=temp.v;
            if(mp.containsKey(temp.v)==false){
                mp.put(temp.v,new PriorityQueue<>((a,b)->{
                  return a.h==b.h? a.node.val-b.node.val:a.h-b.h;
                }));
            }
            mp.get(temp.v).add(temp);
            if(temp.node.left!=null){
                q.addLast(new pair(temp.node.left,temp.h+1,temp.v-1));
            }
            if(temp.node.right!=null){
                q.addLast(new pair(temp.node.right,temp.h+1,temp.v+1));
            }
        }
        List<List<Integer>>res=new ArrayList<>();
        int idx=0;
        for(int vlvl=lmv;vlvl<=rmv;vlvl++){
            List<Integer>tres=new ArrayList<>();
            PriorityQueue<pair>pq=mp.get(vlvl);
            while(pq.size()>0){
                pair rem=pq.remove();
                tres.add(rem.node.val);
            }
            res.add(tres);
        }
        return res;
    }
}

```


## Cpp solution ,same as above but good one
```cpp
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // List to store the final result
        vector<vector<int>> result;

        if (root == nullptr) {
            return result;
        }
        map<int, map<int, priority_queue<int, vector<int>, greater<int>>>> nodesMap;
        queue<pair<TreeNode*, pair<int, int>>> q;
        q.push({root, {0, 0}});  // (node, {x, y})
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            TreeNode* node = p.first;
            int x = p.second.first;
            int y = p.second.second;
            nodesMap[x][y].push(node->data);
            if (node->left != nullptr) {
                q.push({node->left, {x - 1, y + 1}});
            }
            if (node->right != nullptr) {
                q.push({node->right, {x + 1, y + 1}});
            }
        }
        for (auto& p : nodesMap) {
            vector<int> column;
            for (auto& q : p.second) {
                while (!q.second.empty()) {
                    column.push_back(q.second.top());
                    q.second.pop();
                }
            }
            result.push_back(column);
        }

        return result;
    }
};
```
# Vertical Order Traversal: Logic & Structure

This implementation is highly efficient because it leverages the C++ Standard Template Library (STL) to handle sorting logic automatically. By using a nested map structure combined with a min-heap, you ensure that the final output adheres to the three required constraints: column order, row order, and value order for ties.

---

### 1. The Data Structure Breakdown
`map<int, map<int, priority_queue<int, vector<int>, greater<int>>>> nodesMap;`

* **Outer `map<int, ...>`**: Manages the **Horizontal Level ($x$)**. Because `std::map` is an ordered associative container, it automatically arranges your columns from left to right (e.g., -2, -1, 0, 1, 2).
* **Inner `map<int, ...>`**: Manages the **Vertical Level ($y$)**. This ensures that within a single column, nodes are processed strictly from top to bottom.
* **`priority_queue<..., greater<int>>`**: This acts as a **Min-Heap**. If multiple nodes exist at the exact same $(x, y)$ coordinate, the min-heap ensures the smallest value is retrieved first, satisfying the tie-breaker rule.

---

### 2. Why this is better than a simple vector
Using a `vector` inside the inner map would require a manual sorting step for every coordinate pair before finalizing the results. By using a **Min-Heap**, you maintain the sorting property dynamically during the insertion phase. This makes the code:
1.  **More elegant**: The logic is declarative rather than imperative.
2.  **Less error-prone**: You avoid forgetting a `.sort()` call on specific sub-vectors.
3.  **Streamlined**: The final extraction involves simply popping elements until the heap is empty.

---

### 3. Complexity Analysis

| Metric | Complexity | Explanation |
| :--- | :--- | :--- |
| **Time Complexity** | $O(N \log N)$ | Each of the $N$ nodes is inserted into maps and a priority queue. Each insertion takes logarithmic time relative to the number of elements. |
| **Space Complexity** | $O(N)$ | You are storing every node exactly once within the nested data structure. |

---

### 4. Implementation Snippet
```cpp
// Example of how the traversal might be structured
void traverse(TreeNode* root, int x, int y, auto& nodesMap) {
    if (!root) return;
    
    // Insert node value into the min-heap at specific (x, y)
    nodesMap[x][y].push(root->val);
    
    // Standard DFS approach
    traverse(root->left, x - 1, y + 1, nodesMap);
    traverse(root->right, x + 1, y + 1, nodesMap);
}
```

![alt text](002_3_hard_traversal_ques(8).jpg) ![alt text](002_3_hard_traversal_ques(9).jpg) ![alt text](002_3_hard_traversal_ques(10).jpg) ![alt text](002_3_hard_traversal_ques(11).jpg) ![alt text](002_3_hard_traversal_ques(12).jpg) ![alt text](002_3_hard_traversal_ques(13).jpg) ![alt text](002_3_hard_traversal_ques(14).jpg) ![alt text](002_3_hard_traversal_ques(15).jpg) ![alt text](002_3_hard_traversal_ques(16).jpg) ![alt text](002_3_hard_traversal_ques(17).jpg) ![alt text](002_3_hard_traversal_ques(18).jpg) ![alt text](002_3_hard_traversal_ques(19).jpg) ![alt text](002_3_hard_traversal_ques(20).jpg) ![alt text](002_3_hard_traversal_ques(21).jpg) ![alt text](002_3_hard_traversal_ques(22).jpg) 


```java

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int data;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int val) { data = val; left = null, right = null }
 * }
 **/

class Solution {
        public void traverseleft(TreeNode root,List<Integer>res){
		if(root==null) return;
		if(root.left==null && root.right==null) return;
		res.add(root.data);
		if(root.left!=null) traverseleft(root.left,res);
		else traverseleft(root.right,res);
	}
	public void traverseleaves(TreeNode root,List<Integer>res){
		if(root==null) return ;
		if(root.left==null && root.right==null) {
		    res.add(root.data);
		    return;
		    
		}
		traverseleaves(root.left,res);
		traverseleaves(root.right,res);
	}

	public void traverseright(TreeNode root,List<Integer>res){
		if(root==null) return;
	    if(root.left==null && root.right==null) return;
		if(root.right!=null) traverseright(root.right,res);
		else traverseright(root.left,res);
		res.add(root.data);
	}
    public List<Integer> boundary(TreeNode root) {
        List<Integer>res=new ArrayList<>();
		if(root==null) return res;
		res.add(root.data);
		traverseleft(root.left,res);
		traverseleaves(root.left,res);
		traverseleaves(root.right,res);
		traverseright(root.right,res);
		return res;
    }
}
```

# Time Complexity Analysis: Boundary Traversal

The overall time complexity of this algorithm is **$O(N)$**, where **$N$** is the total number of nodes in the binary tree. 

### Why is it $O(N)$?
Even though the logic is split into four separate functions, we are essentially performing a few linear passes over different sections of the tree.

---

### 1. Breakdown by Phase
| Phase | Logic | Complexity |
| :--- | :--- | :--- |
| **Root Access** | A simple $O(1)$ operation to add the first node. | $O(1)$ |
| **Left Boundary** | Travels from the root down to the bottom-left. In the worst case (a skewed tree), it visits $H$ nodes (Height of the tree). | $O(H)$ |
| **Leaf Traversal** | This is a full Depth First Search (DFS) that visits **every node** in the tree to check if it's a leaf. | $O(N)$ |
| **Right Boundary** | Similar to the left boundary, it travels from the root down the right side, visiting $H$ nodes. | $O(H)$ |

---

### 2. Final Calculation
The total work done is the sum of these parts:
$$T(n) = O(1) + O(H) + O(N) + O(H)$$

Since the height of a tree ($H$) can at most be $N$ (in a skewed tree) and is usually $\log N$ in a balanced tree, the **$O(N)$** term from the leaf traversal dominates the overall complexity.

---

### 3. Space Complexity
* **$O(H)$**: This is determined by the recursion stack. 
    * In a **balanced tree**, the space complexity is $O(\log N)$.
    * In a **skewed tree**, the space complexity is $O(N)$.
* Additionally, we use **$O(N)$** space to store the result in the `ArrayList`.

---

### Summary for Interviews
> "The time complexity is linear, **$O(N)$**, because the leaf traversal phase must visit every node in the tree exactly once to identify the leaves. The boundary traversals (left and right) only visit nodes along the height of the tree, which is at most $N$ but typically much less."