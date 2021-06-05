//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 06.09.2020
//


#include <bits/stdc++.h>

using namespace std;

void dfs(int v, int p, vector<vector<int> > &ed, vector<int> &depth, vector<bool> &used,
         vector<int> &f, vector<pair<int, int>> &ans) {
    used[v] = true;
    f[v] = depth[v];
    for (auto u : ed[v]) {
        if (u == p) continue;
        if (!used[u]) {
            depth[u] = depth[v] + 1;
            dfs(u, v, ed, depth, used, f, ans);
            f[v] = min(f[v], f[u]);
            if (f[u] == depth[u]) {
                ans.push_back({v, u});
            }
        } else {
            f[v] = min(f[v], depth[u]);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > ed(n);
    vector<bool> used(n);
    vector<int> depth(n);
    vector<int> f(n);
    map<pair<int, int>, int> map1;
    vector<pair<int, int> > ans;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        ed[v - 1].push_back(u - 1);
        ed[u - 1].push_back(v - 1);
        map1[{v - 1, u - 1}] = i + 1;
        map1[{u - 1, v - 1}] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1, ed, depth, used, f, ans);
        }
    }
    vector<int> ans1;
    for (auto i : ans) {
        ans1.push_back(map1[i]);
    }
    sort(ans1.begin(), ans1.end());
    cout << ans1.size() << '\n';
    for (auto i : ans1) {
        cout << i << ' ';
    }
}
