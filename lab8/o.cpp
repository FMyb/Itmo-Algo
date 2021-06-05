//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 03.10.2020
//

#include <bits/stdc++.h>

using namespace std;

int neg(int x, int n) {
    return x - n >= 0 ? x - n : x + n;
}

int times = 0;

void dfs(int v, bool p, vector<int> &used,
         int color, vector<vector<int> > &ed, vector<int> &timeout) {
    used[v] = color;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, p, used, color, ed, timeout);
        }
    }
    if (p) {
        timeout[times] = v;
        times++;
    }
}

vector<int> css(int n, vector<vector<int>> &ed) {
    times = 0;
    vector<int> timeout(n);
    vector<int> used(n, 0);
    vector<vector<int> > ed1(n);
    for (size_t i = 0; i < ed.size(); i++) {
        for (auto u : ed[i]) {
            ed1[u].push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, true, used, 1, ed, timeout);
        }
    }
    reverse(timeout.begin(), timeout.end());
    vector<int> kss(n);
    int color = 1;
    for (int i : timeout) {
        if (!kss[i]) {
            dfs(i, false, kss, color, ed1, timeout);
            color++;
        }
    }
    return kss;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> color(n);
    for (int i = 0; i < n; i++) {
        cin >> color[i];
    }
    vector<int> connectors(2 * n);
    vector<bool> used(n);
    vector<bool> b(2 * n);
    vector<int> d(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> connectors[i];
        connectors[i]--;
        if (used[connectors[i]]) {
            b[i] = true;
            d[neg(connectors[i], n)] = i;
        } else {
            d[connectors[i]] = i;
        }
        used[connectors[i]] = true;
    }
    vector<vector<int>> ed(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        if (color[connectors[i]] == color[connectors[(i + 1) % (2 * n)]]) {
            int u = b[i] ? connectors[i] + n : connectors[i];
            int v = b[(i + 1) % (2 * n)] ? connectors[(i + 1) % (2 * n)] + n
                                         : connectors[(i + 1) % (2 * n)];
            ed[v].push_back(neg(u, n));
            ed[u].push_back(neg(v, n));
        }
    }
    vector<int> a = css(2 * n, ed);
    for (int i = 0; i < n; i++) {
        if (a[i] == a[neg(i, n)]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        if (a[i] > a[neg(i, n)]) {
            cout << d[i] + 1 << ' ';
        } else {
            cout << d[neg(i, n)] + 1 << ' ';
        }
    }
}
