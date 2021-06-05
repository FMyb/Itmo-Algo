//
// Created by Yarolsav Ilin CT ITMO M3238 on 17.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

int times = 0;

void dfs(int v, bool p, vector<int> &used,
         int color, vector<vector<int> > &ed, vector<int> &timeout) {
    used[v] = color;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, p, used, color, ed, timeout);
        }
    }
    if (p) {
        timeout[times] = v;
        times++;
    }
}

vector<int> css(int n, vector<vector<int>> &ed, vector<vector<int>> &ed1) {
    vector<int> timeout(n);
    vector<int> used(n, 0);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, true, used, 1, ed, timeout);
        }
    }
    reverse(timeout.begin(), timeout.end());
    vector<int> kss(n);
    int color = 1;
    for (int i : timeout) {
        if (!kss[i]) {
            dfs(i, false, kss, color, ed1, timeout);
            color++;
        }
    }
    return kss;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int j = 0; j < x; j++) {
            int u;
            cin >> u;
            edges.push_back({i, --u});
        }
    }
    vector<int> max_par(n);
    vector<int> max_par1(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        max_par[--x] = i;
        max_par1[i] = x + n;
    }
    vector<vector<int>> ed(2 * n);
    vector<vector<int>> ed1(2 * n);
    for (auto u : edges) {
        if (max_par[u.second] != u.first) {
            ed[u.first].push_back(u.second + n);
            ed1[u.second + n].push_back(u.first);
        } else {
            ed[u.second + n].push_back(u.first);
            ed1[u.first].push_back(u.second + n);
        }
    }
    vector<int> color = css(2 * n, ed, ed1);
    vector<vector<int>> ans(n);
    for (auto u : edges) {
        if (max_par[u.second] == u.first) {
            ans[u.first].push_back(u.second);
        } else {
            if (color[max_par[u.second]] == color[max_par1[u.first]]) {
                ans[u.first].push_back(u.second);
            }
        }
    }
    for (const auto &u : ans) {
        cout << u.size() << ' ';
        for (auto i : u) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }
}
