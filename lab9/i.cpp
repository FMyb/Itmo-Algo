//
// Created by Yarolsav Ilin CT ITMO M3238 on 23.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000001;

void union_1(int u, int v, vector<vector<int>> &component, vector<int> &color) {
    if (component[u].size() > component[v].size()) {
        swap(u, v);
    }
    for (auto i : component[u]) {
        color[i] = v;
    }
    component[v].insert(component[v].end(), component[u].begin(), component[u].end());
    component[u].clear();
}

int tree(int n, int m, vector<pair<int, pair<int, int>>> &ed, int w) {
    vector<vector<int>> component(n);
    vector<int> color(n);
    for (int j = 0; j < n; j++) {
        color[j] = j;
        component[j].push_back(j);
    }
    vector<bool> used(n, false);
    int cnt = 0;
    int ans = -INF;
    for (int i = 0; i < m; i++) {
        if (color[ed[i].second.first] != color[ed[i].second.second] && ed[i].first >= w) {
            ans = max(ed[i].first, ans);
            union_1(color[ed[i].second.first], color[ed[i].second.second], component, color);
            cnt++;
        }
        if (cnt == n - 1) {
            break;
        }
    }
    if (cnt != n - 1) {
        return 2 * INF;
    }
    if (ans == -INF) {
        return 2 * INF;
    }
    return ans - w;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> ed;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ed.push_back({w, {u - 1, v - 1}});
    }
    sort(ed.begin(), ed.end());
    int ans = tree(n, m, ed, -INF);
    if (ans == 2 * INF) {
        cout << "NO";
        return 0;
    }
    for (int i = 0; i < m; i++) {
        ans = min(ans, tree(n, m, ed, ed[i].first));
    }
    cout << "YES\n";
    cout << ans;
}
