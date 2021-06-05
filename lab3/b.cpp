#include <bits/stdc++.h>

using namespace std;

struct Node {
    int par;
    int max;
    int min;
    int cnt;

    Node(int par_, int max_, int min_, int cnt_) {
        par = par_;
        max = max_;
        min = min_;
        cnt = cnt_;
    }

    bool operator==(const Node &rhs) const {
        return par == rhs.par &&
               max == rhs.max &&
               min == rhs.min &&
               cnt == rhs.cnt;
    }

    bool operator!=(const Node &rhs) const {
        return !(rhs == *this);
    }

    void print() {
        cout << min + 1 << ' ' << max + 1 << ' ' << cnt << '\n';
    }
};

struct snm {
    vector<Node> par;
    vector<int> rank;

    snm(int n) {
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            par.push_back({i, i, i, 1});
            rank[i] = 1;
        }
    }

    Node get(int v) {
        if (v == par[v].par) {
            return par[v];
        }
        return par[v] = get(par[v].par);
    }


    bool ask(int v, int u) {
        return get(v) == get(u);
    }

    bool union_snm(int v, int u) {
        Node v1 = get(v);
        Node u1 = get(u);
        if (v == u) {
            return false;
        }
        if (rank[v1.par] < rank[u1.par]) swap(u1, v1);
        if (rank[u1.par] < rank[v1.par]) {
            par[v1.par].cnt += par[u1.par].cnt;
            par[v1.par].max = max(par[v1.par].max, par[u1.par].max);
            par[v1.par].min = min(par[v1.par].min, par[u1.par].min);
            par[u1.par] = v1;
        }
        if (rank[u1.par] == rank[v1.par]) {
            par[v1.par].cnt += par[u1.par].cnt;
            par[v1.par].max = max(par[v1.par].max, par[u1.par].max);
            par[v1.par].min = min(par[v1.par].min, par[u1.par].min);
            par[u1.par] = v1;
            rank[v1.par]++;
        }
        return true;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    snm snm1(n);
    string s;
    while (cin >> s) {
        if (s == "union") {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            snm1.union_snm(u, v);
        } else {
            int u;
            cin >> u;
            u--;
            snm1.get(u).print();
        }
    }
}
