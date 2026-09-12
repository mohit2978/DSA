
## Q1. Serialize and Deserialize Binary Tree (LeetCode 297)

**Problem:** Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

**Clarification:** The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

**Example 1:**
```
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
```
```
        1
      /   \
     2     3
          / \
         4   5
```

**Example 2:**
```
Input: root = []
Output: []
```

**Constraints:**
- The number of nodes in the tree is in the range `[0, 10^4]`.
- `-1000 <= Node.val <= 1000`


**The core idea:** convert the tree to a string in preorder (`Node -> Left -> Right`), writing down a special marker (here, `.`) wherever a child is missing. Since preorder always writes the root before its children, and the marker tells us exactly when a subtree has ended, this single string is enough to rebuild the exact original tree shape — no separate "size" or "shape" information needs to be stored.

**Dry run** on `10(20(null,null), 30(null,null))`: walking preorder and writing `.` for every missing child gives `10 20 . . 30 . .` — visit `10`, go left to `20` (write `20`), `20`'s left is missing (write `.`), `20`'s right is missing (write `.`), back up and go right to `30` (write `30`), `30`'s left is missing (write `.`), `30`'s right is missing (write `.`). To rebuild: read tokens one at a time in the same order — `10` becomes the root, then recursively rebuild its left subtree from the *next* tokens (`20`, then `.`, then `.` — so `20` is a leaf), then rebuild its right subtree from whatever tokens are left (`30`, then `.`, then `.` — so `30` is also a leaf). This exact idea, scaled up to a bigger tree, is what the Java solution below implements iteratively.

### A compact pairing: recursive serialize + iterative deserialize

Before the main iterative/recursive approaches below, here is a smaller, self-contained pairing worth knowing: a **recursive** serialize (much shorter to write than the iterative, stack-based one) together with an **iterative**, stack-based deserialize that mirrors the state-machine pattern of the iterative serialize shown further below, just used to *build* the tree instead of *reading* it.

![alt text](<011serialise and kth smallest _240401_001010(1).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(2).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(3).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(4).jpg>)


```java
class Codec {
    private class Pair {
        TreeNode node;
        int state;
    }

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        if (root == null) {
            return "";
        }
        StringBuilder sb = new StringBuilder();
        helper(root, sb);
        return sb.toString();
    }

    void helper(TreeNode node, StringBuilder sb) {
        if (node == null) {
            sb.append(".");
            sb.append(" ");
            return;
        }
        sb.append(node.val);
        sb.append(" ");
        helper(node.left, sb);
        helper(node.right, sb);
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        if (data.length() == 0) {
            return null;
        }
        String[] darray = data.split(" ");
        Stack<Pair> st = new Stack<>();
        Pair rootp = new Pair();
        rootp.node = new TreeNode(Integer.parseInt(darray[0]));
        st.push(rootp);
        int idx = 0;
        while (st.size() > 0) {
            Pair pair = st.peek();
            if (pair.state == 0) {
                idx++;
                pair.state++;
                if (darray[idx].equals(".") == false) {
                    Pair leftp = new Pair();
                    leftp.node = new TreeNode(Integer.parseInt(darray[idx]));
                    pair.node.left = leftp.node;
                    st.push(leftp);
                }
            } else if (pair.state == 1) {
                idx++;
                pair.state++;
                if (darray[idx].equals(".") == false) {
                    Pair rightp = new Pair();
                    rightp.node = new TreeNode(Integer.parseInt(darray[idx]));
                    pair.node.right = rightp.node;
                    st.push(rightp);
                }
            } else {
                st.pop();
            }
        }
        return rootp.node;
    }
}
```

```cpp
class Codec {
    struct Pair {
        TreeNode* node;
        int state;
    };

public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }
        string sb;
        helper(root, sb);
        return sb;
    }

    void helper(TreeNode* node, string& sb) {
        if (node == nullptr) {
            sb += ". ";
            return;
        }
        sb += to_string(node->val) + " ";
        helper(node->left, sb);
        helper(node->right, sb);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.length() == 0) {
            return nullptr;
        }
        vector<string> darray;
        stringstream ss(data);
        string tok;
        while (getline(ss, tok, ' ')) darray.push_back(tok);

        stack<Pair*> st;
        Pair* rootp = new Pair();
        rootp->node = new TreeNode(stoi(darray[0]));
        st.push(rootp);
        int idx = 0;
        while (!st.empty()) {
            Pair* pair = st.top();
            if (pair->state == 0) {
                idx++;
                pair->state++;
                if (darray[idx] != ".") {
                    Pair* leftp = new Pair();
                    leftp->node = new TreeNode(stoi(darray[idx]));
                    pair->node->left = leftp->node;
                    st.push(leftp);
                }
            } else if (pair->state == 1) {
                idx++;
                pair->state++;
                if (darray[idx] != ".") {
                    Pair* rightp = new Pair();
                    rightp->node = new TreeNode(stoi(darray[idx]));
                    pair->node->right = rightp->node;
                    st.push(rightp);
                }
            } else {
                st.pop();
            }
        }
        return rootp->node;
    }
};
```

**Time Complexity: `O(n)`** for both serialize and deserialize — every node is visited/created exactly once. **Space Complexity: `O(n)`** for the output string/token array, plus `O(h)` for the serialize recursion stack or the deserialize's explicit `Stack`/`stack` (both bounded by the tree's height in the well-formed case, though the explicit stack here can briefly hold more than `h` entries since a node's `Pair` stays on the stack across both its state-0 and state-1 steps).

Now, the main approaches:




```java
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
public class Codec {

    private class Pair{
        TreeNode node;
        int state;
        Pair(TreeNode node,int state){
            this.node=node;
            this.state=state;
        }
    }
    public String serialize(TreeNode root) {
        if (root==null) return "";
        StringBuilder sb=new StringBuilder();
        LinkedList<Pair>stk=new LinkedList<>();
        stk.addFirst(new Pair(root,0));
        sb.append(root.val+" ");
        while(stk.size()>0){
            Pair p=stk.getFirst();
            if(p.state==0){
                if(p.node.left!=null){
                    stk.addFirst(new Pair(p.node.left,0));
                    sb.append(p.node.left.val+" ");
                }else sb.append(". ");
                p.state=1;
            }else if(p.state==1){
                if(p.node.right!=null){
                    stk.addFirst(new Pair(p.node.right,0));
                    sb.append(p.node.right.val+" ");
                }else sb.append(". ");                
                p.state=2;
            }else stk.removeFirst();
        }
        return sb.toString();
    }

    // Decodes your encoded data to tree.
    TreeNode helper(String[] data,int[] idx){
        
        if(idx[0]==data.length-1){
            if(data[idx[0]].equals(".")) return null;
            else new TreeNode(Integer.parseInt(data[idx[0]]));
        }
        String s=data[idx[0]];
        idx[0]++;
        if(s.equals(".")==false) {
            TreeNode node=new TreeNode(Integer.parseInt(s));
            node.left=helper(data,idx);
            node.right=helper(data,idx);
            return node;
        }
        
        return null;
    }
    public TreeNode deserialize(String data) {
        if(data.length()==0) return null;
        String[] str=data.split(" ");
        int[] idx=new int[1];
        return helper(str,idx);
    }
}

// Your Codec object will be instantiated and called as such:
// Codec ser = new Codec();
// Codec deser = new Codec();
// TreeNode ans = deser.deserialize(ser.serialize(root));
```

**C++** (same logic, added since only Java existed):
```cpp
class Codec {
    struct Pair {
        TreeNode* node;
        int state;
        Pair(TreeNode* node, int state) : node(node), state(state) {}
    };

public:
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";
        string sb;
        list<Pair> stk;
        stk.push_front(Pair(root, 0));
        sb += to_string(root->val) + " ";
        while (stk.size() > 0) {
            Pair& p = stk.front();
            if (p.state == 0) {
                if (p.node->left != nullptr) {
                    stk.push_front(Pair(p.node->left, 0));
                    sb += to_string(p.node->left->val) + " ";
                } else sb += ". ";
                p.state = 1;
            } else if (p.state == 1) {
                if (p.node->right != nullptr) {
                    stk.push_front(Pair(p.node->right, 0));
                    sb += to_string(p.node->right->val) + " ";
                } else sb += ". ";
                p.state = 2;
            } else stk.pop_front();
        }
        return sb;
    }

    // Decodes your encoded data to tree.
    TreeNode* helper(vector<string>& data, int* idx) {
        if (idx[0] == (int)data.size() - 1) {
            if (data[idx[0]] == ".") return nullptr;
            else new TreeNode(stoi(data[idx[0]]));
        }
        string s = data[idx[0]];
        idx[0]++;
        if (s != ".") {
            TreeNode* node = new TreeNode(stoi(s));
            node->left = helper(data, idx);
            node->right = helper(data, idx);
            return node;
        }
        return nullptr;
    }

    TreeNode* deserialize(string data) {
        if (data.length() == 0) return nullptr;
        vector<string> str;
        stringstream ss(data);
        string tok;
        while (getline(ss, tok, ' ')) str.push_back(tok);
        int idx[1] = {0};
        return helper(str, idx);
    }
};
```

**Time Complexity: `O(n)`** for both `serialize` (every node pushed/popped from the stack a constant number of times) and `deserialize` (every token consumed once). **Space Complexity: `O(n)`** for the output string/token array, plus `O(h)` for the stack/recursion depth.

Q--> here no of nodes is <=$10^4$ so dfs can cause stack overflow??

### You are absolutely correct. $10^4$ is the "Danger Zone" for recursion.

While LeetCode's servers (usually **8MB** stack) will likely let a depth of 10,000 pass, a standard local environment (Visual Studio/Windows default is **1MB**) would crash.

This is a perfect entry for your GitHub repo: **"The Hidden Stack Overflow in Serialize/Deserialize."**

---

### The Math (Why it's risky)
* **Depth:** 10,000 (Worst case skewed tree).
* **Stack Frame:** A `serialize` function is often heavy (string concatenations, stream objects). Let's say conservatively **128 bytes** per frame.
* **Total Usage:**
  $$10,000 \times 128 \text{ bytes} \approx 1.28 \text{ MB}$$

### Result:
* **LeetCode (8MB Stack):** Safe.
* **Local C++ (1MB Stack):** **CRASH** (Stack Overflow).

### The Real Estate: Where does the memory live?

* **DFS (Recursion):** Lives on the **Call Stack**.
    * **Limit:** Extremely small. usually **1 MB** (Windows) to **8 MB** (Linux/Mac).
    * **Cost per Node:** Expensive. Each recursive call creates a "Stack Frame" (Return Address + Registers + Local Variables + Arguments).
    * **Size:** $\approx 64$ to $128$ bytes per node.

* **BFS (Queue):** Lives on the **Heap**.
    * **Limit:** Massive. Restricted only by your RAM (e.g., 8 GB to 32 GB).
    * **Cost per Node:** Cheap. You only store a pointer (`TreeNode*`) in the generic `std::queue` container.
    * **Size:** $\approx 8$ bytes per node (on 64-bit systems).

---

### Scenario A: The Skewed Tree (Linked List)
* **Constraint:** $N = 10,000$. Structure: `1 -> 2 -> 3 -> ...`

**DFS (The Crash):**
* **Depth:** $10,000$.
* **Memory:** $10,000 \times 64 \text{ bytes} \approx \mathbf{640 \text{ KB}}$.
* **Verdict:** **Risky.** If you declare one local `vector` or `string` inside the DFS, you blow the 1MB limit.

**BFS (The Winner):**
* **Width:** $1$ (Only 1 node in the queue at a time).
* **Memory:** $1 \times 8 \text{ bytes} = \mathbf{8 \text{ bytes}}$.
* **Verdict:** Uses almost zero memory.

---

### Scenario B: The Perfect Binary Tree (Wide)
* **Constraint:** $N = 10,000$. Structure: Perfectly balanced.

**DFS:**
* **Depth:** $\log_2(10,000) \approx 14$.
* **Memory:** $14 \times 64 \text{ bytes} \approx \mathbf{1 \text{ KB}}$.
* **Verdict:** **Safe.**

**BFS (The "Heavy" Case):**
* **Width:** The bottom level has $N/2$ nodes ($5,000$).
* **Memory:** $5,000 \times 8 \text{ bytes} \approx \mathbf{40 \text{ KB}}$.
* **Verdict:** **Also Safe.**

> **Wait, isn't 40 KB > 1 KB?** Yes.
> **BUT:** 40 KB is stored on the **Heap** (which has 16 GB of space). It is a drop in the ocean.

---

### The "Production Ready" Conclusion

| Feature | DFS (Stack) | BFS (Queue/Heap) |
| :--- | :--- | :--- |
| **Max Capacity** | ~1 MB (Tiny) | ~16 GB (Huge) |
| **Danger Scenario** | Skewed Trees (Depth $N$) | Dense Graphs / Wide Trees (Width $N$) |
| **Failure Mode** | Stack Overflow (Crash) | OOM (Out of Memory) (Graceful) |

---

### Why "Crash-Proof"?
Even in the worst-case BFS scenario (a massive wide tree), you are storing simple pointers on the Heap.

**To crash a BFS with memory, you would need:**
$$\frac{16 \text{ GB (RAM)}}{8 \text{ bytes (Pointer)}} \approx 2 \text{ Billion nodes}$$

**To crash a DFS with stack overflow, you only need:**
$$\frac{1 \text{ MB (Stack)}}{64 \text{ bytes (Frame)}} \approx 16,000 \text{ nodes}$$

###  Summary:
> "DFS crashes at **16k nodes** (Stack Overflow). BFS survives up to **2 Billion nodes** (RAM limit). Always use BFS for tree serialization in production."

```cpp
class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "null";
        queue<TreeNode*> q;
        q.push(root);
        string res;
        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            if (node) {
                res += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            } else {
                res += "null,";
            }
        }
        return res;
    }

    TreeNode* deserialize(string data) {
        if (data == "null") return nullptr;
        stringstream ss(data);
        string token;
        getline(ss, token, ',');
        TreeNode* root = new TreeNode(stoi(token));
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            if (!getline(ss, token, ',')) break;
            if (token != "null") {
                node->left = new TreeNode(stoi(token));
                q.push(node->left);
            }
            if (!getline(ss, token, ',')) break;
            if (token != "null") {
                node->right = new TreeNode(stoi(token));
                q.push(node->right);
            }
        }
        return root;
    }
};
```

**Java** (same logic, added since only C++ existed):
```java
public class Codec {
    public String serialize(TreeNode root) {
        if (root == null) return "null";
        LinkedList<TreeNode> q = new LinkedList<>();
        q.addLast(root);
        StringBuilder res = new StringBuilder();
        while (!q.isEmpty()) {
            TreeNode node = q.removeFirst();
            if (node != null) {
                res.append(node.val).append(",");
                q.addLast(node.left);
                q.addLast(node.right);
            } else {
                res.append("null,");
            }
        }
        return res.toString();
    }

    public TreeNode deserialize(String data) {
        if (data.equals("null")) return null;
        String[] tokens = data.split(",");
        int i = 0;
        TreeNode root = new TreeNode(Integer.parseInt(tokens[i++]));
        LinkedList<TreeNode> q = new LinkedList<>();
        q.addLast(root);
        while (!q.isEmpty()) {
            TreeNode node = q.removeFirst();
            if (i >= tokens.length) break;
            if (!tokens[i].equals("null")) {
                node.left = new TreeNode(Integer.parseInt(tokens[i]));
                q.addLast(node.left);
            }
            i++;
            if (i >= tokens.length) break;
            if (!tokens[i].equals("null")) {
                node.right = new TreeNode(Integer.parseInt(tokens[i]));
                q.addLast(node.right);
            }
            i++;
        }
        return root;
    }
}
```

**Time Complexity: `O(n)`** for both directions — every node is enqueued/dequeued once. **Space Complexity: `O(n)`** for the output string/token array; the queue itself holds at most `O(w)` nodes at a time (`w` = max width of the tree), which is `O(n)` in the worst case — this lives on the **heap**, not the call stack, which is exactly the BFS-vs-DFS memory trade-off discussed above.


Let us see DFS code too


### The DFS Solution (Preorder: Root $\to$ Left $\to$ Right)


```cpp

class Codec {
public:

    // --- SERIALIZE (Recursion) ---
    // Simple Preorder Traversal
    string serialize(TreeNode* root) {
        if (!root) return "null,";
        // Root -> Left -> Right
        return to_string(root->val) + "," + serialize(root->left) + serialize(root->right);
    }

    // --- DESERIALIZE (Recursion) ---
    TreeNode* deserialize(string data) {
        queue<string> q;
        stringstream ss(data);
        string s;
        // Split string by ',' and put all tokens in a queue
        while(getline(ss, s, ',')) {
            q.push(s);
        }
        return helper(q);
    }

    // Helper Function that does the actual recursion
    TreeNode* helper(queue<string>& q) {
        string s = q.front();
        q.pop();

        // Base Case: If marker is "null", return nullptr
        if (s == "null") return nullptr;

        // Create Node
        TreeNode* node = new TreeNode(stoi(s));
        
        // Recursion Magic:
        // The very next items in the queue are GUARANTEED to be 
        // the Left Subtree (because we serialized in Preorder).
        node->left = helper(q);
        
        // After Left is done, the next items are the Right Subtree.
        node->right = helper(q);

        return node;
    }
};
```

**Java** (same logic, added since only C++ existed):
```java
public class Codec {
    // --- SERIALIZE (Recursion) ---
    // Simple Preorder Traversal
    public String serialize(TreeNode root) {
        if (root == null) return "null,";
        // Root -> Left -> Right
        return root.val + "," + serialize(root.left) + serialize(root.right);
    }

    // --- DESERIALIZE (Recursion) ---
    public TreeNode deserialize(String data) {
        LinkedList<String> q = new LinkedList<>();
        // Split string by ',' and put all tokens in a queue
        for (String s : data.split(",")) {
            q.addLast(s);
        }
        return helper(q);
    }

    // Helper Function that does the actual recursion
    TreeNode helper(LinkedList<String> q) {
        String s = q.removeFirst();

        // Base Case: If marker is "null", return null
        if (s.equals("null")) return null;

        // Create Node
        TreeNode node = new TreeNode(Integer.parseInt(s));

        // Recursion Magic:
        // The very next items in the queue are GUARANTEED to be
        // the Left Subtree (because we serialized in Preorder).
        node.left = helper(q);

        // After Left is done, the next items are the Right Subtree.
        node.right = helper(q);

        return node;
    }
}
```

**Time Complexity: `O(n)`** for both directions — a single Preorder pass. **Space Complexity: `O(n)`** for the token queue, plus `O(h)` for the recursion stack — this is exactly the version whose recursion depth is the risk called out above for very deep, skewed trees.

### Why DFS is "easier" here

* **No "Parent Queue":** In BFS, you have to track "which parent am I attaching this child to?"
* **Automatic State:** In DFS, the recursion stack naturally remembers "I am currently building the left child of Node 5." When `helper(q)` returns, it automatically goes to the next line to build the right child.

---

### The Verdict for Your Repo

**Entry Name:** "Serialize/Deserialize: DFS vs BFS"

* **DFS:** "Elegant, short (15 lines), standard for interviews. **Warning:** Crashes if tree depth > 10k."
* **BFS:** "Robust, scalable, crash-proof. Uses Heap memory. **Trade-off:** Longer code (30+ lines)."

**Both are correct.** If you are in a rush in an interview, write DFS. If the interviewer asks "What if $N=100k$?", switch to BFS logic.








## Q2. Longest Univalue Path (LeetCode 687)


**Problem:** Given the `root` of a binary tree, return *the length of the longest path, where each node in the path has the same value*. This path may or may not pass through the root.

**The length of the path** between two nodes is represented by the number of edges between them.

**Example 1:**
```
Input: root = [5,4,5,1,1,null,5]
Output: 2
Explanation: The shown image shows that the longest path of the same value (i.e. 5).
```
```
        5
      /   \
     4     5
    / \     \
   1   1     5
```

**Example 2:**
```
Input: root = [1,4,5,4,4,null,5]
Output: 2
Explanation: The shown image shows that the longest path of the same value (i.e. 4).
```
```
        1
      /   \
     4     5
    / \     \
   4   4     5
```

**Constraints:**
- The number of nodes in the tree is in the range `[0, 10^4]`.
- `-1000 <= Node.val <= 1000`
- The depth of the tree will not exceed `1000`.

**The idea:** we want the path where all node values are identical, so at any given node, ask: "what's the longest same-value path that extends *downward* from me, going only through my left child?" and the same question going only through my right child. If the left child's value matches this node's own value, the left-extension is `1 + (whatever the left child itself could extend)` — otherwise, going that way breaks the matching-value chain, so the left-extension is `0` (same reasoning for the right side). Every node then checks: does the path that goes *through* me (left-extension + right-extension) beat the best path found so far anywhere in the tree? That "best found so far" is a single running value tracked across the whole recursion, since the actual best univalue path doesn't have to pass through the root — it can be hiding entirely inside some subtree. Whatever a node ultimately hands back up to its own parent, though, can only be *one* of its two extensions (`max(leftExtension, rightExtension)`), since a path handed upward has to continue in a single direction, not branch both ways.

![alt text](<011serialise and kth smallest _240401_001010(10).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(11).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(12).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(13).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(14).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(15).jpg>)


![alt text](<011serialise and kth smallest _240401_001010(16).jpg>) ![alt text](<011serialise and kth smallest _240401_001010(17).jpg>)





**Dry run** on Example 1 (`root = [5,4,5,1,1,null,5]`, tree `5(4(1,1), 5(null,5))`):
- Leaf `1` (left): no children → left/right extensions are both `0`. Running max stays `0`. Returns `0` upward.
- Leaf `1` (right): same — returns `0`.
- Node `4`: its children (`1`, `1`) don't match its own value `4`, so both extensions are `0` regardless of what the children returned. Running max stays `0`. Returns `0` upward.
- Leaf `5` (bottom-right): no children → extensions `0`, `0`. Returns `0`.
- Node `5` (right child of root): its left is missing (extension `0`); its right child is `5`, which **does** match its own value `5`, so its right-extension is `1 + 0 = 1`. Running max updates to `max(0, 0+1) = 1`. Returns `max(0,1) = 1` upward.
- Root `5`: its left child is `4`, which does **not** match root's value `5`, so left-extension is `0`. Its right child is the `5` node just processed, which **does** match, so right-extension is `1 + 1 = 2` (the `1` returned by that child, plus one more edge to reach it). Running max updates to `max(1, 0+2) = 2`.

**Final answer: 2`** — matching the expected output exactly (the path is the two edges `root(5) → right(5) → right.right(5)`).







**A neat implementation trick:** rather than tracking the two extensions (edge-counts) directly, it's convenient to have the helper function count **nodes** instead of edges along the way (so a single node "on its own" reports a count of `1`), and only convert to the requested edge-count once, right at the very end (`answer = nodeCount - 1`). To make the very first (root) call always report its true self-extension regardless of any "parent value" to match against, an out-of-range sentinel value (`-1001`, since the constraints guarantee real values stay within `[-1000, 1000]`) is passed in for that initial call only, meaning "don't filter by any parent value here."

**Java:**
```java
class Solution {
    int len;
    private int helper(TreeNode node, int val) {
        if (node == null) return 0;
        int lx = helper(node.left, node.val);
        int rx = helper(node.right, node.val);
        int mxVal = Math.max(lx, rx) + 1;
        len = Math.max(len, lx + rx + 1);
        if (val != -1001) {
            if (node.val != val) return 0;
            else return mxVal;
        }
        return mxVal;
    }
    public int longestUnivaluePath(TreeNode root) {
        if (root == null) return 0;
        len = 0;
        helper(root, -1001);
        return len - 1;
    }
}
```

**C++:**
```cpp
class Solution {
    int len;
    int helper(TreeNode* node, int val) {
        if (node == nullptr) return 0;
        int lx = helper(node->left, node->val);
        int rx = helper(node->right, node->val);
        int mxVal = max(lx, rx) + 1;
        len = max(len, lx + rx + 1);
        if (val != -1001) {
            if (node->val != val) return 0;
            else return mxVal;
        }
        return mxVal;
    }
public:
    int longestUnivaluePath(TreeNode* root) {
        if (root == nullptr) return 0;
        len = 0;
        helper(root, -1001);
        return len - 1;
    }
};
```

Walking through why this works: `lx` is the recursive call on `node.left`, but passing `node.val` (not the caller's own filter) — so `lx` answers "assuming I only care about paths matching *this* node's value, how many nodes can I extend through `node.left`?" If `node.left`'s own value doesn't match, that call immediately returns `0` (killing that branch), otherwise it returns its own `mxVal` (its longest self-extension, computed unconditionally on the way down). `len` is updated **unconditionally**, on every single call, using this node's own `lx + rx + 1` — the node-count of the longest same-value path *centered at this node* — regardless of whether the node's value happens to match what its own parent wanted. Only the **return value** (what the parent gets to use) is filtered by the `val` parameter.

**Time Complexity: `O(n)`** — a single post-order-style DFS pass, `O(1)` work per node. **Space Complexity: `O(h)`** — only the recursion stack (`h` = height of the tree; worst case `O(n)` for a skewed tree, `O(log n)` for a balanced one).





