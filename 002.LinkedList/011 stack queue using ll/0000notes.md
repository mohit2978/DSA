
## Stack using LL basic using ll class

```java

class LinkedListStack {
    LinkedList<Integer>ll;
    public LinkedListStack() {
        ll=new LinkedList<>();
    }

    public void push(int x) {
       ll.addFirst(x);
    }

    
    public int pop() {
        int val=this.top();
      ll.removeFirst();
      return val;
    }

    public int top() {
       return ll.getFirst();
    }

    public boolean isEmpty() {
        return ll.size()==0;
    }
}

```
## Queue using ll using ll class

```java

class LinkedListQueue {
    LinkedList<Integer>ll;
    public LinkedListQueue() {
        ll=new LinkedList<>();
    }

    public void push(int x) {
       ll.addLast(x);
    }

    public int pop() {
        int val=this.peek();
      ll.removeFirst();
      return val;
    }

    public int peek() {
       return ll.getFirst();
    }

    public boolean isEmpty() {
        return ll.size()==0;
    }
}

```

Now we need to put these functions ourself!!
```java
    ListNode th = null, tt = null;

    private void addFirst(ListNode node) {
        if (th == null)
            th = tt = node;
        else {
            node.next = th;
            th = node;
        }
    }

    public void addLast(int val) {
        Node node = new Node(val);
        if (th== null)
            th= tt = node;
        else {
            tt.next = node;
            tt= node;
        }
    }

int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}

```



## Stack using LL

```cpp

struct ListNode{
        int val;
        ListNode * next;
        ListNode(int x){
            this->next=nullptr;
            this->val=x;
        }
    };
class LinkedListStack {
    ListNode* th;
    ListNode *tt;
    int size;
    void addFirst(ListNode* node) {
        if (th == nullptr)
            {
                th=node;
                tt=node;
            }
        else {
            node->next = th;
            th = node;
        }
        size++;
    }

    int getFirst(){
        return th->val;
    }
int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}
    int sizeFun(){
        return size;
    }
public:
    LinkedListStack() {
        th=tt=nullptr;
        this->size=0;
    }
    
    void push(int x) {
        addFirst(new ListNode(x));
    }
    
    int pop() {
        return removeFirst();
    }
    
    int top() {
        if(isEmpty()==true) return -1;
        return getFirst();
    }
    
    bool isEmpty() {
        return sizeFun()==0;
    }
};
```
This  is correct code which we get after discussion with AI
### First submission
```cpp

struct ListNode{
        int val;
        ListNode * next;
        ListNode(int x){
            this->next=nullptr;
            this->val=x;
        }
    };
class LinkedListStack {
    ListNode* th;
    ListNode *tt;
    int size;
    void addFirst(ListNode* node) {
        if (th == nullptr)
            {
                th=node;
                tt=node;
            }
        else {
            node->next = th;
            th = node;
        }
        size++;
    }

    int getFirst(){
        return th->val;
    }
    int removeFirst(){
        if(th==nullptr) return -1;
        int val=th->val;
        ListNode * temp=th;
        th=th->next;
        temp->next=nullptr;
        delete(temp);
        size--;
        return val;
    }
    int sizeFun(){
        return size;
    }
public:
    LinkedListStack() {
        th=tt=nullptr;
        this->size=0;
    }
    
    void push(int x) {
        addFirst(new ListNode(x));
    }
    
    int pop() {
        return removeFirst();
    }
    
    int top() {
        return getFirst();
    }
    
    bool isEmpty() {
        return sizeFun()==0;
    }
};
```
This removeFirst makes `tt` dahngling if ll has only 1 node and we delete that so

```cpp
    int removeFirst(){
        if(th==nullptr) return -1;
        int val=th->val;
         size--;
        if(th==tt){
            th=tt=nullptr;
            return val;
        }
        ListNode * temp=th;
        th=th->next;
        temp->next=nullptr;
        delete(temp);
        return val;
    }
```
i modified but ai said now 

### The Memory Leak
In your new if(th == tt) block, you set the pointers to nullptr and return the value immediately. You never call delete on that last node, and you never decrement size. Over time, this will consume unnecessary memory.

So we get that so ai code

```cpp
int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}
```

## Queue using LL


```cpp
struct ListNode{
        int val;
        ListNode * next;
        ListNode(int x){
            this->next=nullptr;
            this->val=x;
        }
};

class LinkedListQueue {
    ListNode* th;
    ListNode *tt;
    int size;
    void addLast(int val) {
        ListNode* node = new ListNode(val);
        if (th== nullptr)
            th= tt = node;
        else {
            tt->next = node;
            tt= node;
        }
        size++;
    }
int removeFirst() {
    if (th == nullptr) return -1; // Stack is empty

    ListNode* temp = th;
    int val = temp->val;

    if (th == tt) { 
        // Case: Only one node exists
        th = tt = nullptr;
    } else {
        // Case: Multiple nodes exist
        th = th->next;
    }

    temp->next = nullptr; 
    delete temp; // Always free the memory
    size--;      // Always decrement size
    return val;
}

    int getLast(){
        if(size==0) return -1;
        return th->val;
    }
public:
    LinkedListQueue() {
        th=tt=nullptr;
        this->size=0;
    }
    
    void push(int x) {
        addLast(x);
    }
    
    int pop() {
        return removeFirst();
    }
    
    int peek() {
        return getLast();
    }
    
    bool isEmpty() {
        return size==0;
    }
};
```

Atlast can also add a destructor 

```cpp

~LinkedListQueue() {
        while (th != nullptr) {
            ListNode* temp = th;
            th = th->next;
            delete temp;
        }
        tt = nullptr;
        size = 0;
    }
```    
 removeLast() is never used in either of stack and queue!!

# The "Remove Last" Bottleneck in Linked Lists

A common interview trick question is whether having a `tail` pointer makes `removeLast` an $O(1)$ operation. The answer depends entirely on the **direction** of the links.

---

### 1. Singly Linked List (SLL) with Tail: $O(N)$
Even with a `tail` pointer, removing the last node in a Singly Linked List remains **$O(N)$**.

**The "Physics" of the Problem:**
To successfully remove the last node, the computer must:
1.  **Delete** the current `tail`.
2.  **Update** the node *before* the tail (the second-to-last node) so its `next` pointer becomes `NULL`.
3.  **Update** the `tail` pointer to point to this second-to-last node.

In an SLL, links only go forward ($\rightarrow$). The `tail` pointer knows exactly where the last node is, but it has **no way to look backward** to find the second-to-last node. You are forced to start from the `head` and traverse the entire list to find the predecessor.

---

### 2. Doubly Linked List (DLL) with Tail: $O(1)$
In a Doubly Linked List, `removeLast` becomes a true **$O(1)$** operation.

**The Solution:**
Because each node has a `prev` pointer, the `tail` can "look back" and identify its predecessor instantly without a full traversal.

`"In a Singly Linked List, a tail pointer is only half of the solution. While it gives us $O(1)$ access for insertion, we still need $O(N)$ for removal because we cannot access the predecessor node without a full traversal. To achieve $O(1)$ for both, we must use a Doubly Linked List."`

### Comparison Table: Time Complexity

| Operation | Singly LL (+ Tail) | Doubly LL (+ Tail) |
| :--- | :--- | :--- |
| **Insert at Front** | $O(1)$ | $O(1)$ |
| **Insert at Last** | $O(1)$ | $O(1)$ |
| **Remove from Front** | $O(1)$ | $O(1)$ |
| **Remove from Last** | **$O(N)$** | **$O(1)$** |
