### Mid of ll

![alt text](<001 basics_231123_174231 (1).jpg>) ![alt text](<001 basics_231123_174231 (1)(1).jpg>) ![alt text](<001 basics_231123_174231 (1)(2).jpg>) ![alt text](<001 basics_231123_174231 (1)(3).jpg>) 




Given the head of a singly Linked List, return the middle node of the Linked List.



If the Linked List has an even number of nodes, return the second middle one.

---
Examples:
Input: head -> 3 -> 8 -> 7 -> 1 -> 3

Output(value at returned node): 7

Explanation: There are 5 nodes, so the middle node is the 3rd Node, with value 7.

---

Input: head -> 2 -> 9 -> 1 -> 4 -> 0 -> 4

Output(value at returned node): 4

Explanation: There are 6 nodes, thus both the 3rd and 4th nodes are middle. So the 2nd middle node (4th Node) is returned with value 4.

---

Constraints:
1 <= number of Nodes in the Linked List <= 105

-10^4 <= ListNode.val <= 10^4

```cpp
class Solution {
public:
    ListNode* middleOfLinkedList(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return head;
        ListNode * fast=head;
        ListNode * slow=head;
        while(fast!=nullptr && fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;

    }
};
```



### Delete the mid node

```cpp

/*
Definition of singly linked list:
struct ListNode
{
    int val;
    ListNode *next;
    ListNode()
    {
        val = 0;
        next = NULL;
    }
    ListNode(int data1)
    {
        val = data1;
        next = NULL;
    }
    ListNode(int data1, ListNode *next1)
    {
        val = data1;
        next = next1;
    }
};
*/

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return nullptr;
        ListNode * fast=head;
        ListNode * slow=head;
        ListNode * temp=nullptr;
        while(fast!=nullptr && fast->next!=nullptr){
            temp=(temp==nullptr)?slow:(temp->next);
            slow=slow->next;
            fast=fast->next->next;
        }
        temp->next=slow->next;
        delete(slow);
        return head;
    }
};
```













![alt text](<001 basics_231123_174231 (1)(4).jpg>) ![alt text](<001 basics_231123_174231 (1)(5).jpg>) ![alt text](<001 basics_231123_174231 (1)(6).jpg>)

### Reverse a LL
```cpp

class Solution {
   ListNode* reverse(ListNode* head){

    ListNode * curr=head;
    ListNode* prev=nullptr;

    while(curr!=nullptr){
        ListNode * storage=curr->next;
        curr->next=prev;
        prev=curr;
        curr=storage;
    }

    return prev;

   }
public:
    ListNode* reverseList(ListNode* head) {
        if(head==nullptr || head->next==nullptr) return head;
        return reverse(head);
    }
};

```

tc-->O(n)


 ![alt text](<001 basics_231123_174231 (1)(7).jpg>)
  ![alt text](<001 basics_231123_174231 (1)(8).jpg>) 
```cpp
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    if (l1 == nullptr || l2 == nullptr)
        return l1 != nullptr ? l1 : l2;

    ListNode *dummy = new ListNode(-1);
    ListNode *prev = dummy;

    ListNode *c1 = l1;
    ListNode *c2 = l2;

    while (c1 != nullptr && c2 != nullptr)
    {
        if (c1->val <= c2->val)
        {
            prev->next = c1;
            c1 = c1->next;
        }
        else
        {
            prev->next = c2;
            c2 = c2->next;
        }

        prev = prev->next;
    }

    prev->next = c1 != nullptr ? c1 : c2;

    ListNode *h = dummy->next;
    dummy->next = nullptr;
    delete dummy;
    return h;
}
```

  ![alt text](<001 basics_231123_174231 (1)(9).jpg>) 
  ![alt text](<001 basics_231123_174231 (1)(10).jpg>)
  
  ```cpp

ListNode *midNode(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *slow = head;
    ListNode *fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

//206
ListNode *reverseList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return head;

    ListNode *prev = nullptr;
    ListNode *curr = head;

    while (curr != nullptr)
    {
        ListNode *forw = curr->next; // backup

        curr->next = prev; // link

        prev = curr; // move
        curr = forw;
    }

    return prev;
}

//234
bool isPalindrome(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return true;

    ListNode *mid = midNode(head);
    ListNode *nhead = mid->next;
    mid->next = nullptr;

    nhead = reverseList(nhead);

    ListNode *curr1 = head;
    ListNode *curr2 = nhead;

    bool res = true;
    while (curr1 != nullptr && curr2 != nullptr)
    {
        if (curr1->val != curr2->val)
        {
            res = false;
            break;
        }

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    nhead = reverseList(nhead);
    mid->next = nhead;

    return res;
}


  ```
  
   ![alt text](<001 basics_231123_174231 (1)(11).jpg>) ![alt text](<001 basics_231123_174231 (1)(12).jpg>) ![alt text](<001 basics_231123_174231 (1)(13).jpg>) ![alt text](<001 basics_231123_174231 (1)(14).jpg>) ![alt text](<001 basics_231123_174231 (1)(15).jpg>)



![alt text](<001 basics_231123_174231 (1)(16).jpg>) ![alt text](<001 basics_231123_174231 (1)(17).jpg>) ![alt text](<001 basics_231123_174231 (1)(18).jpg>)

# Segregate odd and even nodes in LL




Given the head of a singly linked list. Group all the nodes with odd indices followed by all the nodes with even indices and return the reordered list.



Consider the 1st node to have index 1 and so on. The relative order of the elements inside the odd and even group must remain the same as the given input.


Examples:
---
Input: head -> 1 -> 2 -> 3 -> 4 -> 5

Output: head -> 1 -> 3 -> 5 -> 2 -> 4

Explanation: The nodes with odd indices are 1, 3, 5 and the ones with even indices are 2, 4.

---

Input: head -> 4 -> 3 -> 2 -> 1

Output: head -> 4 -> 2 -> 3 -> 1

Explanation: The nodes with odd indices are 4, 2 and the ones with even indices are 3, 1.

---

Input: head -> 1

Output:
head -> 1

---

```cpp


class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head==nullptr || head->next ==nullptr) return head;
        ListNode * even =new ListNode(-1);
        ListNode * odd =new ListNode(-1);
        ListNode * curr=head;
        ListNode * h1=odd;
        ListNode * h2=even;
        int index=1;
        while(curr!=nullptr){
            if(index%2==0){
                h2->next=curr;
                h2=h2->next;
            }else{
                h1->next=curr;
                h1=h1->next;
            }
            curr=curr->next;
            index++;
        }
        h1->next=even->next;
        h2->next=nullptr;
        even->next=nullptr;
        delete(even);
        h1=odd;
        odd=odd->next;
        h1->next=nullptr;
        delete(h1);
        return odd;
    }
};
```