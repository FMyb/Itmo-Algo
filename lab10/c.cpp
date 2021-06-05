//
// Created by Yarolsav Ilin CT ITMO M3238 on 13.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, vector<vector<int>> &ed, vector<int> &p, vector<int> &right,
         vector<bool> &usedLeft, vector<bool> &usedRight) {
    usedLeft[v] = true;
    for (auto u : ed[v]) {
        if (!usedRight[u] && p[v] != u) {
            usedRight[u] = true;
            if (right[u] != -1) {
                dfs(right[u], ed, p, right, usedLeft, usedRight);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ed(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int u;
            cin >> u;
            ed[i].push_back(--u);
        }
    }
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        --p[i];
    }
    int ans1 = 0;
    vector<int> right(m, -1);
    for (int i = 0; i < n; i++) {
        if (p[i] != -1) {
            ans1++;
            right[p[i]] = i;
        }
    }
    vector<bool> usedLeft(n);
    vector<bool> usedRight(m);
    for (int i = 0; i < n; i++) {
        if (p[i] == -1) {
            dfs(i, ed, p, right, usedLeft, usedRight);
        }
    }
    cout << ans1 << '\n';
    ans1 = 0;
    for (int i = 0; i < n; i++) {
        if (!usedLeft[i]) {
            ans1++;
        }
    }
    cout << ans1 << ' ';
    for (int i = 0; i < n; i++) {
        if (!usedLeft[i]) {
            cout << i + 1 << ' ';
        }
    }
    ans1 = 0;
    cout << '\n';
    for (int i = 0; i < m; i++) {
        if (usedRight[i]) {
            ans1++;
        }
    }
    cout << ans1 << ' ';
    for (int i = 0; i < m; i++) {
        if (usedRight[i]) {
            cout << i + 1 << ' ';
        }
    }
}
