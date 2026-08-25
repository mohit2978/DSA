
![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1).jpg>)

![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(1).jpg>) 

### Mergesort lists

```cpp
#include <bits/stdc++.h>
using namespace std;


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
    private :
        ListNode* mid (ListNode * node){
            if(node==nullptr || node->next==nullptr) return node;
            ListNode* slow=node;
            ListNode* fast=node;
            while( fast->next!=nullptr && fast->next->next!=nullptr){
                slow=slow->next;
                fast=fast->next->next;
            }
            return slow;
        }  
    
        ListNode* merge(ListNode *l1,ListNode *l2){
            if(l1==nullptr && l2==nullptr) return l1;
            if(l1==nullptr) return l2;
            if(l2==nullptr) return l1;
             ListNode* tmp=new ListNode(-1);
            ListNode *itr1=l1;
            ListNode * itr2=l2;
            ListNode *curr=tmp;
            while(itr1!=nullptr && itr2!=nullptr){
                if(itr1->val < itr2->val){
                    curr->next=itr1;
                    curr=curr->next;
                    itr1=itr1->next;
                    curr->next=nullptr;
                }else{
                    curr->next=itr2;
                    curr=curr->next;
                    itr2=itr2->next;
                    curr->next=nullptr;
                }
            }
            if(itr1!=nullptr) curr->next=itr1;
            if(itr2!=nullptr) curr->next=itr2;
            ListNode * head=tmp->next;
            tmp->next=nullptr;
            delete(tmp);
            return head;
    
        }  
    public:
        ListNode* sortList(ListNode* head) {
            if(head==nullptr || head->next==nullptr) return head;
            ListNode* middle=mid(head);
            ListNode *l1=head;
            ListNode *l2=middle->next;
            middle->next=nullptr;
            l1=sortList(l1);
            l2=sortList(l2);
           return merge(l1,l2);
        }
};

int main(){
    
    return 0;
}

```
### Merge k sorted lists

```java

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode merge(ListNode h1,ListNode h2){
        if(h1==null) return h2;
        if(h2==null) return h1;
        ListNode dummy=new ListNode(-1);
        ListNode curr=dummy;
        while(h1!=null&&h2!=null){
            if(h1.val<h2.val){
                ListNode node=new ListNode(h1.val);
                curr.next=node;
                h1=h1.next;
            }
            else{
                ListNode node=new ListNode(h2.val);
                curr.next=node;
                h2=h2.next;
            }
            curr=curr.next;
        }
        while(h1!=null){
             ListNode node=new ListNode(h1.val);
                curr.next=node;
                h1=h1.next;
             curr=curr.next;
            
        }
        while(h2!=null){
              ListNode node=new ListNode(h2.val);
                curr.next=node;
                h2=h2.next;
             curr=curr.next;
        }
        return dummy.next;
    }
    
    public ListNode mergelist(ListNode[] lists,int si,int li){
        if(si==li) return lists[si];
        int mid=(si+li)/2;
        ListNode l1=mergelist(lists,si,mid);
        ListNode l2=mergelist(lists,mid+1,li);
        return merge(l1,l2);
    }
    public ListNode mergeKLists(ListNode[] lists) {
        if(lists.length==0) return null;
        return mergelist(lists,0,lists.length-1);
    }
}
```
# # Flattening of LL

### Problem Statement
Given a special linked list containing `n` head nodes where every node in the linked list contains two pointers:
* 'Next' points to the next node in the list
* 'Child' pointer to a linked list where the current node is the head

Each of these child linked lists is in sorted order and connected by a 'child' pointer.

Flatten this linked list such that all nodes appear in a single sorted layer connected by the 'child' pointer and return the head of the modified list.

### Examples

**Example 1**
```text
Input:
head -> 1 -> 4 -> 7 -> 9 -> 12
        |    |    |    |     |
        2    5    8    10    11
        |    |
        3    6

Output: head -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 11 -> 12

Explanation: All the linked lists are joined together and sorted in a single level through the child pointer.
```
### Constraints
- $n == \text{Number of head nodes}$
- $1 \leq n \leq 100$
- $1 \leq \text{Number of nodes in each child linked list} \leq 100$
- $0 \leq \text{ListNode.val} \leq 1000$
- All child linked lists are sorted in non-decreasing order.

## Striver sol

```cpp
#include <bits/stdc++.h>
using namespace std;

// Definition of special linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode *child;
    ListNode() {
        val = 0;
        next = NULL;
        child = NULL;
    }
    ListNode(int data1) {
        val = data1;
        next = NULL;
        child = NULL;
    }
    ListNode(int data1, ListNode *next1, ListNode* next2) {
        val = data1;
        next = next1;
        child = next1;
    }
};

class Solution {
private:
    /* Merge the two linked lists in a particular
     order based on the data value */
    ListNode* merge(ListNode* list1, ListNode* list2){
        /* Create a dummy node as a 
        placeholder for the result */
        ListNode* dummyNode = new ListNode(-1);
        ListNode* res = dummyNode;
    
        // Merge the lists based on data values
        while(list1 != NULL && list2 != NULL){
            if(list1->val < list2->val){
                res->child = list1;
                res = list1;
                list1 = list1->child;
            }
            else{
                res->child = list2;
                res = list2;
                list2 = list2->child;
            }
            res->next = NULL;
        }
    
        // Connect the remaining elements if any
        if(list1){
            res->child = list1;
        } else {
            res->child = list2;
        }
    
        // Break the last node's link to prevent cycles
        if(dummyNode->child){
            dummyNode->child->next = NULL;
        }
        
        return dummyNode->child;
    }

public:
    // Function to flatten a linked list with child pointers 
    ListNode* flattenLinkedList(ListNode* head) {
        // If head is null or there is no next node
        if(head == NULL || head->next == NULL){
            return head; // Return head
        }
    
        // Recursively flatten the rest of the linked list
        ListNode* mergedHead = flattenLinkedList(head->next);
        
        // Merge the lists
        head = merge(head, mergedHead);
        return head;
    }
};

// Function to print the linked list
void printLinkedList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->child;
    }
    cout << endl;
}

// Function to print the linked list in a grid-like structure
void printOriginalLinkedList(ListNode* head, int depth) {
    while (head != nullptr) {
        cout << head->val;

        /* If child exists, recursively
         print it with indentation */
        if (head->child) {
            cout << " -> ";
            printOriginalLinkedList(head->child, depth + 1);
        }

        // Add vertical bars for each level in the grid
        if (head->next) {
            cout << endl;
            for (int i = 0; i < depth; ++i) {
                cout << "| ";
            }
        }
        head = head->next;
    }
}

int main() {
    // Create a linked list with child pointers
    ListNode* head = new ListNode(5);
    head->child = new ListNode(14);

    head->next = new ListNode(10);
    head->next->child = new ListNode(4);

    head->next->next = new ListNode(12);
    head->next->next->child = new ListNode(20);
    head->next->next->child->child = new ListNode(13);

    head->next->next->next = new ListNode(7);
    head->next->next->next->child = new ListNode(17);

    // Print the original linked list structure
    cout << "Original linked list:" << endl;
    printOriginalLinkedList(head, 0);

    // Creating an instance of Solution class
    Solution sol;
    
    // Function call to flatten the linked list
    ListNode* flattened = sol.flattenLinkedList(head);
    
    // Printing the flattened linked list
    cout << "\nFlattened linked list: ";
    printLinkedList(flattened);

    return 0;
}
```

## My sol
```CPP
/*
Definition of special linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode *child;
    ListNode()
    {
        val = 0;
        next = NULL;
        child = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
        child = NULL;
    }
    ListNode(int data1, ListNode *next1, ListNode* next2)
    {
        val = data1;
        next = next1;
        child = next1;
    }
};
*/

class Solution {
    ListNode* merge(ListNode* h1, ListNode* h2) {
        if (h1 == nullptr) return h2;
        if (h2 == nullptr) return h1;
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;
        while (h1 != nullptr && h2 != nullptr) {
            if (h1->val < h2->val) {
                curr->child = h1;
                h1 = h1->child;
            } else {
                curr->child = h2;
                h2 = h2->child;
            }
            curr = curr->child;
        }
        while (h1 != nullptr) {
            curr->child = h1;
            h1 = h1->child;
            curr = curr->child;
        }
        while (h2 != nullptr) {
            // ListNode node=new ListNode(h2.val);
            curr->child = h2;
            h2 = h2->child;
            curr = curr->child;
        }
        return dummy->child;
    }

    ListNode* mergelist(vector<ListNode*> lists, int si, int li) {
        if (si == li) return lists[si];
        int mid = (si + li) / 2;
        ListNode* l1 = mergelist(lists, si, mid);
        ListNode* l2 = mergelist(lists, mid + 1, li);
        return merge(l1, l2);
    }

    ListNode* mergeKLists(vector<ListNode*> & lists) {
        if (lists.size() == 0) return nullptr;
        return mergelist(lists, 0, lists.size() - 1);
    }

   public:
    ListNode* flattenLinkedList(ListNode*& head) {
        if (head == nullptr || head->next == nullptr) return head;
        vector<ListNode*> temp;
        ListNode* curr = head;
        while (curr != nullptr) {
            temp.push_back(curr);
            curr = curr->next;
        }
        return mergeKLists(temp);
    }
};
```
This comparison is a battle between **Recursion** (Solution 1) and **Divide and Conquer / Merge K-Sorted Lists** (Solution 2).

While both are logically sound, **Solution 2 is the more advanced, "Senior-level" approach.** Here is the breakdown of why.

### 1. Complexity Analysis: The "Skew" Problem
* **Solution 1 (Recursion from Right to Left):**
    * This works like `Merge(List1, Merge(List2, Merge(List3, List4)))`.
    * **Time Complexity:** $O(N \cdot K^2)$ in the worst case, where $K$ is the number of main nodes (columns) and $N$ is the average nodes in a child list. If the list is long, you are merging the same elements over and over again.
* **Solution 2 (Divide and Conquer):**
    * This works exactly like **Merge Sort**. It merges pairs of lists, then pairs of the resulting lists.
    * **Time Complexity:** $O(N \cdot K \log K)$.
    * **Why it wins:** Because of the $\log K$ factor. In a large system with 1,000 columns, Solution 1 does 1,000 merge operations. Solution 2 only does about 10 "levels" of merging.

### 2. Space & Memory (Stack vs. Heap)
* **Solution 1:** Uses the **Recursion Stack**. If you have 10,000 columns, you will hit a **Stack Overflow**.
* **Solution 2:** Uses a Vector to store pointers and an explicit **Merge-Sort-style recursion**. While it also uses recursion, the depth is only $\log K$. For 1,000,000 nodes, the depth is only 20. It is virtually "overflow-proof."

### 3. Engineering Precision (The `next` pointer)
There is a subtle but vital bug-fix in Solution 1 that Solution 2 missed:

In Solution 1, you see:
```cpp
res->next = NULL; // Crucial!
```

When flattening, the problem usually requires the result to be a single vertical list (using `child`). If you don't explicitly null out the `next` pointers during the merge, your final "flattened" list will still have "ghost" pointers pointing to the side, which can cause infinite loops or memory leaks in some test environments.

* Solution 2 should ideally set `curr->next = nullptr` inside its merge loop to be truly "clean."

### 4. Code Readability & Style
* **Solution 1:** Is **"Competitive Programming"** style. It's short and recursive.
* **Solution 2:** Is **"System Design"** style. It treats the problem as a "Merge K Sorted Lists" problem.

### Interview Tip
If the interviewer says **"How would you optimize this if there are millions of columns?"**, Solution 2 is the only correct answer. You can even mention that using a **Priority Queue (Min-Heap)** instead of Divide & Conquer would also achieve $O(N \cdot K \log K)$ and is very common in production.

### Summary Table

| Feature | Solution 1 (Linear Recursion) | Solution 2 (Divide & Conquer) |
| :--- | :--- | :--- |
| **Complexity** | $O(N \cdot K^2)$ | $O(N \cdot K \log K)$ |
| **Scalability** | **Low** (Stack Overflow risk) | **High** |
| **Pattern** | Simple Recursion | Merge Sort / K-Way Merge |
| **Verdict** | Good for Beginners. | **Winner for Senior Interviews.** |

Let:
* $K$ = Number of main nodes (the "columns" or the length of the top-level list).
* $N$ = Average number of nodes in each vertical child list.
* Total nodes in the entire structure $\approx N \times K$.

### 1. The "Levels" of Merging
In Divide and Conquer, we don't merge List 1 into List 2, then into List 3. Instead, we merge them in pairs:
* **Level 1:** We merge $K$ lists into $K/2$ lists.
* **Level 2:** We merge $K/2$ lists into $K/4$ lists.
* ...and so on until only 1 list remains.

The number of levels in this "Tournament" is always $\log K$.

### 2. The Work Done at Each Level
At every single level, we are essentially touching every node in the entire structure **once** to perform the comparisons:
* In **Level 1**, we process $N \times K$ nodes.
* In **Level 2**, we still process the same $N \times K$ nodes (just combined into longer lists).
* The work done per level is $O(N \times K)$.

### 3. The Total Calculation
$$Total\ TC = (\text{Work per Level}) \times (\text{Number of Levels})$$
$$Total\ TC = O(N \cdot K) \times \log K$$
$$Total\ TC = O(N \cdot K \log K)$$

### Comparison: Why is this better than Solution 1?

**Solution 1 (Linear Merge):**
* You merge List 1 (size $N$) with List 2 (size $N$). Work = $2N$.
* Then you merge the result (size $2N$) with List 3 (size $N$). Work = $3N$.
* Then with List 4. Work = $4N$.
* **Total Work:** $2N + 3N + 4N \dots + KN$

This is an **Arithmetic Progression**: $N \times (2+3+4 \dots + K) \approx \mathbf{O(N \cdot K^2)}$

**The Difference:**
If $K = 1000$:
* **Solution 1:** $1000^2 = 1,000,000$ operations per node.
* **Solution 2:** $1000 \times \log(1000) \approx 1000 \times 10 = 10,000$ operations per node.
* **Solution 2 is 100 times faster for 1,000 lists.**

### Space Complexity (SC)
* $O(\log K)$: This is the height of the recursion tree. Even though we are merging $K$ lists, the computer only needs to remember $\log K$ function calls at any one time.
* This is why Solution 2 is much safer against **Stack Overflow** than the linear $O(K)$ recursion of Solution 1.

![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(2).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(3).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(4).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(5).jpg>) 

```cpp
// temporary head, temporary tail
ListNode *th = nullptr;
ListNode *tt = nullptr;

void addFirstNode(ListNode *node)
{
    if (th == nullptr)
    {
        th = node;
        tt = node;
    }
    else
    {
        node->next = th;
        th = node;
    }
}
int lengthOfLL(ListNode *node)
{
    if (node == nullptr)
        return 0;

    int len = 0;
    while (node != nullptr)
    {
        node = node->next;
        len++;
    }

    return len;
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    if (head == nullptr || head->next == nullptr || k == 1)
        return head;

    // original head, original tail
    ListNode *oh = nullptr;
    ListNode *ot = nullptr;

    int len = lengthOfLL(head);
    ListNode *curr = head;

    while (len >= k)
    {
        int tempK = k;
        while (tempK-- > 0)
        {
            ListNode *forw = curr->next;
            curr->next = nullptr;
            addFirstNode(curr);
            curr = forw;
        }

        if (oh == nullptr)
        {
            oh = th;
            ot = tt;
        }
        else
        {
            ot->next = th;
            ot = tt;
        }

        th = nullptr;
        tt = nullptr;
        len -= k;
    }

    ot->next = curr;
    return oh;
}
```


```java

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public int length(ListNode head){
        if(head==null) return 0;
        ListNode curr=head;
        int length=0;
        while(curr!=null){
            curr=curr.next;
            length++;
        }
        return length;
    }
    public void addfirst(ListNode[]temp,ListNode node){
        if(temp[0]==null){
            temp[0]=temp[1]=node;
        }
        else{
            node.next=temp[0];
            temp[0]=node;
        }
    }
    
    public ListNode reverseKGroup(ListNode head, int k) {
        if(head==null||head.next==null||k==1) return head;
        ListNode[] temp=new ListNode[2];
        int len=length(head);
        ListNode ah=null;
        ListNode at=null;
        ListNode curr=head;
        while(len>=k){
            int tempVar=k;
            while(tempVar-->0){
                ListNode forward=curr.next;
                curr.next=null;
                addfirst(temp,curr);
                curr=forward;
            }
            if(ah==null){
                ah=temp[0];
                at=temp[1];
            }
            else{
                at.next=temp[0];
                at=temp[1];
            }
            temp[0]=temp[1]=null;
            len-=k;
            
        }
        at.next=curr;
        return ah;
        
    }
}

```


![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(6).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(7).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(8).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(9).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(10).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(11).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(12).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(13).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(14).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(15).jpg>) ![alt text](<003 merge k sorted list and reverse nodes_240412_185705 (1)(16).jpg>)