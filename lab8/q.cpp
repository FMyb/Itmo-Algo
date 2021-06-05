//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 03.10.2020
//

#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int from;
    int to;
    char c;

    Edge(int from, int to, char c) : from(from), to(to), c(c) {}
};

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

vector<int> css(int n, vector<vector<int>> &ed) {
    times = 0;
    vector<int> timeout(n);
    vector<int> used(n, 0);
    vector<vector<int> > ed1(n);
    for (size_t i = 0; i < ed.size(); i++) {
        for (auto u : ed[i]) {
            ed1[u].push_back(i);
        }
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
    return kss;
}

bool check(int cnt, int n, vector<Edge> &ed) {
    vector<vector<int>> ed1(2 * n);
    for (int i = 0; i < cnt; i++) {
        Edge u = ed[i];
        if (u.c == 'T') {
            ed1[u.from + n].push_back(u.to + n);
            ed1[u.to + n].push_back(u.from + n);
            ed1[u.to].push_back(u.from);
            ed1[u.from].push_back(u.to);
        } else {
            ed1[u.from + n].push_back(u.to);
            ed1[u.to].push_back(u.from + n);
            ed1[u.to + n].push_back(u.from);
            ed1[u.from].push_back(u.to + n);
        }
    }
    auto c = css(2 * n, ed1);
    for (int i = 0; i < n; i++) {
        if (c[i] == c[i + n]) {
            return false;
        }
    }
    return true;
}

int bin_search(int n, int m, vector<Edge> &ed) {
    int l = 0;
    int r = m + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid, n, ed)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<Edge> ed;
    for (int i = 0; i < m; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        ed.push_back({--u, --v, c});
    }
    int ans = bin_search(n, m, ed);
    cout << ans;
}
