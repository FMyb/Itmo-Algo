//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 05.09.2020
//

#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9 + 1;

void dfs(int v, vector<vector<pair<int, int>>> &ed, vector<bool> &used, vector<int> &dist) {
    used[v] = true;
    for (auto u : ed[v]) {
        if (!used[u.first]) {
            dfs(u.first, ed, used, dist);
        }
        dist[v] = min(dist[v], dist[u.first] + u.second);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> ed(n);
    vector<int> dist(n, INF);
    int s, t;
    cin >> s >> t;
    if (s == t) {
        cout << 0;
        return 0;
    }
    s--;
    t--;
    dist[t] = 0;
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        ed[v - 1].push_back({u - 1, w});
    }
    vector<bool> used(n);
    dfs(s, ed, used,  dist);
    if (dist[s] >= INF / 2) {
        cout << "Unreachable";
        return 0;
    }
    cout << dist[s];
}
