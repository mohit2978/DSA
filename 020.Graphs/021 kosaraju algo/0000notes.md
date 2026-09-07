
## Q1. Strongly Connected Components (Kosaraju's Algorithm)

**Practice Question:** GfG — Strongly Connected Components (Kosaraju's Algo)





A directed graph is strongly connected if there is a path between all pairs of vertices. A strongly connected component (**SCC**) of a directed graph is a maximal strongly connected subgraph. For example, there are 3 SCCs in the following graph.

![SCC definition example — 3 strongly connected components: {0,1,2}, {3}, {4}](img-scc-intro-example.svg)

**TC of this is `O(V+E)`.**

 ### 1. The Core Concept: "The Round Trip"
A **Strongly Connected Component (SCC)** is a group of nodes in a directed graph where you can get from any node to any other node within that group and get back.

Think of it as **"Two-Way Street" Zones**:
* If you can drive from $A \to B$ and find a way back from $B \to A$, then $A$ and $B$ are in the **same SCC**.
* If you can drive from $A \to B$ but can never return to $A$ (because the roads are one-way), then $A$ and $B$ are **NOT** in the same SCC.

### 2. Visualizing It (The "Islands" Analogy)
Imagine a directed graph as a collection of **Islands** connected by **One-Way Bridges**.

* **Inside an Island (The SCC):**
    * You can travel freely between any two points. It is a "cycle-rich" environment. Every node effectively belongs to a cycle with every other node.
* **Between Islands:**
    * Once you cross a bridge from Island 1 to Island 2, you can never go back.
    * This structure implies that if you shrink each SCC into a single "Super Node," the resulting graph is always a **DAG (Directed Acyclic Graph)**.

### 3. Real-World Examples
* **Social Networks (Twitter/X):**
    * **SCC:** A "Clique" where everyone follows everyone else. User A follows B, B follows C, and C follows A.
    * **Not SCC:** You follow a celebrity, but they don't follow you back. You are not in the same component.
* **The Web:**
    * **SCC:** A cluster of related Wikipedia pages that all link to one another.
    * **Not SCC:** A page that links to a PDF download. The PDF cannot link back to the page.

### Summary
* **Undirected Graph:** Being "Connected" is simple (is there a path?).
* **Directed Graph:** Being "Strongly Connected" is strict (is there a round trip?).
* **Key Property:** An SCC is the **largest possible** group of nodes that are all mutually reachable.
 
Undirected graph mein bhi chotay leke chota hi connected component; **Kosaraju is for Strongly Connected Component**.

**Example** (10-node graph): We can reach `6,7,8` through `9`; `9,7,8` through `6`; `9,6,8` through `7`; `9,6,7` through `8`. So `{6,7,8,9}` is strongly connected component.

Now see: `6` se `1` nahi ja sakte, `6` se `0` nahi ja sakte, toh unko strongly connected component nahi kahenge (`1` and `0` are not part of that SCC, even though there's an edge coming *into* `6` from `1` — the edge only goes one way).

### GfG Problem — Strongly Connected Components (Kosaraju's Algo)

**Difficulty:** Medium

Given a Directed Graph with `V` vertices (Numbered from `0` to `V-1`) and `E` edges, Find the number of strongly connected components in the graph.

**Example 1:**

```
Input: graph with edges 0->1, 1->2, 2->0, 0->3, 3->4

Output: 3
```

**Explanation:** We can clearly see that there are 3 Strongly Connected Components in the Graph — `{0,1,2}`, `{3}`, `{4}`.

**Expected Time Complexity:** `O(V+E)`.
**Expected Auxiliary Space:** `O(V)`.

**Constraints:**
```
1 <= V <= 5000
0 <= E <= (V*(V-1))
0 <= u, v <= N-1
Sum of E over all testcases will not exceed 25*10^6
```
**Remember: Kosaraju is for SCC (Only in Directed Graph).**

### Final Code (Java)

```java
class Solution
{
    private void dfs(int v,ArrayList<ArrayList<Integer>> adj,int[] vis,LinkedList<Integer>stk){
        vis[v]=1;
        for(var v1:adj.get(v)){
            if(vis[v1]==0){
                dfs(v1,adj,vis,stk);
                    
            }
        }
        
        stk.addFirst(v);
    }
       private void dfs2(int v,ArrayList<ArrayList<Integer>> adj,int[] vis){
        vis[v]=2;
        for(var v1:adj.get(v)){
            if(vis[v1]==1){
                dfs2(v1,adj,vis);
                    
            }
        }
        
    }
    private void transpose(ArrayList<ArrayList<Integer>> adj,ArrayList<ArrayList<Integer>> adj2){
       for(int i=0;i<adj.size();i++){
           for(int n:adj.get(i)){
               adj2.get(n).add(i);
           }
       }
    }
    //Function to find number of strongly connected components in the graph.
    public int kosaraju(int V, ArrayList<ArrayList<Integer>> adj)
    {
        LinkedList<Integer>stk=new LinkedList<>();
        int[] vis=new int[V+1];
        for(int v=0;v<V;v++){
            if(vis[v]==0){
                dfs(v,adj,vis,stk);
            }
        }
        ArrayList<ArrayList<Integer>> adj2=new ArrayList<>();
        for(int v=0;v<adj.size();v++){
            adj2.add(new ArrayList<>());
        }
        transpose(adj,adj2);
        int count=0;
        while(stk.size()>0){
            int el=stk.removeFirst();
            if(vis[el]==1){
                dfs2(el,adj2,vis);
                count++;
            }
        }
        return count;
    }
}
```

### Code (C++)

```cpp
class Solution {
private:
    void dfs(int v, vector<vector<int>>& adj, vector<int>& vis, list<int>& stk) {
        vis[v] = 1;
        for (int v1 : adj[v]) {
            if (vis[v1] == 0) {
                dfs(v1, adj, vis, stk);
            }
        }
        stk.push_front(v);
    }

    void dfs2(int v, vector<vector<int>>& adj, vector<int>& vis) {
        vis[v] = 2;
        for (int v1 : adj[v]) {
            if (vis[v1] == 1) {
                dfs2(v1, adj, vis);
            }
        }
    }

    void transpose(vector<vector<int>>& adj, vector<vector<int>>& adj2) {
        for (int i = 0; i < (int)adj.size(); i++) {
            for (int n : adj[i]) {
                adj2[n].push_back(i);
            }
        }
    }

public:
    // Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<vector<int>>& adj) {
        list<int> stk;
        vector<int> vis(V + 1, 0);
        for (int v = 0; v < V; v++) {
            if (vis[v] == 0) {
                dfs(v, adj, vis, stk);
            }
        }

        vector<vector<int>> adj2(V);
        transpose(adj, adj2);

        int count = 0;
        while (!stk.empty()) {
            int el = stk.front();
            stk.pop_front();
            if (vis[el] == 1) {
                dfs2(el, adj2, vis);
                count++;
            }
        }
        return count;
    }
};
```

**Complexity:**
- **Time:** `O(V + E)` — Pass 1 (DFS + push to stack) visits every vertex and edge once: `O(V+E)`. Building the transpose is `O(V+E)` (one pass over every edge). Pass 2 (DFS on the transposed graph, popping from the stack) again visits every vertex and edge at most once across all the calls combined: `O(V+E)`. Total: `O(V+E)`.
- **Space:** `O(V)` — the `vis` array and the stack both hold at most `V` entries; the transposed adjacency list `adj2` is `O(V+E)` but that's usually counted as part of the input/output representation rather than auxiliary space, matching the problem's stated `O(V)` expected auxiliary space.

### 1. The Problem: "The Leak"
Imagine you have two castles, **Castle A** and **Castle B**.
Inside each castle, there are many rooms connected to each other (Strongly Connected).
There is a one-way bridge from **Castle A to Castle B**.

**If you run DFS on Castle A in the original graph:**
* You explore all the rooms in Castle A.
* Then, you accidentally cross the bridge and explore Castle B too.
* **Result:** Your DFS thinks A and B are one giant castle. You failed to separate them. The DFS "leaked" out.

### 2. The Solution: "The Trap" (Transpose)
Now, imagine you reverse the direction of every bridge (**Transpose**).
The bridge now goes from **Castle B $\to$ Castle A**.

**Now, run DFS on Castle A again:**
* You explore all the rooms in Castle A. (You can still move around inside because cycles work both ways).
* You try to leave Castle A. **You can't.**
* The bridge to B is gone (it now points towards you).
* Any other bridges that used to lead out now lead in.
* **Result:** The DFS is **trapped** inside Castle A. It marks only Castle A as visited and stops.
* **Success:** You have successfully counted "1 Component" and isolated it from the rest.

### 3. Why the Stack Matters
You might ask: *"Wait, if the bridge is now B $\to$ A, what if I start DFS at B? Won't I leak into A?"*

**Yes, you would.**
That is why the **First Pass (Stack)** is critical.
* The stack ensures you always start with **Castle A** (the one that was originally upstream).
* In the Reversed Graph, Castle A becomes a **"Sink"** (a dead end).
* By starting with the dead end, you guarantee you can't go anywhere else.

### Summary
* **Original Graph:** $A \to B$. DFS on A "leaks" into B.
* **Transposed Graph:** $B \to A$. DFS on A is trapped. It hits a wall because the edge points backward.

> **The Code:** `dfs2` is essentially walking around a room with all the doors locked from the outside. It finds everyone in the room but cannot leave.



### The "Component" Definition (For SCCs / Kosaraju)

In algorithms like **Kosaraju's** or **Tarjan's**, we don't just look at single nodes; we look at groups of nodes (**Strongly Connected Components**).

Imagine **"Source Island"** and **"Sink Island"**:

* **Source Component:**
    * The "Top of the Hill."
    * You can drive from here to *anywhere else* in the graph.
    * But you can never come back. Once you leave a Source Component, you fall down the hill.
    * **No incoming edges** from other islands.

* **Sink Component:**
    * The "Bottom of the Pit."
    * You can arrive here from *anywhere*.
    * But you can never leave. You are trapped.
    * **No outgoing edges** to other islands.

###  Why Kosaraju flips them?
This is the **"Aha!" moment** for the algorithm.

* **Original Graph:**
    * DFS naturally flows from **Source $\to$ Sink**.
    * If you start at the Source, you "leak" into the Sink. You can't separate them.

* **Transposed (Reversed) Graph:**
    * The **Source** becomes a **Sink**. (The "Tap" becomes a "Drain").
    * The **Sink** becomes a **Source**.
    * Now, if you start at the original Source (which is now a Sink), you are **trapped**. You can't flow anywhere. You are isolated. 

### Summary:
* **Source:** The start. "I can reach everyone, but nobody can reach me."
* **Sink:** The end. "Everyone can reach me, but I can't reach anyone."

### The stack stores nodes based on who finishes LAST.

#### 1. The "Boss" Analogy
Think of the DFS as a manager making phone calls.

* **Component A (Source)** calls **Component B (Sink)**.
* A cannot hang up the phone until B is done talking.
* Therefore, **B finishes first** and goes into the stack (bottom).
* **A finishes last** and goes into the stack (top).

#### 2. The Result on the Stack
Because the "Source Component" (the one that reaches everyone else) has to wait for everyone downstream to finish, its nodes end up at the **TOP** of the stack.

#### 3. Why is this perfect for Pass 2?
* **Top of Stack = Source Component.**
* **Transposed Graph:** The Source becomes a **Sink** (a trap).
* So, when you pop from the top of the stack, you are guaranteed to be starting in a **Trap**. You can't leak out to the rest of the graph because the edges are reversed.

#### Summary:

* **Stack Bottom:** The "Sink" components (finished early).
* **Stack Top:** The "Source" components (finished last).
* **Why?** Because the Source is responsible for visiting the Sink, so it must stay "active" longer.

Q--> A scc is always  a cycle

No, that is a common misconception. A Strongly Connected Component (SCC) is **NOT** always a simple cycle.

Here is the "Senior Engineer" distinction:

### 1. The Distinction: Cycle vs. SCC
* **A Cycle:** A simple path that starts and ends at the same node (e.g., $A \to B \to C \to A$).
* **An SCC:** A group of nodes where **everyone can reach everyone else**.

### 2. Why they are different (Counter-Examples)

**Case A: The "Messy Web" (Not a simple cycle)**
Imagine 4 nodes: $A, B, C, D$.
* $A \to B$
* $B \to C$
* $C \to A$ (This is a cycle $A-B-C$).
* **Now add extra edges:** $A \to C$ and $B \to A$.
* **Result:** This is a dense web of connections. You can go $A \to C \to A$, or $A \to B \to A$.
* **Verdict:** This whole group $\{A, B, C\}$ is an SCC, but it is much more complex than a single loop. It contains *multiple* overlapping cycles.

**Case B: The "Single Node" (Trivial SCC)**
Imagine a graph with just one node $A$ and no edges at all.
* **Is it an SCC?** Yes. By definition, $A$ can reach itself (trivial path of length 0).
* **Is it a cycle?** No. There are no edges.

### 3. The Relationship
* **Every Cycle is part of an SCC:** If you have a cycle, all nodes in that cycle belong to the same SCC.
* **Not every SCC is a Cycle:** An SCC can be a single node, or a complex combination of many intersecting cycles.

### Summary Table

| Feature | Simple Cycle | Strongly Connected Component (SCC) |
| :--- | :--- | :--- |
| **Structure** | A single loop (Ring). | A "blob" of nodes with full connectivity. |
| **Complexity** | Simple ($N$ edges for $N$ nodes). | Can be Dense ($N^2$ edges possible). |
| **Trivial Case** | Must have at least 1 edge ($A \to A$). | Can have 0 edges (Single isolated node). |
| **Logic** | $A \to \dots \to A$. | $\forall u,v: \text{path}(u \to v) \text{ AND } \text{path}(v \to u)$. |

> **Interview Tip:**
> If an interviewer asks this, say: *"An SCC is a set of mutually reachable nodes. While it **contains** cycles (if size > 1), it is often a complex union of multiple overlapping cycles, not just a single ring."*


## Q2. Find a Mother Vertex

**Practice Question:** GfG — Mother Vertex



Given a Directed Graph, find a Mother Vertex in the Graph (if present). A Mother Vertex is a vertex through which we can reach all the other vertices of the Graph.

**Example 1:**

```
Input: graph with edges 1->0, 0->2, 0->3, 2->1, 3->4

Output: 0
```

**Explanation:** According to the given edges, all nodes can be reached from nodes 0, 1 and 2. But, since 0 is minimum among 0, 1 and 3, so 0 is the output.

![Mother Vertex example — node 0 can reach every other node](img-mother-vertex-example.svg)

**Example 2:**

```
Input: graph with edges 0->1, 2->1

Output: -1
```

**Explanation:** According to the given edges, no vertices are there from where we can reach all vertices. So, output is -1.

**Expected Time Complexity:** `O(V + E)`
**Expected Space Complexity:** `O(V)`

**Constraints:** `1 <= V <= 500`

### Dry Run — "Last Man Standing"

**No need of Stack!** 1st-ly, DFS mein jo last root visited, choose voh, use Mother Vertex ka candidate chuno.

For a 6-node graph `0->1, 1->2, 2->0, 2->3, 3->4->5, 5->3`: at first we call `DFS(0)`, which visits `{0, 1, 2}`. `3` can be Mother Vertex, as none ek visited jo pehle se hai — use call karo, discover it as new, `visit(3)`.

**Trace for GfG Example 1** (`1->0, 0->2, 0->3, 2->1, 3->4`):

```
i=0: not visited -> DFS(0). 0 reaches {0,2,1,3,4} — everyone.
     Loop finishes without ever starting a fresh DFS again.
     Candidate = 0.
```

**Trace for a different-order graph** (same edges, loop hits `2` before `0`):

```
i=0: 0 -> reach dekho (0's own neighbour) hai already visited hai — no, wait re-derive:
     If node 2 is visited first: DFS(2) -> visits {2, 1, 0, 3, 4} since 2->1->0->{2,3}->3->4 (all reachable via 2's own chain)
     Candidate = 2, and everyone else ends up visited too.
```

*(Regardless of which node the loop reaches first, whichever node's DFS ends up covering the whole graph becomes — and stays — the final candidate, since no later `i` can trigger a fresh DFS once everything is already visited.)*


**Brute-force solution can be:** har vertex se DFS call karo, check karo ki sab visit ho rahe hain ya nahi. `O(V(V+E))`.

![alt text](image.png)

### 1. What is a "Strongly Connected Component" (SCC)?
An **SCC** is a group of nodes where everyone can reach everyone else. It is like a "Round Trip" zone.
* If you start at **0**, you can go to **2**, then **1**, and back to **0**.
* If you start at **1**, you can go to **0**, then **2**, and back to **1**.

In your specific image, the nodes `{0, 1, 2}` form a single SCC. They are locked together in a cycle.

### 2. The "Super Node" View (Condensation Graph)
To understand the "First" SCC, imagine shrinking that cycle into a single big dot called **Team A**.

$$\text{Team A } (\{0, 1, 2\}) \to \text{Node 3} \to \text{Node 4}$$

In this simplified view (called a **DAG** or **Condensation Graph**):
* **Team A** is at the very top. It has outgoing edges but no incoming edges from the rest of the world (Nodes 3 or 4).
* Because it is at the top, it is called the **Source Component** (or the "First" SCC).

### 3. Why is this important for the Mother Vertex?
A **Mother Vertex** must live inside this "First" SCC (Source Component).

**The Rule:** If any node in the Source SCC can reach the rest of the graph, then **every** node in that SCC can also reach the rest of the graph.

In your example:
* Since **0** can reach **3** and **4**...
* And **1** can reach **0** (because they are in the same SCC)...
* Then **1** can effectively reach **3** and **4** too.

### Summary
* The **"First SCC"** is simply the group of nodes at the start of the flow.
* **In your image:** The cycle `{0, 1, 2}` is the First SCC.
* **The Result:** Any node inside this group (0, 1, or 2) is a valid Mother Vertex. The algorithm is happy finding any of them.

### The Intuition: "The Cleanup Crew"
Imagine the Mother Vertex is the **"Boss"** and all other nodes are **"Employees"**. The Boss can call (reach) every Employee, but Employees cannot call the Boss.

We iterate through our list of people ($0$ to $V-1$) and ask them to "Start a Phone Chain" (DFS).
There are only two scenarios:

**Scenario 1: We pick the "Boss" (Mother) First**
* We start DFS from the Boss.
* The Boss calls Employee A, who calls Employee B, etc.
* Since the Boss can reach everyone, this single DFS traversal visits every single node in the graph.
* The loop finishes. We never start a DFS again because everyone is already visited.
* **Result:** The Boss was the last (and only) node to start a DFS. **Candidate = Boss.**

**Scenario 2: We pick an "Employee" (Child) First**
* We start DFS from Employee A.
* Employee A can only reach their own small team (or nobody). They finish their calls. We mark them as visited.
* The loop continues. We pick Employee B. They call their team. We mark them visited.
* Finally, we reach the Boss in the loop.
* The Boss looks at their list. They see Employee A (Already Visited). They see Employee B (Already Visited).
* The Boss marks themselves as visited and finishes.
* **Result:** The Boss was the last node to start a DFS. **Candidate = Boss.**

---

### The "Deep Dive" (For the Interviewer)
If the interviewer asks "Why?", draw this simple graph: `1 -> 0` and `1 -> 2`.
(Node 1 is the Mother).

Now trace the loop: `for (int i = 0; i < 3; i++)`

**Step 1: i = 0**
* Is 0 visited? **No.**
* Start `DFS(0)`.
* 0 points to nothing. DFS ends.
* **Current Candidate:** 0
* **Status:** 0 is visited. 1, 2 are unvisited.

**Step 2: i = 1 (The Mother)**
* Is 1 visited? **No.**
* Start `DFS(1)`.
* 1 tries to go to 0. 0 is already visited. (Do nothing).
* 1 goes to 2.
* Start `DFS(2)`.
* 2 points to nothing. DFS ends.
* 1 finishes.
* **Current Candidate:** 1
* **Status:** 0, 1, 2 are all visited.

**Step 3: i = 2**
* Is 2 visited? **Yes.**
* **SKIP.**

**Final Result:** The last node that actually ran code was **1**.

---

### The "SCC / DAG" Explanation (The Senior Logic)
This is the technical answer that gets you hired.

* **Topological Order:** If you view the graph as a hierarchy, the Mother Vertex sits at the very top (**Source**). The nodes that cannot reach anyone else sit at the bottom (**Sink**).
* **The Rule of DFS:**
    * If you process a **Child (Sink)** first, it gets marked "Visited" and is removed from the pool. The Mother is still waiting in the list.
    * If you process the **Mother (Source)** first, it reaches down and marks the Child "Visited". The Child is removed from the pool (the loop skips it).
* **The Inevitable Conclusion:**
    * A Child node cannot eliminate a Mother node from the loop (because Children can't reach Mothers).
    * A Mother node always eliminates the Children (by visiting them).
    * Therefore, the Mother Vertex (if it exists) is always the "Last Man Standing" in the loop. It is either processed last, or it is processed early and eliminates everyone else from being processed at all.

### Summary Phrase for the Interview
> "A Mother Vertex is like the root of a tree. If I start DFS from the leaves (children) first, I only mark small sections. The root is still unvisited. Eventually, I must visit the root. Once I visit the root, it covers everything else. So, the root is always the last unvisited node that triggers a new traversal."

 ```java

class Solution
{
    //Function to find a Mother Vertex in the Graph.
    private void dfs(int v,int[] vis, ArrayList<ArrayList<Integer>>adj,int vis_val,int n_vis_val){
        vis[v]=vis_val;
        for(var i:adj.get(v)){
            if(vis[i]==n_vis_val){
                dfs(i,vis,adj,vis_val,n_vis_val);
            }
        }
        
    }

    public int findMotherVertex(int V, ArrayList<ArrayList<Integer>>adj)
    {
        int potential_mother_vertex=-1;
        int[] vis=new int[V+1];
        for(int i=0;i<V;i++){
            if(vis[i]==0){
                potential_mother_vertex=i;
                dfs(i,vis,adj,1,0);
            }
        }
        dfs(potential_mother_vertex,vis,adj,2,1);
        for(int i=0;i<V;i++){
            if(vis[i]==1) return -1;
        }
        return potential_mother_vertex;
    }
}
```
 This is a clever and optimized implementation of the **Mother Vertex** finding algorithm.
Instead of the standard approach (checking every node or resetting the visited array), this code uses a **Two-Pass DFS strategy** with a "state toggle" optimization to save space and time.

Here is the "Senior Engineer" breakdown of the logic.

### The Algorithm: "Last Man Standing"
The core mathematical property used here is:

> If a Mother Vertex exists, it must be the **last vertex** from which a DFS traversal was initiated in a full graph scan.

**Why?**
* If a node `U` is a Mother Vertex, it can reach everyone.
* If we start a DFS from `U` early, it visits everyone, and the loop finishes.
* If we start DFS from other nodes first, they will visit whatever they can. Eventually, we must process `U`. Once we process `U`, it will visit everything remaining.

Therefore, the last node that triggers a fresh DFS call is our **only candidate** for being the Mother Vertex.
 

 ###  Complexity Analysis

* **Time Complexity:** $O(V + E)$
    * We run DFS exactly twice. Once to find the candidate, once to verify. Both are linear traversals.
* **Space Complexity:** $O(V)$
    * Recursion stack + `vis` array.
* **Senior Note:** This implementation is space-optimal because it reuses the `int[] vis` array for both passes instead of allocating a second one.

### Summary Verdict
* This is a **Production-Grade** solution.
* It avoids $O(V \cdot E)$ naive approaches.
* It uses the "Last Finished Vertex" property of Directed Graphs (related to Kosaraju's Algorithm for SCCs).
* It manages state cleanly (`0` -> `1` -> `2`) to avoid re-allocations.


Q--> a mother vertex will never be visited by any node other than is SCC??

Ans-->
### Yes, you are exactly right.
This is a fundamental property of a Mother Vertex.

### The Logic (Proof by Contradiction)
Let's prove why a node outside the Mother Vertex's Strongly Connected Component (SCC) can never visit the Mother Vertex.

**Assume the opposite:** Imagine there is a node **A** that is outside the Mother's SCC, but **A** can somehow reach the Mother Vertex (**M**).

1.  **Path:** $A \to \dots \to M$
2.  **Recall the definition of a Mother Vertex:** A Mother Vertex must be able to reach every node in the graph.
3.  **Therefore:** M must be able to reach A.
4.  **Path:** $M \to \dots \to A$

**The Result:**
* If **A** can reach **M**, and **M** can reach **A**, they are stuck in a **Cycle**.
* By definition, any two nodes in a cycle belong to the **SAME SCC**.

**The Contradiction:**
* We started by saying **A** was **outside** the SCC.
* But the logic proves **A** must be **inside** the SCC.
* **Therefore, it is impossible for an "outsider" to reach the Mother Vertex.**

---

### The "Source Component" Visualization
If you condense the graph into a **DAG (Directed Acyclic Graph)** of SCCs:

* **The Mother SCC (Source):** It sits at the very top of the hierarchy. It has arrows pointing **out** to the rest of the graph.
* **The Rest of the Graph:** It is "downstream." Arrows point **away** from the Mother SCC.
* **Incoming Edges?** A Source Component (by definition) has **Zero Incoming Edges** from other components.

### Summary
> If an outsider could visit the Mother, the Mother wouldn't be at the "top" of the graph anymore (because someone would be above it), and it would fail to be a Mother Vertex to that node above it.


Q--> can i say source cant be reached by anyone and sink by everyone so source will be always on TOS at end of dfs and at last vertex visited in mother vertex??


 Connecting the Dots: Topological Sort, SCCs, and Mother Vertex

Yes, you can absolutely say that. You have correctly connected the dots between three different advanced concepts: **Topological Sort (Stack)**, **SCCs (Source/Sink)**, and the **Mother Vertex**.

Here is the "Senior Engineer" verification of your statement:

### 1. "Source can't be reached by anyone..."
* **Correct.** In the Condensation Graph (where every SCC is a single dot), a **Source Component** has an **In-Degree of 0**.
* **Visual:** It is the "Tap" at the top of the hill. Water flows out, but no water flows in from other components.

### 2. "...and Sink by everyone..."
* **Mostly Correct.** A **Sink Component** has an **Out-Degree of 0**. It traps flow.
* **Nuance:** In a disconnected graph, a sink might not be reachable by literally everyone (e.g., a disconnected island), but in the context of a connected flow or a Mother Vertex graph, the Sink is the ultimate destination where all paths end.

### 3. "...so Source will be always on TOS (Top of Stack) at end of DFS"
* **100% Correct.**
* **The Logic:** DFS goes deep. It visits the children (Sinks) first and finishes them. It only finishes the parent (Source) after all children are done.
* **The Result:** The Source is the last to finish, so it sits on the **Top of the Stack**.

### 4. "...and last vertex visited in Mother Vertex"
* **100% Correct.**
* **The Connection:** The Mother Vertex algorithm effectively looks for a **Source Component**.
* Since the Source Component "covers" the whole graph, it is either:
    1. Processed early (and marks everyone else visited).
    2. Processed last (because nobody else could reach it to mark it visited).
* In the standard algorithm (`for i=0 to n`), the last node to trigger a DFS is always from a Source Component (the Top of the Stack equivalent).

### Summary Table

| Concept | Source Component | Sink Component |
| :--- | :--- | :--- |
| **Reachability** | Can reach everyone (Mother). | Can be reached by others. |
| **Incoming Edges** | None (from outside). | Many. |
| **DFS Finish Time** | Last (Finishes after children). | First (Finishes before parents). |
| **Stack Position** | Top (Popped first in Kosaraju). | Bottom (Buried deep). |
| **Mother Vertex Candidate?** | **YES** (Must be here). | **NO** (Can't reach Source). |

> **Verdict:** Your mental model is now complete. You understand the "Flow" of directed graphs.

### More Mother Vertex Q&A

If stack like Kosaraju ki tarah DFS1 karte, stack ke top Mother Vertex hoga — stack ke top se hum DFS2 lagake check karenge ki can we visit whole graph from that? Done by Stack ki `O(V)` space ho jaati!!

**Brute-force solution can be:** har Vertex se DFS call kare, check karo ki sab visit ho rahe hain ya nahi — `O(V(V+E))`.

---

## Q3. Clone Graph

**Practice Question:** LeetCode 133 — Clone Graph

### Dry Run — 7-node graph (`0-3-4`, `1-2`, `4-5-6`)

We use a `HashMap<Node, Node>` to map original nodes to their clones.

At `5`, so `5` ke liye new node `5'` & put in map. `6'` as neighbor of `4'` & `5'` — `4'` as neighbor of `5'` is already visited coming from host of `6`, but `6'`s neighbors [`4'` & `5'` are its neighbors] — both are already visited & put in `6'`.

At `2`, in the tree we create its new node `2'`. `0'` — one dekhe `0` neighbour hai already visited hai — so it's like same `0'` deal. So: `0' -> `, `1' -> 0'`, `2' -> 1'`. At `2` in the tree we create its new node `2'`.

### LeetCode 133 — Clone Graph

**Difficulty:** Medium

Given a reference of a node in a **connected** undirected graph.

Return a **deep copy** (clone) of the graph.

Each node in the graph contains a value (`int`) and a list (`List[Node]`) of its neighbors.

```java
class Node {
    public int val;
    public List<Node> neighbors;
}
```

**Why can't we just return the same graph, or a shallow copy?**

- **Returning the same graph:** you can't return the same graph object — it's not a copy at all.
- **Naive/shallow clone:** "This looks like a clone. The nodes are NEW. Graph looks the same" — but if you don't rewire the neighbor lists correctly, "the nodes were cloned, but the graph is messed up — doesn't have the same connections."
- **Correct clone:** brand-new node objects, with the exact same edge structure as the original.

**Example 1:**

```
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]
```

**Explanation:** There are 4 nodes in the graph.
```
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
```

![Clone Graph example — original graph and its deep-cloned copy](img-clone-graph-example.svg)

**Example 2:** `adjList = [[]]` → Output: `[[]]`. The graph consists of only one node with `val = 1` and it does not have any neighbors.

**Example 3:** `adjList = []` → Output: `[]`. This is an empty graph, it does not have any nodes.

**Constraints:**
- The number of nodes in the graph is in the range `[0, 100]`.
- `1 <= Node.val <= 100`
- `Node.val` is unique for each node.
- There are no repeated edges and no self-loops in the graph.
- The Graph is connected and all nodes can be visited starting from the given node.

**Test case format:** For simplicity, each node's value is the same as the node's index (1-indexed). The graph is represented in the test case using an adjacency list. The given node will always be the first node with `val = 1`. You must return the copy of the given node as a reference to the cloned graph.

### Node Definition

```java
/*
// Definition for a Node.
class Node {
    public int val;
    public List<Node> neighbors;
    public Node() {
        val = 0;
        neighbors = new ArrayList<Node>();
    }
    public Node(int _val) {
        val = _val;
        neighbors = new ArrayList<Node>();
    }
    public Node(int _val, ArrayList<Node> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
}
*/
```

### Accepted — Own Code (Java)

HashMap is used to check whether we have visited node already or not — as here we are not given no. of `V` vertices, so we can't make a `visited` array; HashMap ki key node ke key address hai, jo next node hai uske liye.

```java
 /*
// Definition for a Node.
class Node {
    public int val;
    public List<Node> neighbors;
    public Node() {
        val = 0;
        neighbors = new ArrayList<Node>();
    }
    public Node(int _val) {
        val = _val;
        neighbors = new ArrayList<Node>();
    }
    public Node(int _val, ArrayList<Node> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
}
*/

class Solution {
    private Node dfs(Node node,Map<Node,Node>nodes){
        if(node==null) return null;
        Node cNode=new Node(node.val);
        nodes.put(node,cNode);
        for(var ls:node.neighbors){
            if(nodes.containsKey(ls)==false){
                    dfs(ls,nodes);
            }
            cNode.neighbors.add(nodes.get(ls));
        }
        return cNode;
    }
    public Node cloneGraph(Node node) {
        Map<Node,Node>nodes=new HashMap<>();
        Node cloneGraph=dfs(node,nodes);
        return cloneGraph;
        
    }
}
```

### Accepted — Own Code (C++)

```cpp
class Solution {
private:
    Node* dfs(Node* node, unordered_map<Node*, Node*>& nodes) {
        if (node == nullptr) return nullptr;
        Node* cNode = new Node(node->val);
        nodes[node] = cNode;
        for (Node* ls : node->neighbors) {
            if (nodes.find(ls) == nodes.end()) {
                dfs(ls, nodes);
            }
            cNode->neighbors.push_back(nodes[ls]);
        }
        return cNode;
    }

public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*, Node*> nodes;
        return dfs(node, nodes);
    }
};
```

**Complexity:**
- **Time:** `O(V + E)` — each node is visited (and cloned) exactly once thanks to the `nodes` map check, and each edge is processed exactly once (to wire up `cNode->neighbors`).
- **Space:** `O(V)` for the `nodes` map (one entry per original node) plus `O(V)` for the recursion stack in the worst case (a graph that's essentially a long chain) — the cloned graph itself (`O(V+E)`) is the required output, not auxiliary space.


**Alternative approach:** Given nodes `<= 100`, so we can use an Array of nodes of size `101`, & then instead of HashMap we use that Array.







































