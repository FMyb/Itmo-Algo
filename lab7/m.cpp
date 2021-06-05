//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 26.05.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, int depth, vector<vector<int>> &ed,
         vector<int> &vtx, vector<pair<int, int>> &d, vector<int> &ind) {
    d.push_back({depth, d.size()});
    vtx.push_back(v);
    ind[v] = vtx.size() - 1;
    for (auto u : ed[v]) {
        dfs(u, depth + 1, ed, vtx, d, ind);
        d.push_back({depth, d.size()});
        vtx.push_back(v);
    }
}

int rmq(int l, int r, vector<int> &log2, vector<vector<pair<int, int>>> &dp) {
    int k = log2[r - l + 1];
    if (dp[k][l].first <= dp[k][r + 1 - (1 << k)].first) {
        return dp[k][l].second;
    } else {
        return dp[k][r + 1 - (1 << k)].second;
    }
}

int lca(int u, int v, vector<int> &ind,
        vector<int> &vtx, vector<int> &log2, vector<vector<pair<int, int>>> &dp) {
    if (ind[u] > ind[v]) {
        swap(u, v);
    }
    return vtx[rmq(ind[u], ind[v], log2, dp)];
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ed(n);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        ed[x].push_back(i);
    }
    vector<int> vtx;
    vector<pair<int, int>> d;
    vector<int> ind(n);
    dfs(0, 0, ed, vtx, d, ind);
    int n1 = n;
    n = d.size();
    vector<int> log2(n + 1);
    log2[1] = 0;
    for (int i = 2; i <= n; i++) {
        log2[i] = 1 + log2[i / 2];
    }
    vector<vector<pair<int, int>>> dp(log2[n] + 1, vector<pair<int, int>>(n));
    for (int i = 1; i < n; i++) {
        dp[0][i] = d[i];
    }
    for (int k = 1; k <= log2[n]; k++) {
        for (int i = 0; i < n; i++) {
            if (dp[k - 1][i].first < dp[k - 1][min(n - 1, i + (1 << (k - 1)))].first) {
                dp[k][i] = dp[k - 1][i];
            } else {
                dp[k][i] = dp[k - 1][min(n - 1, i + (1 << (k - 1)))];
            }
        }
    }
    int a1, a2;
    cin >> a1 >> a2;
    long long x, y, z;
    cin >> x >> y >> z;
    int v = lca(a1, a2, ind, vtx, log2, dp);
    long long ans = v;
    for (int i = 1; i < m; i++) {
        a1 = (int) ((x * a1 + y * a2 + z) % n1);
        a2 = (int) ((x * a2 + y * a1 + z) % n1);
        v = lca((a1 + v) % n1, a2, ind, vtx, log2, dp);
        ans += v;
    }
    cout << ans;
}
