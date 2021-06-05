//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> component(80000);
vector<int> color(80000);

void union_1(int u, int v) {
    if (component[u].size() > component[v].size()) {
        swap(u, v);
    }
    for (auto i : component[u]) {
        color[i] = v;
    }
    component[v].insert(component[v].end(), component[u].begin(), component[u].end());
    component[u].clear();
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        color[i] = i;
        component[i].push_back(i);
    }
    vector<pair<long long, pair<int, int>>> ed;
    for (int i = 0; i < m; i++) {
        int v, u, w;
        cin >> v >> u >> w;
        v--;
        u--;
        ed.push_back({w, {v, u}});
    }
    sort(ed.begin(), ed.end());
    vector<bool> used(n, false);
    int cnt = 0;
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        if (color[ed[i].second.first] != color[ed[i].second.second]) {
            ans += ed[i].first;
            union_1(color[ed[i].second.first], color[ed[i].second.second]);
            cnt++;
        }
        if (cnt == n - 1) {
            break;
        }
    }
    cout << ans;
}
