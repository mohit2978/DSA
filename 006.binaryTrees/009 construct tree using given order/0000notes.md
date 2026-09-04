# Notes


![alt text](004_construct_tree_using_given_order.jpg)
![alt text](004_construct_tree_using_given_order(1).jpg) ![alt text](004_construct_tree_using_given_order(2).jpg) ![alt text](004_construct_tree_using_given_order(3).jpg) ![alt text](004_construct_tree_using_given_order(4).jpg) ![alt text](004_construct_tree_using_given_order(5).jpg) ![alt text](004_construct_tree_using_given_order(6).jpg) ![alt text](004_construct_tree_using_given_order(7).jpg) ![alt text](004_construct_tree_using_given_order(8).jpg) ![alt text](004_construct_tree_using_given_order(9).jpg) ![alt text](004_construct_tree_using_given_order(10).jpg) 

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

    private TreeNode construct(int[] pre,int preSt,int preEd,int[] in,int inSt,int inEd,HashMap<Integer,Integer>map){
        if(preSt>preEd|| inSt>inEd) return null;
        if(preSt==preEd){
            return new TreeNode(pre[preSt]);
        }
        int prerootel=pre[preSt];
        TreeNode root=new TreeNode(prerootel);
        int inrootelidx=map.get(prerootel);
        int noleftsideel=inrootelidx-inSt;
        int preLeftEd=preSt+noleftsideel;
        TreeNode leftNode=construct(pre,preSt+1,preLeftEd,in,inSt,inrootelidx-1,map);
        TreeNode rightNode=construct(pre,preLeftEd+1,preEd,in,inrootelidx+1,inEd,map);
        root.left=leftNode;
        root.right=rightNode;
        return root;
    }
    public TreeNode buildTree(int[] preorder, int[] inorder) {
         HashMap<Integer,Integer>map=new HashMap<>();
        for(int i=0;i<inorder.length;i++){
            map.put(inorder[i],i);
        }
        return construct(preorder,0,preorder.length-1,inorder,0,inorder.length-1,map);
    }
}

```
## using find 

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
    private int find(int[] arr,int val,int st,int ed){
        for(int i=st;i<=ed;i++){
            if(arr[i]==val) return i;
        }
        return -1;
    }
    private TreeNode construct(int[] pre,int preSt,int preEd,int[] in,int inSt,int inEd,HashMap<Integer,Integer>map){
        if(preSt>preEd|| inSt>inEd) return null;
        if(preSt==preEd){
            return new TreeNode(pre[preSt]);
        }
        int prerootel=pre[preSt];
        TreeNode root=new TreeNode(prerootel);
        int inrootelidx=find(in,prerootel,inSt,inEd);//map.get(prerootel);
        int noleftsideel=inrootelidx-inSt;
        int preLeftEd=preSt+noleftsideel;
        TreeNode leftNode=construct(pre,preSt+1,preLeftEd,in,inSt,inrootelidx-1,map);
        TreeNode rightNode=construct(pre,preLeftEd+1,preEd,in,inrootelidx+1,inEd,map);
        root.left=leftNode;
        root.right=rightNode;
        return root;
    }
    public TreeNode buildTree(int[] preorder, int[] inorder) {
         HashMap<Integer,Integer>map=new HashMap<>();
        for(int i=0;i<inorder.length;i++){
            map.put(inorder[i],i);
        }
        return construct(preorder,0,preorder.length-1,inorder,0,inorder.length-1,map);
    }
}

```

# Binary Tree Reconstruction: Preorder & Inorder

This algorithm reconstructs a unique binary tree by using the properties of Preorder (Root-Left-Right) and Inorder (Left-Root-Right) traversals.

### 1. The Core Logic
The strategy relies on two key observations:
1. **Preorder** always gives you the **Root** first.
2. **Inorder** tells you the size of the **Left and Right subtrees** once you know where the Root is.



---

### 2. Variable Breakdown
In your `construct` method, the pointer logic is as follows:

* **`prerootel`**: The first element of the current preorder range (`pre[preSt]`). This is the root of the current subtree.
* **`inrootelidx`**: The index of that root in the inorder array.
* **`noleftsideel`**: Calculated as `inrootelidx - inSt`. This tells us exactly how many nodes belong to the left subtree.
* **`preLeftEd`**: Calculated as `preSt + noleftsideel`. This defines the boundary for the left subtree nodes within the preorder array.

---

### 3. Complexity Analysis

#### Time Complexity: $O(N^2)$ (Current Version)
While you pass a `HashMap` into the function, your code currently uses a helper function `find()` which performs a linear scan:
* For every node ($N$), you call `find()`, which takes $O(N)$ in the worst case.
* **To optimize to $O(N)$**: Replace `find(in, prerootel, inSt, inEd)` with `map.get(prerootel)`. Since lookups in a HashMap are $O(1)$, the total time would drop to linear.

#### Space Complexity: $O(N)$
* **Data Structure**: You store all $N$ nodes in the `HashMap`.
* **Recursion Stack**: In a skewed tree, the stack depth can go up to $O(N)$. In a balanced tree, it is $O(\log N)$.

---

### 4. Code Optimization Note
Your `buildTree` method already builds a `HashMap`, but your `construct` method isn't using it yet! 

**Change this:**
```java
int inrootelidx = find(in, prerootel, inSt, inEd);

```

![alt text](004_construct_tree_using_given_order(11).jpg) ![alt text](004_construct_tree_using_given_order(12).jpg) ![alt text](004_construct_tree_using_given_order(13).jpg)

![alt text](004_construct_tree_using_given_order(14).jpg) ![alt text](004_construct_tree_using_given_order(15).jpg)

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
     private TreeNode construct(int[] post,int postSt,int postEd,int[] in,int inSt,int inEd,HashMap<Integer,Integer>map){
        if(postSt>postEd|| inSt>inEd) return null;
        if(postSt==postEd){
            return new TreeNode(post[postSt]);
        }
        int postrootel=post[postEd];
        TreeNode root=new TreeNode(postrootel);
        int inrootelidx=map.get(postrootel);
        int noleftsideel=inrootelidx-inSt;
        int postLeftEd=postSt+noleftsideel-1;
        TreeNode leftNode=construct(post,postSt,postLeftEd,in,inSt,inrootelidx-1,map);
        TreeNode rightNode=construct(post,postLeftEd+1,postEd-1,in,inrootelidx+1,inEd,map);
        root.left=leftNode;
        root.right=rightNode;
        return root;
    }
    public TreeNode buildTree(int[] inorder, int[] postorder) {
        HashMap<Integer,Integer>map=new HashMap<>();
        for(int i=0;i<inorder.length;i++){
            map.put(inorder[i],i);
        }
        return construct(postorder,0,postorder.length-1,inorder,0,inorder.length-1,map);
    }
}

```

# Binary Tree Reconstruction: Inorder & Postorder

Reconstructing a tree from Inorder and Postorder uses the "Bottom-Up" property of Postorder. In Postorder (**Left-Right-Root**), the root of any subtree is always the last element of its range.



---

### 1. The Pointer Logic
The transition from `postorder` to `inorder` requires careful index management to separate the left and right subtrees.

* **`postrootel`**: `post[postEd]` (The last element in the current postorder range).
* **`inrootelidx`**: Found via `map.get(postrootel)`. This splits the inorder array into left and right.
* **`noleftsideel`**: `inrootelidx - inSt`. This tells us how many nodes are in the left subtree.
* **`postLeftEd`**: `postSt + noleftsideel - 1`. 
    * We start at `postSt` and jump forward by the number of left-side elements. 
    * We subtract 1 because the range is 0-indexed relative to the start.

---

### 2. Recursive Calls Breakdown
Unlike Preorder, where the right subtree starts immediately after the left, here we must also account for skipping the root at the very end (`postEd - 1`).

| Subtree | Postorder Range | Inorder Range |
| :--- | :--- | :--- |
| **Left** | `[postSt, postLeftEd]` | `[inSt, inrootelidx - 1]` |
| **Right** | `[postLeftEd + 1, postEd - 1]` | `[inrootelidx + 1, inEd]` |

---

### 3. Complexity Analysis

#### Time Complexity: $O(N)$
* **Mapping**: Building the `HashMap` takes $O(N)$.
* **Construction**: Each node is visited exactly once. Because you are using `map.get()` for $O(1)$ lookups, each recursive step is $O(1)$.
* **Total**: $O(N)$.

#### Space Complexity: $O(N)$
* **HashMap**: Stores $N$ elements, taking $O(N)$ space.
* **Recursion Stack**: 
    * $O(H)$ where $H$ is the height.
    * In the worst case (skewed tree), this is $O(N)$.
    * In a balanced tree, this is $O(\log N)$.

---

### 4. Comparison: Preorder vs. Postorder
The primary difference in your implementation is where you "slice" the array:
* **Preorder:** Root is at `preSt`. Left subtree follows at `preSt + 1`.
* **Postorder:** Root is at `postEd`. Left subtree starts at `postSt`. Right subtree ends at `postEd - 1`.



---

### 5. Summary Checklist for Interviews
* [x] **Root Identification**: Last element of postorder.
* [x] **Subtree Size**: Calculated using the Inorder index.
* [x] **Base Case**: If start index > end index, return null.
* [x] **Optimization**: Used a HashMap to avoid $O(N)$ searches in Inorder array.

 ![alt text](004_construct_tree_using_given_order(16).jpg) ![alt text](004_construct_tree_using_given_order(17).jpg) ![alt text](004_construct_tree_using_given_order(18).jpg) ![alt text](004_construct_tree_using_given_order(19).jpg) ![alt text](004_construct_tree_using_given_order(20).jpg) ![alt text](004_construct_tree_using_given_order(21).jpg) 











