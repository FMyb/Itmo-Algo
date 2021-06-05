#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000000;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            if (len == 1) {
                dp[i][i] = 1;
                continue;
            }
            dp[i][i + len - 1] = ((dp[i][i + len - 2] +
                                   dp[i + 1][i + len - 1]) % MOD
                                  - dp[i + 1][i + len - 2] + MOD) % MOD;
            if (a[i] == a[i + len - 1]) {
                dp[i][i + len - 1] += (dp[i + 1][i + len - 2] + 1) % MOD;
                dp[i][i + len - 1] %= MOD;
            }
        }
    }
    cout << dp[0][n - 1] % MOD;
}
