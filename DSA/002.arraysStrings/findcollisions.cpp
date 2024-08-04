#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
const int MOD = 1e9 + 7;
const int P = 31;
const int N = 1e5;
vector<ll> powerOfP(N + 1, 1);

ll polynomialHash(string &s) {
    ll ans = 0;
    for (int i = 0; i < s.length(); i++) {
        ans = (ans + (s[i] - 'a' + 1) * powerOfP[i]) % MOD;
    }
    return ans;
}

void findCollision(string original) {
    ll targetHash = polynomialHash(original);

    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            string test = "";
            test += c1;
            test += c2;
            if (polynomialHash(test) == targetHash) {
                cout << "Collision found: " << test << endl;
                return;
            }
        }
    }

    cout << "No collision found" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 1; i <= N; i++) {
        powerOfP[i] = (powerOfP[i - 1] * P) % MOD;
    }

    string original = "a";
    cout << "Original string: " << original << endl;
    cout << "Original hash: " << polynomialHash(original) << endl;

    findCollision(original);

    return 0;
}
