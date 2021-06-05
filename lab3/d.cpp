#include <vector>
#include <stdio.h>
#include <assert.h>

using namespace std;

struct snm {
    vector<int> par;
    vector<int> rank;
    vector<int> right;

    snm(int n) {
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            par.push_back(i);
            right.push_back(i);
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
        if (rank[u] < rank[v]) {
            par[u] = v;
        }
        if (rank[u] == rank[v]) {
            par[v] = u;
            rank[v]++;
        }
        right[u] = max(right[u], right[v]);
        right[v] = max(right[u], right[v]);
        return true;
    }
};

int main() {
    int n;
    scanf("%d", &n);
    snm s(n);
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        x--;
        int y = s.right[s.get(x)];
        if (y == n - 1) {
            if (used[y]) {
                x = 0;
            } else {
                used[y] = true;
                printf("%d ", y + 1);
                continue;
            }
        }
        int k = s.get(x);
        assert(!used[s.right[k]]);
        used[s.right[k]] = true;
        printf("%d ", s.right[k] + 1);
        if (s.right[k] != n - 1) {
            s.union_snm(s.right[k], s.right[k] + 1);
        }
    }
}
