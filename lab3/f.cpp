#include <bits/stdc++.h>

using namespace std;

struct request {
    string name;
    int v;
    int u;
};

int get(int v, vector<int> &par) {
    if (v == par[v]) {
        return v;
    }
    return par[v] = get(par[v], par);
}

bool ask(int v, int u, vector<int> &par) {
    return get(v, par) == get(u, par);
}

bool union_snm(int v, int u, vector<int> &par, vector<int> &rank) {
    v = get(v, par);
    u = get(u, par);
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

int main() {
    ios_base::sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> par(n);
    vector<int> rank(n);
    for (int i = 0; i < n; i++) {
        par[i] = i;
        rank[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
    }
    vector<request> a(k);
    vector<bool> ans;
    for (int i = 0; i < k; i++) {
        cin >> a[i].name >> a[i].v >> a[i].u;
        a[i].v--;
        a[i].u--;
    }
    reverse(a.begin(), a.end());
    for (int i = 0; i < k; i++) {
        if (a[i].name == "ask") {
            ans.push_back(ask(a[i].v, a[i].u, par));
        }
        if (a[i].name == "cut") {
            union_snm(a[i].v, a[i].u, par, rank);
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto x : ans) {
        if (x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
