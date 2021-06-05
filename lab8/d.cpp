//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 19.09.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, vector<vector<int>> &ed, vector<bool> &used, vector<vector<bool>> &dp) {
    if (ed[v].empty()) {
        dp[v][0] = false;
        dp[v][1] = false;
        return;
    }
    used[v] = true;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, ed, used, dp);
        }
        if (!dp[u][1]) {
            dp[v][0] = true;
        }
        if (!dp[u][0]) {
            dp[v][1] = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> ed(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ed[--u].push_back(--v);
    }
    vector<bool> used(n);
    vector<vector<bool>> dp(n, vector<bool>(2, false));
    dfs(--s, ed, used, dp);
    if (dp[s][0]) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
}
