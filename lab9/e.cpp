//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

const long long INF = 8 * 1e18;

struct V {
    int v;
    int u;
    long long w;
};

void dfs(int v, vector<vector<int>> &ed, vector<bool> &used) {
    used[v] = true;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, ed, used);
        }
    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    s--;
    vector<V> ed;
    vector<vector<int>> ed1(n);
    for (int i = 0; i < m; i++) {
        int v, u;
        long long w;
        cin >> v >> u >> w;
        ed.push_back({v - 1, u - 1, w});
        ed1[v - 1].push_back(u - 1);
    }
    vector<long long> dist(n, INF);
    dist[s] = 0;
    vector<bool> negative_cycle(n, false);
    for (int i = 0; i < n + 1; i++) {
        for (auto e : ed) {
            if (dist[e.v] != INF && dist[e.u] > dist[e.v] + e.w) {
                dist[e.u] = max(-INF, dist[e.v] + e.w);
                if (i == n) {
                    negative_cycle[e.u] = true;
                }
            }
        }
    }
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        if (negative_cycle[i] && dist[i] != INF && !used[i]) {
            dfs(i, ed1, used);
        }
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            cout << "-\n";
        } else {
            if (dist[i] == INF) {
                cout << "*\n";
            } else {
                cout << dist[i] << '\n';
            }
        }
    }
}
