

By default a Java `PriorityQueue` is a **min-heap** — the smallest element gets the most priority.

```
peek()    -> O(1)
add()     ]
remove()  ]  -> O(log n)
```

- **`remove()`** → removes the most-priority element, i.e. `30` here, since the min element gets the most priority.
- **`peek()`** → returns the most-priority element (without removing it).

### Basic Demo

```java
import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        pq.add(20);
        pq.add(40);
        pq.add(33);
        pq.add(57);
        pq.add(10);
        pq.add(67);

        System.out.println(pq.peek()); // 10 is o/p
    }
}
```

After this, if we do `pq.remove()`, `10` is removed, and then if we do `pq.remove()` again, `20` is removed — as the new minimum element is taken as the most-priority element.

### Sort an array using a Priority Queue

```java
int[] arr = {10, 57, 33, 44, 56, 11, 98};
for (int val : arr) {
    pq.add(val);      // n insertions, each O(log n) -> O(n log n)
}

while (pq.size() > 0) {
    System.out.println(pq.peek());
    pq.remove();       // n removals, each O(log n) -> O(n log n)
}
```

`n log n` (insertions) `+ n log n` (removals) `= 2n log n = O(n log n)` — so this sorts the array in `O(n log n)`.

### Making a Max-Heap

```java
PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());
```

Priority on rank basis — chote ho toh most priority (by default, the *smaller* value has the most priority in a min-heap). Passing `Collections.reverseOrder()` flips this — **to set priority of the max element as 1st**, i.e. this makes it a max-heap.

---

## Q. K-Largest Element(s)

**Practice Question:** LeetCode 215 — Kth Largest Element in an Array

**Example:**

```
Input:  [10, 19, 3, 74, 86, 57, 24, 5, 11],  k = 3
Output: 86, 74, 57   [Top 3 largest elements]
```

Constraint: `k <= N` (`N` is the array length).

### Naive Approach

Make a Priority Queue with the Max element as most priority (i.e. a max-heap of **all** `n` elements), then do `k` removals from it.

```
TC -> O(n log n) + O(k log n)
      (n log n to fill the Priority Queue with all n elements, then k log n for the k removals)
SC -> O(n)
```

We want better: **`TC -> O(n log k)` & `SC -> O(k)`** — the priority queue should never hold more than `k` elements at once.

### Optimized Approach — Dry Run (k = 3)

Keep a **min-heap of size k**. For every element beyond the first `k`, compare it with the heap's minimum (`peek()`); if the new element is bigger, remove the min and insert the new element instead. This way the heap always holds the `k` largest elements seen so far, with the smallest of those `k` sitting on top.

```
arr = [10, 19, 3, 74, 86, 57, 24, 5, 11],  k = 3

Initially, fill heap with the first k elements: [10, 19, 3]

At 74: check the min value & compare — 74 > 3, so remove 3 & put 74
       heap: [10, 19, 74]

At 86: 86 > 10 (the min), so remove 10 & put 86 there
       heap: [86, 19, 74]

At 57: 57 > 19, so put 57 there instead of 19
       heap: [86, 74, 57]

At 24: 24 < 57 (the current min) -> i++  (skip, don't insert)
At 5:  5 < 57 -> i++  (skip)
At 11: 11 < 57 -> i++  (skip)

Final heap: [86, 74, 57]
```

For K-largest: keep removing the minimum & keep making the heap "bigger" (i.e. keep only the largest candidates) — it's like: small nikalte jao & bade banate jao (keep discarding the small ones, keep building up with the bigger ones).

**Complexity:** `O(n log k)` — `k` elements sit in the priority queue (each op costs `log k`), and we do this insertion/comparison `n` times total. **Space:** `O(k)`.

### Code

```java
import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        int[] arr = new int[n];

        for (int i = 0; i < n; i++) {
            arr[i] = Integer.parseInt(br.readLine());
        }

        int k = Integer.parseInt(br.readLine());

        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int i = 0; i < k; i++) {
            pq.add(arr[i]);              // k log k
        }
        for (int i = k; i < arr.length; i++) {
            int val = pq.peek();
            if (val < arr[i]) {
                pq.remove();
                pq.add(arr[i]);
            }
        }                                  // (n-k) log k
        while (pq.size() > 0) {
            System.out.println(pq.peek());
            pq.remove();                   // k log k
        }
    }
}
```

Total: `k log k + (n-k) log k + k log k = (n+k) log k`. Since `k << n`, this simplifies to **`n log k`**.

### Variant — output in decreasing order

**Example 2:** `nums = [3,2,3,1,2,4,5,5,6], k = 4` → `Output: 4`

Decreasing order — bade se chote (largest to smallest): agar output aise chahiye toh, ArrayList mein bhar ke ulta display kar do (if the output is required in that order, collect the popped elements into an `ArrayList`, then display it reversed):

```java
public static void solve(int n, int[] arr, int k) {
    PriorityQueue<Integer> pq = new PriorityQueue<>();
    for (int i = 0; i < k; i++) {
        pq.add(arr[i]);
    }
    for (int i = k; i < arr.length; i++) {
        int val = pq.peek();
        if (val < arr[i]) {
            pq.remove();
            pq.add(arr[i]);
        }
    }
    ArrayList<Integer> al = new ArrayList<>();
    while (pq.size() > 0) {
        al.add(pq.peek());
        pq.remove();
    }
    for (int i = al.size() - 1; i >= 0; i--) {
        System.out.print(al.get(i) + " ");
    }
}
```

### LeetCode 215 — Accepted Solution

```java
class Solution {
    public int findKthLargest(int[] arr, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        for (int i = 0; i < k; i++) {
            pq.add(arr[i]);
        }
        for (int i = k; i < arr.length; i++) {
            int val = pq.peek();
            if (val < arr[i]) {
                pq.remove();
                pq.add(arr[i]);
            }
        }
        return pq.peek();
    }
}
```

**Complexity:**
- **Time:** `O(n log k)` — as derived above: `k log k` to seed the heap, `(n-k) log k` to scan the rest, and (for the single-answer version) an `O(1)` final `peek()`. Since `k <= n`, this is always at least as good as, and typically much better than, sorting the whole array (`O(n log n)`).
- **Space:** `O(k)` for the heap — it never holds more than `k` elements at a time.

**LeetCode Solutions for Kth Largest — comparison of approaches:**

1. **Quick Select Algorithm** (for finding just the `k`th largest, not all top-`k`) → `O(N)` on average, but `O(N²)` in the worst case.
2. **Using a heap** (as above) → `O(N log k)` time, with `O(k)` extra space.
