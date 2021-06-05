#include <vector>
#include <stdio.h>

using namespace std;

struct snm {
    vector<int> par;
    vector<int> rank;

    snm(int n) {
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            par.push_back(i);
            rank[i] = 1;
        }
    }

    int get(int v) {
        if (v == par[v]) {
            return v;
        }
        return par[v] = get(par[v]);
    }

    bool ask(int v, int u) {
        return get(v) == get(u);
    }

    bool union_snm(int v, int u) {
        v = get(v);
        u = get(u);
        if (v == u) {
            return false;
        }
        if (rank[v] < rank[u]) swap(u, v);
        if (rank[u] < rank[v]) par[u] = v;
        if (rank[u] == rank[v]) {
            par[v] = u;
            rank[v]++;
        }
        return true;
    }
};

struct snm__qq {
    vector<int> par;
    vector<int> rank;

    snm__qq(int n) {
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            par.push_back(i);
            rank[i] = i;
        }
    }

    int get(int v) {
        if (v == par[v]) {
            return v;
        }
        return par[v] = get(par[v]);
    }

    bool ask(int v, int u) {
        return get(v) == get(u);
    }

    bool union_snm(int v, int u) {
        v = get(v);
        u = get(u);
        if (v == u) {
            return false;
        }
        if (rank[v] < rank[u]) swap(u, v);
        if (rank[u] < rank[v]) par[u] = v;
        if (rank[u] == rank[v]) {
            par[v] = u;
        }
        return true;
    }
};

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    snm s(n);
    snm__qq sqq(n);
    for (int i = 0; i < q; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        x--;
        y--;
        if (t == 1) {
            if (s.ask(x, y)) {
                continue;
            }
            if (sqq.ask(sqq.get(x) + 1, y)) {
                sqq.union_snm(x, y);
            }
            s.union_snm(x, y);
        } else if (t == 2) {
            for (int i = sqq.get(x) + 1; i <= y; i = sqq.get(i) + 1) {
                sqq.union_snm(x, i);
                s.union_snm(x, i);
            }
        } else {
            if (s.ask(x, y)) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
}
