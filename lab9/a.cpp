//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

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
    queue<int> q;
    vector<int> d(n, INF);
    d[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : ed[v]) {
            if (d[u] == INF) {
                d[u] = d[v] + 1;
                q.push(u);
            }
        }
    }
    for (auto u : d) {
        cout << u << ' ';
    }
}

