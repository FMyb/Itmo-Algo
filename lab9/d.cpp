//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

void dijkstra(int v, int n, vector<vector<pair<int, int>>> &ed, vector<int> &dist) {
    set<pair<int, int>> q;
    dist[v] = 0;
    for (int i = 0; i < n; i++) {
        q.insert({dist[i], i});
    }
    while (!q.empty()) {
        v = q.begin()->second;
        q.erase(q.begin());
        for (auto x : ed[v]) {
            int u = x.first, w = x.second;
            if (dist[u] > dist[v] + w) {
                q.erase({dist[u], u});
                dist[u] = dist[v] + w;
                q.insert({dist[u], u});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> ed(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ed[--u].push_back({--v, w});
        ed[v].push_back({u, w});
    }
    vector<int> dist(n, INF);
    dijkstra(0, n, ed, dist);
    for (int i = 0; i < n; i++) {
        cout << dist[i] << ' ';
    }
}
