
A class `Student` with attributes:

```
name
height
weight
```

Now we will create a object of class `Student`, say `s`:

```java
Student s = new Student("A", 179, 80);
//                        ↑ height  ↑ weight
```

Now if we do `System.out.println(s);` → then gives some thing but not object.

`System.out.println()` → print statement. So in class `Student` we have `toString()` function which prints student as string. The print statement will print return value of `toString()`.

If you do `public static toString() { return "hello"; }` then o/p by `System.out.println(s)` will be `"hello"`. But we want to print the object `s`, so we return:

```java
this.name + " " + this.ht + " " + this.wt;
```

```java
static class Student {
    String name;
    int ht;
    int wt;

    Student(String name, int ht, int wt) {
        this.name = name;
        this.ht = ht;
        this.wt = wt;
    }

    public String toString() {
        return this.name + "-> " + this.ht + "," + this.wt;
    }
}

public static void main(String[] args) throws Exception {
    Student s = new Student("A", 179, 80);
    System.out.println(s);
}
```

### Sorting an array of Students

Now we have a Student array & we need to `sort()` them on base of height.

```java
Students[] students = new Students[5];
students[0] = new Student("A", 180, 75);
students[1] = new Student("B", 150, 85);
students[2] = new Student("C", 185, 72);
students[3] = new Student("D", 165, 65);
students[4] = new Student("E", 177, 55);
```

We created student array & added objects to the indexes, now we need to sort them on base of height.

Priority Queue (collection wali) use Comparable

Now we need to make the class `Comparable` so that we can add objects in Priority Queue & Priority Queue sorts them on base of height.




### The `Comparable` Interface

It sorts on base of height of student.

### Full Working Program

```java
import java.util.*;

public class Main {
    static class Student implements Comparable<Student> {
        String name;
        int ht;
        int wt;

        Student(String name, int ht, int wt) {
            this.name = name;
            this.ht = ht;
            this.wt = wt;
        }

        public String toString() {
            return this.name + " " + this.ht + " " + this.wt;
        }

        public int compareTo(Student other) {
            return this.ht - other.ht;
        }
    }

    public static void main(String[] args) {
        Student[] s = new Student[5];
        s[0] = new Student("A", 180, 75);
        s[1] = new Student("B", 150, 85);
        s[2] = new Student("C", 185, 72);
        s[3] = new Student("D", 165, 65);
        s[4] = new Student("E", 177, 55);

        PriorityQueue<Student> pq = new PriorityQueue<>();
        for (var stu : s) {
            pq.add(stu);
        }

        while (pq.size() > 0) {
            Student s1 = pq.peek();
            pq.remove();
            System.out.println(s1);
        }
    }
}
```

**Output:** `B 150 85` `D 165 65` `E 177 55` `A 180 75` `C 185 72`



### Now we want to sort on base of weight — enter `Comparator`

Now we want to sort on base of weight. You will change `compareTo()` of course. Now I say I want kbhi height ke base pe or kbhi weight ke base pe — or I say I have 2 arrays, one we need sort on base of height and one on base of weight. So now what to do?

Now we make another class which implements `Comparator` interface, & it has fn `compare` which has both Student object (as it is outside class so no `this` is used here) & it compares both on base of weight.

```java
static class StudentWeightComparator implements Comparator<Student> {
    public int compare(Student s1, Student s2) {
        return s1.weight - s2.weight;
    }
}
```

```
if s1.weight > s2.weight return +ve
if s1.weight < s2.weight return -ve
```

Else — we have to make 2 Priority Queue to sort on different basis.

```java
PriorityQueue<Student> pqHt = new PriorityQueue<>();
PriorityQueue<Student> pqWt = new PriorityQueue<>(new StudentWeightComparator());
```



**It says Priority Queue you have to use that Comparator class to compare things, not that Comparable interface.**

**Two things we have:** Comparable is in class; Comparator & Comparable — Comparator outside class.

### Full example — 2 attributes, 2 PriorityQueues

```java
import java.util.*;

public class Main {
    static class Student implements Comparable<Student> {
        String name;
        int ht;
        int wt;

        Student(String name, int ht, int wt) {
            this.name = name;
            this.ht = ht;
            this.wt = wt;
        }

        public String toString() {
            return this.name + " " + this.ht + " " + this.wt;
        }

        public int compareTo(Student other) {
            return this.ht - other.ht;
        }
    }

    static class stuwtcomparator implements Comparator<Student> {
        public int compare(Student s1, Student s2) {
            return s1.wt - s2.wt;
        }
    }

    public static void main(String[] args) {
        Student[] s = new Student[5];
        s[0] = new Student("A", 180, 75);
        s[1] = new Student("B", 150, 85);
        s[2] = new Student("C", 185, 72);
        s[3] = new Student("D", 165, 65);
        s[4] = new Student("E", 177, 55);

        PriorityQueue<Student> pqht = new PriorityQueue<>();
        PriorityQueue<Student> pqwt = new PriorityQueue<>(new stuwtcomparator());

        for (var stu : s) {
            pqht.add(stu);
            pqwt.add(stu);
        }

        System.out.println("Sort on base of height");
        while (pqht.size() > 0) {
            Student s1 = pqht.peek();
            System.out.println(s1);
            pqht.remove();
        }

        System.out.println("Sort on base of weight");
        while (pqwt.size() > 0) {
            Student s1 = pqwt.remove();
            System.out.println(s1);
        }
    }
}
```

**Output:**

```
sort according to height          sort according to weight
B 150 85 33                       E 177 55 88
D 165 65 75                       D 165 65 75
E 177 55 88                       C 185 72 99
A 180 75 90                       A 180 75 90
C 185 72 99                       B 150 85 33
```

### Sorting on 3+ attributes

Now in Student class we have 4 attributes:

```
① name    ③ weight
② height  ④ Marks
```

Now sort accordingly to all 3 (height, weight & marks) — as in previous we have 2 Priority Queue for sorting according to 2 attributes, here we will have 3 Priority Queues.

Now we will sort according to height in class, so use Comparable interface & sort according to weight & Marks & use Comparator interface for them:

```java
import java.util.*;

public class Main {
    static class Student implements Comparable<Student> {
        String name;
        int wt;
        int ht;
        int marks;

        Student(String name, int ht, int wt, int marks) {
            this.name = name;
            this.wt = wt;
            this.ht = ht;
            this.marks = marks;
        }

        public String toString() {
            return this.name + " " + this.ht + " " + this.wt + " " + this.marks;
        }

        public int compareTo(Student other) {
            return this.ht - other.ht;
        }
    }

    static class stuwtcompare implements Comparator<Student> {
        public int compare(Student s1, Student s2) {
            return s1.wt - s2.wt;
        }
    }

    static class stumarkscompare implements Comparator<Student> {
        public int compare(Student s1, Student s2) {
            return s1.marks - s2.marks;
        }
    }

    public static void main(String[] args) {
        Student[] s = new Student[5];
        s[0] = new Student("A", 180, 75, 90);
        s[1] = new Student("B", 150, 85, 33);
        s[2] = new Student("C", 185, 72, 99);
        s[3] = new Student("D", 165, 65, 75);
        s[4] = new Student("E", 177, 55, 88);

        PriorityQueue<Student> pqht = new PriorityQueue<>();
        PriorityQueue<Student> pqwt = new PriorityQueue<>(new stuwtcompare());
        PriorityQueue<Student> pqmarks = new PriorityQueue<>(new stumarkscompare());

        for (var val : s) {
            pqht.add(val);
            pqwt.add(val);
            pqmarks.add(val);
        }

        System.out.println("sort according to height");
        while (pqht.size() > 0) {
            Student s1 = pqht.peek();
            System.out.println(s1);
            pqht.remove();
        }

        System.out.println("sort according to weight");
        while (pqwt.size() > 0) {
            Student s1 = pqwt.remove();
            System.out.println(s1);
        }

        System.out.println("sort according to marks");
        while (pqmarks.size() > 0) {
            Student s1 = pqmarks.remove();
            System.out.println(s1);
        }
    }
}
```

**Output:**

```
sort according to height:  B D E A C
sort according to weight:  E D C A B
sort according to marks:   B D E A C
```

### Sorting by Name — using String's own `Comparable`

String class mein already `compareTo` implemented hai, toh hum use call karte hai:

```java
/*
 * public int compareTo(String anotherString) { ... }
 */
```

*(Original `java.lang.String` source: it compares character-by-character; jo character different hai, use compare kar ke chota vale ko phle put kar dega.)*

Toh String ko lie hum khud se kuch likhne ki jo pehle hai use case karna hai:

```java
public int compareTo(Student other) {
    return this.name.compareTo(other.name);
}
```

**Output (Sort by Name):** `A` `B` `C` `D` `E`

Class hi used to compare Strings.

---

## Building a Generic Priority Queue From Scratch

Now I have made everything outside class Student, so used 3 classes that implement Comparator.

### First pass — `MyPriorityQueue` for `int`

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
        if (data.size() == 0) {
            System.out.println("Underflow");
            return -1;
        }
        if (data.size() == 1) {
            return data.remove(0);
        }
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

Just the previous program where we have made our own Priority Queue using Heap.

### Second pass — make it generic: `MyPriorityQueue<T>`

We have to make a generic Priority Queue, so put `<T>` — it says that at instantiation, main mein kuch bhi accept karungi. ArrayList bhi `T` ki ho jaegi & previous constructor bhi hata do. Swap mein change:

```java
public static class MyPriorityQueue<T> {
    ArrayList<T> data;

    public MyPriorityQueue() {
        data = new ArrayList<>();
    }

    // public MyPriorityQueue(int[] arr) {
    //     data = new ArrayList<>();
    //     for(int val: arr){
    //         data.add(val);
    //     }
    //     for(int i = data.size() / 2 - 1; i >= 0; i--){
    //         downheapify(i);
    //     }
    // }

    public void add(T val) {
        data.add(val);
        upheapify(data.size() - 1);
    }

    public void swap(int i, int j) {
        T ith = data.get(i);
        T jth = data.get(j);
        data.set(i, jth);
        data.set(j, ith);
    }
}
```

Also change in `add()`/`remove()` — now `add` takes `T` type value & return type of `remove` is `T` too, & `T` also for `peek()` too:

```java
public T remove() {
    if (data.size() == 0) {
        System.out.println("Underflow");
        return null;
    }
    // ...
}

public T peek() {
    // write your code
}
```

`(i-1)` returns the value, where `null` return hoga.

### Comparing generic `T` objects

As `T` type ke hai objects, so we need to compare them. Now how to compare? For comparison we have `Comparator`, but if `Comparator` null then? Then we use `Comparable`.

For comparing we use another fn `isSmaller()` & then we use `Comparator` if it is available, else we use `Comparable`. We check element at `i` is smaller than element at `j`.

```java
boolean isSmaller(int i, int j) {
    T ith = data.get(i);
    T jth = data.get(j);

    if (cmptr != null) {
        if (cmptr.compare(ith, jth) < 0) {
            return true;
        } else {
            return false;
        }
    } else {
        Comparable cith = (Comparable) ith;
        Comparable cjth = (Comparable) jth;
        if (cith.compareTo(cjth) < 0) {
            return true;
        } else {
            return false;
        }
    }
}
```

This fn we are going to use everywhere we want to compare. If condition is written as `cdata < pardata` or `isSmaller(cdata, pardata) == true`.

Now we need to provide Comparator support. If we have made no-comparator constructor at line 10 will be called, else line 15 constructor is called.

We have made a variable of Comparator type in class `MyPriorityQueue`, & in constructor we need to initialise that:

```java
public static class MyPriorityQueue<T> {
    ArrayList<T> data;
    Comparator cmptr;

    public MyPriorityQueue() {
        data = new ArrayList<>();
        cmptr = null;
    }

    public MyPriorityQueue(Comparator cmptr) {
        data = new ArrayList<>();
        this.cmptr = cmptr;
    }
}
```

### Fixing `upheapify`/`downheapify` to use `isSmaller()`

**Changes to be made:** it is still wrong as `issmaller` fn takes indexes, so only pass `(li, priority)` in line 60 & in line 61 only `(ri, priority)`:

```java
public void upheapify(int i) {
    if (i == 0) return;
    int pari = (i - 1) / 2;
    if (issmaller(i, pari)) {
        swap(i, pari);
        upheapify(pari);
    }
}

public void downheapify(int i) {
    int li = 2 * i + 1;
    int ri = 2 * i + 2;
    int priority = i;
    if (li < data.size() && issmaller(li, priority))
        priority = li;
    if (ri < data.size() && issmaller(ri, priority))
        priority = ri;
    if (priority != i) {
        swap(priority, i);
        downheapify(priority);
    }
}
```

### Full `MyPriorityQueue<T>` — code working, perfect

```java
public static class MyPriorityQueue<T> {
    ArrayList<T> data;
    Comparator cmp;

    public MyPriorityQueue() {
        data = new ArrayList<>();
        cmp = null;
    }

    public MyPriorityQueue(Comparator cmp) {
        data = new ArrayList<>();
        this.cmp = cmp;
    }

    public void swap(int i, int j) {
        T ith = data.get(i);
        T jth = data.get(j);
        data.set(i, jth);
        data.set(j, ith);
    }

    boolean issmaller(int i, int j) {
        T ith = data.get(i);
        T jth = data.get(j);
        if (cmp != null) {
            if (cmp.compare(ith, jth) < 0) return true;
            else return false;
        } else {
            Comparable cith = (Comparable) ith;
            Comparable cjth = (Comparable) jth;
            if (cith.compareTo(cjth) < 0) return true;
            else return false;
        }
    }

    public void upheapify(int i) {
        if (i == 0) return;
        int pari = (i - 1) / 2;
        if (issmaller(i, pari)) {
            swap(i, pari);
            upheapify(pari);
        }
    }

    public void add(T val) {
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
        if (li < data.size() && issmaller(li, priority))
            priority = li;
        if (ri < data.size() && issmaller(ri, priority))
            priority = ri;
        if (priority != i) {
            swap(priority, i);
            downheapify(priority);
        }
    }

    public T remove() {
        if (data.size() == 0) {
            System.out.println("Underflow");
            return null;
        }
        if (data.size() == 1) {
            return data.remove(0);
        }
        swap(data.size() - 1, 0);
        T rval = data.remove(data.size() - 1);
        downheapify(0);
        return rval;
    }

    public T peek() {
        if (data.size() == 0) {
            System.out.println("Underflow");
            return null;
        }
        return data.get(0);
    }

    public int size() {
        return data.size();
    }
}
```

Now we create Student class:

```java
static class Student implements Comparable<Student> {
    String name;
    int wt;
    int ht;
    int marks;

    Student(String name, int ht, int wt, int marks) {
        this.name = name;
        this.ht = ht;
        this.wt = wt;
        this.marks = marks;
    }

    public String toString() {
        return this.name + " " + this.ht + " " + this.wt + " " + this.marks;
    }

    public int compareTo(Student other) {
        return this.name.compareTo(other.name);
    }
}

static class compareht implements Comparator<Student> {
    public int compare(Student s1, Student s2) {
        return s1.ht - s2.ht;
    }
}

static class comparewt implements Comparator<Student> {
    public int compare(Student s1, Student s2) {
        return s1.wt - s2.wt;
    }
}

static class comparemarks implements Comparator<Student> {
    public int compare(Student s1, Student s2) {
        return s1.marks - s2.marks;
    }
}
```

Here on this page we have `main()` function:

```java
public static void main(String[] args) {
    Student[] s = new Student[5];
    s[0] = new Student("E", 180, 75, 90);
    s[1] = new Student("O", 150, 85, 33);
    s[2] = new Student("R", 185, 72, 99);
    s[3] = new Student("M", 165, 65, 75);
    s[4] = new Student("A", 177, 55, 88);

    MyPriorityQueue<Student> pqname = new MyPriorityQueue<>();
    MyPriorityQueue<Student> pqht = new MyPriorityQueue<>(new compareht());
    MyPriorityQueue<Student> pqwt = new MyPriorityQueue<>(new comparewt());
    MyPriorityQueue<Student> pqmarks = new MyPriorityQueue<>(new comparemarks());

    for (var stu : s) {
        pqname.add(stu);
        pqht.add(stu);
        pqwt.add(stu);
        pqmarks.add(stu);
    }

    System.out.println("Sort on base of name");
    while (pqname.size() > 0) {
        var val = pqname.remove();
        System.out.println(val);
    }

    System.out.println("Sort on base of height");
    while (pqht.size() > 0) {
        var val = pqht.remove();
        System.out.println(val);
    }

    System.out.println("Sort on base of weight");
    while (pqwt.size() > 0) {
        var val = pqwt.remove();
        System.out.println(val);
    }

    System.out.println("Sort on base of marks");
    while (pqmarks.size() > 0) {
        var val = pqmarks.remove();
        System.out.println(val);
    }
}
```

**Output:**

```
Sort on base of name         Sort on base of height        Sort on base of weight        Sort on base of marks
A 177 55 88                  O 150 85 33                    A 177 55 88                    O 150 85 33
E 180 75 90                  M 165 65 75                    M 165 65 75                    M 165 65 75
M 165 65 75                  A 177 55 88                    R 185 72 99                    A 177 55 88
O 150 85 33                  E 180 75 90                    E 180 75 90                    E 180 75 90
R 185 72 99                  R 185 72 99                    O 150 85 33                    R 185 72 99
```

### Q&A — why doesn't `Comparator` need typecasting, but `Comparable` does?

Comparator mein typecast nahi kiya, but Comparable mein kiya? Why?

`Comparator` already class nahi hai but `Comparable` nahi (i.e. `Comparator` here is passed in as an already-typed helper class instance, so its `compare(T, T)` signature already matches — no cast needed). `T` ko compare nahi kar sakta isliye usko typecast karna pada, but `Comparable` `T` ke saath cast ho jaega (i.e. since `T` itself doesn't extend `Comparable` generically, we must cast the raw `T` object down to the raw `Comparable` interface before calling `compareTo()` on it).

Collections: `reverseOrder()` hume ek `Comparator` return karta hai, jisme jo humne code likha hai uske ulta likha hota hai (bade vale ko chota jaisa dikhata hai) — i.e. `Collections.reverseOrder()` gives back a `Comparator` that flips the usual ordering, so the largest is treated as if it were the smallest, giving a max-heap instead of a min-heap.

**Complexity (for the final `MyPriorityQueue<T>`):**
- **Time:** `add()` and `remove()` are `O(log n)` — same array-as-complete-binary-tree reasoning as the earlier Heap Implementation notes; `isSmaller()` itself is `O(1)` (a single `Comparator.compare()` call or `Comparable.compareTo()` call), so it doesn't change the asymptotic bound of `upheapify()`/`downheapify()`. `peek()` and `size()` are `O(1)`.
- **Space:** `O(n)` for the underlying `ArrayList<T>`.
