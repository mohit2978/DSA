## Array vs ArrayList vs LinkedList
**Array**
- Fixed size — set at creation, can't grow or shrink
- Can hold primitives (`int[]`, `char[]`) or objects
- Fastest access: O(1) by index
- No built-in methods for insert/remove/search — you write the logic
- Least overhead, most memory-efficient

**ArrayList**
- Backed by a dynamic (resizable) array internally
- Only holds objects (autoboxes primitives, e.g. `int` → `Integer`)
- Access by index: O(1)
- Insert/remove at end: O(1) amortized
- Insert/remove at beginning or middle: O(n) — shifts elements
- Good when you read/access a lot, don't insert/delete much in the middle

**LinkedList**
- Doubly-linked list internally (each node has data + pointers to prev/next)
- Only holds objects
- Access by index: O(n) — has to traverse from head or tail
- Insert/remove at beginning or end: O(1)
- Insert/remove in the middle: O(n) to find the spot, O(1) to actually link it
- Implements both `List` and `Deque`, so it works well as a stack/queue
- More memory overhead per element (extra pointers)

### Quick comparison table

| Feature | Array | ArrayList | LinkedList |
|---|---|---|---|
| Size | Fixed | Dynamic | Dynamic |
| Data type | Primitives + objects | Objects only | Objects only |
| Get by index | O(1) | O(1) | O(n) |
| Insert/delete at end | N/A (fixed) | O(1) amortized | O(1) |
| Insert/delete at start/middle | N/A | O(n) | O(1) once found, O(n) to find |
| Memory overhead | Low | Medium | High |
| Implements | — | `List` | `List`, `Deque` |

### When to use which
- **Array**: size is known and fixed, performance/memory is critical (e.g. numeric computation)
- **ArrayList**: default choice for most cases — frequent random access, occasional additions at the end
- **LinkedList**: frequent insertions/deletions at the beginning or middle, or when you need queue/stack/deque behavior

### Example
```java
int[] arr = new int[5];               // fixed size
arr[0] = 10;

List<Integer> arrayList = new ArrayList<>();
arrayList.add(10);
arrayList.add(0, 5);                  // insert at index 0 → shifts elements

List<Integer> linkedList = new LinkedList<>();
linkedList.add(10);
linkedList.add(0, 5);                 // insert at index 0 → cheap, just relinks
```

In practice: reach for `ArrayList` unless you have a specific reason (heavy front/middle insertions, queue-like usage) to use `LinkedList`, and use plain arrays only when size is fixed or you need raw performance.


Let's go through both carefully with concrete numbers.

## ArrayList: why it's "amortized" O(1), not exact O(1)

"Amortized" means: **not every single call is O(1), but averaged over a long sequence of calls, the cost per call works out to a constant.**

### Concrete example

Say the backing array starts at capacity 4, and doubles when full.

```
capacity = 4, size = 0
add(a) → arr = [a, _, _, _]        size=1   cost = 1 (just place it)
add(b) → arr = [a, b, _, _]        size=2   cost = 1
add(c) → arr = [a, b, c, _]        size=3   cost = 1
add(d) → arr = [a, b, c, d]        size=4   cost = 1   (array now FULL)
add(e) → FULL! Must resize:
           1. allocate new array of capacity 8
           2. copy a, b, c, d over        → cost = 4 (copying)
           3. place e                      → cost = 1
                                     total cost = 5
         arr = [a, b, c, d, e, _, _, _]   size=5
add(f) → arr = [a, b, c, d, e, f, _, _]   size=6   cost = 1
add(g) → cost = 1
add(h) → cost = 1                  (array full again, capacity 8)
add(i) → resize to 16, copy 8 elements → cost = 9
```

### Now add up the total cost

For 8 additions (a through h): costs were `1,1,1,1,5,1,1,1` = **12 total**, for 8 operations → average **1.5 per operation**.

Keep going further and this average gets *closer and closer to a constant* (roughly 3, depending on growth factor), no matter how large n gets. It never grows with n. That's the key.

### Why it stays constant: the doubling is what saves it

Each time you resize, you double the capacity, so resizes happen less and less often relative to the number of elements:
- Resize at size 4 (cost 4 copies)
- Resize at size 8 (cost 8 copies)
- Resize at size 16 (cost 16 copies)

The copy cost of each resize is roughly proportional to how many O(1) insertions you got "for free" since the last resize. So the expensive copy is essentially **pre-paying** for the cheap insertions that follow it. Spread that expensive step over all the cheap steps, and the average per-call cost is a constant — hence **O(1) amortized**, not O(1) exact.

If it *doubled* every time — as opposed to, say, adding a fixed amount of 1 slot every time — the math works out (via geometric series) to a constant amortized cost. That's why growth-factor resizing is used instead of "add 1 slot at a time" (which would actually degrade to real O(n) per insert).

## LinkedList: why append is O(1) exact, every single time

A LinkedList keeps a direct reference to the **tail** node. There is no array, no capacity, no resizing — ever. Adding at the end is *always* just:

```
addLast(x):
    newNode = Node(x)
    newNode.prev = tail
    tail.next = newNode
    tail = newNode
```

That's 3-4 pointer assignments. It does **not matter** if the list has 10 elements or 10 million — the cost is identical, fixed, constant work.

### Example trace

```
list: A <-> B <-> C        tail = C

add(D):
    D.prev = C
    C.next = D
    tail = D
list: A <-> B <-> C <-> D   tail = D     (cost: 3 pointer updates, always)

add(E):
    E.prev = D
    D.next = E
    tail = E
list: A <-> B <-> C <-> D <-> E   tail = E   (cost: still 3 pointer updates)
```

No copying, no shifting, no traversal (because `tail` is already known/stored). Every `addLast` call does the *exact same fixed amount of work*, regardless of history or list size. That's **true O(1)**, not just averaged.

## The core distinction

| | ArrayList `add(x)` | LinkedList `addLast(x)` |
|---|---|---|
| Occasionally does extra work? | Yes — resize + copy | No — never |
| Cost varies by call? | Yes (mostly cheap, rarely expensive) | No (always the same) |
| Why constant on average | Doubling spreads the rare expensive resize over many cheap calls | There's nothing that ever gets expensive — no resizing exists |
| Correct term | Amortized O(1) | Exact (worst-case) O(1) |

## Disadvantages of LinkedList

**1. No random access — O(n) to get by index**
```java
list.get(500);  // has to walk from head (or tail) 500 nodes deep
```
Unlike ArrayList (`arr[500]` directly), LinkedList must traverse node-by-node. This kills performance for anything read-heavy.

**2. Higher memory overhead per element**
Each node stores the data *plus* two references (prev and next pointers). For a list of `Integer` objects:
- ArrayList: just the object reference in a contiguous array slot
- LinkedList: object reference + prev pointer + next pointer + object header for the Node itself

Roughly 2-3x more memory per element compared to ArrayList.

**3. Poor cache locality**
Array-backed structures store elements contiguously in memory, so the CPU cache can prefetch efficiently. LinkedList nodes are scattered wherever the JVM heap allocated them — jumping from node to node means frequent cache misses, making iteration slower in practice than ArrayList even though both are "O(n)" for a full traversal.

**4. Insertion/deletion in the middle still requires O(n) traversal**
People often think "LinkedList is O(1) for insert/delete" — true only *once you're already at the position*. Finding that position (via `get(index)` or iterating) is still O(n). So `add(index, x)` in the middle is O(n) overall, same as ArrayList, just for a different reason (search vs. shift).

**5. No indexed binary search**
`Collections.binarySearch()` on a LinkedList degrades to O(n log n) effectively, because even though comparisons are O(log n), each "jump to the middle" access is O(n) on a LinkedList — so it loses the whole benefit of binary search.

**6. Iterator overhead for indexed operations**
Methods like `get(i)` internally create/traverse via an iterator each time — calling `get(i)` in a loop is O(n²) total, a common performance trap:
```java
for (int i = 0; i < list.size(); i++) {
    list.get(i);   // O(n) each call → O(n²) total!  (use an Iterator instead)
}
```

**7. Extra pointer maintenance = more error-prone / more work per operation**
Every insert/delete touches multiple pointer references (prev/next on neighboring nodes). More moving parts than a simple array index write, and more chances for subtle bugs when implementing custom linked structures.

### Bottom line
LinkedList only wins when you're doing frequent insertions/deletions at the **head or tail** (or using it as a Deque/Queue). For anything involving indexed access or random reads, ArrayList is almost always faster and more memory-efficient — which is why LinkedList is used far less often in practice than people expect.


 

# Custom Linked List Implementation in Java

## What is a Linked List

A Linked List is a linear data structure where each node holds two things:
1. **data**
2. **reference to the next node**

A general linked list looks like this: each node stores content plus the address (pointer) of the next node. The last node's pointer points to `null`.

```java
public static class Node {
    int data;
    Node next;
}
```

Sometimes we also maintain a **tail pointer** in the list (in addition to head), so we don't have to traverse the whole list just to reach the last node. We'll design our LinkedList **with a tail pointer**.

## Setting up the class

To create our own LinkedList, we design a class like this:

```java
public static class LinkedList {
    Node head;
    Node tail;
    int size;
}
```

- `head` → reference to the first node
- `tail` → reference to the last node
- `size` → number of elements currently in the list

A linked list of size 4 would conceptually look like: a `LinkedList` object living on the heap, containing `head`, `tail`, and `size = 4`, where `head` points to the first node (1) and `tail` points to the last node (4), and the nodes are chained `1 → 2 → 3 → 4`.

To actually use this, we wrap `Node` and `LinkedList` inside an outer structure and keep them as private inner classes with the fields private, since we don't want the internal logic to be directly manipulated from outside:

```java
public class linkedlist {
    private class Node {
        int data = 0;
        Node next = null;

        public Node(int data) {
            this.data = data;
        }
    }

    private Node head = null;
    private Node tail = null;
    private int size = 0;
}
```

## size() and isEmpty()

```java
public int size() {
    return this.size;
}

public boolean isEmpty() {
    return this.size == 0;
}
```

`size()` simply returns the stored count — O(1).

## toString() — displaying the list

```java
@Override
public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("[");
    Node curr = this.head;
    while (curr != null) {
        sb.append(curr.data);
        if (curr.next != null)
            sb.append(", ");

        curr = curr.next;
    }
    sb.append("]");

    return sb.toString();
}
```

Here `curr` starts pointing at `head`, and we move forward (`curr = curr.next`) until `curr` becomes `null`. This means `toString()` is **O(n)** since it has to traverse the whole linked list.

## addFirst()

We don't want our internal logic to be exposed publicly, and we also want abstraction — so the main logic lives in a **private** helper function, and the public function is just a thin wrapper.

```java
private void addFirstNode(Node node) {
    if (this.size == 0)
        this.head = this.tail = node;
    else {
        node.next = this.head;
        this.head = node;
    }
    this.size++;
}

public void addFirst(int data) {
    Node node = new Node(data);
    addFirstNode(node);
}
```

**Logic:** In `addFirstNode()`, we make the new node first. Then:
- If `size == 0`, both `head` and `tail` point to this new node.
- Otherwise, the new node's `next` becomes the current `head`, and then `head` is updated to point to the new node.

Example: `[1] → [2] → [3]`, calling `addFirst(4)` gives `[4] → [1] → [2] → [3]`.

This operation is **O(1)** — no traversal needed, just pointer updates.

## addLast()

```java
private void addLastNode(Node node) {
    if (this.size == 0)
        this.head = this.tail = node;
    else {
        this.tail.next = node;
        this.tail = node;
    }
    this.size++;
}

public void addLast(int data) {
    Node node = new Node(data);
    addLastNode(node);
}
```

**Logic:** Create the node, and in `addLastNode()`:
- If `size == 0`, both `head` and `tail` point to the new node.
- Otherwise, the current `tail`'s `next` becomes the new node, then `tail` is updated to point to the new node.

`size++` happens once, at the end — this is common to both `addFirstNode` and `addLastNode`.

This is **O(1)** since the new node is just attached directly to the tail — no traversal needed.

These two operations (`addFirst`, `addLast`) are very important to get right; there are cases (like the empty-list case) that are easy to miss.

## getFirst(), getLast(), getAt()

```java
private Node getFirstNode() {
    return this.head;
}

public int getFirst() {
    if (this.size == 0)
        return -1;

    return getFirstNode().data;
}
```

```java
private Node getLastNode() {
    return this.tail;
}

public int getLast() {
    if (this.size == 0)
        return -1;

    return getLastNode().data;
}
```

`getFirst()` and `getLast()` are easily understood — they just return the data at `head`/`tail` directly. Both are **O(1)**.

```java
private Node getNodeAt(int idx) {
    Node curr = this.head;
    while (idx-- > 0) {
        curr = curr.next;
    }

    return curr;
}

public int getAt(int idx) {
    if (idx < 0 || idx >= this.size)
        return -1;

    return getNodeAt(idx).data;
}
```

**Logic:** If we are passed an index, we first check that we haven't received an invalid index. Then we put the main logic inside `getNodeAt()`: we move `curr` starting from `head`, while decrementing `idx` until it's no longer `> 0`. Then we return the node where we landed.

Alternatively, this can be optimized a bit further:
```java
if (idx == 0) return head;
if (idx == size - 1) return tail;
```

`getNodeAt()` is **O(n)** since it may need to traverse (nearly) the entire list.

## addAt() — add a node at a particular index

```java
private void addNodeAt(Node node, int idx) {
    if (idx == 0)
        addFirstNode(node);
    else if (idx == this.size)
        addLastNode(node);
    else {
        Node prevNode = getNodeAt(idx - 1);
        Node forwNode = prevNode.next;

        prevNode.next = node;
        node.next = forwNode;
        this.size++;
    }
}

public void addAt(int idx, int data) {
    if (idx < 0 || idx > this.size)
        return;

    Node node = new Node(data);
    addNodeAt(node, idx);
}
```

**Logic:**
- First check if `idx < 0` or `idx > size`; if so, the index is invalid and we return.
- Then create the node, and pass control to `addNodeAt()`.
- If `idx == 0` → call `addFirstNode()`.
- If `idx == size` → call `addLastNode()`.
- Indexing starts at 0, so `idx == size` correctly means "add at the end."
- Otherwise (general middle case):
  - `prevNode = getNodeAt(idx - 1)` — the node just before where we want to insert.
  - `forwNode = prevNode.next` — the node currently after `prevNode`, which will now come after our new node.
  - `prevNode.next = node` — link the previous node to the new node.
  - `node.next = forwNode` — link the new node to what used to come next.

This links the new node in correctly: `prevNode` now points to `node`, and `node` points to whatever `prevNode` used to point to. This general-case insertion is **O(n)**, because of the traversal needed to reach `idx - 1`.

## removeFirst()

```java
private Node removeFirstNode() {
    Node node = this.head;
    if (this.size == 1)
        this.head = this.tail = null;
    else {
        this.head = this.head.next;
        node.next = null;
    }

    this.size--;
    return node;
}

public int removeFirst() {
    if (this.size == 0)
        return -1;

    Node node = removeFirstNode();
    return node.data;
}
```

**Logic:** Removing a value from the front always means checking `if (size == 0)` first — easy to forget. Inside `removeFirstNode()`:
- If `size == 1`, both `head` and `tail` become `null`.
- Otherwise, move `head` forward to `head.next`, and disconnect the old head's `next` (set to `null`).

Also note: in functions where an index is passed (`getAt()`, `addAt()`, `removeAt()`), always check that the passed index is valid first.

This is **O(1)**.

## removeLast()

```java
private Node removeLastNode() {
    Node node = this.tail;
    if (this.size == 1)
        this.head = this.tail = null;
    else {
        Node secondLast = getNodeAt(this.size - 2);
        secondLast.next = null;
        this.tail = secondLast;
    }
    this.size--;
    return node;
}

public int removeLast() {
    if (this.size == 0)
        return -1;

    return removeLastNode().data;
}
```

**Logic:**
- First check `if (size == 0)`.
- Inside the main logic:
  - If `size == 1`, set `head = tail = null`.
  - Otherwise, find the second-last node (`getNodeAt(size - 2)`), make its `next` point to `null`, and set it as the new `tail`.

This is **O(n)**, because finding the second-last node requires traversing (almost) the whole linked list — unlike `removeFirst()`, there's no way to jump directly to the second-last node without a doubly-linked structure.

## removeAt() — remove node at a particular index

```java
private Node removeNodeAt(int idx) {
    if (idx == 0)
        return removeFirstNode();
    else if (idx == this.size - 1)
        return removeLastNode();
    else {
        Node prevNode = getNodeAt(idx - 1);
        Node node = prevNode.next;
        Node forwNode = node.next;

        node.next = null;
        prevNode.next = forwNode;
        this.size--;

        return node;
    }
}

public int removeAt(int idx) {
    if (idx < 0 || idx >= this.size)
        return -1;

    return removeNodeAt(idx).data;
}
```

**Logic:**
- First check for an invalid index. This also implicitly checks whether `size == 0`, since any index would be invalid in that case.
- Main logic sits in the `else` branch:
  - `prevNode = getNodeAt(idx - 1)` — the `(idx - 1)`th node.
  - `node = prevNode.next` — the node we actually want to delete.
  - `forwNode = node.next` — the node right after the one being deleted.
  - `node.next = null` — disconnect the node being removed.
  - `prevNode.next = forwNode` — bridge the gap by linking `prevNode` directly to `forwNode`.

Visually: with a chain `A → B → C → D → E`, if we're deleting `C`, `prevNode` is `B`, `node` is `C`, `forwNode` is `D`. After the operation: `B.next = D`, and `C.next = null` (fully detached), giving `A → B → D → E`.

This is **O(n)** in the general case, due to the traversal needed to find `idx - 1`.

## set() functions

Before moving to more complex operations, it helps to note that **set functions** (`setFirst()`, `setLast()`, `setAt()`) follow the exact same pattern:
- Reuse the private `getXNode()` functions to locate the correct node.
- Instead of returning `.data`, assign a new value to `.data`.

For example, `setFirst(data)` would locate the node via `getFirstNode()`, and set its `.data` to the new value — same helper function reused, just for writing instead of reading.

## Summary of LinkedList operations

| Public method | Private helper | Time Complexity |
|---|---|---|
| `addFirst()` | `addFirstNode()` | O(1) |
| `addLast()` | `addLastNode()` | O(1) |
| `addAt()` | `addNodeAt()` | O(n) |
| `getFirst()` | `getFirstNode()` | O(1) |
| `getLast()` | `getLastNode()` | O(1) |
| `getAt()` | `getNodeAt()` | O(n) |
| `removeFirst()` | `removeFirstNode()` | O(1) |
| `removeLast()` | `removeLastNode()` | O(n) |
| `removeAt()` | `removeNodeAt()` | O(n) |
| `setFirst()`, `setLast()`, `setAt()` | reuse `getXNode()` | O(1) / O(1) / O(n) |

## Using the LinkedList

To create an object of our custom LinkedList, we create another class (a client class) and use our written LinkedList inside its `main()`:

```java
import java.io.*;
import java.util.*;

public class client {
    public static void main(String[] args) throws Exception {
        linkedlist ll = new linkedlist();
        ll.addFirst(10);
        System.out.println(ll.getFirst());
        System.out.println(ll.size());
        ll.addLast(40);
        System.out.println(ll.removeAt(2));
        ll.addAt(1, 20);
        System.out.println(ll.getLast());
        System.out.println(ll);
        System.out.println(ll.removeAt(2));
        ll.addLast(50);
        System.out.println(ll);
        ll.addAt(2, 30);
        System.out.println(ll.getFirst());
        System.out.println(ll.getAt(3));
        System.out.println(ll);
    }
}
```

## Cpp implementation

```cpp
#include <bits/stdc++.h>
using namespace std;


struct ListNode {
    int val; 
    ListNode* next;

    //constructors
    ListNode(int data1) : val(data1), next(nullptr) {} 
    ListNode(int data1, ListNode* next1) : val(data1), next(next1) {} 
};


class Solution {
public:
    //insert at head
    ListNode* insertAtHead(ListNode* &head, int X) {
        ListNode* node=new ListNode(X);
        node->next=head;
        head=node;
        return head;
    }

    //insert at tail
    ListNode* insertAtTail(ListNode* &head, int X) {
        ListNode *node=new ListNode(X);
        if(head==nullptr){
            head=node;
            return head;
        }
        ListNode *tmp=head;
        while(tmp->next!=nullptr){
            tmp=tmp->next;
        }
        tmp->next=node;
        return head;
    }

    //insert at kth position

    ListNode* insertAtKthPosition(ListNode* &head, int X, int K) {
        if(K==1) return insertAtHead(head,X);
        ListNode * tmp=head;
        for(int i=1;i<K-1;i++){
            tmp=tmp->next;
        }
        ListNode * list=tmp->next;
        ListNode * node=new ListNode(X);
        tmp->next=node;
        node->next=list;
        return head;
    }
    //insert node having val val before node of val X
    //it is possible X is not present in LL
    ListNode* insertBeforeX(ListNode* &head, int X, int val) {
        if(head==nullptr) return head;
        if(head->val==X) return insertAtHead(head,val);
        ListNode * tmp=head;
        ListNode * prev=nullptr;
        while(tmp!=nullptr && tmp->val!=X){
            prev=tmp;
            tmp=tmp->next;
        }
        if(tmp==nullptr) return head; //if X is not present then return as it is
        ListNode* node=new ListNode(val);
        prev->next=node;
        node->next=tmp;
        return head;
    }
    

    //delete 1st node
    ListNode* deleteHead(ListNode* &head) {
        if(head==nullptr|| head->next==nullptr) return nullptr;
        ListNode *tmp=head;
        head=head->next;
        tmp->next=nullptr;
        return head;

    }
    //delete the last node
       ListNode* deleteTail(ListNode* &head) {
        if(head==nullptr|| head->next==nullptr) return nullptr;
        ListNode* tmp=head;
        while(tmp->next->next!=nullptr) tmp=tmp->next;
        delete tmp->next; //extra step here we need to delete it too 
        tmp->next=nullptr;
        return head;

    }

    //delete kth node if k=1 delete head fucntion call if we have size too
    //then if k== size we can can deleteTail but here we have no size
    ListNode* deleteKthNode(ListNode* &head, int k) {
        if(head==nullptr) return head;
        if (k==1) return deleteHead(head);
        ListNode* tmp=head;
        for(int i=1;i<k-1;i++){
            tmp=tmp->next;
        }
        ListNode *deletenode=tmp->next;
        tmp->next=deletenode->next;
        delete deletenode;
        return head;
    }

    //delete node with value X

    ListNode* deleteNodeWithValueX(ListNode* &head, int X) {
        if(head->val==X) return deleteHead(head);
        ListNode * prev=nullptr;
        ListNode * curr= head;
        while(curr!=nullptr && curr->val!=X  ){
            //first check curr !=null then check for curr->val
            prev=curr;
            curr=curr->next;
        }
        if(curr==nullptr) return head;
        prev->next=curr->next;
        delete curr;
        return head;
    }

    //Function for Linked List Traversal
    vector<int> LLTraversal(ListNode* head) {
       vector<int>v;
        if(head==nullptr ) return v;
        ListNode* tmp=head;
        while(tmp!=nullptr){
            v.push_back(tmp->val);
            tmp=tmp->next;
        }
        return v;
    }
};

int main() {
    //Manual creation of nodes
    ListNode* y1 = new ListNode(2);
    ListNode* y2 = new ListNode(5);
    ListNode* y3 = new ListNode(8);
    ListNode* y4 = new ListNode(7);

    // Linking the nodes
    y1->next = y2;
    y2->next = y3;
    y3->next = y4;

    //Instance of
    //Solution class
    Solution sol;

    //Calling LLTraversal method 
    //To get the values
    vector<int> result = sol.LLTraversal(y1);

    //Printing the result
    cout << "Linked List Values:" << endl;
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    //Clean up 
    //Allocated memory
    delete y1;
    delete y2;
    delete y3;
    delete y4;

    return 0;
}

```