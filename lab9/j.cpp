//
// Created by Yarolsav Ilin CT ITMO M3238 on 25.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct edge {
    int from;
    int to;
    int w;
};

int times = 0;

void dfs1(int v, bool p, vector<int> &used,
          int color, vector<vector<int> > &ed, vector<int> &timeout) {
    used[v] = color;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs1(u, p, used, color, ed, timeout);
        }
    }
    if (p) {
        timeout[times] = v;
        times++;
    }
}

pair<int, vector<int>> condensation(int n, vector<edge> &edges) {
    times = 0;
    vector<int> timeout(n);
    vector<int> used(n, 0);
    vector<vector<int>> ed(n);
    vector<vector<int>> ed1(n);
    for (auto e : edges) {
        ed[e.from].push_back(e.to);
        ed1[e.to].push_back(e.from);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(i, true, used, 1, ed, timeout);
        }
    }
    reverse(timeout.begin(), timeout.end());
    vector<int> kss(n);
    int color = 1;
    for (int i : timeout) {
        if (!kss[i]) {
            dfs1(i, false, kss, color, ed1, timeout);
            color++;
        }
    }
    for (int i = 0; i < n; i++) {
        kss[i]--;
    }
    return {color - 1, kss};
}


void dfs(int v, vector<edge> &ed, vector<bool> &used) {
    used[v] = true;
    for (auto e : ed) {
        if (e.from == v) {
            int u = e.to;
            if (!used[u]) {
                dfs(u, ed, used);
            }
        }
    }
}

long long findMST(vector<edge> &edges, int n, int root) {
    long long res = 0;
    vector<int> min_edge(n, INF);
    for (auto e : edges) {
        min_edge[e.to] = min(e.w, min_edge[e.to]);
    }
    for (int v = 0; v < n; v++) {
        if (v != root) {
            res += min_edge[v];
        }
    }
    vector<edge> zero;
    for (auto e : edges) {
        if (e.w == min_edge[e.to]) {
            edge e1 = e;
            e1.w = e.w - min_edge[e.to];
            zero.push_back(e1);
        }
    }
    vector<bool> used(n);
    dfs(root, zero, used);
    bool f = false;
    for (auto i : used) {
        if (!i) {
            f = true;
        }
    }
    if (!f) {
        return res;
    }
    auto u = condensation(n, zero);
    int comp_count = u.first;
    vector<int> new_comp = u.second;
    vector<edge> new_edges;
    for (auto e : edges) {
        if (new_comp[e.from] != new_comp[e.to]) {
            new_edges.push_back({new_comp[e.from], new_comp[e.to], e.w - min_edge[e.to]});
        }
    }
    res += findMST(new_edges, comp_count, new_comp[root]);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<edge> ed;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ed.push_back({u - 1, v - 1, w});
    }
    vector<bool> used(n);
    dfs(0, ed, used);
    for (auto i : used) {
        if (!i) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES\n";
    long long ans = findMST(ed, n, 0);
    cout << ans;
}
