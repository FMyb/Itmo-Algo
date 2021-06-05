//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 18.09.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, vector<set<int>> &ed, vector<bool> &used, vector<int> &ans) {
    used[v] = true;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, ed, used, ans);
        }
    }
    ans.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<set<int>> ed(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ed[--u].insert(--v);
    }
    vector<bool> used(n);
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, ed, used, ans);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n - 1; i++) {
        if (!ed[ans[i]].count(ans[i + 1])) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}
