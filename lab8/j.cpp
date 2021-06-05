//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 18.09.2020
//

#include <bits/stdc++.h>

using namespace std;

bool ans = true;

void dfs(int v, int color, vector<vector<int>> &ed, vector<int> &used) {
    if (!ans) return;
    used[v] = color;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, 3 - color, ed, used);
        } else if (used[v] == used[u]) {
            ans = false;
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ed(n);
    vector<int> used(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ed[--u].push_back(--v);
        ed[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, 1, ed, used);
        }
    }
    if (ans) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}
