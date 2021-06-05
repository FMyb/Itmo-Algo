//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.11.2020.
//

#include <bits/stdc++.h>

using namespace std;


bool dfs(int v, vector<vector<int>> &ed, vector<int> &px, vector<int> &py, vector<bool> &used) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (auto u : ed[v]) {
        if (py[u] == -1) {
            py[u] = v;
            px[v] = u;
            return true;
        } else {
            if (dfs(py[u], ed, px, py, used)) {
                py[u] = v;
                px[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> ed(n);
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        ed[--u].push_back(--v);
    }
    vector<int> px(n, -1);
    vector<int> py(m, -1);
    bool isPath = true;
    while (isPath) {
        isPath = false;
        vector<bool> used(n);
        for (int i = 0; i < n; i++) {
            if (px[i] == -1) {
                if (dfs(i, ed, px, py, used)) {
                    isPath = true;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (px[i] != -1) {
            ans++;
        }
    }
    cout << ans;
}
