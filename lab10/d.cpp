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

pair<vector<int>, vector<int>> ver(int n, int m, vector<vector<int>> &ed, vector<int> &p) {
    vector<int> ans1;
    vector<int> right(m, -1);
    for (int i = 0; i < n; i++) {
        if (p[i] != -1) {
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
    vector<int> ans2;
    for (int i = 0; i < n; i++) {
        if (!usedLeft[i]) {
            ans1.push_back(i);
        }
    }
    for (int i = 0; i < m; i++) {
        if (usedRight[i]) {
            ans2.push_back(i);
        }
    }
    return {ans1, ans2};
}

bool dfs1(int v, vector<vector<int>> &ed, vector<int> &px, vector<int> &py, vector<bool> &used) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (auto u : ed[v]) {
        if (py[u] == -1) {
            py[u] = v;
            px[v] = u;
            return true;
        } else {
            if (dfs1(py[u], ed, px, py, used)) {
                py[u] = v;
                px[v] = u;
                return true;
            }
        }
    }
    return false;
}

vector<int> parr(int n, int m, vector<vector<int>> &ed) {
    vector<int> px(n, -1);
    vector<int> py(m, -1);
    bool isPath = true;
    while (isPath) {
        isPath = false;
        vector<bool> used(n);
        for (int i = 0; i < n; i++) {
            if (px[i] == -1) {
                if (dfs1(i, ed, px, py, used)) {
                    isPath = true;
                }
            }
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        ans.push_back(px[i]);
    }
    return ans;
}


void solve() {
    int n, m;
    cin >> n >> m;
    vector<set<int>> ed(n);
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        while (c != 0) {
            ed[i].insert(c - 1);
            cin >> c;
        }
    }
    vector<vector<int>> ed1(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ed[i].count(j) == 0) {
                ed1[i].push_back(j);
            }
        }
    }

    auto p = parr(n, m, ed1);

    auto ans = ver(n, m, ed1, p);
    vector<bool> used(n), used1(m);
    for (auto u : ans.first) {
        used[u] = true;
    }
    for (auto u : ans.second) {
        used1[u] = true;
    }
    vector<int> ans1;
    vector<int> ans2;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            ans1.push_back(i);
        }
    }
    for (int i = 0; i < m; i++) {
        if (!used1[i]) {
            ans2.push_back(i);
        }
    }
    cout << ans1.size() + ans2.size() << '\n';
    cout << ans1.size() << ' ' << ans2.size() << '\n';
    for (auto u : ans1) {
        cout << u + 1 << ' ';
    }
    cout << '\n';
    for (auto u : ans2) {
        cout << u + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    int k;
    cin >> k;
    for (int test = 0; test < k; test++) {
        solve();
    }
}
