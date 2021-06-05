//
// Created by Yarolsav Ilin CT ITMO M3238 on 12.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

int n;

bool dfs(int v, vector<vector<int>> &ed, vector<int> &matching,
         vector<int> &matchingTo, vector<bool> &used) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (auto u : ed[v]) {
        if (matching[u] == -1 || dfs(matching[u], ed, matching, matchingTo, used)) {
            matching[u] = v;
            matchingTo[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    int m;
    cin >> n >> m;
    vector<vector<int>> ed(n);
    vector<vector<int>> ed1(2 * n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        ed[u].push_back(v);
        ed1[u].push_back(v + n);
    }

    vector<int> matching(2 * n, -1);
    vector<int> matchingTo(2 * n, -1);
    for (int i = 0; i < n; i++) {
        vector<bool> used(2 * n);
        dfs(i, ed1, matching, matchingTo, used);
    }
    vector<bool> used(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        ans++;
        used[i] = true;
        int x = matching[i + n];
        while (x != -1) {
            used[x] = true;
            x = matching[x + n];
        }
        x = matchingTo[i] - n;
        while (x > -1) {
            used[x] = true;
            x = matchingTo[x] - n;
        }
    }
    cout << ans;
}
