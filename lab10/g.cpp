//
// Created by Yarolsav Ilin CT ITMO M3238 on 15.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

void dfs(int v, vector<vector<int>> &ed, vector<bool> &used) {
    used[v] = true;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, ed, used);
        }
    }
}


int main() {
//    ifstream fin;
//    fin.open("in.txt");
//    ofstream fout("out.txt");
    int n;
    cin >> n;
    vector<int> deg(n);
    vector<multiset<int>> ed(n);
    vector<vector<int>> ed1(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        deg[i] = x;
        for (int j = 0; j < x; j++) {
            int u;
            cin >> u;
            ed[i].insert(u - 1);
            ed1[i].push_back(u - 1);
        }
    }

    int oddV = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2) {
            oddV++;
        }
    }
    if (oddV > 2) {
        cout << -1;
        return 0;
    }
    vector<bool> used(n);
    for (int i = 0; i < n; i++) {
        if (deg[i] > 0) {
            dfs(i, ed1, used);
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] > 0 && !used[i]) {
            cout << -1;
            return 0;
        }
    }
    int v = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2) {
            v = i;
            break;
        }
    }
    stack<int> s;
    s.push(v);
    vector<int> ans;
    while (!s.empty()) {
        int w = s.top();
        if (deg[w] == 0) {
            s.pop();
            ans.push_back(w + 1);
            continue;
        }
        for (auto u : ed1[w]) {
            auto itr = ed[w].find(u);
            if (itr != ed[w].end()) {
                s.push(u);
                deg[w]--;
                deg[u]--;
                ed[w].erase(itr);
                auto itr1 = ed[u].find(w);
                ed[u].erase(itr1);
                break;
            }
        }
    }
    cout << ans.size() - 1 << '\n';
    for (int an : ans) {
        cout << an << ' ';
    }
}
