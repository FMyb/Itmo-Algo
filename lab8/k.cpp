//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 19.09.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, int p, vector<vector<int> > &ed, vector<int> &depth, vector<bool> &used,
         vector<int> &f) {
    used[v] = true;
    f[v] = depth[v];
    for (auto u : ed[v]) {
        if (u == p) continue;
        if (!used[u]) {
            depth[u] = depth[v] + 1;
            dfs(u, v, ed, depth, used, f);
            f[v] = min(f[v], f[u]);
        } else {
            f[v] = min(f[v], depth[u]);
        }
    }
}

int maxColor = 0;

void paint(int v, int col, vector<vector<int>> &ed,
           vector<int> &color, vector<int> &f, vector<int> &depth) {
    color[v] = col;
    for (auto u : ed[v]) {
        if (color[u] == 0) {
            if (f[u] > depth[v]) {
                maxColor++;
                paint(u, maxColor, ed, color, f, depth);
            } else {
                paint(u, col, ed, color, f, depth);
            }
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
    vector<int> depth(n);
    vector<bool> used(n);
    vector<int> color(n);
    vector<int> f(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1, ed, depth, used, f);
        }
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            maxColor++;
            paint(i, maxColor, ed, color, f, depth);
        }
    }
    cout << maxColor << '\n';
    for (auto col : color) {
        cout << col << ' ';
    }
}
