#include <bits/stdc++.h>

using namespace std;

const int M = 16714589;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> log2(n + 1);
    log2[1] = 0;
    for (int i = 2; i <= n; i++) {
        log2[i] = 1 + log2[i / 2];
    }
    vector<vector<int>> dp(log2[n] + 1, vector<int>(n));
    vector<int> a(n);
    cin >> a[0];
    dp[0][0] = a[0];
    for (int i = 1; i < n; i++) {
        a[i] = ((23 * a[i - 1]) % M + 21563 % M) % M;
        dp[0][i] = a[i];
    }
    for (int k = 1; k <= log2[n]; k++) {
        for (int i = 0; i < n; i++) {
            dp[k][i] = min(dp[k - 1][i], dp[k - 1][min(n - 1, i + (1 << (k - 1)))]);
        }
    }
    int v, u;
    cin >> u >> v;
    for (int i = 1; i < m; i++) {
        int l = u - 1, r = v - 1;
        if (r < l) swap(l, r);
        int k = log2[r - l + 1];
        int ans = min(dp[k][l], dp[k][r + 1 - (1 << k)]);
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
    }
    cout << u << ' ' << v;
    int l = u - 1, r = v - 1;
    if (r < l) swap(l, r);
    int k = log2[r - l + 1];
    int ans = min(dp[k][l], dp[k][r + 1 - (1 << k)]);
    cout << ' ' << ans;
}
