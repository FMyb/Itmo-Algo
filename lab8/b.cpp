//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 05.09.2020
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

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> timeout(n);
    vector<int> used(n, 0);
    vector<vector<int> > ed(n);
    vector<vector<int> > ed1(n);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        ed[v - 1].push_back(u - 1);
        ed1[u - 1].push_back(v - 1);
    }
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
    cout << color - 1 << '\n';
    for (int i = 0; i < n; i++) {
        cout << kss[i] << ' ';
    }
}
