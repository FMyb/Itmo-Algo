//
// Created by Yarolsav Ilin CT ITMO M3238 on 15.11.2020.
//

#include <bits/stdc++.h>

using namespace std;


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> deg(n);
    vector<multiset<int>> ed(n);
    vector<vector<int>> ed1(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        ed[u].insert(v);
        ed[v].insert(u);
        ed1[u].push_back(v);
        ed1[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    int oddV = 0;
    vector<int> odd;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2) {
            oddV++;
            odd.push_back(i);
        }
    }
    assert(oddV % 2 == 0);
    auto ed2 = ed;
    for (size_t i = 0; i < odd.size(); i += 2) {
        int &x = odd[i + 1];
        int &i1 = odd[i];
        deg[x]++;
        deg[i1]++;
        ed[i1].insert(x);
        ed[x].insert(i1);
        ed1[i1].push_back(x);
        ed1[x].push_back(i1);
    }
    int v = 0;
    stack<int> s;
    s.push(v);
    vector<int> ans;
    while (!s.empty()) {
        int w = s.top();
        if (deg[w] == 0) {
            s.pop();
            ans.push_back(w);
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
    vector<vector<int>> ans1;
    ans1.push_back(vector<int>());
    ans1.back().push_back(ans[0]);
    for (size_t i = 1; i < ans.size(); i++) {
        if (ed2[ans[i - 1]].count(ans[i]) == 0) {
            ans1.push_back(vector<int>());
            ans1.back().push_back(ans[i]);
        } else {
            ans1.back().push_back(ans[i]);
            ed2[ans[i]].erase(ans[i - 1]);
            ed2[ans[i - 1]].erase(ans[i]);
        }
    }
    if (ans1.size() != 1 && ans1[0][0] == ans1.back().back()) {
        vector<int> c;
        for (int i : ans1.back()) {
            c.push_back(i);
        }
        c.pop_back();
        for (int i : ans1[0]) {
            c.push_back(i);
        }
        ans1[0] = c;
        ans1.pop_back();
    }
    cout << ans1.size() << '\n';
    for (auto &i : ans1) {
        for (auto j : i) {
            cout << j + 1 << ' ';
        }
        cout << '\n';
    }
}
