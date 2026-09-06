
**Hash Map operations and their time complexities:**
- Insert → O(1)
- Delete → O(1)
- Search on some index/key → O(1)

All three are O(1) — this is the power of Hash Map.

---

## Direct Access Table (DAT)

**Problem:** Count the frequency of elements in: `0, 1, 8, 4, 6, 8, 9, 1, 1, 0, 1`

**Solution approach:** Use a **Direct Access Table (DAT)**

What is a DAT? It is:
- Just a Hash Map where keys are numbers
- OR simply a plain array (if the frequency/value range is not very large)

**When can you use a plain array instead of a Hash Map?**
When the key range is small and known. For example, if all elements are between 0–9, you can use an array of size 10 as your "hash map."

**Rule:** For Count Sort type problems → Use DAT

---

## How Hash Map Works Internally

**The mechanism:**

There is a **Pool of Keys** (e.g., A, B, C, D, E, F, G, H).

These keys are passed through a **Hash Function**.

The Hash Function is applied ON the key and returns a number (an array index).

The value is then stored at that index in an array.

**So:** Based on the value returned by the Hash Function, the value is placed at that array index. The value is stored in the array at that position.

**Visually:**
```
Key (e.g., "C") → [Hash Function] → index 2 → Array[2] = value
```

This is why lookup is O(1) — given a key, apply the hash function, get the index directly, access the array at that index. No searching needed.

---

## Collision & Chaining

**Collision:** A collision occurs when **multiple keys map to the same array index** through the hash function.

**Example:** If h("A") = 3 and h("G") = 3, both want to go to index 3 — that's a collision.

**How to avoid collision?**
Use a better hash function that distributes keys more uniformly.

**But if collision still occurs, two main techniques to handle it:**

**Technique 1 — Chaining:**
- At each array index, instead of storing one value, store a **Linked List**
- When multiple keys map to the same index, all their values go into the Linked List at that index
- When searching, go to the index and then search within the Linked List

**Interview Tip:**
Chaining is the primary collision resolution technique expected in coding interviews because it is straightforward to implement and reason about.

**Searching in Chaining:**
We do searching within the Linked List at each index.

---

## Chaining: Load Factor & Time Complexity

**Linked List search takes O(N)** — but we try to keep the Linked List size limited.

**How?** By keeping the Linked List of size λ (lambda). This limits the size of each LL, so:
- Search time in each LL = O(λ)
- Insert time = O(λ)
- Delete time = O(λ)

Since λ is limited (kept small by design), we say insert and delete time is effectively **O(1)**.

**λ (lambda) is called the Load Factor.**

The load factor = number of elements / table size. When it gets too large, the hash table **rehashes** (resizes) itself to keep λ small.

**Other techniques for collision management exist**, such as Open Addressing, covered next.

---

## Open Addressing: Introduction & Linear Probing Setup

**Technique 2 — Open Addressing:**
In open addressing, all elements are stored IN the array itself — no linked lists, no extra memory outside the array.

When a collision occurs, we look for another empty slot in the array.

**Example setup:**
- Elements to insert: `11, 21, 44, 31, 22, 45, 43`
- Table size: 10
- Hash function: `h(x) = x % 10`

**Starting insertions:**

- 11 % 10 = 1 → 11 maps to index **1** ✓
- 21 % 10 = 1 → collision! Index 1 is taken → 21 goes to **next empty space** → index **2** ✓

**Key guarantee:** It is guaranteed that we will never have more elements than the table size. So we will always find an empty slot.

---

## Linear Probing: Continuing Insertions

Continuing with the remaining insertions:

- 44 % 10 = 4 → maps to index **4** ✓
- 31 % 10 = 1 → index 1 is filled → try index 2 → filled → try index 3 → **31 goes to 3** ✓

**What is Linear Probing?**
When a collision happens, we search **linearly** (one by one, +1 each time) for the next empty slot. This linear search for an empty probe space is called **Linear Probing**.

**Table state so far:**

```
Index: 0  | 1  | 2  | 3  | 4  | 5 | 6 | 7 | 8 | 9
Value: _  | 11 | 21 | 31 | 44 | _ | _ | _ | _ | _
```

**Now comes 22:**
- 22 % 10 = 2 → index 2 is filled → linear probing → goes to next empty space → **index 5** ✓

(Index 3 and 4 are also filled, so probing goes 2→3→4→5, landing at 5.)

---

## Disadvantage of Linear Probing: Clustering

**Disadvantage of Linear Probing → Clustering**

Suppose indices 1, 2, 3, 6, 7 are already filled (a cluster exists).

**Question:** What is the probability of the next new element going to index 4?

At index 4, an element can arrive there if its hash maps to indices 1, 2, 3, OR 4 — because from any of those filled indices, linear probing will eventually push it to index 4.

- Elements ending in 1 → hash to 1 → probe → land at 4
- Elements ending in 2 → hash to 2 → probe → land at 4
- Elements ending in 3 → hash to 3 → probe → land at 4
- Elements ending in 4 → hash directly to 4

So probability of landing at index 4 = **4/10 = 40%**

Compare:
- Index 5 → only elements ending in 5 → probability = **1/10 = 10%**
- Index 8 → elements ending in 6, 7, 8 → probability = **3/10 = 30%**
- Index 9 → only elements ending in 9 → probability = **1/10 = 10%**
- Index 0 → only elements ending in 0 → probability = **1/10 = 10%**

All these add up to 100%.

**The problem:** The probability of getting filled NEAR the cluster (index 4) is **much higher** than other indices. So the cluster will keep growing!

---

## Primary Clustering: The Snowball Effect

**The real disadvantage:**
The chances of getting filled near a cluster is MORE than at any other index.

**Snowball analogy:**
Imagine a snowball rolling on snow. As it rolls, it picks up more snow and gets bigger. The bigger it gets, the MORE snow it picks up per roll. It just keeps growing.

Similarly:
- A smaller cluster has less probability of attracting the next element
- A larger cluster has MORE probability of attracting the next element
- So larger clusters grow even faster — a self-reinforcing cycle

This is called the **Clustering Effect** (or **Primary Clustering**) and we must avoid it.

This is why we don't use Linear Probing in practice.

---

## Search & Deletion in Linear Probing

**Search in Linear Probing:**
- Compute the hash index for the key
- Start searching linearly from that index
- Continue until: the value is found OR an **empty index** is found (if empty, the element doesn't exist)

**Deletion — The Problem:**

Suppose the table has: `11 | 21 | 31 | 41 | 55` at indices 1–5.

Now delete **21** from index 2.

Then search for **31**:
- 31 % 10 = 1 → go to index 1 (found 11, not 31)
- Linear probe → go to index 2 → it's EMPTY now (21 was deleted)
- The algorithm concludes: **31 is not found** ❌

But 31 IS there at index 3! The deletion of 21 created a false empty slot that terminated the search too early.

**Solution → Use a Marker (Tombstone):**
Instead of truly deleting (making the slot empty), we place a **Marker** (also called a tombstone) at the deleted slot. The marker means: "Something was here before, but it's been deleted."

When searching and we encounter a Marker, we **continue searching** — we do NOT stop. We only stop if we find a genuinely empty slot (one that never had an element).

---

## Tombstone Marker Behavior & Worst Case Analysis

**Behavior on seeing a Marker during search:**
On seeing a Marker → **continue the search** (don't stop, the element might be further ahead).

**Time Complexity of Insert, Search, Delete in Open Addressing:**
In the **worst case**, they can all become **O(N)** — this happens when only one giant cluster exists and every probe goes through it linearly. It's essentially a linear search at that point.

**Clustering is the core problem here.** That's why we don't prefer Linear Probing.

---

## Quadratic Probing (Solution to Primary Clustering)

**Why Linear Probing fails:** Because we jump linearly (+1 each time), we create physical adjacent clusters (Primary Clustering).

**Solution → Quadratic Probing:**
Instead of jumping by 1 each time, we jump by **quadratic increments** (1, 4, 9, 16…).

**Formula for Linear Probing:**
`h(k, i) = (h(k) + i) mod TableSize`
(where i = collision number: 1st collision i=1, 2nd collision i=2, etc.)

**Formula for Quadratic Probing:**
`h(k, i) = (h(k) + c₁·i + c₂·i²) % TableSize`

This means:
- 1st collision → jump by c₁·1 + c₂·1² positions
- 2nd collision → jump by c₁·2 + c₂·4 positions
- 3rd collision → jump by c₁·3 + c₂·9 positions
- The jumps grow quadratically, spreading elements far apart

**Result:** No physical adjacent clusters form. Elements spread out more.

---

## Secondary Clustering in Quadratic Probing

**Quadratic Probing solves Primary Clustering**, but introduces a new problem.

Even though elements don't cluster physically (no adjacent filled slots), consider this:

If two keys X and Y both hash to the **same initial index**, then:
- They will both follow the **exact same probe sequence** after the collision
- 1st probe → same position
- 2nd probe → same position
- And so on...

They fight for the same slots even if they are physically far apart in the array. They create a **virtual cluster** — a "Secondary Cluster."

**This is called Secondary Clustering.**

Even though there are no contiguous physical clusters, if two elements map to the same initial index, they will follow the exact same probe sequence across the array. This forms a virtual cluster, known as **Secondary Clustering**.

---

## Double Hashing: Solution to Secondary Clustering

**Problem with Quadratic Probing:** Two keys colliding at the same index always follow the same probe sequence → Secondary Clustering.

**Root cause:** The probe sequence after collision is the same for both keys because the jump formula only depends on the collision number `i`, not on the key itself.

**Solution → Double Hashing:**
Use a SECOND, DIFFERENT hash function `h'(k)` that depends on the KEY:

`h(k, i) = (h(k) + i · h'(k)) mod TableSize`

Where:
- `h(k)` = primary hash function
- `h'(k)` = secondary hash function (completely different from h(k))
- `i` = collision number

**Now:** If keys X and Y both collide at the same index, their jump sizes are different because `h'(X) ≠ h'(Y)`. So they follow **completely different probe sequences** after the collision.

**No Secondary Clustering!**

**Key Principle:** When two keys collide, their subsequent probe sequences must diverge. Double Hashing achieves this because the step size depends on the key itself.

---

## Secondary Hash Function h'(k) Design & Triple Hashing

**What should h'(k) be?**
The secondary hash function `h'(k)` can be something like **SHA-256** or any function that guarantees:

> Two different values (keys) will give two different outputs (indices).

This ensures that colliding keys will always have different jump sizes and thus different probe sequences.

**Triple Hashing:**
Some people even use Triple Hashing — a third hash function. But:
- More complex to implement
- More time-consuming to compute
- It's a **tradeoff**: more hash functions = better collision management but more complexity

**General rule in practice:**
We use **Double Hashing only** — it provides a good balance between collision management quality and implementation complexity. Triple hashing is rarely worth it.

---

## Interview Context & Purpose

**This entire material** (Heap, Recursion, Hash Map) is prepared for:
- **Telephonic rounds** (phone interviews)
- **Face-to-face rounds** at top product companies like **Facebook (Meta)** and **Amazon**

This is interview-level DSA content — the depth of understanding expected for FAANG-level technical interviews.


# HashMap Physics: Load Factors & Collisions

### 1. The Workflow
`Key` -> `Hash Function` -> `Index` -> `Storage`

### 2. Load Factor ($\alpha$)
- **Formula:** $n / m$ (Elements / Capacity).
- **Threshold (0.75):** When reached, the map doubles in size (Rehash).
- **Physics:** High load factor = High collisions = Slow performance.

### 3. Collision Resolution
1. **Chaining:** Use Linked Lists at each index. 
   - *Pro Tip:* Java 8+ converts long lists (8+ items) into **Red-Black Trees** to keep search $O(\log N)$.
2. **Open Addressing:** Find the next empty slot.
   - Linear Probing: $i+1$
   - Quadratic Probing: $i+k^2$
   - Double Hashing: $i + k \cdot hash_2(key)$

### 4. Complexity
- **Average:** $O(1)$ for Search, Insert, and Delete.
- **Worst Case:** $O(n)$ (When all keys collide into one slot).

## HashMap Implementation — From Scratch

HashMap implementation. HashMap is a table of Key & values.

**HashMap fn →** `put()`, `containsKey()`, `keySet()`, `Set()`, `remove()`, `size()`

**Eg:**

```
Key      Value
India    135
China    200
Poland   80
US       280
```

New we `put(India,140)` → put dekhega ki India hai ya nahi. If already hai toh it will update the India value. `we do put(Pak,50)` then it will be inserted.

Put ke case chota hash fn decide karta hai key kis bucket mein jaegi.

**`Set()`** → key jo hai Map mein jo uski value return ho jaegi & key nahi hai toh Null return hoga.

**`containsKey()`** → return true if key hai Else return false.

**`remove()`** → return value after deletion if key hai, then returns null.

*In demo fn mein parameter Key jati hai. All 3 are `O(1)` operation.*

**`keySet()`** → returns all Keys.

New lets see how these fn work in `O(1)`:

```java
public void put(K key, V value) throws Exception { }
public V get(K key) throws Exception { }
public boolean containsKey(K key) { }
public V remove(K key) throws Exception { }
public ArrayList<K> keyset() throws Exception { }
```

**Syntax of various function. HashMap is implemented by Array of Linked List (Address of Array called as Buckets).**

```
[  0  |  1  |  2  |  3  ]
   |     |     |     |
(J,27) (Pak,50) (US,60) (NJ,3)
   |                       |
(C,140)                (Iceland,1)
```

When we do `map.put(UK,200)`, there is Hash fn applied & that tells ki kaun se index ke jaega UK. If UK nahi pade if pade hai toh bataega kaun se index ke pade hai. Suppose hash fn gives bucket 3. So UK is compared with LL on bucket 3, if UK present or not — if UK nil hai toh update value of UK, else insert UK.

Hash fn chalane ko board sirf uhi bucket se compare karni baki sabse nahi.

### Load Factor

```
n → Total Elements (Jo Add hui hai)   n = 8
N → no. of buckets (Array indices)    N = 4

λ = n/N = 8/4 = 2
```

Average no. of Elements per bucket or **Loading factor**.

Can we say `put` ki Complexity `O(λ)` hai kyoki uhne bucket ke elements se hi compare kiya:

```
λ ≤ k     k is Threshold value. λ hmeshe k se neeche hi rhega [kaise? will discuss later] [k is some constant]

Get() → put Key in hash fn, hash fn tells bucket. Sirf bucket vale Elements se compare, so here TC also O(λ)

ContainsKey() → put Key in hash fn. hash fn tells bucket no. Sirf jo usi bucket ke Element hain unse compare karo & if present hai then return true Else false, TC → O(λ)

Remove() → Also same. if present hai then delete & return Value Else return null so TC → O(λ)

Size() → n hi size hai

keySet() → All keys ko store karlo ArrayList mein
```

**New Question is how to make `λ <= k`?** So for that we use a concept called as **Rehashing**.

After every `put`, ya toh update hoga ya insert hoga & update hone se `n` toh same hi hai & `λ` bhi same hi rahega. If insert hua toh `n` bhi bda jayega → `λ` bhi bda jayega.

**Now if `λ > k` then we do rehashing.**

```
n = 8, N = 4, λ = 2, k = 2 suppose
λ <= k

Now we insert 1 more Element so n = 9

λ = 9/4 = 2.25 > k
```

**Now we do rehashing:** We create a new Array of double size of this & there we put all the Elements, so we increase `N`. The `λ, k` rehte same, the `N`, `2N` ho jaega.

```
N = 8 so λ = 9/8 = 1.11.... < k
```

Now we insert Each & Every Element of previous Array & fill the Elements in new array by `put()` call. Possible hai ki phle jaise nahi the & we get a different configuration:

```
[  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  ]
  |     |     |     |     |     |
                                   |
```

So `λ < k` again → **Once in a while we do rehashing [a costly operation]**.

```
put(), get(), remove(), containsKey() → O(λ)
```

`λ = O(k)` where `k` is some constant, so `λ = O(1)` for the set, containsKey is `O(1)`.

`λ` is controlled by rehashing — Once in a while we do a costly operation like in ArrayList we double the size.

**Toh `λ` is controlled by rehashing which makes TC → `O(1)`.**

### Given Code Skeleton

```java
import java.io.*;
import java.util.*;

public class Main {
    public static class HashMap<K, V> {           // generic ✅ supports die hei as hashcode
        private class HMNode {                      // kese ki bi bn
            K key;
            V value;                                 // n(nodes) attribute hai (int, String, boolean, int) dono
            HMNode(K key, V value) {
                this.key = key;
                this.value = value;
            }
        }

        private int size;                            // n
        private LinkedList<HMNode>[] buckets;         // N = buckets.length

        public HashMap() {
            initbuckets(4);                           // LL ko array hai buckets
            size = 0;                                 // 9 bins ke buckets
        }

        private void initbuckets(int N) {
            buckets = new LinkedList[N];
            for (int bi = 0; bi < buckets.length; bi++) {
                buckets[bi] = new LinkedList<>();     // while N LL initialise
            }
        }

        public void put(K key, V value) throws Exception {
            // write your code here
        }

        public V get(K key) throws Exception {
            // write your code here
        }

        public boolean containsKey(K key) {
            // write your code here
        }

        public V remove(K key) throws Exception {
            // write your code here
        }

        public ArrayList<K> keyset() throws Exception {
            // write your code here
        }

        public int size() {
            // write your code here
        }

        public void display() {
            System.out.println("Display Begins");
            for (int bi = 0; bi < buckets.length; bi++) {
                System.out.print("Bucket" + bi + " ");
                for (HMNode node : buckets[bi]) {
                    System.out.print(node.key + "@" + node.value + " ");
                }
                System.out.println(".");
            }
            System.out.println("Display Ends");
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        HashMap<String, Integer> map = new HashMap();

        String str = br.readLine();
        while (str.equals("quit") == false) {
            if (str.startsWith("put")) {
                String[] parts = str.split(" ");
                String key = parts[1];
                Integer val = Integer.parseInt(parts[2]);
                map.put(key, val);
            } else if (str.startsWith("get")) {
                String[] parts = str.split(" ");
                String key = parts[1];
                System.out.println(map.get(key));
            } else if (str.startsWith("containsKey")) {
                String[] parts = str.split(" ");
                String key = parts[1];
                System.out.println(map.containsKey(key));
            } else if (str.startsWith("remove")) {
                String[] parts = str.split(" ");
                String key = parts[1];
                System.out.println(map.remove(key));
            } else if (str.startsWith("size")) {
                System.out.println(map.size());
            } else if (str.startsWith("keyset")) {
                System.out.println(map.keyset());
            } else if (str.startsWith("display")) {
                map.display();
            }
            str = br.readLine();
        }
    }
}
```

### The Hash Function

Lets see Hash fn. Java has a fn called `hashCode()` jo ek intgr return krta hai. Key & parameter mein sab letr `int, boolean, String`.

Ye jo `hashCode()` ne return kia vah kuch bhi ho sakta hai (even-vo bhi), sket, but sirf hume bucket index chahiye jo bucket.length se chota ho — that's why hum `Math.abs(hc) % buckets.length` return karte hai.

```java
int hc = key.hashCode();
return Math.abs(hc) % bucket.length;
```

```java
public void put(K key, V value) throws Exception {
    int bi = hashfn(key);                    // bi = bucket index
    int di = getIndexWithinBucket(key, bi);  // di = data index [index within bucket]
}

private int hashfn(K key) {
    int hc = key.hashCode();
    return Math.abs(hc) % buckets.length;
}
```

Hme chahiye bucket length se chota banane do mod.

**Now we do `map.put(S,7)`:**

```
int bi = hashfn(S)     bi = 2

Now 2 ke LL ke loop lagega
```

```java
private int getIndexWithinBucket(K key, int bi) {
    int di = 0;
    for (HMNode node : buckets[bi]) {
        if (node.key.equals(key)) {
            return di;
        }
        di++;
    }

    return -1;
}
```

Loop within bucket index. If bi de hai toh return `di`. Else `-1`. If `-1` then do insert:

```java
public void put(K key, V value) throws Exception {
    int bi = hashfn(key);
    int di = getIndexWithinBucket(key, bi);

    if (di != -1) {   // only update
        HMNode node = buckets[bi].get(di);
        node.value = value;
    } else {
        // insert
    }
}
```

Now lets see all case jo nahi pade hai hashfn nai hasCode() howshe same li'value return kreye for a Key. Ab insert kreye:

```java
} else {
    HMNode node = new HMNode(key, value);
    buckets[bi].add(node);
    size++;
}
```

*(Insert kia toh `size++` bhi kreye.)*

**Now this is our `put` — how it looks like:**

```java
public void put(K key, V value) throws Exception {
    int bi = hashfn(key);
    int di = getIndexWithinBucket(key, bi);

    if (di != -1) {
        HMNode node = buckets[bi].get(di);
        node.value = value;
    } else {
        HMNode node = new HMNode(key, value);
        buckets[bi].add(node);
        size++;
    }

    double lambda = size * 1.0 / buckets.length;
    if (lambda > 2.0) {
        rehash();   // we do it later
    }
}
```

**Now lets do `containsKey`** — easy after `put`:

```java
public boolean containsKey(K key) {
    int bi = hashfn(key);
    int di = getIndexWithinBucket(key, bi);

    if (di != -1) {
        return true;
    } else {
        return false;
    }
}
```

**Now we do `get` fn** — easy after `put`:

```java
public V get(K key) throws Exception {
    int bi = hashfn(key);
    int di = getIndexWithinBucket(key, bi);

    if (di != -1) {
        HMNode node = buckets[bi].get(di);
        return node.value;
    } else {
        return null;
    }
}
```

Jane ki LL has fn same as of ArrayList — `we have get() & add() fn in both`.

**Now lets do `remove`** — Same as of `set()`, but iske bar humein LL se remove kreye, `set()` nahi:

```java
public V remove(K key) throws Exception {
    int bi = hashfn(key);
    int di = getIndexWithinBucket(key, bi);

    if (di != -1) {
        HMNode node = buckets[bi].remove(di);
        size--;
        return node.value;
    } else {
        return null;
    }
}
```

`hash fn` chalane ko sirf uhi bucket se compare karni baki sabse nahi.

**Very simple:**

```java
public int size() {
    return size;
}
```

Now lets see `keySet()` fn — Sb keys ek ArrayList mein return bani hai. Lets see on next page.

```java
public ArrayList<K> keyset() throws Exception {
    ArrayList<K> keys = new ArrayList<>();
    for (int i = 0; i < buckets.length; i++) {
        for (HMNode node : buckets[i]) {
            keys.add(node.key);
        }
    }
    return keys;
}
```

**Now lets see `rehash()` fn which keeps `λ` in its limit:**

toh isme we create a new ArrayList of double size — array ke baad phir purani keys ko phirse naye array mein `put()` kar do!! Ab purani keys different locations ke jaenge — as length of Array bdal gyi, hash fn ki range bhi bdal gayi, isse Mod bhi badal gaya, which is double now.

```java
private void rehash() throws Exception {
    LinkedList<HMNode>[] oba = buckets;   // oba → old bucket array

    initbuckets(oba.length * 2);
    size = 0;

    for (int i = 0; i < oba.length; i++) {
        for (HMNode node : oba[i]) {      // LL
            put(node.key, node.value);    // b hia se put
        }
    }
}
```

### Full Implementation (2nd pass)

```java
import java.util.LinkedList;
import java.util.ArrayList;

public class HashMap {
    // Data Members===========================================

    private class Node {
        Integer key = null;
        Integer value = null;

        Node(Integer key, Integer value) {
            this.key = key;
            this.value = value;
        }
    }

    private LinkedList<Node>[] Buckets;
    private int totalNoOfNodes = 0;
    private int bucketLen = 0;

    // Constructor=============================================

    private void intilize(int size) {
        bucketLen = size;
        Buckets = new LinkedList[size];
        for (int i = 0; i < size; i++)
            Buckets[i] = new LinkedList<>();

        totalNoOfNodes = 0;
    }

    public HashMap() {
        intilize(10);
    }

    // Basic Functions==========================================

    public int size() {
        return this.totalNoOfNodes;
    }

    public boolean isEmpty() {
        return this.totalNoOfNodes == 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        int tempSize = this.totalNoOfNodes;
        for (int i = 0; i < this.bucketLen; i++) {
            LinkedList<Node> group = this.Buckets[i];
            int size = group.size();
            while (size-- > 0) {
                // Instead:
                // Node node = group.getFirst();
                Node node = group.removeFirst();
                sb.append(node.key + "=" + node.value);
                group.addLast(node);

                if (--tempSize != 0)
                    sb.append(",");
            }
        }
        sb.append("}");
        return sb.toString();
    }

    private LinkedList<Node> getGroup(Integer key) {   // returns LL that has particular key
        int hc = getHashCode(key);
        return Buckets[hc];
    }

    private int getHashCode(Integer key) {
        return Math.abs(key.hashCode()) % bucketLen;
    }

    public ArrayList<Integer> keySet() {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < this.bucketLen; i++) {
            LinkedList<Node> group = this.Buckets[i];
            int size = group.size();
            while (size-- > 0) {
                Node node = group.removeFirst();
                ans.add(node.key);
                group.addLast(node);
            }
        }
        return ans;
    }

    // Put key if absent & value is default value
    public void put(Integer key, Integer value) {
        boolean res = containsKey(key);
        LinkedList<Node> group = getGroup(key);

        if (res) {
            group.getFirst().value = value;   // update
        } else {
            Node node = new Node(key, value);  // insert
            group.addLast(node);
            this.totalNoOfNodes++;

            double lambda = group.size() / (1.0 * this.bucketLen);
            if (lambda > 0.4)
                rehash();
        }
    }

    public void putIfAbsent(Integer key, Integer defaultValue) {
        boolean res = containsKey(key);
        LinkedList<Node> group = getGroup(key);
        if (!res) {
            Node node = new Node(key, defaultValue);
            group.addLast(node);
            this.totalNoOfNodes++;
        }
    }

    // Simple
    public Integer get(Integer key) {
        boolean res = containsKey(key);
        LinkedList<Node> group = getGroup(key);
        return res ? group.getFirst().value : null;
    }

    public Integer getOrDefault(Integer key, Integer defaultValue) {
        Integer val = get(key);
        return val != null ? val : defaultValue;
    }

    public boolean containsKey(Integer key) {
        LinkedList<Node> group = getGroup(key);
        int gs = group.size();
        boolean res = false;
        while (gs-- > 0) {
            if (group.getFirst().key.equals(key)) {
                res = true;
                break;
            }

            group.addLast(group.removeFirst());
        }

        return res;
    }

    public Integer remove(Integer key) {
        boolean res = containsKey(key);
        LinkedList<Node> group = getGroup(key);

        if (res) {
            this.totalNoOfNodes--;
            return group.removeFirst().key;
        }
        return null;
    }

    private void rehash() {
        LinkedList<Node>[] temp = this.Buckets;
        intilize((int) (this.bucketLen * 2));    // 1 <= ...

        for (int i = 0; i < temp.length; i++) {
            LinkedList<Node> group = temp[i];
            int size = group.size();
            while (size-- > 0) {
                Node node = group.removeFirst();
                put(node.key, node.value);
            }
        }
    }
}
```

### Client Test

```java
public class client {
    public static void test() {
        HashMap map = new HashMap();
        map.put(100, 1);
        map.put(200, 3);
        map.put(300, 7);
        map.put(400, 18);
        map.remove(400);
        map.put(200, 30);

        System.out.println(map.keySet());
    }

    public static void main(String[] args) {
        test();
    }
}
```

### Aside — Revisiting the Heap Implementation

Lets see Heap too — Heap already done but lets see refresh in code.

```java
import java.util.ArrayList;

public class heap {
    // Data Members===========================================

    private ArrayList<Integer> arr;
    private int noOfEle = 0;
    private boolean isMaxHeap = true;

    // Constructors============================================

    private void intialize(boolean isMaxHeap) {
        this.arr = new ArrayList<>();
        this.noOfEle = 0;
        this.isMaxHeap = isMaxHeap;
    }

    public heap(boolean isMaxHeap) {
        intialize(isMaxHeap);
    }

    public heap() {
        this(true);
    }

    // Creating heap from Array, O(n)
    public heap(int[] data, boolean isMaxHeap) {
        this(isMaxHeap);

        for (int ele : data)
            this.arr.add(ele);

        this.noOfEle = this.arr.size();

        for (int i = this.noOfEle - 1; i >= 0; i--) { // NlogN -> N
            downHeapify(i);
        }
    }

    // exceptions.==============================================

    private void UnderFlowPointerException() throws Exception {
        if (this.noOfEle == 0)
            throw new Exception("HeapUnderFlowException");
    }

    // Basics Functions.=========================================

    public int size() {
        return this.noOfEle;
    }

    public boolean isEmpty() {
        return this.noOfEle == 0;
    }

    public int compareTo(int t, int o) {
        if (isMaxHeap) {
            return this.arr.get(t) - this.arr.get(o);
        } else {
            return this.arr.get(o) - this.arr.get(t);
        }
    }

    private void swap(int i, int j) {
        int e1 = this.arr.get(i);
        int e2 = this.arr.get(j);

        this.arr.set(i, e2);
        this.arr.set(j, e1);
    }

    // O(LogN)
    private void downHeapify(int pi) {
        int maxIdx = pi, lci = 2 * pi + 1, rci = 2 * pi + 2;
        if (lci < this.noOfEle && compareTo(lci, maxIdx) > 0)
            maxIdx = lci;
        if (rci < this.noOfEle && compareTo(rci, maxIdx) > 0)
            maxIdx = rci;

        if (maxIdx != pi) {
            swap(pi, maxIdx);
            downHeapify(maxIdx);
        }
    }

    // O(LogN)
    private void upheapify(int ci) {
        int pi = (ci - 1) / 2;
        if (compareTo(ci, pi) > 0) {
            swap(ci, pi);
            upheapify(pi);
        }
    }

    // O(1)
    public int peek() throws Exception {
        UnderFlowPointerException();
        return this.arr.get(0);
    }

    // O(LogN)
    public int remove() throws Exception {
        UnderFlowPointerException();

        int rEle = this.arr.get(0);
        swap(0, this.noOfEle - 1);
        this.arr.remove(this.noOfEle - 1);

        this.noOfEle--;
        downHeapify(0);

        return rEle;
    }

    // O(LogN)
    public void add(int data) {
        this.arr.add(data);
        this.noOfEle++;
        upheapify(this.noOfEle - 1);
    }
}
```

### Standalone `heapSort` utility

`t → this`, `o → other`.

```java
public class heapSort {

    public static int compareTo(int[] arr, int t, int o, boolean isIncreasing) {
        if (isIncreasing) {
            return arr[t] - arr[o];
        } else {
            return arr[o] - arr[t];
        }
    }

    public static void downHeapify(int[] arr, int pi, int lidx, boolean isIncreasing) {
        int maxIdx = pi, lci = 2 * pi + 1, rci = 2 * pi + 2;
        if (lci <= lidx && compareTo(arr, lci, maxIdx, isIncreasing) > 0)
            maxIdx = lci;
        if (rci <= lidx && compareTo(arr, rci, maxIdx, isIncreasing) > 0)
            maxIdx = rci;

        if (pi != maxIdx) {
            int temp = arr[pi];
            arr[pi] = arr[maxIdx];
            arr[maxIdx] = temp;
            downHeapify(arr, maxIdx, lidx, isIncreasing);
        }
    }

    public static void heapSort(int[] arr, boolean isIncreasing) {
        int n = arr.length, lidx = n - 1;
        for (int i = lidx; i >= 0; i--) {
            downHeapify(arr, i, lidx, isIncreasing);
        }

        while (lidx >= 0) {
            int temp = arr[lidx];
            arr[lidx] = arr[0];
            arr[0] = temp;
            downHeapify(arr, 0, --lidx, isIncreasing);
        }
    }
}
```

See `compareTo()` fn: `arr[t] - arr[o]` makes sure array is in Increasing Order; `arr[o] - arr[t]` is in decreasing Order. If `isIncreasing` is true then do `arr[t]-arr[o]` else `arr[o]-arr[t]`.

**Complexity (HashMap operations):**
- **Time:** `O(λ)` average for `put()`, `get()`, `containsKey()`, `remove()` — each only ever scans within the single bucket the key hashes to, never the whole table. Since rehashing keeps `λ = n/N` bounded by a constant `k`, this makes every operation effectively `O(1)` amortized. `size()` is `O(1)`. `keySet()` is `O(n)` — it must visit every node once across all buckets.
- **Space:** `O(n + N)` — `n` nodes stored across `N` bucket headers (linked lists).
- **Rehashing** itself costs `O(n)` (re-inserting every existing node into the doubled bucket array), but since it only triggers once `n` roughly doubles since the last rehash, this cost amortizes to `O(1)` extra per `put()`, exactly like `ArrayList` doubling.

### Cpp code

```cpp

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>

using namespace std;

template <typename K, typename V>
class MyHashMap {
private:
    struct Node {
        K key;
        V value;
        Node(K k, V v) : key(k), value(v) {}
    };

    vector<list<Node>> buckets;
    int noOfElements;
    int bucketCount;
    double loadFactorThreshold = 0.75;

    // Helper to get bucket index
    int getBucketIndex(K key) {
        // C++ built-in hash function
        size_t hc = hash<K>{}(key);
        return hc % bucketCount;
    }

    void rehash() {
        vector<list<Node>> oldBuckets = buckets;
        
        // Double the capacity
        bucketCount *= 2;
        buckets.assign(bucketCount, list<Node>());
        noOfElements = 0;

        for (auto& group : oldBuckets) {
            for (auto& node : group) {
                put(node.key, node.value);
            }
        }
    }

public:
    MyHashMap(int initialCapacity = 10) {
        this->bucketCount = initialCapacity;
        this->noOfElements = 0;
        buckets.assign(bucketCount, list<Node>());
    }

    void put(K key, V value) {
        int bi = getBucketIndex(key);
        
        // Search if key exists
        for (auto& node : buckets[bi]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }

        // If not found, add new
        buckets[bi].push_back(Node(key, value));
        noOfElements++;

        // Check Global Load Factor
        if ((1.0 * noOfElements) / bucketCount > loadFactorThreshold) {
            rehash();
        }
    }

    V* get(K key) {
        int bi = getBucketIndex(key);
        for (auto& node : buckets[bi]) {
            if (node.key == key) {
                return &(node.value);
            }
        }
        return nullptr; // Return pointer so we can return null if not found
    }

    bool containsKey(K key) {
        int bi = getBucketIndex(key);
        for (auto& node : buckets[bi]) {
            if (node.key == key) return true;
        }
        return false;
    }

    bool remove(K key) {
        int bi = getBucketIndex(key);
        auto& group = buckets[bi];
        for (auto it = group.begin(); it != group.end(); ++it) {
            if (it->key == key) {
                group.erase(it);
                noOfElements--;
                return true;
            }
        }
        return false;
    }

    int size() { return noOfElements; }
};

int main() {
    MyHashMap<string, int> map;
    map.put("Apple", 100);
    map.put("Banana", 200);
    
    if (map.containsKey("Apple")) {
        cout << "Apple price: " << *map.get("Apple") << endl;
    }

    map.remove("Apple");
    cout << "Size after removal: " << map.size() << endl;

    return 0;
}
```

### Java code

```java
import java.util.ArrayList;
import java.util.LinkedList;

public class HashMap<K, V> {

    private class Node {
        K key = null;
        V value = null;

        Node(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString() {
            return key + "=" + value;
        }
    }

    private LinkedList<Node>[] buckets;
    private int NoOFElements = 0;
    private int maxSizeOfBucket = 0;

    private void intialize(int size) {
        buckets = new LinkedList[size];
        for (int i = 0; i < size; i++) {
            buckets[i] = new LinkedList<>();
        }

        this.maxSizeOfBucket = size;
        this.NoOFElements = 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        int sizeOfMap = this.NoOFElements;
        for (int i = 0; i < this.maxSizeOfBucket; i++) {
            LinkedList<Node> group = this.buckets[i];
            int size = group.size();
            while (size-- > 0) {
                sb.append(group.getFirst());
                if (sizeOfMap > 1)
                    sb.append(",");

                group.addLast(group.removeFirst());
                sizeOfMap--;
            }
        }

        sb.append("]");

        return sb.toString();
    }

    public HashMap() {
        intialize(10);
    }

    public Integer size() {
        return this.NoOFElements;
    }

    public boolean isEmpty() {
        return this.size() == 0;
    }

    private void rehash() {
        LinkedList<Node>[] temp = this.buckets;
        intialize(2 * this.maxSizeOfBucket);
        for (int i = 0; i < temp.length; i++) {
            LinkedList<Node> group = temp[i];
            int size = group.size();
            while (size-- > 0) {
                Node node = group.removeFirst();
                put(node.key, node.value);
            }
        }
    }

    public void put(K key, V value) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (res) {
            group.getFirst().value = value;
        } else {
            Node node = new Node(key, value);
            group.addLast(node);
            this.NoOFElements++;

            double lambda = (0.4 * this.maxSizeOfBucket);
            if (group.size() >= lambda)
                rehash();
        }
    }

    // if you found return value if not return null.
    public V get(K key) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (res)
            return group.getFirst().value;

        return null;
    }

    public V remove(K key) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (res) {
            this.NoOFElements--;
            return group.removeFirst().value;
        }
        return null;
    }

    public boolean containsKey(K key) {
        LinkedList<Node> group = group(key);
        int size = group.size();
        while (size-- > 0) {
            if (group.getFirst().key == key)
                return true;
            group.addLast(group.removeFirst());
        }
        return false;
    }

    private void allkeysOfGroup(LinkedList<Node> group, ArrayList<K> ans) {
        int size = group.size();
        while (size-- > 0) {
            ans.add(group.getFirst().key);
            group.addLast(group.removeFirst());
        }
    }

    public ArrayList<K> keySet() {
        ArrayList<K> ans = new ArrayList<>();
        for (int i = 0; i < this.maxSizeOfBucket; i++) {
            allkeysOfGroup(this.buckets[i], ans);
        }

        return ans;
    }

    public V getOrDefault(K key, V defaultValue) {
        V value = get(key);
        if (value == null)
            return defaultValue;
        return value;
    }

    public void putIfAbsent(K key, V value) {
        LinkedList<Node> group = group(key);
        boolean res = containsKey(key);
        if (!res)
            put(key, value);
    }

    private LinkedList<Node> group(K key) {
        int groupNo = groupNo(key);
        return this.buckets[groupNo];
    }

    private Integer groupNo(K key) {
        Integer hc = Math.abs(key.hashCode());
        return hc % maxSizeOfBucket;
    }

}

```
### Client

```java

import java.util.Scanner;
import java.util.ArrayList;

public class client {
    public static Scanner scn = new Scanner(System.in);

    public static void main(String[] args) {
        HashMap<Character, ArrayList<Integer>> map = new HashMap<>();
        String str = "asdasasaaasskacbasmcbasmcasbcjhcbsahcjhcsvhcsHVcsvhjcks";
        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            map.putIfAbsent(ch, new ArrayList<>());
            map.get(ch).add(i);
        }

        for(Character ch : map.keySet()){
            System.out.println(ch + " -> " + map.get(ch));
        }

    }
}
```
# Why Top-Tier Companies Care About HashMap Internals

### 1. Security (Hash Flooding)
- **Concept:** Attackers use keys with the same hash to force $O(N)$ complexity.
- **Solution:** Use randomized hash seeds or switch to balanced trees (Red-Black Trees) for collisions.

### 2. Hardware Optimization (Cache Locality)
- **Concept:** Linear Probing is faster than Chaining on modern CPUs.
- **Why:** The CPU loads chunks of memory (Cache Lines). If the next item is right next to the current one, the CPU doesn't have to go back to RAM.

### 3. Real-Time Reliability (Incremental Rehashing)
- **Concept:** Moving 1 million items during a resize causes "Stop the World" pauses.
- **Solution:** Move a few items at a time during normal `put` and `get` operations to smooth out latency.


## LeetCode 706 — Design HashMap

*(level1 mai tha ye vhi se dekh ke chep dia — this was already solved in Level 1, just pasted in here for reference.)*

**Difficulty:** Easy

Design a HashMap without using any built-in hash table libraries.

Implement the `MyHashMap` class:
- `MyHashMap()` initializes the object with an empty map.
- `void put(int key, int value)` inserts a `(key, value)` pair into the HashMap. If the `key` already exists in the map, update the corresponding `value`.
- `int get(int key)` returns the `value` to which the specified `key` is mapped, or `-1` if this map contains no mapping for the `key`.
- `void remove(key)` removes the `key` and its corresponding `value` if the map contains the mapping for the `key`.

**Example 1:**

```
Input
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
Output
[null, null, null, 1, -1, null, 1, null, -1]
```

**Constraints:**
- `0 <= key, value <= 10^6`
- At most `10^4` calls will be made to `put`, `get`, and `remove`.

```java

class MyHashMap {
    private int size;
    private LinkedList<HMNode>[] bucket;
    private class HMNode{
        int key;
        int val;
        HMNode(int key,int val){
            this.key=key;
            this.val=val;
        }
    }

    private void initBucket(int k){
        bucket=new LinkedList[k];
        for(int i=0;i<k;i++){
            bucket[i]=new LinkedList<>();
        }
    }
    public MyHashMap() {
        size=0;
        initBucket(4);
    }
    private int getWithInLL(int key,int i){
        int res=0;
        for(HMNode node:bucket[i]){
            if(node.key==key) return res;
            res++;
        }
        return -1;
    }
    private void rehash(){
        LinkedList<HMNode>[] oldBucket=bucket;
        initBucket(oldBucket.length*2);
        this.size=0;
        for(int i=0;i<oldBucket.length;i++){
            for(var node:oldBucket[i]){
                put(node.key,node.val);
            }
        }
    }
    public void put(int key, int value) {
        int idx=key%bucket.length;
        int llidx=getWithInLL(key,idx);
        if(llidx!=-1){
            bucket[idx].get(llidx).val=value;
        }else{
            bucket[idx].add(new HMNode(key,value));
            size++;
        }
        double lambda=size*1.0/bucket.length;
        if(lambda>2.0) rehash();
    }
    
    public int get(int key) {
        int idx=key%bucket.length;
        int llidx=getWithInLL(key,idx);
        if(llidx!=-1){
            return bucket[idx].get(llidx).val;
        }else{
           return -1;
        }
    }
    
    public void remove(int key) {
        int idx=key%bucket.length;
        int llidx=getWithInLL(key,idx);
        if(llidx!=-1){
            bucket[idx].remove(llidx);
            size--;
        }
    }
}

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */
```




