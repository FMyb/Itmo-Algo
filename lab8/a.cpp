//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 05.09.2020
//

#include <bits/stdc++.h>

using namespace std;

bool p = false;

void dfs(int v, vector<vector<int>> &ed, vector<int> &used, vector<int> &ans) {
    if (p) return;
    used[v] = 1;
    for (auto u : ed[v]) {
        if (p) return;
        if (used[u] == 0) {
            dfs(u, ed, used, ans);
        } else if (used[u] == 1) {
            p = true;
            return;
        }
    }
    if (p) return;
    used[v] = 2;
    ans.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ed(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ed[--u].push_back(--v);
    }
    vector<int> used(n);
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i, ed, used, ans);
        }
        if (p) {
            cout << -1;
            return 0;
        }
    }
    if (p) {
        cout << -1;
        return 0;
    }
    for (int i = n - 1; i >= 0; i--) {
        cout << ans[i] + 1 << ' ';
    }
}
