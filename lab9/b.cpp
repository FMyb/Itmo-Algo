//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

const long long INF = 1000000000000000001;

int main() {
    ios_base::sync_with_stdio(false);
    int n, s, t;
    cin >> n >> s >> t;
    s--;
    t--;
    vector<vector<pair<int, long long>>> ed(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x != -1) {
                ed[i].push_back({j, x});
            }
        }
    }
    vector<long long> d(n, INF);
    vector<int> used(n, false);
    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (v == -1 || d[v] > d[j])) {
                v = j;
            }
        }
        if (v == -1) {
            break;
        }
        used[v] = true;
        for (auto u : ed[v]) {
            d[u.first] = min(d[u.first], d[v] + u.second);
        }
    }
    if (d[t] == INF) {
        cout << -1;
    } else {
        cout << d[t];
    }
}
