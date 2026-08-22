# Notes


![alt text](<006_231121_163402 (1).jpg>)







![alt text](<006_231121_163402 (1)(1).jpg>) ![alt text](<006_231121_163402 (1)(2).jpg>) ![alt text](<006_231121_163402 (1)(3).jpg>) ![alt text](<006_231121_163402 (1)(4).jpg>)

```java
/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/

class Solution {
    public Node copyRandomList(Node head) {
        Node curr=head;
        Map<Node,Node>map=new HashMap<>();
        Node dummy=new Node(-1);
        Node tmp=dummy;
        while(curr!=null){
            Node node=new Node(curr.val);
            map.put(curr,node);
            tmp.next=node;
            tmp=tmp.next;
            curr=curr.next;
        }
        curr=head;
        tmp=dummy.next;
        while(curr!=null){
            Node rn=curr.random;
            Node rntmp=map.get(rn);
            tmp.random=rntmp;
            curr=curr.next;
            tmp=tmp.next;
        }
        return dummy.next;
    }
}
```

 ![alt text](<006_231121_163402 (1)(5).jpg>) ![alt text](<006_231121_163402 (1)(6).jpg>)



![alt text](<006_231121_163402 (1)(7).jpg>) ![alt text](<006_231121_163402 (1)(8).jpg>) ![alt text](<006_231121_163402 (1)(9).jpg>) ![alt text](<006_231121_163402 (1)(10).jpg>) 

```java

/*
// Definition for a Node.
class Node {
    int val;
    Node next;
    Node random;

    public Node(int val) {
        this.val = val;
        this.next = null;
        this.random = null;
    }
}
*/

class Solution {
    public Node copyRandomList(Node head) {
       Node curr=head;
       while(curr!=null)
       {
           Node str=curr.next;
           Node node=new Node(curr.val);
           curr.next=node;
           node.next=str;
           curr=str;
       }
       curr=head;
       while(curr!=null){
          if(curr.random!=null) curr.next.random=curr.random.next;
          else curr.next.random=null;
           curr=curr.next.next;
       }
       Node dummy=new Node(-1);
       Node tmp=dummy;
       curr=head;
       while(curr!=null){
         Node nxt=curr.next;
         tmp.next=nxt;
         curr.next=nxt.next;
         if(curr.next!=null) nxt.next=curr.next.next;
         curr=curr.next;
         tmp=tmp.next;
       }
       return dummy.next;
    }
}
```

![alt text](<006_231121_163402 (1)(11).jpg>) ![alt text](<006_231121_163402 (1)(12).jpg>)

```java
import java.util.*;

class AllOne {

    private class Node {
        Node prev, next;
        int count = 0;
        List<String> list;

        Node(String key, int count) {
            this.count = count;
            list = new ArrayList<>();
            this.list.add(key);
        }
    }

    private HashMap<String, Node> map;
    private Node head = null, tail = null;

    public AllOne() {
        this.map = new HashMap<>();
    }

    private void addAtHead(Node node) {
        if (this.head == null)
            this.head = this.tail = node;
        else {
            this.head.next = node;
            node.prev = this.head;
            this.head = node;
        }
    }

    private void addAtTail(Node node) {
        if (this.head == null)
            this.head = this.tail = node;
        else {
            node.next = this.tail;
            this.tail.prev = node;
            this.tail = node;
        }
    }

    private void addNext(Node currNode, Node node) {
        if (currNode == this.head)
            addAtHead(node);
        else {
            Node nextNode = currNode.next;
            currNode.next = node;
            node.prev = currNode;

            node.next = nextNode;
            nextNode.prev = node;
        }
    }

    public void inc(String key) {
        if (map.size() == 0) {
            Node node = new Node(key, 1);
            map.put(key, node);
            this.head = this.tail = node;
        } else if (map.containsKey(key)) {
            Node node = map.get(key);
            Node nextNode = node.next;
            if (nextNode == null) {
                Node newNode = new Node(key, node.count + 1);
                addAtHead(node);
                map.put(key, newNode);
            } else if (nextNode.count == node.count + 1) {
                map.put(key, nextNode);
                List<String> list = nextNode.list;
                list.add(key);
            } else {
                Node newNode = new Node(key, node.count + 1);
                addNext(node, newNode);
                map.put(key, newNode);
            }

            List<String> list = node.list;
            list.remove(key);
        } else {
            if (this.tail.count == 1) {
                map.put(key, this.tail);
                List<String> list = this.tail.list;
                list.add(key);
            } else {
                Node newNode = new Node(key, 1);
                addAtTail(newNode);
                map.put(key, newNode);
            }
        }
    }

    public void dec(String key) {

    }

    public String getMinKey() {
        if (this.tail == null)
            return "";
        List<String> list = this.tail.list;
        return list.get(list.size() - 1);
    }

    public String getMaxKey() {
        if (this.head == null)
            return "";
        List<String> list = this.head.list;
        return list.get(0);
    }
}

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * String param_3 = obj.getMaxKey();
 * String param_4 = obj.getMinKey();
 */
````
Need to complete it


