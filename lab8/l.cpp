//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 19.09.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, vector<vector<int> > &ed, vector<int> &depth, vector<bool> &used, vector<int> &f) {
    used[v] = true;
    f[v] = depth[v];
    for (auto u : ed[v]) {
        if (!used[u]) {
            depth[u] = depth[v] + 1;
            dfs(u, ed, depth, used, f);
            f[v] = min(f[v], f[u]);
        } else {
            f[v] = min(f[v], depth[u]);
        }
    }
}

int maxColor = 0;

void paint(int v, int color, vector<vector<int>> &ed, vector<bool> &used, vector<int> &f,
           vector<int> &depth, map<pair<int, int>, int> &col) {
    used[v] = true;
    for (auto u : ed[v]) {
        if (!used[u]) {
            if (f[u] >= depth[v]) {
                int newColor = ++maxColor;
                col[{v, u}] = newColor;
                col[{u, v}] = newColor;
                paint(u, newColor, ed, used, f, depth, col);
            } else {
                col[{v, u}] = color;
                col[{u, v}] = color;
                paint(u, color, ed, used, f, depth, col);
            }
        } else if (depth[u] < depth[v]) {
            col[{v, u}] = color;
            col[{u, v}] = color;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ed(n);
    vector<bool> used(n);
    vector<int> depth(n);
    vector<int> f(n);
    vector<pair<int, int>> numEd(m);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        ed[v - 1].push_back(u - 1);
        ed[u - 1].push_back(v - 1);
        numEd[i] = {v - 1, u - 1};
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, ed, depth, used, f);
        }
    }
    fill(used.begin(), used.end(), false);
    map<pair<int, int>, int> col;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            paint(i, maxColor, ed, used, f, depth, col);
        }
    }
    cout << maxColor << '\n';
    for (int i = 0; i < m; i++) {
        cout << col[numEd[i]] << ' ';
    }
}
