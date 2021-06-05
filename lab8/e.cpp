//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 06.09.2020
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, vector<vector<int> > &ed, vector<int> &used, vector<int> &prev,
         int &start, int &finish) {
    used[v] = 1;
    for (auto u : ed[v]) {
        if (used[u] == 0) {
            prev[u] = v;
            dfs(u, ed, used, prev, start, finish);
        } else if (used[u] == 1) {
            start = v;
            finish = u;
        }
    }
    used[v] = 2;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > ed(n);
    vector<int> used(n, 0);
    vector<int> prev(n, -1);
    int start = -1, finish = -1;
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        ed[v - 1].push_back(u - 1);
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, ed, used, prev, start, finish);
        }
    }

    if (start == -1) {
        cout << "NO";
    } else {
        cout << "YES" << '\n';
        vector<int> ans;
        while (start != finish) {
            ans.push_back(start + 1);
            start = prev[start];
        }
        ans.push_back(finish + 1);
        reverse(ans.begin(), ans.end());
        for (auto i : ans) {
            cout << i << ' ';
        }
    }
}
