## Comparison Table: Why Heap?

To understand why Heap is necessary, let's compare 4 data structures across 4 primary operations:

| Data Structure | Search | Insert | Delete | Min/Max |
|---|---|---|---|---|
| Unsorted Array | O(N) | O(1) | O(N) | O(N) |
| Sorted Array | O(log N) | O(N) | O(N) | O(1) |
| Linked List | O(N) | O(1) | O(N) | O(N) |
| **Heap** | **O(log N)** | **O(log N)** | **O(log N)** | **O(1)** |

**Why is Delete O(N) in Unsorted Array?**
You first search (O(N)), then delete. But in a sorted array after deleting, you must shift all subsequent elements to fill the gap — that's another O(N). So the total cost stays O(N) but for a different reason.

**Why is Insert O(N) in Sorted Array?**
You must find the correct position to maintain sorted order (O(log N) search), but then shift all elements to the right to make room — that shifting is O(N).

**The critical insight:** Delete is always dependent on Search — you Search first, then Delete. So the time complexity of both is the same, EXCEPT in Sorted Array where you additionally need to shift elements after deletion to fill the empty space.

**Why is Min/Max O(1) in Sorted Array?**
Because the minimum is always at index 0 and maximum at the last index — constant time access.

**Why is Heap the best?**
No other data structure gives you O(log N) for Insert, Search, Delete AND O(1) for Min/Max simultaneously. This is the unique power of Heap.

---

## When to Use Heap & Binary Tree Types

**Important clarification on "insertion" terminology:**
When we say insert is O(1) for Unsorted Array or Linked List, we are NOT saying insert in sorted order. We are simply saying "insert into the data structure" — just add it anywhere. This is just insertion into a DS, not sorted insertion.

**The new data structure (Heap) gives us:**
- Insert → O(log N)
- Search → O(log N)
- Delete → O(log N)
- Find Min/Max → O(1)

**When do we use Heap?**
When **finding Min/Max is our primary task**, and we also need reasonably fast insert/search/delete — that is when Heap is the ideal choice.

**Typical interview questions that require Heap:**
- Kth largest element
- Kth smallest element
- Kth minimum
- And similar order-statistic problems

**Binary Tree (BT) — Two Types:**

Understanding Heap requires distinguishing two types of Binary Trees:

**1. Almost Complete Binary Tree:**
All levels are completely filled EXCEPT the last level. The last level is filled from LEFT to RIGHT (you cannot have a node on the right if the left is empty).

**2. Perfect Binary Tree:**
ALL levels are completely filled. Every internal node has exactly 2 children, and all leaf nodes are at the same level.

**Heaps are Almost Complete Binary Trees** — this is the structural definition of a Heap.

---

## Heap Structure, Height, and Implementation

**Why Almost Complete BT matters:**
Because Heap is an Almost Complete Binary Tree, its height is **always O(log N)**. This is guaranteed — it can never be skewed or unbalanced. This is what gives all heap operations their O(log N) guarantee.



**Critical distinction — Array vs Heap Array:**
- A regular array is NOT a Heap
- But a **Heap Array** (an array used to represent a heap) IS used to make a Heap
- The array stores the tree level by level (BFS order)

**Critical distinction — Priority Queue vs Heap:**
- A Priority Queue is NOT a Heap
- A Priority Queue is an ADT (Abstract Data Type) — it defines behavior, not implementation
- It is USED to behave like a Heap
- Think of it like: Stack is an ADT, Array is used to implement it

**Practical rule for coding:**
- For **implementation** → use Array (to store the heap internally)
- For **solving problems/queries** → use Priority Queue (the interface Java/C++ provides)

**PQ → Priority Queue.** PQ is a concept & is implemented by **Heap**.

Heap has 2 property: ① Heap Order Property ② Complete Binary Tree

These property help to make add & remove → `O(log n)` & peek → `O(1)`.

### ① Heap Order Property (HOP)

Parent ki priority dono children se zyada hogi. If rank list, then parent smaller than both of its children.

**Parent priority > both children priority.** Left & Right children ki priority mein koi fark nahi hota!! (There's no difference in priority between the left and right child — either can hold the higher-priority spot.)

```
        a
       / \
      b   c
     / \ / \
    d  e f  g
```

`Priority of a > Priority of b, Priority of c`
`Priority of b > Priority of d, e`
`Priority of c > Priority of b, g`

So overall `a` has highest priority.

HOP makes sure ki root pe highest priority element ho, so `O(1)` as only need to do `list.get(0)`.

### ② Complete Binary Tree (CBT)

`h` levels then `(h-1)` levels fully filled, `h`th level will be filled from Left to Right.

CBT ki vajah se add & remove() normal tree structure `O(log n)` nahi lagega. (Because of the CBT property, `add()`/`remove()` don't cost `O(log n)` the way they would in a normal, possibly-skewed tree — the height is guaranteed to be `log n`.)

Here see `O(h)` height ki so `h = O(log n)` in Complete Binary Tree.

Remember: fn name is **Up-Heapify** so upar check hota hai parent se. If ye simple Binary Tree lete toh hume Euler tour lagana padta ye toh Array List hai jiske yaha se add kar per she best nahi. (If this were a plain Binary Tree, we'd need an Euler tour to add — but since it's an ArrayList, we can just add at the end, which is the best option.)

Now let's see Remove. Remove is most difficult among these. For this you must also remember array is a Linear DS.

---

## How This Property Helps → Array Representation of a Tree

How this property helps to get `TC -> O(log n)` of add & remove? With help of this property we can represent a Tree in form of an ArrayList.

If we have `h` levels, then `(h-1)` levels completely fill, the `h`th level will be filled from Left to Right.

ArrayList ki vajah se `O(log n)` mein ho jaata hai add() aur remove() — normal tree structure `O(log n)` nahi degi.

### ArrayList ko dekhne ka doosra tarika — abhi tak linearly dekhte the

```
Index: 0  1  2  3  4  5  6  7  8
Value: 10 20 30 40 50 60 70 80 90
```

Ab aise dekho:

```
                10⁰
              /      \
           20¹        30²
          /   \       /   \
        40³   50⁴   60⁵   70⁶
       /  \
     80⁷  90⁸
```

Unnatural hai par zid kar ke phir bhi ab se aise dekh, sirf heap ke liye. (It's unnatural, but let's still look at it this way from now on, just for the heap.)

Here we are learning that an array can be visualised as a tree like above.

Levels vale ke liye aise pdhna:

```
L -> left    R -> right
```

`10, 20, 30, 40, 50, 60, 70, 80, 90` — every level read L to R:

```
at level 1 -> 10
   level 2 -> 20, 30
   level 3 -> 40, 50, 60, 70
   level 4 -> 80, 90
```

By this way, we are ensuring Complete Binary Tree property, as we are filling level by level & so next level only after one level is filled, also filling levels L to R.

### Now we want to add()

So this is our Priority Queue. If you visualise array like a tree we get `peek -> O(1)`, `add` & `remove in O(log n)`.

`peek -> list.get(0)`, so `O(1)`.

Now we want to `add()`. add hoga toh last mein hi hume `add(5)` ka dikha, `add ke helper fn hai upHeapify()`.

`upHeapify()` dekheya kyunki mera parent mujhse zyada priority nahi hai toh yes toh swap ho jaega — `5 & 60`.

### Dry Run — `add(5)`

```
       10
      /  \
    20    30
   /  \   /  \
  40  50 60  70
 /\
80 90    (5)
```

Now 5 sees its parent i.e. `30`, will `30` has more priority than me (we are talking of rank list so more priority => less in value) but `30` has more value, so swap `30` & `5`.

```
       10
      /  \
    20     5
   /  \   /  \
  40  50 60  70
 /\        \
80 90       30
```

Now again `10` & `5` compared, as `10` is parent, so swap `10` & `5`.

```
        5
      /  \
    20    10
   /  \   /  \
  40  50 60  70
 /\        \
80 90       30
```

Here see `O(h)` steps kia so `h = O(log n)` in Complete Binary Tree.

### Removal

Toh if hume ko most priority wale element remove karna hai, tab root wala ke de do — which makes TC of peek → `O(1)`.

### ② Complete Binary Tree (extraction)

This property helps to get add & remove in `O(log n)`.

```
                    white hai:  CBT ke upper ke level fill hote & uske baad last level left to right
```

Remember ek hi tree bnaa hi ye Complete Binary Tree hi hoti.

`g1` (add) `g2` similarly:

```
add(el) : al.add(el);
          upHeapify();  -> Ab tak Heapify hoga jab tak el ahni khi j'sach nhi phuch jae
```

Ye hi upHeapify() ki tarah, jab tak jagah jahe tak `90` (replaced element) ko uski sahi position nahi mil jati.

**Getting child & parent:**

```
0 ka child   1, 2
1 ka child   3, 4
2 ka child   5, 6
3 ka child   7, 8

i ka child = (2i+1, 2i+2)
2i+1 -> Left Child
2i+2 -> Right Child  -- Remember it

parentIndex = (childIndex - 1) / 2   -- Remember it
```

### Full ArrayList-based PriorityQueue class

Add & remove complete karne hai.

```java
public static class PriorityQueue {
    ArrayList<Integer> data;

    public PriorityQueue() {
        data = new ArrayList<>();
    }

    public void swap(int i, int j) {
        int ith = data.get(i);
        int jth = data.get(j);
        data.set(i, jth);
        data.set(j, ith);
    }

    public void upheapify(int i) {
        if (i == 0) return;
        int pari = (i - 1) / 2;
        int pardata = data.get(pari);
        int cdata = data.get(i);
        if (pardata > cdata) {
            swap(i, pari);
            upheapify(pari);
        }
    }

    public void add(int val) {
        if (data.size() == 0) {
            data.add(val);
            return;
        }
        data.add(val);
        upheapify(data.size() - 1);
    }

    public void downheapify(int i) {
        int li = 2 * i + 1;
        int ri = 2 * i + 2;
        int priority = i;
        if (li < data.size() && data.get(li) < data.get(priority))
            priority = li;
        if (ri < data.size() && data.get(ri) < data.get(priority))
            priority = ri;
        if (priority != i) {
            swap(priority, i);
            downheapify(priority);
        }
    }

    public int remove() {
        swap(data.size() - 1, 0);
        int rval = data.remove(data.size() - 1);
        downheapify(0);
        return rval;
    }

    public int peek() {
        if (data.size() == 0) {
            System.out.println("Underflow");
            return -1;
        }
        return data.get(0);
    }

    public int size() {
        return data.size();
    }
}
```


### Dry Run — `remove()`

```
        10
      /    \
    20      30
   /  \    /  \
  40  50  60  70
 /\
80 90
```

`remove()` → highest priority element hatane hai, seedhe hata doge toh array ko aage shift karna hoga so `O(n)`. But we want `O(log n)`.

**Also → swap 1st & last element.**

Now removal from list is `O(1)`.

Now priority list khareb ho gyi, use phirse check karo as upper `90` so now we will do downHeapify().

```
        90
      /    \
    20      30
   /  \    /  \
  40  50  60  70
 /\
80
```

`(90, 20, 30)` mein se sabse chota kaun sa hai `20` so swap `20 & 90`.

```
        20
      /    \
    90      30
   /  \    /  \
  40  50  60  70
 /\
80
```

`ab (90, 40, 50)` mein se minimum kaun sa hai `40` so swap `(40, 90)`. Now see it is again following both property of Heap.

```
        20
      /    \
    40      30
   /  \    /  \
  90  50  60  70
 /\
80
```

Dono visualisation hamesha yaad rakhni hai (both — the array and the tree view — need to always be kept in mind).

### `add()` full trace, height O(log n)

```java
public void add(int val) {
    data.add(val);
    upheapify();
}
```

`g1` sees till root & `g2` sees till a particular node.

```
add -> O(1) + O(log n) = O(log n)
        ^         ^
   add to list  Up Heapify
   in ArrayList
```

`remove() -> highest priority element hatana hai, seedhe hata dete toh array ko aage shift karna hoga so O(n) to seedhe hi hoga`. So we will swap 1st & last element as last element delete karna is `O(1)` & then we will do downHeapify() as jo element root aaya he uska size vaise poore tree ki unbalance ho dega.

**Complexity:**
- **Time:** `add()` and `remove()` are both `O(log n)` — the array-as-tree representation guarantees a height of `O(log n)` (since the tree is always complete), and both `upheapify()` and `downheapify()` do at most one comparison-and-swap per level, so the total work is bounded by the height. `peek()` is `O(1)` — the highest-priority element always sits at index `0`.
- **Space:** `O(n)` for the underlying `ArrayList`, one slot per element stored.

---


# Why the Height of a Heap is $\log N$

In a Binary Heap, the tree is always **complete**, meaning every level is fully filled except possibly the last level, which is filled from left to right. This structure ensures the minimum possible height for a given number of nodes.

---

### 1. The Relationship Between Nodes and Levels
Let $H$ be the height of the tree (where a single root node has $H = 0$).

* **Level 0:** $2^0 = 1$ node
* **Level 1:** $2^1 = 2$ nodes
* **Level 2:** $2^2 = 4$ nodes
* **Level $h$:** $2^h$ nodes

In a **perfect** binary tree where every level is full, the total number of nodes $N$ is the sum of nodes at each level:
$$N = 2^0 + 2^1 + 2^2 + \dots + 2^H$$

This is a geometric series that sums to:
$$N = 2^{H+1} - 1$$

---

### 2. Solving for Height ($H$)
To find the height in terms of $N$, we rearrange the formula:

1.  Add 1 to both sides:
    $$N + 1 = 2^{H+1}$$
2.  Take the logarithm (base 2) of both sides:
    $$\log_2(N + 1) = H + 1$$
3.  Isolate $H$:
    $$H = \log_2(N + 1) - 1$$

For large $N$, the constants $(-1$ and $+1)$ become insignificant, leaving us with:
$$H \approx \log_2 N$$

---

### 3. Why this matters for Complexity
Every time you move down one level in a heap (during `heapify`), you are essentially cutting the remaining number of nodes you have to look at by **half**. This "divide by two" behavior is the definition of a logarithmic relationship.

* **Searching in a List:** $O(N)$
* **Moving through Heap Height:** $O(\log N)$

---

### Summary
> "A heap is a complete binary tree. Because the number of nodes doubles at each level, the number of levels required to hold $N$ nodes is only $\log_2 N$. This logarithmic height is what makes heap operations like insertion and deletion so fast."

---

## why `remove()`/`add()` in the array-tree stay `O(log n)`

because both operation are done on height of tress whoch is O(logN) we have seen

---

## Building a Heap from a Given Array 

**Method 1** → using `add()` we've already written: iski array ke values pe loop laga ke `add()` kar do heap mein:

```java
public MyPriorityQueue(int[] arr) {
    data = new ArrayList<>();
    for (int val : arr) {
        add(val);
    }
}
```


 previously we were adding in Priority Queue by `add()` function, ek ek karke add kar rahe the — ab poore array ek saath add karne hai. An array is given as input data & we need to convert that to Heap.



For `n` elements in array → `O(n log n)`.

**Why `TC -> O(n log n)` here?** Agar hume upheapify use kiya toh:

```
0 -> 0.2^0
1 -> 1.2^1
2 -> 2.2^2
...
h -> h.2^h
```

`T(n) = 0.2^0 + 1.2^1 + ... + h.2^h`, `h = O(log n)`, `T(n) = n log n`.

This was upheapify after adding to ArrayList, but now we perform downHeapify(). downHeapify() mein se leaves node ke kaam nahi padega.

we want to add all values in `O(n)` instead of `O(n log n)

**Method 2** 

### Why Down-Heapify is the Efficient Choice

As on leaves no need to do downheapify and leaves have maximum nodes so our maximum work is already done as leaves are already heap so no need to do donheapify on  them.

Now Complete Binary Tree property is satisfied but Heap Order property is not valid as Heap toh bana hi nahi. Lekin leaves nodes toh Heap hoti hi hai toh unpe downHeapify() nahi lagta. But non-leaf nodes upar downHeapify() lagega.

```
Level 0 -> 2^0.3  (3 levels neeche jaa sakte hain)
Level 1 -> 2^1.2  (2 levels neeche jaate hain)
Level 2 -> 2^2.1  (1 level neeche jaata hai)
Level 3 (leaves) -> 2^3.0  (leaves so neeche nahi jaana)
```

CBT mein leaves mein sabse zyada nodes hote hain. upHeapify() mein toh leaves ko sabse upper le jaana hota hai & root ko upper jaana hi nahi hota, so sabse zyada nodes ko sabse zyada kaam karna hota. If we use downHeapify() at leaves, nothing to do so a major portion of work is reduced.


### Efficient Constructor — using `downheapify()` from `n/2 - 1` to `0`

Non-leaf nodes are from `(n/2 - 1)` index, where `n` is no. of elements in array (`n` is not last index of array, it's `arraylist.size()`). So `n/2` is the 1st leaf index.

```java
public MyPriorityQueue(int[] arr) {
    data = new ArrayList<>();
    // for(int val: arr){
    //     add(val);
    // }

    // change it to add all values in O(n) instead of O(n log n)
    for (int val : arr) {
        data.add(val);
    }

    for (int i = data.size() / 2 - 1; i >= 0; i--) {
        downheapify(i);
    }
}
```



### Height-weighted node-count proof for `T(n) = O(n)`

```
Level 0 (root)         -> 2^(h-3).3 & so on
Level 1                -> 2^(h-2).2
Level (h-1)            -> 2^(h-1).1  (1 work as neeche jaane padega)
Level h (leaves)       -> 2^h.0      (nodes work as 0 neeche jaane padega)
```

$$T(n) = 2^h.0 + 2^{h-1}.1 + 2^{h-2}.2 + \dots + 2^0.h$$

We have to solve this AGP (arithmetico-geometric progression) here (via shift-and-subtract, matching the derivation below):

```
T(n)  =        2^h.0 + 2^(h-1).1 + ... + 2.(h-1) + 2^0.h
2T(n) = 2^(h+1).0 + 2^h.1 + ... + 2.h
```

Subtracting: `T(n) = 2^h + 2^(h-1) + ... + 2 - 2^0.h` (a GP, sum `= 2(2^h - 1)/(2-1)`)

$$T(n) = 2(2^h - 1) - h = 2(2^{\log n} - 1) - \log n = 2(n-1) - \log n = O(n)$$


# Why $n/2$ to $0$ in Build Heap?

When we convert a random array into a heap, we only call `heapify` (or `downheapify`) on the **non-leaf nodes**. 

### 1. Leaf Nodes are Already Heaps
In a complete binary tree represented as an array, roughly half of the nodes are **leaves** (nodes with no children). 
* A single node with no children **already satisfies** the Max-Heap or Min-Heap property by default.
* Therefore, calling `downheapify` on a leaf node does nothing; it's a wasted operation.

### 2. Identifying the Last Non-Leaf Node
In a zero-indexed array of size **$n$**:
* **Leaf Nodes** are located from index $\lfloor n/2 \rfloor$ to $n-1$.
* **Non-Leaf Nodes** are located from index $0$ to $\lfloor n/2 \rfloor - 1$.

By starting at $n/2 - 1$, we are starting at the very last node that actually has at least one child.

---

## Build heap from array 

Min heap
```cpp
class Solution {
       // Custom comparator logic based on isMax flag
 bool compareTo(int a, int b, bool isMax) {
        if (isMax)
            return a > b;
        else
            return a < b;
    }

 void downheapify(int pi, vector<int>& arr, int li, bool isMax) {
        int targetIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci <= li && compareTo(arr[lci], arr[targetIdx], isMax))
            targetIdx = lci;
        if (rci <= li && compareTo(arr[rci], arr[targetIdx], isMax))
            targetIdx = rci;

        if (pi != targetIdx) {
            swap(arr[pi], arr[targetIdx]); 
            downheapify(targetIdx, arr, li, isMax);
        }
    }
public:
    void buildMinHeap(vector<int> &nums) {
        int n=nums.size();
         for (int i = n / 2 - 1; i >= 0; i--) {
        downheapify(i, nums, n - 1,false);
    }
    }
};
```



### 3. The "Bottom-Up" Strategy
We process the nodes in **reverse order** ($n/2 \to 0$) to ensure that when we call `downheapify` on a parent, both of its child subtrees are **already valid heaps**.

1. We fix the smallest sub-trees at the bottom first.
2. We move up to the next level and fix those.
3. Finally, we fix the root.

If we started from the root ($0$) and moved down, the children might not be heaps yet, so the root wouldn't "sink" to its correct global position in one pass.

---

### 4. Mathematical Efficiency ($O(N)$ vs $O(N \log N)$)
This is the most surprising part:
* If you insert nodes one by one (top-down), the complexity is **$O(N \log N)$**.
* By using the **Bottom-Up** approach (starting from $n/2$), the complexity is actually **$O(N)$**.

**Why?**
Most nodes are at the bottom of the tree. In this approach, the nodes at the bottom move a very short distance (0 or 1 step), and only the few nodes at the top move the full height of the tree. The summation of this work converges to $O(N)$.

---

### Summary Table
| Strategy | Range | Complexity | Reason |
| :--- | :--- | :--- | :--- |
| **Top-Down** | $0$ to $n-1$ | $O(N \log N)$ | Treating it like $N$ separate insertions. |
| **Bottom-Up** | $n/2 - 1$ to $0$ | **$O(N)$** | Leaves are skipped; higher density of nodes do less work. |

---

## Heap impl general
```java
import java.util.ArrayList;

public class heap {
    private ArrayList<Integer> arr;
    private int size = 0;
    private boolean isMax = true;

    private void intialize(boolean isMax) {
        this.arr = new ArrayList<>();
        this.size = 0;
        this.isMax = isMax;
    }

    public heap() {
        intialize(true);
    }

    public heap(int[] arr, boolean isMax) { // O(n)
        intialize(isMax);
        for (int ele : arr)
            this.arr.add(ele);

        for (int i = this.arr.size() - 1; i >= 0; i--) {
            downHeapify(i);
        }

        this.size = arr.length;
    }

    // General Functions.

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public void add(int data) { // O(logN)
        this.arr.add(data);
        this.size++;
        upheapify(this.size - 1);
    }

    public int remove() { // O(logN)
        int n = this.arr.size();
        int rv = this.arr.get(0);

        swap(0, n - 1);
        this.arr.remove(n - 1);
        this.size--;

        downHeapify(0);
        return rv;
    }

    public int peek() { // O(1)
        return this.arr.get(0);
    }

    private int compareTo(int a,int b){
        if(isMax){
            return this.arr.get(a) - this.arr.get(b);
        }else{
            return this.arr.get(b) - this.arr.get(a);
        }

    }

    private void swap(int i, int j) { // O(1)
        int ei = arr.get(i);
        int ej = arr.get(j);

        arr.set(i, ej);
        arr.set(j, ei);
    }

    private void upheapify(int ci) { // O(logn)
        int pi = (ci - 1) / 2;
        if (pi >= 0 && compareTo(ci,pi) > 0) {
            swap(pi, ci);
            upheapify(pi);
        }
    }

    private void downHeapify(int pi) { // O(logn)
        int maxIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci < this.arr.size() && compareTo(lci,maxIdx) > 0)
            maxIdx = lci;
        if (rci < this.arr.size() && compareTo(rci,maxIdx) > 0)
            maxIdx = rci;

        if (maxIdx != pi) {
            swap(maxIdx, pi);
            downHeapify(maxIdx);
        }
    }

}

```



## Heapsort

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Required for std::swap

using namespace std;

class HeapSort {
public:
    // Custom comparator logic based on isMax flag
    static bool compareTo(int a, int b, bool isMax) {
        if (isMax)
            return a > b;
        else
            return a < b;
    }

    static void downheapify(int pi, vector<int>& arr, int li, bool isMax) {
        int targetIdx = pi;
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;

        if (lci <= li && compareTo(arr[lci], arr[targetIdx], isMax))
            targetIdx = lci;
        if (rci <= li && compareTo(arr[rci], arr[targetIdx], isMax))
            targetIdx = rci;

        if (pi != targetIdx) {
            swap(arr[pi], arr[targetIdx]); 
            downheapify(targetIdx, arr, li, isMax);
        }
    }

    static void display(const vector<int>& arr) {
        for (int ele : arr)
            cout << ele << " ";
        cout << endl;
    }
};

int main() {
    vector<int> arr = { 10, 20, 30, -2, -3, -4, 5, 6, 7, 8, 9, 22, 11, 13 };
    int n = arr.size();
    
    // isMax = true -> Ascending Sort
    // isMax = false -> Descending Sort
    bool isMax = true; 

    // Build Heap: Start from the last non-leaf node (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; i--) {
        HeapSort::downheapify(i, arr, n - 1, isMax);
    }

    // Extraction phase
    int li = n - 1;
    while (li >= 0) {
        swap(arr[0], arr[li--]); // Move current root to the end
        HeapSort::downheapify(0, arr, li, isMax);
    }

    HeapSort::display(arr);

    return 0;
}
```
1st step build heap from array assume min heap 

2ns step extraction phase

# The Extraction Phase: Turning a Heap into a Sorted Array

Once the `Build-Heap` phase is finished, the maximum element (in a Max-Heap) is at `arr[0]`. However, the rest of the elements are not in order. The Extraction Phase fixes this.

### 1. The Logic Step-by-Step
We repeat the following process until the heap is empty:

1.  **Swap:** We swap the root (`arr[0]`) with the last element of the current heap (`arr[li]`). 
    * *Why?* This "locks" the largest element into its correct final position at the end of the array.
2.  **Shrink:** We decrease the heap size (`li--`). 
    * *Why?* We don't want to touch the elements we've already "locked" at the back.
3.  **Heal (Down-Heapify):** The new root is now a small value that was swapped up from the bottom. It violates the heap property. We call `downheapify` to sink it back to its correct spot.
    * *Why?* To bring the *next* largest element to `arr[0]` for the next iteration.

---

### 2. Sorting Direction
The type of heap you build determines the final sort order:

| Heap Type | Extraction Result | Final Array Order |
| :--- | :--- | :--- |
| **Max-Heap** | Largest elements moved to the back | **Ascending** (1, 2, 3...) |
| **Min-Heap** | Smallest elements moved to the back | **Descending** (3, 2, 1...) |

---

### 3. Complexity Analysis
* **Number of Extractions:** We perform $N$ extractions.
* **Work per Extraction:** Each `downheapify` takes $O(\log N)$ time (the height of the tree).
* **Total Time:** $N \times \log N = O(N \log N)$.

---

### 4. Visualization of the "Locking" Effect
Imagine an array `[30, 20, 10]`:
1. **Swap** 30 and 10: `[10, 20, | 30]` (30 is locked).
2. **Heapify** 10: 20 moves up: `[20, 10, | 30]`.
3. **Swap** 20 and 10: `[10, | 20, 30]` (20 is locked).
4. **Result:** `[10, 20, 30]` (Fully Sorted).

### Summary for Interviews
> "The extraction phase is necessary because a heap is only a **partial ordering**. To get a **total ordering** (a sorted array), we repeatedly swap the maximum element to the end of the array and rebuild the heap with the remaining elements. This takes $O(N \log N)$ time."

for making heap from array we have two approaches 

1. Bottom up --> for non leaf node we call downheapify .this has TC of O(n)
2. top down--> for each array element insert in heap and apply upheapify.normal insertion of heap ,so for n insertions it takes o(n log n) time 

we use 1st one to build heap from array as takes O(n) time and let us discuss this in detail now




## Q Heapify Algorithm

Given an array of **n** integers, convert the array into a **Max-Heap** using the **Heapify** algorithm.

A **Max-Heap** is a complete binary tree where the value of each node is greater than or equal to the values of its children. In the array representation of a heap:
- The root is at index `0`.
- For any element at index `i`, its left child is at index `2*i + 1` and its right child is at index `2*i + 2`.

The goal is to rearrange the elements in the array in-place so that they satisfy the Max-Heap property.

### Example 1
**Input:** `arr = [4, 10, 3, 5, 1]`  
**Output:** `[10, 5, 3, 4, 1]`  

### Example 2
**Input:** `arr = [1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17]`  
**Output:** `[17, 15, 13, 9, 6, 5, 10, 4, 8, 3, 1]`  

### Constraints
- `1 <= arr.length <= 10^5`
- `1 <= arr[i] <= 10^6`


### Min heap it is 

```cpp
class Solution {
    void upheapify(int idx,vector<int>& arr){
        int pidx=(idx-1)/2;
        if(pidx>=0 && arr[pidx]>arr[idx]){
            swap(arr[pidx],arr[idx]);
            upheapify(pidx,arr);
        }
    }
    void downheapify(int idx,vector<int>& arr ){
        int n=arr.size();
        int residx=idx;
        int lidx=2*idx+1;
        int ridx=2*idx+2;
        if(lidx<n && arr[residx]>arr[lidx]){
            residx=lidx;
        }
        if(ridx<n && arr[residx]>arr[ridx]){
            residx=ridx;
        }
        if(residx!=idx){
            swap(arr[residx],arr[idx]);
            downheapify(residx,arr);
        }

    }
public:
    void heapify(vector<int> &nums, int ind, int val) {
        int oldVal=nums[ind];
        nums[ind]=val;
        if(oldVal>nums[ind]) upheapify(ind,nums);
        else downheapify(ind,nums);
    }
};
```
if old val was greater than and new value is less and it is min heap so offcurse value will move up

if old value is less than new value  and it is min heap so offcourse larger value will move down so we use downheapify


## Basic Min Heap code 

```cpp 
class Solution{
    vector<int>heap;
    void upheapify(int idx){
        int pidx=(idx-1)/2;
        if(pidx>=0 && heap[pidx]>heap[idx]){
            swap(heap[pidx],heap[idx]);
            upheapify(pidx);
        }
    }
    void downheapify(int idx ){
        int n=heap.size();
        int residx=idx;
        int lidx=2*idx+1;
        int ridx=2*idx+2;
        if(lidx<n && heap[residx]>heap[lidx]){
            residx=lidx;
        }
        if(ridx<n && heap[residx]>heap[ridx]){
            residx=ridx;
        }
        if(residx!=idx){
            swap(heap[residx],heap[idx]);
            downheapify(residx);
        }

    }
    void heapify( int ind, int val) {
        int oldVal=heap[ind];
        heap[ind]=val;
        if(oldVal>heap[ind]) upheapify(ind);
        else downheapify(ind);
    }
    void add(int val){
        heap.push_back(val);
        upheapify(heapSize()-1);
    }
    void remove(){
        if(heapSize()==0) return;
        if(heapSize()==1) {
            heap.pop_back();
            return;
        }
        int idx=heapSize()-1;
        swap(heap[0],heap[idx]);
        heap.pop_back();
        downheapify(0);
    }
    public:

        void initializeHeap(){

        }

        void insert(int key){
            add(key);
        }

        void changeKey(int index, int new_val){
            heapify(index,new_val);
        }

        void extractMin(){
            remove();
        }

        bool isEmpty(){
            return heap.size()==0;
        }

        int getMin(){
            if(isEmpty()==true) return -(1e5+1);
            return heap[0];
        }

        int heapSize(){
            return heap.size();
        }
};

```

## Basic max heap code
```cpp

class Solution{
    vector<int>heap;
    void upheapify(int idx){
        int pidx=(idx-1)/2;
        if(pidx>=0 && heap[pidx]<heap[idx]){
            swap(heap[pidx],heap[idx]);
            upheapify(pidx);
        }
    }
    void downheapify(int idx ){
        int n=heap.size();
        int residx=idx;
        int lidx=2*idx+1;
        int ridx=2*idx+2;
        if(lidx<n && heap[residx]<heap[lidx]){
            residx=lidx;
        }
        if(ridx<n && heap[residx]<heap[ridx]){
            residx=ridx;
        }
        if(residx!=idx){
            swap(heap[residx],heap[idx]);
            downheapify(residx);
        }

    }
    void heapify( int ind, int val) {
        int oldVal=heap[ind];
        heap[ind]=val;
        if(oldVal<heap[ind]) upheapify(ind);
        else downheapify(ind);
    }
    void add(int val){
        heap.push_back(val);
        upheapify(heapSize()-1);
    }
    void remove(){
        if(heapSize()==0) return;
        if(heapSize()==1) {
            heap.pop_back();
            return;
        }
        int idx=heapSize()-1;
        swap(heap[0],heap[idx]);
        heap.pop_back();
        downheapify(0);
    }
    public:

        void initializeHeap(){

        }

        void insert(int key){
            add(key);
        }

        void changeKey(int index, int new_val){
            heapify(index,new_val);
        }

        void extractMax(){
            remove();
        }

        bool isEmpty(){
            return heap.size()==0;
        }

        int getMax(){
            if(isEmpty()==true) return -(1e5+1);
            return heap[0];
        }

        int heapSize(){
            return heap.size();
        }
};
```


## Convert min heap to  max heap


```cpp

class Solution {
        void downheapify(int idx,vector<int>& heap ){
        int n=heap.size();
        int residx=idx;
        int lidx=2*idx+1;
        int ridx=2*idx+2;
        if(lidx<n && heap[residx]<heap[lidx]){
            residx=lidx;
        }
        if(ridx<n && heap[residx]<heap[ridx]){
            residx=ridx;
        }
        if(residx!=idx){
            swap(heap[residx],heap[idx]);
            downheapify(residx,heap);
        }

    }
public:
    vector<int> minToMaxHeap(vector<int> nums) {
        int n=nums.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
        downheapify(i, nums);
    }
    return nums;
    }
};
```
