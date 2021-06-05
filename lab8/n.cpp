//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 26.09.2020
//

#include <bits/stdc++.h>

using namespace std;

int times;

void dfs(int v, bool p, int vol, vector<int> &used,
         int color, vector<vector<int> > &ed, vector<int> &timeout) {
    used[v] = color;
    for (int u = 0; u < (int) used.size(); u++) {
        if (!used[u] && ed[v][u] <= vol) {
            dfs(u, p, vol, used, color, ed, timeout);
        }
    }
    if (p) {
        timeout[times] = v;
        times++;
    }
}

bool check(int n, int vol, vector<vector<int>> &ed, vector<vector<int>> ed1) {
    times = 0;
    vector<int> timeout(n);
    vector<int> used(n, 0);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, true, vol, used, 1, ed, timeout);
        }
    }
    reverse(timeout.begin(), timeout.end());
    vector<int> kss(n);
    int color = 1;
    for (int i : timeout) {
        if (!kss[i]) {
            dfs(i, false, vol, kss, color, ed1, timeout);
            color++;
        }
    }
    return color <= 2;
}

int bin_find(int n, vector<vector<int>> &ed, vector<vector<int>> &ed1) {
    int l = -1;
    int r = 1000000001;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(n, m, ed, ed1)) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> ed(n, vector<int>(n));
    vector<vector<int>> ed1(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            ed[i][j] = x;
            ed1[j][i] = x;
        }
    }
    int ans = bin_find(n, ed, ed1);
    cout << ans;
}
