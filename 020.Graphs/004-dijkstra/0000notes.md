# Q1. Dijkstra

## Relax edge code
```cpp

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, 1e9);

        dist[S] = 0;
        pq.push({0, S});

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto &it : adj[node]) {
                int adjNode = it[0];
                int edgeWeight = it[1];

                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};

```

### Java: Edge Relaxation

This matches the preceding C++ relaxation method: update the distance before insertion and ignore stale entries on removal. Each adjacency entry contains `[neighbour, weight]`. As in the existing C++ code, the `1_000_000_000` sentinel and integer arithmetic assume all required path costs fit below that sentinel without overflow.

```java
import java.util.*;

class DijkstraRelaxation {
    public int[] dijkstra(int V, ArrayList<ArrayList<ArrayList<Integer>>> adj, int S) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        int[] dist = new int[V];
        Arrays.fill(dist, 1_000_000_000);
        dist[S] = 0;
        pq.add(new int[]{0, S});

        while (!pq.isEmpty()) {
            int[] entry = pq.remove();
            int d = entry[0];
            int node = entry[1];
            if (d > dist[node]) continue;

            for (ArrayList<Integer> edge : adj.get(node)) {
                int adjNode = edge.get(0);
                int edgeWeight = edge.get(1);
                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.add(new int[]{dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
}
```
## simple pq with vis code

```cpp
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, S});

        vector<int> res(V, 1e9);
        vector<bool> vis(V, false);

        while(!pq.empty()) {
            int wt = pq.top().first;
            int v = pq.top().second;
            pq.pop();

            if(vis[v]) continue;
            vis[v] = true;
            res[v] = wt;

            for(auto &it : adj[v]) {
                int nbr = it[0];
                int w = it[1];
                if(!vis[nbr]) {
                    pq.push({wt + w, nbr});
                }
            }
        }
        return res;
    }
};
```

### Dijkstra with a Priority Queue of Triplets

The traversal resembles BFS, but replaces the FIFO queue with a min-priority queue ordered by total path weight. Each entry contains `(vertex, path-so-far, weight-so-far)`.

1. Insert the source with its own label as the path and weight zero.
2. Remove the entry with the smallest accumulated weight.
3. If its vertex was already visited, skip the entry.
4. Mark the vertex visited and print its path and weight.
5. For each unvisited neighbour, append that neighbour to the path and add the edge weight before inserting the new triplet.

Mark on removal, not on insertion: an expensive entry may be inserted before a cheaper route to the same vertex is discovered. The first non-skipped removal finalizes that vertex's distance. A later entry for the same vertex is ignored.

### Worked Example: Source `0`

Use this undirected weighted graph:

| Edge | Weight |
| --- | ---: |
| `0–1` | 10 |
| `0–3` | 40 |
| `1–2` | 10 |
| `2–3` | 10 |
| `3–4` | 2 |
| `4–5` | 3 |
| `4–6` | 8 |
| `5–6` | 3 |

The table lists heap entries in increasing weight order for readability; a binary heap's internal array is not fully sorted. An entry is shown as `(vertex, path, weight)`.

| Removal | Action | Heap after adding neighbours |
| --- | --- | --- |
| Initial state | Insert `(0, 0, 0)` | `(0, 0, 0)` |
| `(0, 0, 0)` | Finalize `0`; add `1` and `3` | `(1, 01, 10)`, `(3, 03, 40)` |
| `(1, 01, 10)` | Finalize `1`; skip visited `0`; add `2` | `(2, 012, 20)`, `(3, 03, 40)` |
| `(2, 012, 20)` | Finalize `2`; add the cheaper route to `3` | `(3, 0123, 30)`, `(3, 03, 40)` |
| `(3, 0123, 30)` | Finalize `3`; add `4` | `(4, 01234, 32)`, `(3, 03, 40)` |
| `(4, 01234, 32)` | Finalize `4`; add `5` and `6` | `(5, 012345, 35)`, `(3, 03, 40)`, `(6, 012346, 40)` |
| `(5, 012345, 35)` | Finalize `5`; add a cheaper route to `6` | `(6, 0123456, 38)`, `(3, 03, 40)`, `(6, 012346, 40)` |
| `(6, 0123456, 38)` | Finalize `6` | Two entries of weight `40` remain |
| The two weight-`40` entries | Both vertices are already visited; skip both | Empty |

The two entries of equal weight may be removed in either order without changing the answer. The shortest distance from `0` to `6` is `38`, using `0 → 1 → 2 → 3 → 4 → 5 → 6`.

```text
0 via 0 @ 0
1 via 01 @ 10
2 via 012 @ 20
3 via 0123 @ 30
4 via 01234 @ 32
5 via 012345 @ 35
6 via 0123456 @ 38
```

### Initializing the Path Correctly

The starting path must contain the actual source. In Java, use `new Trip(src, src + "", 0)`, not `new Trip(src, "0", 0)`. Hard-coding `"0"` gives the wrong printed path when the source is not zero, even though the stored source vertex and computed weights can still be correct.

An edge can be read using an index (`graph.get(v).get(i)`) or an enhanced loop (`for (Edge e : graph.get(v))`). Both use the same neighbour and weight. The triplet comparison orders entries by `wt`: return positive, negative, or zero according to whether this entry is heavier, lighter, or equal.

### Java: Print Shortest Paths and Weights

This complete example uses the triplet and visited-on-removal logic. The compact path strings match the single-digit vertex labels in the example; use separators when labels can contain multiple digits.

```java
import java.util.*;

class DijkstraPaths {
    static class Edge {
        int nbr;
        int wt;

        Edge(int nbr, int wt) {
            this.nbr = nbr;
            this.wt = wt;
        }
    }

    static class Trip implements Comparable<Trip> {
        int v;
        String psf;
        int wt;

        Trip(int v, String psf, int wt) {
            this.v = v;
            this.psf = psf;
            this.wt = wt;
        }

        public int compareTo(Trip other) {
            if (this.wt > other.wt) return 1;
            else if (this.wt < other.wt) return -1;
            else return 0;
        }
    }

    static void printShortestPaths(List<List<Edge>> graph, int src) {
        PriorityQueue<Trip> pq = new PriorityQueue<>();
        pq.add(new Trip(src, src + "", 0));
        boolean[] vis = new boolean[graph.size()];

        while (!pq.isEmpty()) {
            Trip removed = pq.remove();
            if (vis[removed.v]) continue;
            vis[removed.v] = true;
            System.out.println(removed.v + " via " + removed.psf + " @ " + removed.wt);

            for (Edge e : graph.get(removed.v)) {
                if (!vis[e.nbr]) {
                    pq.add(new Trip(e.nbr, removed.psf + e.nbr, removed.wt + e.wt));
                }
            }
        }
    }

    public static void main(String[] args) {
        int[][] edges = {
            {0, 1, 10}, {0, 3, 40}, {1, 2, 10}, {2, 3, 10},
            {3, 4, 2}, {4, 5, 3}, {4, 6, 8}, {5, 6, 3}
        };
        List<List<Edge>> graph = new ArrayList<>();
        for (int i = 0; i < 7; i++) graph.add(new ArrayList<>());
        for (int[] e : edges) {
            graph.get(e[0]).add(new Edge(e[1], e[2]));
            graph.get(e[1]).add(new Edge(e[0], e[2]));
        }
        printShortestPaths(graph, 0);
    }
}
```

### C++: Print Shortest Paths and Weights

```cpp
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Edge {
    int nbr;
    int wt;
};

struct Trip {
    int v;
    string psf;
    int wt;
};

struct CompareTrip {
    bool operator()(const Trip& a, const Trip& b) const {
        return a.wt > b.wt;
    }
};

void printShortestPaths(const vector<vector<Edge>>& graph, int src) {
    priority_queue<Trip, vector<Trip>, CompareTrip> pq;
    pq.push({src, to_string(src), 0});
    vector<bool> vis(graph.size(), false);

    while (!pq.empty()) {
        Trip removed = pq.top();
        pq.pop();
        if (vis[removed.v]) continue;
        vis[removed.v] = true;
        cout << removed.v << " via " << removed.psf << " @ " << removed.wt << '\n';

        for (const Edge& e : graph[removed.v]) {
            if (!vis[e.nbr]) {
                pq.push({e.nbr, removed.psf + to_string(e.nbr), removed.wt + e.wt});
            }
        }
    }
}

int main() {
    vector<vector<int>> edges = {
        {0, 1, 10}, {0, 3, 40}, {1, 2, 10}, {2, 3, 10},
        {3, 4, 2}, {4, 5, 3}, {4, 6, 8}, {5, 6, 3}
    };
    vector<vector<Edge>> graph(7);
    for (const auto& e : edges) {
        graph[e[0]].push_back({e[1], e[2]});
        graph[e[1]].push_back({e[0], e[2]});
    }
    printShortestPaths(graph, 0);
    return 0;
}
```

These examples print reachable vertices only. Without storing path strings, this lazy-heap traversal uses `O(V + E)` auxiliary storage and `O(V + E log(E + 1))` time. Copying a path string into every queued entry adds work and storage proportional to the copied path lengths; parent pointers avoid that duplication when reconstructing paths later.

### Java: Distances with Visited-on-Removal

The existing Java implementation below returns distances instead of printing full paths.      

```java
class Solution
{
    static class trip{
        int v;
        int wt;
        trip(int v,int wt){
            this.v=v;
            this.wt=wt;
        }
    }
    public  int[] dijkstra(int V, ArrayList<ArrayList<ArrayList<Integer>>> adj, int S)
    {
        PriorityQueue<trip> pq=new PriorityQueue<>((trip a,trip b)-> (a.wt-b.wt));
        pq.add(new trip(S ,0));
        boolean[] vis=new boolean[V];
        int[] res=new int[V];
        Arrays.fill(res, (int)1e9);
        while(pq.size()>0){
            trip rem=pq.remove();
            if(vis[rem.v]==true) continue;
            vis[rem.v]=true;
            res[rem.v]=rem.wt;
            for(var itr:adj.get(rem.v)){
                int nbr=itr.get(0);
                int w=itr.get(1);
                if(vis[nbr]==false){
                    pq.add(new trip(nbr,rem.wt+w));
                }
            }
        }

       return res;
    }
}

```
### Cpp code

```cpp
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, S});

        vector<int> res(V, 1e9);
        vector<bool> vis(V, false);

        while(!pq.empty()) {
            int wt = pq.top().first;
            int v = pq.top().second;
            pq.pop();

            if(vis[v]) continue;
            vis[v] = true;
            res[v] = wt;

            for(auto &it : adj[v]) {
                int nbr = it[0];
                int w = it[1];
                if(!vis[nbr]) {
                    pq.push({wt + w, nbr});
                }
            }
        }
        return res;
    }
};
```

### "Blind Push" vs. "Edge Relaxation" in Dijkstra

The main difference between these two approaches lies in efficiency and the total number of items pushed into the Priority Queue (PQ).

---

### 1. Your Approach ("Blind Push")
In this version, you push a neighbor into the PQ every time you encounter an edge to an unvisited node, regardless of the path's quality.

* **The Logic:** `if (!vis[nbr]) { pq.push(...) }`
* **The Problem:** Suppose you have already found a path to **Node B** with a cost of **10**. Later, you find another path to **Node B** with a cost of **100**.
    * **Your code checks:** "Is B visited?" No.
    * **Action:** It pushes `{100, B}` into the PQ.
* **Result:** You now have a "trash" entry in your heap. While the algorithm will eventually discard it, these redundant entries waste memory and increase the $O(\log N)$ overhead for every subsequent heap operation.

---

### 2. The Standard Approach ("Edge Relaxation")
Standard Dijkstra only pushes a node into the PQ if the new path is **strictly better** (shorter) than the best path found so far.

* **The Logic:** `if (dist[u] + weight < dist[v]) { dist[v] = ...; pq.push(...); }`
* **The Benefit:** Using the same example (current best to B is 10, new path is 100):
    * **Standard code checks:** "Is 100 < 10?" No.
    * **Action:** It does nothing.
* **Result:** The "trash" path never enters the PQ. This keeps the heap size to a minimum, ensuring the algorithm runs at peak speed.

---

### Comparison Summary

| Feature | Blind Push | Edge Relaxation (Standard) |
| :--- | :--- | :--- |
| **PQ Size** | Large (Contains redundant paths) | **Small** (Only optimal paths) |
| **Heap Overhead** | Higher (More $O(\log N)$ ops) | **Lower** |
| **Memory** | Higher | **Efficient** |
| **Verdict** | Okay for beginners | **Recommended for Production/CP** |

---
## Relax edge code
```cpp

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, 1e9);

        dist[S] = 0;
        pq.push({0, S});

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto &it : adj[node]) {
                int adjNode = it[0];
                int edgeWeight = it[1];

                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};

```
### Dijkstra's Algorithm: Complexity Analysis

For the standard **Adjacency List + Min-Priority Queue (Binary Heap)** implementation, the complexities are as follows:

---

### Time Complexity: $O(E \log V)$

* **$E$:** Number of Edges
* **$V$:** Number of Vertices

**Why?**
1.  **Edge Traversal:** we traverse every edge in the graph at least once ($O(E)$).
2.  **Heap Operations:** For every edge, we might push a new node into the priority queue or update a distance.
3.  **Logarithmic Cost:** Inserting into or popping from a binary heap takes logarithmic time relative to the number of items. In the worst case, the heap can hold up to $E$ items (one for each edge).

> **The Math:** $E \times \log(E)$. Since $E \le V^2$ in a simple graph, $\log(E) \le \log(V^2)$, which is $2 \log(V)$. This simplifies the constant to $O(E \log V)$.

---

### Space Complexity: $O(V + E)$

* **$O(V + E)$:** To store the graph using an **Adjacency List**.
* **$O(V)$:** To store the `dist` array and the **priority_queue** (which, in a optimized implementation, stores at most $V$ nodes).

---

### Comparison of Implementations

| Implementation | Time Complexity | Best Use Case |
| :--- | :--- | :--- |
| **Binary Heap (Priority Queue)** | $O(E \log V)$ | **Sparse Graphs** (Most Interview Problems) |
| **Array (Naive)** | $O(V^2)$ | **Dense Graphs** (where $E \approx V^2$) |
| **Fibonacci Heap** | $O(E + V \log V)$ | Theoretical best (Often too complex for interviews) |

---


>Note: Dijkstra doesnt work for negative weights ,it only works for positive weights ,for negative weights we have bellman ford!!



## Relax edge code
```cpp

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, 1e9);

        dist[S] = 0;
        pq.push({0, S});

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto &it : adj[node]) {
                int adjNode = it[0];
                int edgeWeight = it[1];

                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};

```



### The Stale Entry — Most Asked Interview Question

```cpp
if (d > dist[u]) continue;
```

When we updated `dist[3]` from 11 to 10, the old entry `{11, 3}` is **still sitting in the heap**. We cannot remove it. So when it gets popped:

```
d=11, dist[3]=10
11 > 10 → this is stale → skip ✅

Without this check:
we'd reprocess node 3 unnecessarily
push its neighbours again with wrong distances ❌
```

---

### Why Negative Weights Break Dijkstra

```
Graph: 0 →(4)→ 1 →(-10)→ 2
                0 →(2)→ 2

Dijkstra pops 2 with dist=2, marks it FINAL
Later finds path 0→1→2 = 4+(-10) = -6 which is BETTER
But node 2 is already finalised — too late ❌

Negative weights = use Bellman Ford instead
```

---

### Complexity

```
V = vertices, E = edges

Time:  O((V + E) log V)
         ↑           ↑
    each node    each edge push
    popped once  to heap = log V

Space: O(V + E)
         ↑    ↑
       dist  heap + adjacency list
```


```cpp
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<vector<int>>> &adj, int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, S});

        vector<int> res(V, 1e9);
        vector<bool> vis(V, false);

        while(!pq.empty()) {
            int wt = pq.top().first;
            int v = pq.top().second;
            pq.pop();

            if(vis[v]) continue;
            vis[v] = true;
            res[v] = wt;

            for(auto &it : adj[v]) {
                int nbr = it[0];
                int w = it[1];
                if(!vis[nbr]) {
                    pq.push({wt + w, nbr});
                }
            }
        }
        return res;
    }
};
```
This is also dijsktsra we have seen  ,which to use??








Yes! This is also Dijkstra — but with a **slightly different implementation style**. Let me compare both.

---

### Two Valid Approaches

| | Your code | My code |
|---|---|---|
| Visited tracking | `vis[]` boolean array | `if(d > dist[u]) continue` |
| dist update | `res[v] = wt` when popped | `dist[v] = newDist` when pushing |
| Push condition | `if(!vis[nbr])` | `if(newDist < dist[v])` |
| Style | visited-based | distance-based |

Both are correct. Both are O((V+E) log V).

---

### Your Code Flow

```cpp

int wt = pq.top().first;
int v  = pq.top().second;

if(vis[v]) continue;

vis[v] = true;
res[v] = wt;

if(!vis[nbr])
    pq.push({wt + w, nbr});
```

---

### Key Difference — When Distance is Set

**My approach — distance set at PUSH time:**
```cpp

dist[v] = newDist;
pq.push({newDist, v});

if(d > dist[u]) continue;
```

**Your approach — distance set at POP time:**
```cpp

pq.push({wt + w, nbr});

vis[v] = true;
res[v] = wt;
```

---

### Why Your Code is Still Correct

```
Min heap always pops smallest distance first
First time a node is popped = smallest possible distance
  because all other paths in heap cost >= current
  + non-negative edges on top
  = can never be smaller

So first pop = optimal distance ✅
vis[] prevents processing same node twice ✅
```

---

### One Subtle Difference — Push Condition

**Your code:**
```cpp
if(!vis[nbr])
    pq.push({wt + w, nbr});
```

**My code:**
```cpp
if(newDist < dist[v])
    pq.push({dist[v], v});
```

Your code pushes neighbour if **not yet finalised** — even if a better entry already exists in heap. This means heap can have more duplicate entries.

```
Example:
Node 3 reachable via two paths: cost 11 and cost 10
Your code pushes BOTH {11,3} and {10,3} to heap
Mine pushes {11,3} first, then when 10 found,
  dist[3] updates to 10 and pushes {10,3}
  but also has {11,3} as stale

Both end up with same stale entries in heap
Both skip them correctly (vis[] vs d>dist[])
```
Let me trace both codes **side by side** on the same example.

---

### The Graph

```
0 →(4)→ 1
0 →(2)→ 2
2 →(1)→ 1       ← shorter path to node 1 exists!
1 →(5)→ 3
```

So node 1 reachable two ways:
```
0→1 = 4
0→2→1 = 2+1 = 3   ← shorter
```

---

### My Code — dist[] updated at PUSH time

```cpp
dist[v] = newDist;
pq.push({newDist, v});
```

**Trace:**

```
dist = [0, INF, INF, INF]
pq   = [{0,0}]

─── pop {0, node=0} ───
  neighbour 1: newDist=4 < INF → dist[1]=4, push {4,1}
  neighbour 2: newDist=2 < INF → dist[2]=2, push {2,2}

dist = [0, 4, 2, INF]
pq   = [{2,2}, {4,1}]

─── pop {2, node=2} ───
  neighbour 1: newDist=3 < dist[1]=4
               → dist[1]=3         ← updated immediately
               → push {3,1}        ← new entry

dist = [0, 3, 2, INF]
pq   = [{3,1}, {4,1}]
           ↑     ↑
         fresh  stale (dist was 4, now 3)

─── pop {3, node=1} ───
  3 == dist[1]=3 → NOT stale → process ✅
  neighbour 3: newDist=8, push {8,3}

─── pop {4, node=1} ───
  4 > dist[1]=3 → STALE → skip ✅

Final dist = [0, 3, 2, 8]
```

---

### Your Code — dist set at POP time, vis[] tracks finalised

```cpp
if(!vis[nbr])
    pq.push({wt+w, nbr});
vis[v]=true;
res[v]=wt;
```

**Trace:**

```
res = [INF, INF, INF, INF]
vis = [F, F, F, F]
pq  = [{0,0}]

─── pop {0, node=0} ───
  vis[0]=false → process
  vis[0]=true, res[0]=0

  neighbour 1: vis[1]=false → push {4,1}
  neighbour 2: vis[2]=false → push {2,2}

pq  = [{2,2}, {4,1}]
vis = [T, F, F, F]

─── pop {2, node=2} ───
  vis[2]=false → process
  vis[2]=true, res[2]=2

  neighbour 1: vis[1]=false → push {3,1}  ← pushed again!

pq  = [{3,1}, {4,1}]
           ↑     ↑
         fresh  stale (same node, different cost)
vis = [T, F, T, F]

─── pop {3, node=1} ───
  vis[1]=false → process  ✅ first time seeing node 1
  vis[1]=true, res[1]=3   ← correct! smallest cost wins

  neighbour 3: vis[3]=false → push {8,3}

─── pop {4, node=1} ───
  vis[1]=TRUE → skip ✅   ← stale entry caught here

Final res = [0, 3, 2, 8] ✅ same answer
```

---

### Side by Side — What's in the Heap

```
After processing node 2:

My code heap:                Your code heap:
[{3,1}, {4,1}]              [{3,1}, {4,1}]
    ↑      ↑                    ↑      ↑
  fresh   stale              fresh   stale

IDENTICAL heap contents! ✅
```

---

### How Each Detects the Stale Entry

```
Stale entry = {4, node=1}

My code:
  pop {4,1}
  check: 4 > dist[1]=3?  YES → skip
  "distance in heap > best known distance"

Your code:
  pop {4,1}
  check: vis[1]=true?    YES → skip
  "node already finalised"

Different check, same result ✅
```

---

### The Core Difference Visualised

```
MY CODE:
                     dist[1] updated HERE
                           ↓
  push {4,1} ─────────────► dist[1]=4
                             ...
  push {3,1} ─────────────► dist[1]=3  ← overwrites
                             ...
  pop  {3,1} → 3==dist[1]=3 → valid ✅
  pop  {4,1} → 4> dist[1]=3 → stale ❌ skip


YOUR CODE:
                     res[1] updated HERE
                                    ↓
  push {4,1} → nothing updated yet
  push {3,1} → nothing updated yet
  ...
  pop  {3,1} → vis[1]=false → valid ✅ → res[1]=3
  pop  {4,1} → vis[1]=true  → stale ❌ skip
```

---

### Summary in One Table

| Moment | My code | Your code |
|---|---|---|
| When dist set | at PUSH | at POP |
| Stale detection | `d > dist[u]` | `vis[u] == true` |
| Heap contents | identical | identical |
| Final answer | same | same |
| Conceptual model | "update eagerly, check at pop" | "push freely, finalise at pop" |

Both are correct because the **min-heap guarantees the smallest cost entry is always popped first** — so whether you detect stale entries via `dist[]` or `vis[]`, you always process each node at its optimal cost exactly once.
---

### Which is Preferred in Interview?

```
Your approach (vis[] based):
✅ cleaner code — no stale check logic
✅ easier to explain — "first pop = final"
✅ more intuitive — visited = done
⚠️ slightly more entries in heap

My approach (dist[] based):
✅ more entries pruned before pushing
✅ dist[] available at any time during algorithm
⚠️ stale check needed — slightly more logic
```

**For interviews — your approach is actually cleaner to write and explain.**

---

### One Real Issue in Your Code ⚠️

```cpp
vector<int> res(V, 1e9);

```

Safer to write:

```cpp
vector<int> res(V, INT_MAX);

vector<int> res(V, 1e9);
```

Also if you do `wt + w` where `wt` is near `INT_MAX`:

```cpp

int wt = INT_MAX;
int w  = 5;
wt + w = overflow ❌

```

---

### Summary

```
Both implementations are correct Dijkstra ✅

Your code  →  vis[] array  →  finalise at pop
My code    →  dist[] check →  update at push

Yours is arguably cleaner for interviews
The only real difference is heap size
(yours may have slightly more entries)
```



# Q3. Get shortest path from 1 to n,given edge list

## My code

```cpp
class Solution {
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});

        vector<int> dist(n + 1, 1e9);
        vector<int> par(n + 1);
        for (int i = 1; i <= n; i++) par[i] = i;
        dist[1] = 0;

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (d > dist[node]) continue;

            for (auto& it : adj[node]) {
                int nbr = it.first;
                int w = it.second;

                if (d + w < dist[nbr]) {
                    dist[nbr] = d + w;
                    par[nbr] = node;
                    pq.push({d + w, nbr});
                }
            }
        }

        if (par[n] == n) return {-1};

        vector<int> path;
        int node = n;
        while (par[node] != node) {
            path.push_back(node);
            node = par[node];
        }
        path.push_back(1);
        reverse(path.begin(), path.end());
        path.insert(path.begin(), dist[n]);

        return path;
    }
};
```

### Java counterpart: Reconstruct the Path

Maintain a parent whenever a shorter route is found, then follow parents backward from `n`, reverse the result, and insert the total distance at the beginning. The returned format is `[distance, 1, ..., n]`, or `[-1]` if no path exists. This version follows the preceding C++ code exactly, including `par[n] == n` as its unreachable test; that test assumes `n > 1` and returns `[-1]` for `n == 1`.

```java
import java.util.*;

class WeightedShortestPath {
    public List<Integer> shortestPath(int n, int m, int[][] edges) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i <= n; i++) adj.add(new ArrayList<>());
        for (int[] edge : edges) {
            adj.get(edge[0]).add(new int[]{edge[1], edge[2]});
            adj.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        pq.add(new int[]{0, 1});
        int[] dist = new int[n + 1];
        Arrays.fill(dist, 1_000_000_000);
        int[] par = new int[n + 1];
        for (int i = 1; i <= n; i++) par[i] = i;
        dist[1] = 0;

        while (!pq.isEmpty()) {
            int[] entry = pq.remove();
            int d = entry[0];
            int node = entry[1];
            if (d > dist[node]) continue;
            for (int[] edge : adj.get(node)) {
                int nbr = edge[0];
                int w = edge[1];
                if (d + w < dist[nbr]) {
                    dist[nbr] = d + w;
                    par[nbr] = node;
                    pq.add(new int[]{d + w, nbr});
                }
            }
        }
        if (par[n] == n) return new ArrayList<>(Arrays.asList(-1));
        List<Integer> path = new ArrayList<>();
        int node = n;
        while (par[node] != node) {
            path.add(node);
            node = par[node];
        }
        path.add(1);
        Collections.reverse(path);
        path.add(0, dist[n]);
        return path;
    }
}
```
If all have unit weight then no need of Dijkstara or all edges are of same weight just simple bfs

here we have 0 to n-1 nodes
## Striver code(code 1)

```cpp
class Solution {
private:

    void bfs(int src, vector<int> adj[],
             vector<int> &dist) {

        dist[src] = 0;

        queue<int> q;

        q.push(src);

        while(!q.empty()) {

            int node = q.front();
            q.pop();

            for(auto adjNode : adj[node]) {

                if(dist[node] + 1 < dist[adjNode]) {

                    dist[adjNode] = 1 + dist[node];

                    q.push(adjNode);
                }
            }
        }
    }

public:

    vector<int> shortestPath(vector<vector<int>>& edges,
                             int N, int M){

        vector<int> adj[N];

        for(auto it : edges) {
            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector <int> dist(N, 1e9);

        bfs(0, adj, dist);

        for(int i = 0; i < N; i++) {
            if (dist[i] == 1e9)
                dist[i] = -1;
        }

        return dist;
    }
};
```

### Java counterpart: Unit-Weight BFS (Code 1)

Vertices are numbered `0..N-1`, and the source is `0`. Updating a distance before enqueueing prevents duplicate discovery. Unreachable vertices return `-1`. Time is `O(V + E)` and space is `O(V + E)` including the adjacency list.

```java
import java.util.*;

class UnitWeightBfs {
    void bfs(int src, List<List<Integer>> adj, int[] dist) {
        dist[src] = 0;
        Queue<Integer> q = new ArrayDeque<>();
        q.add(src);
        while (!q.isEmpty()) {
            int node = q.remove();
            for (int adjNode : adj.get(node)) {
                if (dist[node] + 1 < dist[adjNode]) {
                    dist[adjNode] = 1 + dist[node];
                    q.add(adjNode);
                }
            }
        }
    }

    public int[] shortestPath(int[][] edges, int N, int M) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < N; i++) adj.add(new ArrayList<>());
        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }
        int[] dist = new int[N];
        Arrays.fill(dist, 1_000_000_000);
        bfs(0, adj, dist);
        for (int i = 0; i < N; i++) {
            if (dist[i] == 1_000_000_000) dist[i] = -1;
        }
        return dist;
    }
}
```
## My code(code 2)

```cpp
class Solution {
  public:
    vector<int> shortestPath(vector<vector<int>>& edges, int n,int M){
      vector<vector<int>> adj(n );
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<int> dist(n , 1e9);
        queue<pair<int,int>> q;
        q.push({0,0});
        while(q.size()>0){
          auto vertex=q.front();
          q.pop();
          int wt=vertex.first;
          int v=vertex.second;
          dist[v]=min(wt,dist[v]);
          for(int k=0;k<adj[v].size();k++){
            if(dist[adj[v][k]]==1e9){
              q.push({wt+1,adj[v][k]});
            }
          }
        }
        for(int i=0;i<dist.size();i++){
          if(dist[i]==1e9) dist[i]=-1;
        }
        return dist;
    }
};

```
### Java counterpart: Distance Updated on Removal (Code 2)

This preserves the preceding C++ logic for comparison, including repeated queue entries. The discussion below explains its performance problem; the Code 1 approach is the standard implementation.

```java
import java.util.*;

class UnitWeightBfsPop {
    public int[] shortestPath(int[][] edges, int n, int M) {
        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }
        int[] dist = new int[n];
        Arrays.fill(dist, 1_000_000_000);
        Queue<int[]> q = new ArrayDeque<>();
        q.add(new int[]{0, 0});
        while (!q.isEmpty()) {
            int[] vertex = q.remove();
            int wt = vertex[0];
            int v = vertex[1];
            dist[v] = Math.min(wt, dist[v]);
            for (int k = 0; k < adj.get(v).size(); k++) {
                int nbr = adj.get(v).get(k);
                if (dist[nbr] == 1_000_000_000) {
                    q.add(new int[]{wt + 1, nbr});
                }
            }
        }
        for (int i = 0; i < dist.length; i++) {
            if (dist[i] == 1_000_000_000) dist[i] = -1;
        }
        return dist;
    }
}
```
# BFS: Marking Visited on Push vs. Pop

This is a classic example of **"Marking Visited on Push"** vs. **"Marking Visited on Pop."**

* **Code 1:** **Correct (Standard BFS).** It updates the distance/visited status *before* pushing to the queue.
* **Code 2:** **Buggy / Inefficient.** It updates the distance *after* popping from the queue.

Here is the "Senior Engineer" breakdown of why Code 2 is dangerous.

### 1. The "Queue Explosion" Bug in Code 2
The critical error in the second snippet is here:

```cpp

if(dist[adj[v][k]] == 1e9) {
    q.push({wt+1, adj[v][k]});

}
```
Because you don't update `dist` immediately, the neighbor remains "Unvisited" ($1e9$) even though it is already sitting in the queue.

**Scenario:**
1.  Imagine Node A connects to B and C. Both B and C connect to D.
2.  **Pop A:** Push B and C. (Distances of B and C are still $1e9$).
3.  **Pop B:** See neighbor D. `dist[D]` is $1e9$. Push D.
4.  **Pop C:** See neighbor D. `dist[D]` is **still** $1e9$ (because B didn't update it yet!). Push D *again*.
5.  **Result:** Node D enters the queue twice. In a large, dense graph, this causes the queue size to explode exponentially, leading to **Time Limit Exceeded (TLE)** or **Memory Limit Exceeded (MLE)**.

### 2. Why Code 1 is Correct
Code 1 follows the **Golden Rule of BFS**: "Mark as visited the moment you see it."


```cpp
if(dist[node] + 1 < dist[adjNode]) {
    dist[adjNode] = 1 + dist[node];
    q.push(adjNode);
}
```
By updating `dist` before pushing, if another node tries to visit `adjNode` later in the same layer, the `if` condition will fail, and it won't be pushed again.

### 3. Redundant Logic in Code 2
* `dist[v] = min(wt, dist[v])`: In an unweighted BFS, the **first time** you reach a node is always the shortest path. You never need `min`. You just need to check "Have I been here before?"
* **priority_queue vs queue:** Your Code 2 uses `queue`, which is correct for unweighted graphs. If you used `priority_queue` (Dijkstra), the "lazy update" (checking on pop) would be valid, but for standard BFS, it is wrong.

### Senior Engineer Recommendation
**Use Code 1.** It is the standard template.

If you strictly want to fix Code 2, you must move the update logic inside the loop:

```cpp
while(!q.empty()){
    int node = q.front().second;
    q.pop();

    for(int neighbor : adj[node]){
        if(dist[neighbor] == 1e9){
            dist[neighbor] = dist[node] + 1;
            q.push({dist[neighbor], neighbor});
        }
    }
}
```


**Fixed Code 2:**

---

let us back to dijkstra

# Q4. Why `if (d > dist[node]) continue;`??

## Lazy Deletion in Dijkstra's Algorithm

This is a critical optimization known as **"Lazy Deletion."**

Here is the "Senior Engineer" explanation of why that line is mandatory for performance, even though the algorithm works without it.

### 1. The Problem: Duplicate Entries
Standard C++ `priority_queue` does not support the `decrease_key` operation.
* **Ideal Dijkstra:** If we find a shorter path to a node already in the queue, we update its value.
* **Real (C++) Dijkstra:** We cannot update the value inside the heap. Instead, we just push a new pair `{new_dist, node}` into the queue.

**Result:** The Priority Queue ends up containing multiple versions of the same node.
* **Version 1:** `{10, NodeA}` (Old, worse path)
* **Version 2:** `{5, NodeA}` (New, better path)

### 2. The Execution Flow
1.  **Pop Version 2:** The min-heap pops `{5, NodeA}` first (because $5 < 10$).
2.  **Process:** You relax all neighbors of Node A using distance 5. `dist[NodeA]` is now finalized as 5.
3.  **Time Passes...**
4.  **Pop Version 1:** Eventually, the heap pops the "stale" entry `{10, NodeA}`.

### 3. The "Guard Clause"
**Without the line** `if (d > dist[node]) continue;`:
* You would take this outdated path (cost 10).
* You would iterate through all of Node A's neighbors again.
* You would try to relax edges using a suboptimal distance ($10 + weight$), which is waste of CPU cycles.

**With the Guard Clause:**
```cpp


if (10 > 5) continue;
```

### Summary

* **Is it for Correctness?** No. Dijkstra will still give the right answer without it (redundant relaxations won't find a shorter path).
* **Is it for Complexity?** **YES.**
    * **With Check:** Each node is processed once. Complexity: $O(E \log V)$.
    * **Without Check:** Each edge pushing to the queue could trigger a process. Complexity degrades towards $O(E \cdot \text{Degree} \cdot \log E)$, which effectively makes it much slower on dense graphs.

> **Senior Tip:** This line converts the "Push duplicate" workaround from a memory leak into a valid $O(E \log V)$ implementation. **Always include it.**

## Striver code
```cpp
#define P pair<int,int>

class Solution {
public:

    vector<int> shortestPath(int n, int m,
                vector<vector<int>> &edges) {
        vector<P> adj[n + 1];

        for (auto it : edges) {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }
        priority_queue<P, vector<P>, greater<P>> pq;
        vector<int> dist(n + 1, 1e9);
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
        dist[1] = 0;
        pq.push({0, 1});

        while (!pq.empty())
        {

            auto it = pq.top();
            pq.pop();

            int node = it.second;
            int dis = it.first;

            for (auto it : adj[node]) {

                int adjNode = it.first;
                int edWt = it.second;

                if (dis + edWt < dist[adjNode]) {

                    dist[adjNode] = dis + edWt;
                    pq.push({dis + edWt, adjNode});
                    parent[adjNode] = node;
                }
            }
        }
        if (dist[n] == 1e9)
            return {-1};

        vector<int> path;
        int node = n;
        while (parent[node] != node) {

            path.push_back(node);
            node = parent[node];
        }

        path.push_back(1);
        reverse(path.begin(), path.end());
        path.insert(path.begin(), dist[n]);

        return path;
    }
};

```
### Java counterpart: Parent Reconstruction without the Stale Check

This matches the preceding Striver version: it tests reachability using the distance sentinel and does not skip stale heap entries. The path format is unchanged. For a one-vertex graph it returns distance zero and path [1], giving [0,1] overall.

```java
import java.util.*;

class WeightedShortestPathNoSkip {
    public List<Integer> shortestPath(int n, int m, int[][] edges) {
        List<List<int[]>> adj = new ArrayList<>();
        for (int i = 0; i <= n; i++) adj.add(new ArrayList<>());
        for (int[] edge : edges) {
            adj.get(edge[0]).add(new int[]{edge[1], edge[2]});
            adj.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        pq.add(new int[]{0, 1});
        int[] dist = new int[n + 1];
        Arrays.fill(dist, 1_000_000_000);
        int[] par = new int[n + 1];
        for (int i = 1; i <= n; i++) par[i] = i;
        dist[1] = 0;

        while (!pq.isEmpty()) {
            int[] entry = pq.remove();
            int d = entry[0];
            int node = entry[1];

            for (int[] edge : adj.get(node)) {
                int nbr = edge[0];
                int w = edge[1];
                if (d + w < dist[nbr]) {
                    dist[nbr] = d + w;
                    par[nbr] = node;
                    pq.add(new int[]{d + w, nbr});
                }
            }
        }
        if (dist[n] == 1_000_000_000) return new ArrayList<>(Arrays.asList(-1));
        List<Integer> path = new ArrayList<>();
        int node = n;
        while (par[node] != node) {
            path.add(node);
            node = par[node];
        }
        path.add(1);
        Collections.reverse(path);
        path.add(0, dist[n]);
        return path;
    }
}
```
