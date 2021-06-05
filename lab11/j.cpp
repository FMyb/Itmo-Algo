#include <bits/stdc++.h>

using namespace std;

int n;
const long long INF = 1000000000000000000;

struct edge {
    int v;
    long long c;
    long long f;
    int w;
};

int s, t;
vector<edge> e;
vector<vector<int>> ed;
vector<edge> ee;
vector<vector<int>> eed;

void add_edge(int u, int v, long long c, int w) {
    edge e1 = {v, c, 0, w};
    edge e2 = {u, 0, 0, w};
    eed[u].push_back((int) ee.size());
    ee.push_back(e1);
    eed[v].push_back((int) ee.size());
    ee.push_back(e2);
}

bool bfs(vector<int> &d, int A, int W) {
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty() && d[t] == -1) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < ed[v].size(); ++i) {
            int id = ed[v][i];
            int to = e[id].v;
            if (d[to] == -1 && e[id].c - e[id].f >= A && e[id].w >= W) {
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

long long dfs(int v, long long f, int A, int W, vector<int> &d, vector<int> &ptr) {
    if (!f) return 0;
    if (v == t) return f;
    for (; ptr[v] < (int) ed[v].size(); ++ptr[v]) {
        int id = ed[v][ptr[v]];
        int to = e[id].v;
        if (d[to] != d[v] + 1) continue;
        if (e[id].c - e[id].f >= A && e[id].w >= W) {
            long long p = dfs(to, min(f, e[id].c - e[id].f), A, W, d, ptr);
            if (p) {
                e[id].f += p;
                e[id ^ 1].f -= p;
                return p;
            }
        }
    }
    return 0;
}

long long dinic(int A, int W) {
    ed = eed;
    e = ee;
    long long f = 0;
    while (A > 0) {
        while (true) {
            vector<int> d(2 * n + 2, -1);
            if (!bfs(d, A, W)) break;
            vector<int> ptr(2 * n + 2);
            while (long long p = dfs(s, INF, A, W, d, ptr))
                f += p;
        }
        A /= 2;
    }
    return f;
}

int bin_find() {
    int l = 0;
    int r = 1000001;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        long long ttt = dinic(1, m);
        if (ttt == n) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    eed.resize(2 * n + 2);
    s = 0;
    t = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        add_edge(0, i, 1, 1000001);
    }
    for (int i = n + 1; i <= 2 * n; i++) {
        add_edge(i, t, 1, 1000001);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= 2 * n; j++) {
            int w;
            cin >> w;
            add_edge(i, j, 1, w);
        }
    }
    cout << bin_find();
}
