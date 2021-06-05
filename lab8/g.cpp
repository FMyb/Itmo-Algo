//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 06.09.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, int col, vector<vector<int>> &ed, vector<int> &used) {
    used[v] = col;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, col, ed, used);
        }
    }
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
        ed[v].push_back(u);
    }
    int col = 1;
    vector<int> used(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, col++, ed, used);
        }
    }
    cout << col - 1 << '\n';
    for (auto i : used) {
        cout << i << ' ';
    }
}
