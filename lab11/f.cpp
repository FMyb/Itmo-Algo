#include <bits/stdc++.h>

using namespace std;

int n;
const long long INF = 1000000000000000000;

struct edge {
    int v;
    long long c;
    long long f;
    int mincup;
};

int s, t;
vector<edge> e;
vector<vector<int>> ed;

int add_edge(int u, int v, long long c, int minc) {
    edge e1 = {v, c, 0, minc};
    edge e2 = {u, 0, 0, minc};
    ed[u].push_back((int) e.size());
    int a = (int) e.size();
    e.push_back(e1);
    ed[v].push_back((int) e.size());
    e.push_back(e2);
    return a;
}

bool bfs(vector<int> &d, int A) {
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty() && d[t] == -1) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < ed[v].size(); ++i) {
            int id = ed[v][i];
            int to = e[id].v;
            if (d[to] == -1 && e[id].c - e[id].f >= A) {
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

long long dfs(int v, long long f, int A, vector<int> &d, vector<int> &ptr) {
    if (!f) return 0;
    if (v == t) return f;
    for (; ptr[v] < (int) ed[v].size(); ++ptr[v]) {
        int id = ed[v][ptr[v]];
        int to = e[id].v;
        if (d[to] != d[v] + 1) continue;
        if (e[id].c - e[id].f >= A) {
            long long p = dfs(to, min(f, e[id].c - e[id].f), A, d, ptr);
            if (p) {
                e[id].f += p;
                e[id ^ 1].f -= p;
                return p;
            }
        }
    }
    return 0;
}

long long dinic(int A) {
    long long f = 0;
    while (A > 0) {
        while (true) {
            vector<int> d(n, -1);
            if (!bfs(d, A)) break;
            vector<int> ptr(n);
            while (long long p = dfs(s, INF, A, d, ptr))
                f += p;
        }
        A /= 2;
    }
    return f;
}

int main() {
    ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m;
    n += 2;
    ed.resize(n);
    s = 0;
    t = n - 1;
    int A = 0;
    vector<int> c;
    for (int i = 0; i < m; i++) {
        int u, v, minc, maxc;
        cin >> u >> v >> minc >> maxc;
        A = max(A, maxc);
        add_edge(s, v, minc, 0);
        c.push_back(add_edge(u, v, maxc - minc, minc));
        add_edge(u, t, minc, 0);
    }
    dinic(A);
    for (auto u : ed[0]) {
        if (e[u].f < e[u].c) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES\n";
    for (auto u : c) {
        cout << e[u].f + e[u].mincup << '\n';
    }
}
