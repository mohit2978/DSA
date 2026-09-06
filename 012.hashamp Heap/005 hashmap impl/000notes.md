
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

 ![alt text](<006 hashmap youtube_231018_213422.jpg>) ![alt text](<006 hashmap youtube_231018_213422(1).jpg>) ![alt text](<006 hashmap youtube_231018_213422(2).jpg>) ![alt text](<006 hashmap youtube_231018_213422(3).jpg>) ![alt text](<006 hashmap youtube_231018_213422(4).jpg>) ![alt text](<006 hashmap youtube_231018_213422(5).jpg>) ![alt text](<006 hashmap youtube_231018_213422(6).jpg>) ![alt text](<006 hashmap youtube_231018_213422(7).jpg>) ![alt text](<006 hashmap youtube_231018_213422(8).jpg>) ![alt text](<006 hashmap youtube_231018_213422(9).jpg>) ![alt text](<006 hashmap youtube_231018_213422(10).jpg>) ![alt text](<006 hashmap youtube_231018_213422(11).jpg>) ![alt text](<006 hashmap youtube_231018_213422(12).jpg>) ![alt text](<006 hashmap youtube_231018_213422(13).jpg>) ![alt text](<006 hashmap youtube_231018_213422(14).jpg>) ![alt text](<006 hashmap youtube_231018_213422(15).jpg>) ![alt text](<006 hashmap youtube_231018_213422(16).jpg>) ![alt text](<006 hashmap youtube_231018_213422(17).jpg>) ![alt text](<006 hashmap youtube_231018_213422(18).jpg>) ![alt text](<006 hashmap youtube_231018_213422(19).jpg>) ![alt text](<006 hashmap youtube_231018_213422(20).jpg>) ![alt text](<006 hashmap youtube_231018_213422(21).jpg>)

![alt text](<006 hashmap youtube_231018_213422(22).jpg>) ![alt text](<006 hashmap youtube_231018_213422(23).jpg>) ![alt text](<006 hashmap youtube_231018_213422(24).jpg>) ![alt text](<006 hashmap youtube_231018_213422(25).jpg>) ![alt text](<006 hashmap youtube_231018_213422(26).jpg>) ![alt text](<006 hashmap youtube_231018_213422(27).jpg>)

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


![alt text](<010flatten bt and bt to dll_240401_000940(24).jpg>) ![alt text](<010flatten bt and bt to dll_240401_000940(25).jpg>)



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




