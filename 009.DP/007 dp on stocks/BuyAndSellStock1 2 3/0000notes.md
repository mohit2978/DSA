# Q1 Best Time to Buy and Sell Stock

[View question on takeUforward](https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock?subject=dsa&approach=optimal)

Given an array `arr` of `n` integers, where `arr[i]` represents the price of the stock on the `i`th day, determine the maximum profit achievable by buying and selling the stock at most once.

The stock must be purchased before it is sold, and both actions cannot occur on the same day.

### Test Cases

**Example 1**

- Input: `arr = [10, 7, 5, 8, 11, 9]`
- Output: `6`

**Example 2**

- Input: `arr = [5, 4, 3, 2, 1]`
- Output: `0`

**Example 3**

- Input: `arr = [3, 8, 1, 4, 6, 2]`
- Output: `5`

### Constraints

- $1 \le n \le 10^5$
- $0 \le arr[i] \le 10^6$


![alt text](<Dp on stocks 1 and 2_260207_165404_0.png>) ![alt text](<Dp on stocks 1 and 2_260207_165404_1.png>) ![alt text](<Dp on stocks 1 and 2_260207_165404_2.png>) ![alt text](<Dp on stocks 1 and 2_260207_165404_3.png>) ![alt text](<Dp on stocks 1 and 2_260207_165404_4.png>) ![alt text](<Dp on stocks 1 and 2_260207_165404_5.png>) ![alt text](<Dp on stocks 1 and 2_260207_165404_6.png>)


```java
class Solution {
   /*
   Given an array arr of n integers, where arr[i] represents price of the stock on the ith day. Determine the maximum profit achievable by buying and selling the stock at most once. 
    The stock should be purchased before selling it, and both actions cannot occur on the same day.
   */
  /*
  every day is potential sell day
  we choose min day before that sell day 
  so to get max profit on that sell day we need to buy on which price is minimum
  */
    public int stockBuySell1(int[] arr, int n) {
        int maxProfit = 0;
        int mini = arr[0]; 
        for (int i = 1; i < n; i++) {
            int curProfit = arr[i] - mini; 
            maxProfit = Math.max(maxProfit, curProfit); 
            mini = Math.min(mini, arr[i]); 
        }
        return maxProfit; 
    }
}

```

# Q2 Best Time to Buy and Sell Stock II

[View question on takeUforward](https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-ii?subject=dsa&approach=optimal)

Given an array `arr` of `n` integers, where `arr[i]` represents the price of the stock on the `i`th day, determine the maximum profit achievable by completing any number of transactions.

You may buy and sell the stock multiple times, but you can hold at most one share at a time. You must sell the stock before buying it again. Buying and selling on the same day is allowed.

### Test Cases

**Example 1**

- Input: `arr = [9, 2, 6, 4, 7, 3]`
- Output: `7`

**Example 2**

- Input: `arr = [2, 3, 4, 5, 6]`
- Output: `4`

**Example 3**

- Input: `arr = [8, 6, 5, 4, 3]`
- Output: `0`

### Constraints

- $1 \le n \le 10^5$
- $0 \le arr[i] \le 10^4$

## Recursion

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int func(int ind, int buy, int n, vector<int> &arr) {
        if (ind == n) {
            return 0;
        }

        int profit = 0;

        if (buy == 0) {
            profit = max(
                func(ind + 1, 0, n, arr),
                -arr[ind] + func(ind + 1, 1, n, arr)
            );
        }

        if (buy == 1) {
            profit = max(
                func(ind + 1, 1, n, arr),
                arr[ind] + func(ind + 1, 0, n, arr)
            );
        }

        return profit;
    }

public:
    int stockBuySell(vector<int> &arr, int n) {
        if (n == 0) {
            return 0;
        }
        return func(0, 0, n, arr);
    }
};
```

### Java

```java
class Solution {
    private int func(int ind, int buy, int n, int[] arr) {
        if (ind == n) {
            return 0;
        }

        int profit = 0;

        if (buy == 0) {
            profit = Math.max(
                func(ind + 1, 0, n, arr),
                -arr[ind] + func(ind + 1, 1, n, arr)
            );
        }

        if (buy == 1) {
            profit = Math.max(
                func(ind + 1, 1, n, arr),
                arr[ind] + func(ind + 1, 0, n, arr)
            );
        }

        return profit;
    }

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) {
            return 0;
        }
        return func(0, 0, n, arr);
    }
}
```

## Memoization

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int func(int ind, int buy, int n, vector<int> &arr,
             vector<vector<int>> &dp) {
        if (ind == n) {
            return 0;
        }

        if (dp[ind][buy] != -1) {
            return dp[ind][buy];
        }

        int profit = 0;

        if (buy == 0) {
            profit = max(
                func(ind + 1, 0, n, arr, dp),
                -arr[ind] + func(ind + 1, 1, n, arr, dp)
            );
        }

        if (buy == 1) {
            profit = max(
                func(ind + 1, 1, n, arr, dp),
                arr[ind] + func(ind + 1, 0, n, arr, dp)
            );
        }

        return dp[ind][buy] = profit;
    }

public:
    int stockBuySell(vector<int> &arr, int n) {
        if (n == 0) {
            return 0;
        }

        vector<vector<int>> dp(n, vector<int>(2, -1));
        return func(0, 0, n, arr, dp);
    }
};
```

### Java

```java
import java.util.Arrays;

class Solution {
    private int func(int ind, int buy, int n, int[] arr, int[][] dp) {
        if (ind == n) {
            return 0;
        }

        if (dp[ind][buy] != -1) {
            return dp[ind][buy];
        }

        int profit = 0;

        if (buy == 0) {
            profit = Math.max(
                func(ind + 1, 0, n, arr, dp),
                -arr[ind] + func(ind + 1, 1, n, arr, dp)
            );
        }

        if (buy == 1) {
            profit = Math.max(
                func(ind + 1, 1, n, arr, dp),
                arr[ind] + func(ind + 1, 0, n, arr, dp)
            );
        }

        return dp[ind][buy] = profit;
    }

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) {
            return 0;
        }

        int[][] dp = new int[n][2];
        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }

        return func(0, 0, n, arr, dp);
    }
}
```

## Tabulation

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int func(vector<int> &arr, int n) {
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                int profit = 0;

                if (buy == 0) {
                    profit = max(
                        dp[ind + 1][0],
                        -arr[ind] + dp[ind + 1][1]
                    );
                }

                if (buy == 1) {
                    profit = max(
                        dp[ind + 1][1],
                        arr[ind] + dp[ind + 1][0]
                    );
                }

                dp[ind][buy] = profit;
            }
        }

        return dp[0][0];
    }

public:
    int stockBuySell(vector<int> &arr, int n) {
        return func(arr, n);
    }
};
```

### Java

```java
class Solution {
    private int func(int n, int[] arr, int[][] dp) {
        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                int profit = 0;

                if (buy == 0) {
                    profit = Math.max(
                        dp[ind + 1][0],
                        -arr[ind] + dp[ind + 1][1]
                    );
                }

                if (buy == 1) {
                    profit = Math.max(
                        dp[ind + 1][1],
                        arr[ind] + dp[ind + 1][0]
                    );
                }

                dp[ind][buy] = profit;
            }
        }

        return dp[0][0];
    }

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) {
            return 0;
        }

        int[][] dp = new int[n + 1][2];
        return func(n, arr, dp);
    }
}
```

## Space Optimized

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int func(vector<int> &arr, int n) {
        vector<int> ahead(2, 0);
        vector<int> cur(2, 0);

        for (int ind = n - 1; ind >= 0; ind--) {
            cur[0] = max(ahead[0], -arr[ind] + ahead[1]);
            cur[1] = max(ahead[1], arr[ind] + ahead[0]);
            ahead = cur;
        }

        return ahead[0];
    }

public:
    int stockBuySell(vector<int> &arr, int n) {
        if (n == 0) {
            return 0;
        }
        return func(arr, n);
    }
};
```

### Java

```java
class Solution {
    private int func(int n, int[] arr) {
        int[] ahead = new int[2];
        int[] cur = new int[2];

        for (int ind = n - 1; ind >= 0; ind--) {
            cur[0] = Math.max(ahead[0], -arr[ind] + ahead[1]);
            cur[1] = Math.max(ahead[1], arr[ind] + ahead[0]);
            ahead = cur.clone();
        }

        return ahead[0];
    }

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) {
            return 0;
        }
        return func(n, arr);
    }
}
```

# Q3 Best Time to Buy and Sell Stock III

[View question on takeUforward](https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-iii?subject=dsa&approach=optimal)

Given an array `arr` of `n` integers, where `arr[i]` represents the stock price on the `i`th day, determine the maximum profit obtainable by completing at most two transactions.

You may hold at most one share at a time, so a stock must be sold before it can be bought again. Buying and selling on the same day is allowed.

### Test Cases

**Example 1**

- Input: `arr = [4, 2, 7, 1, 11, 5]`
- Output: `15`

**Example 2**

- Input: `arr = [1, 3, 2, 8, 4, 9]`
- Output: `12`

**Example 3**

- Input: `arr = [5, 7, 2, 10, 6, 9]`
- Output: `11`

### Constraints

- $1 \le n \le 10^5$
- $0 \le arr[i] \le 10^6$

![alt text](<Dp on stocks 3 and 4_260825_162740.png>)
## Recursion

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int func(int ind, int buy, int cap, int n, vector<int> &arr) {
        if (ind == n || cap == 0) {
            return 0;
        }

        if (buy == 0) {
            return max(
                func(ind + 1, 0, cap, n, arr),
                -arr[ind] + func(ind + 1, 1, cap, n, arr)
            );
        }

        return max(
            func(ind + 1, 1, cap, n, arr),
            arr[ind] + func(ind + 1, 0, cap - 1, n, arr)
        );
    }

public:
    int stockBuySell(vector<int> &arr, int n) {
        if (n == 0) {
            return 0;
        }
        return func(0, 0, 2, n, arr);
    }
};
```

### Java

```java
class Solution {
    private int func(int ind, int buy, int cap, int n, int[] arr) {
        if (ind == n || cap == 0) {
            return 0;
        }

        if (buy == 0) {
            return Math.max(
                func(ind + 1, 0, cap, n, arr),
                -arr[ind] + func(ind + 1, 1, cap, n, arr)
            );
        }

        return Math.max(
            func(ind + 1, 1, cap, n, arr),
            arr[ind] + func(ind + 1, 0, cap - 1, n, arr)
        );
    }

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) {
            return 0;
        }
        return func(0, 0, 2, n, arr);
    }
}
```

## Memoization

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int func(int ind, int buy, int cap, int n, vector<int> &arr,
             vector<vector<vector<int>>> &dp) {
        if (ind == n || cap == 0) {
            return 0;
        }

        if (dp[ind][buy][cap] != -1) {
            return dp[ind][buy][cap];
        }

        if (buy == 0) {
            return dp[ind][buy][cap] = max(
                func(ind + 1, 0, cap, n, arr, dp),
                -arr[ind] + func(ind + 1, 1, cap, n, arr, dp)
            );
        }

        return dp[ind][buy][cap] = max(
            func(ind + 1, 1, cap, n, arr, dp),
            arr[ind] + func(ind + 1, 0, cap - 1, n, arr, dp)
        );
    }

public:
    int stockBuySell(vector<int> &arr, int n) {
        if (n == 0) {
            return 0;
        }

        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(2, vector<int>(3, -1))
        );
        return func(0, 0, 2, n, arr, dp);
    }
};
```

### Java

```java
import java.util.Arrays;

class Solution {
    private int func(int ind, int buy, int cap, int n, int[] arr,
                     int[][][] dp) {
        if (ind == n || cap == 0) {
            return 0;
        }

        if (dp[ind][buy][cap] != -1) {
            return dp[ind][buy][cap];
        }

        if (buy == 0) {
            return dp[ind][buy][cap] = Math.max(
                func(ind + 1, 0, cap, n, arr, dp),
                -arr[ind] + func(ind + 1, 1, cap, n, arr, dp)
            );
        }

        return dp[ind][buy][cap] = Math.max(
            func(ind + 1, 1, cap, n, arr, dp),
            arr[ind] + func(ind + 1, 0, cap - 1, n, arr, dp)
        );
    }

    public int stockBuySell(int[] arr, int n) {
        if (n == 0) {
            return 0;
        }

        int[][][] dp = new int[n][2][3];
        for (int ind = 0; ind < n; ind++) {
            for (int buy = 0; buy < 2; buy++) {
                Arrays.fill(dp[ind][buy], -1);
            }
        }

        return func(0, 0, 2, n, arr, dp);
    }
}
```

## Tabulation

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stockBuySell(vector<int> &arr, int n) {
        vector<vector<vector<int>>> dp(
            n + 1, vector<vector<int>>(2, vector<int>(3, 0))
        );

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (buy == 0) {
                        dp[ind][buy][cap] = max(
                            dp[ind + 1][0][cap],
                            -arr[ind] + dp[ind + 1][1][cap]
                        );
                    } else {
                        dp[ind][buy][cap] = max(
                            dp[ind + 1][1][cap],
                            arr[ind] + dp[ind + 1][0][cap - 1]
                        );
                    }
                }
            }
        }

        return dp[0][0][2];
    }
};
```

### Java

```java
class Solution {
    public int stockBuySell(int[] arr, int n) {
        int[][][] dp = new int[n + 1][2][3];

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (buy == 0) {
                        dp[ind][buy][cap] = Math.max(
                            dp[ind + 1][0][cap],
                            -arr[ind] + dp[ind + 1][1][cap]
                        );
                    } else {
                        dp[ind][buy][cap] = Math.max(
                            dp[ind + 1][1][cap],
                            arr[ind] + dp[ind + 1][0][cap - 1]
                        );
                    }
                }
            }
        }

        return dp[0][0][2];
    }
}
```

## Space Optimized

### C++

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stockBuySell(vector<int> &arr, int n) {
        vector<vector<int>> ahead(2, vector<int>(3, 0));
        vector<vector<int>> cur(2, vector<int>(3, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (buy == 0) {
                        cur[buy][cap] = max(
                            ahead[0][cap],
                            -arr[ind] + ahead[1][cap]
                        );
                    } else {
                        cur[buy][cap] = max(
                            ahead[1][cap],
                            arr[ind] + ahead[0][cap - 1]
                        );
                    }
                }
            }
            ahead = cur;
        }

        return ahead[0][2];
    }
};
```

### Java

```java
class Solution {
    public int stockBuySell(int[] arr, int n) {
        int[][] ahead = new int[2][3];
        int[][] cur = new int[2][3];

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= 2; cap++) {
                    if (buy == 0) {
                        cur[buy][cap] = Math.max(
                            ahead[0][cap],
                            -arr[ind] + ahead[1][cap]
                        );
                    } else {
                        cur[buy][cap] = Math.max(
                            ahead[1][cap],
                            arr[ind] + ahead[0][cap - 1]
                        );
                    }
                }
            }

            for (int buy = 0; buy < 2; buy++) {
                ahead[buy] = cur[buy].clone();
            }
        }

        return ahead[0][2];
    }
}
```







