//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 06.09.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, int p, vector<vector<int> > &ed, vector<int> &depth, vector<bool> &used,
         vector<int> &f, vector<int> &ans, int root) {
    used[v] = true;
    bool ok = true;
    f[v] = depth[v];
    int cnt = 0;
    for (auto u : ed[v]) {
        if (u == p) continue;
        if (!used[u]) {
            depth[u] = depth[v] + 1;
            cnt++;
            dfs(u, v, ed, depth, used, f, ans, root);
            f[v] = min(f[v], f[u]);
            if (f[u] >= depth[v]) {
                ok = false;
            }
        } else {
            f[v] = min(f[v], depth[u]);
        }
    }
    if (!ok && v != root) {
        ans.push_back(v);
    }
    if (cnt >= 2 && v == root) {
        ans.push_back(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > ed(n);
    vector<bool> used(n);
    vector<int> depth(n, 0);
    vector<int> f(n);
    vector<int> ans;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        ed[v - 1].push_back(u - 1);
        ed[u - 1].push_back(v - 1);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1, ed, depth, used, f, ans, i);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i + 1 << ' ';
    }
}
