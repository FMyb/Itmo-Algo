//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 25.05.2020
//

#include <bits/stdc++.h>

using namespace std;

const int N = 500001;

vector<int> par(N);
vector<int> rank_(N);
vector<int> lcaClass(N);

int get(int v) {
    if (v == par[v]) {
        return v;
    }
    return par[v] = get(par[v]);
}

bool ask(int v, int u) {
    return get(v) == get(u);
}

int union_snm(int v, int u) {
    v = get(v);
    u = get(u);
    if (v == u) {
        return v;
    }
    if (rank_[v] < rank_[u]) swap(u, v);
    if (rank_[u] < rank_[v]) par[u] = v;
    if (rank_[u] == rank_[v]) {
        par[v] = u;
        rank_[v]++;
    }
    return get(v);
}


void union_(int x, int y, int pred) {
    int lead = union_snm(x, y);
    lcaClass[lead] = pred;
}

void dfs(int v, vector<vector<int>> &ed, vector<bool> &used,
    vector<vector<int>> &requests, map<pair<int, int>, int> &ans) {
    used[v] = true;
    lcaClass[v] = v;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, ed, used, requests, ans);
            union_(v, u, v);
        }
    }
    for (auto u : requests[v]) {
        if (used[u]) {
            int x = get(u);
            ans[{u, v}] = lcaClass[x];
            ans[{v, u}] = lcaClass[x];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    for (int i = 0; i < N; i++) {
        par[i] = i;
        rank_[i] = 1;
    }
    int c = 0;
    int m;
    cin >> m;
    vector<vector<int>> ed(N);
    vector<pair<int, int>> hist;
    vector<vector<int>> requests(N);
    for (int i = 0; i < m; i++) {
        string s;
        int u, v;
        cin >> s >> u >> v;
        if (s == "ADD") {
            if (c == 0) {
                c = u;
            }
            ed[--u].push_back(--v);
            ed[v].push_back(u);
        } else {
            requests[--u].push_back(--v);
            requests[v].push_back(u);
            hist.push_back({u, v});
        }
    }
    c--;
    vector<bool> used(N);
    map<pair<int, int>, int> ans;
    dfs(c, ed, used, requests, ans);
    for (auto u : hist) {
        cout << ans[u] + 1 << endl;
    }
}
