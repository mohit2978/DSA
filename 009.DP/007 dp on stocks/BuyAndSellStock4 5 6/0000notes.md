# Q4 Best Time to Buy and Sell Stock IV

[View question on takeUforward](https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-iv?subject=dsa&approach=optimal)

Given an array `arr` of `n` integers, where `arr[i]` represents the stock price on the `i`th day, determine the maximum profit obtainable by completing at most `k` transactions.

You may hold at most one share at a time, so a stock must be sold before it can be bought again. Buying and selling on the same day is allowed.

### Test Cases

**Example 1**

- Input: `arr = [3, 2, 6, 5, 0, 3], k = 2`
- Output: `7`

**Example 2**

- Input: `arr = [1, 2, 4, 2, 5, 7, 2, 4, 9, 0], k = 3`
- Output: `15`

**Example 3**

- Input: `arr = [1, 3, 2, 8, 4, 9], k = 2`
- Output: `12`

### Constraints

- $1 \le n \le 10^3$
- $0 \le arr[i] \le 10^4$
- $0 \le k \le 100$

![alt text](<Dp on stocks 3 and 4_260825_162740 (2).png>)
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
    int stockBuySell(vector<int> &arr, int n, int k) {
        if (n == 0 || k == 0) {
            return 0;
        }
        return func(0, 0, k, n, arr);
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

    public int stockBuySell(int[] arr, int n, int k) {
        if (n == 0 || k == 0) {
            return 0;
        }
        return func(0, 0, k, n, arr);
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
    int stockBuySell(vector<int> &arr, int n, int k) {
        if (n == 0 || k == 0) {
            return 0;
        }

        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(2, vector<int>(k + 1, -1))
        );
        return func(0, 0, k, n, arr, dp);
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

    public int stockBuySell(int[] arr, int n, int k) {
        if (n == 0 || k == 0) {
            return 0;
        }

        int[][][] dp = new int[n][2][k + 1];
        for (int ind = 0; ind < n; ind++) {
            for (int buy = 0; buy < 2; buy++) {
                Arrays.fill(dp[ind][buy], -1);
            }
        }

        return func(0, 0, k, n, arr, dp);
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
    int stockBuySell(vector<int> &arr, int n, int k) {
        vector<vector<vector<int>>> dp(
            n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0))
        );

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
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

        return dp[0][0][k];
    }
};
```

### Java

```java
class Solution {
    public int stockBuySell(int[] arr, int n, int k) {
        int[][][] dp = new int[n + 1][2][k + 1];

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
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

        return dp[0][0][k];
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
    int stockBuySell(vector<int> &arr, int n, int k) {
        vector<vector<int>> ahead(2, vector<int>(k + 1, 0));
        vector<vector<int>> cur(2, vector<int>(k + 1, 0));

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
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

        return ahead[0][k];
    }
};
```

### Java

```java
class Solution {
    public int stockBuySell(int[] arr, int n, int k) {
        int[][] ahead = new int[2][k + 1];
        int[][] cur = new int[2][k + 1];

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int cap = 1; cap <= k; cap++) {
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

        return ahead[0][k];
    }
}
```

# Q5 Best Time to Buy and Sell Stock with Transaction Fees

[View question on takeUforward](https://takeuforward.org/plus/dsa/problems/best-time-to-buy-and-sell-stock-with-cooldown-and-transaction-fees?subject=dsa&approach=optimal)

Given an array `arr`, where `arr[i]` represents the stock price on the `i`th day, and an integer `fee`, determine the maximum profit obtainable from any number of transactions.

Only one share may be held at a time, so the stock must be sold before it can be bought again. The transaction fee is charged whenever a stock is sold.

### Test Cases

**Example 1**

- Input: `arr = [1, 3, 4, 0, 2], fee = 1`
- Output: `3`

**Example 2**

- Input: `arr = [1, 3, 2, 8, 4, 9], fee = 2`
- Output: `8`

**Example 3**

- Input: `arr = [10, 3, 7, 5, 1, 3], fee = 3`
- Output: `1`

### Constraints

- $1 \le n \le 10^5$
- $0 \le arr[i], fee \le 10^4$

## Memoization

### Java

```java
import java.util.Arrays;

class Solution {
    private int func(int ind, int buy, int n, int[] arr,
                     int[][] dp, int fee) {
        if (ind == n) {
            return 0;
        }

        if (dp[ind][buy] != -1) {
            return dp[ind][buy];
        }

        if (buy == 0) {
            return dp[ind][buy] = Math.max(
                func(ind + 1, 0, n, arr, dp, fee),
                -arr[ind] + func(ind + 1, 1, n, arr, dp, fee)
            );
        }

        return dp[ind][buy] = Math.max(
            func(ind + 1, 1, n, arr, dp, fee),
            arr[ind] - fee + func(ind + 1, 0, n, arr, dp, fee)
        );
    }

    public int stockBuySell(int[] arr, int n, int fee) {
        if (n == 0) {
            return 0;
        }

        int[][] dp = new int[n][2];
        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }

        return func(0, 0, n, arr, dp, fee);
    }
}
```

## Tabulation

### Java

```java
class Solution {
    public int stockBuySell(int[] arr, int n, int fee) {
        int[][] dp = new int[n + 1][2];

        for (int ind = n - 1; ind >= 0; ind--) {
            dp[ind][0] = Math.max(
                dp[ind + 1][0],
                -arr[ind] + dp[ind + 1][1]
            );

            dp[ind][1] = Math.max(
                dp[ind + 1][1],
                arr[ind] - fee + dp[ind + 1][0]
            );
        }

        return dp[0][0];
    }
}
```

## Space Optimized

### Java

```java
class Solution {
    public int stockBuySell(int[] arr, int n, int fee) {
        int[] ahead = new int[2];
        int[] cur = new int[2];

        for (int ind = n - 1; ind >= 0; ind--) {
            cur[0] = Math.max(
                ahead[0],
                -arr[ind] + ahead[1]
            );

            cur[1] = Math.max(
                ahead[1],
                arr[ind] - fee + ahead[0]
            );

            ahead = cur.clone();
        }

        return ahead[0];
    }
}
```

# Q6 Best Time to Buy and Sell Stock with Cooldown

[View question on LeetCode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/)

Given an array `prices`, where `prices[i]` is the stock price on the `i`th day, determine the maximum profit obtainable from any number of transactions.

Only one share may be held at a time, so the stock must be sold before it can be bought again. After selling a stock, you cannot buy another stock on the following day because that day is a cooldown day.

### Test Cases

**Example 1**

- Input: `prices = [1, 2, 3, 0, 2]`
- Output: `3`

**Example 2**

- Input: `prices = [1]`
- Output: `0`

### Constraints

- $1 \le prices.length \le 5000$
- $0 \le prices[i] \le 1000$

## Memoization

### Java

```java
import java.util.Arrays;

class Solution {
    private int func(int ind, int buy, int cooldown, int[] prices,
                     int[][][] dp) {
        if (ind == prices.length) {
            return 0;
        }

        if (dp[ind][buy][cooldown] != -1) {
            return dp[ind][buy][cooldown];
        }

        int profit;

        if (cooldown == 1) {
            profit = func(ind + 1, 0, 0, prices, dp);
        } else if (buy == 0) {
            profit = Math.max(
                func(ind + 1, 0, 0, prices, dp),
                -prices[ind] + func(ind + 1, 1, 0, prices, dp)
            );
        } else {
            profit = Math.max(
                func(ind + 1, 1, 0, prices, dp),
                prices[ind] + func(ind + 1, 0, 1, prices, dp)
            );
        }

        return dp[ind][buy][cooldown] = profit;
    }

    public int maxProfit(int[] prices) {
        int n = prices.length;
        int[][][] dp = new int[n][2][2];

        for (int ind = 0; ind < n; ind++) {
            for (int buy = 0; buy < 2; buy++) {
                Arrays.fill(dp[ind][buy], -1);
            }
        }

        return func(0, 0, 0, prices, dp);
    }
}
```

## Tabulation

### Java

```java
class Solution {
    public int maxProfit(int[] prices) {
        int n = prices.length;
        int[][][] dp = new int[n + 1][2][2];

        for (int ind = n - 1; ind >= 0; ind--) {
            dp[ind][0][1] = dp[ind + 1][0][0];

            dp[ind][0][0] = Math.max(
                dp[ind + 1][0][0],
                -prices[ind] + dp[ind + 1][1][0]
            );

            dp[ind][1][0] = Math.max(
                dp[ind + 1][1][0],
                prices[ind] + dp[ind + 1][0][1]
            );
        }

        return dp[0][0][0];
    }
}
```

## Space Optimized

### Java

```java
class Solution {
    public int maxProfit(int[] prices) {
        int[][] ahead = new int[2][2];

        for (int ind = prices.length - 1; ind >= 0; ind--) {
            int[][] cur = new int[2][2];

            cur[0][1] = ahead[0][0];

            cur[0][0] = Math.max(
                ahead[0][0],
                -prices[ind] + ahead[1][0]
            );

            cur[1][0] = Math.max(
                ahead[1][0],
                prices[ind] + ahead[0][1]
            );

            ahead = cur;
        }

        return ahead[0][0];
    }
}
```










