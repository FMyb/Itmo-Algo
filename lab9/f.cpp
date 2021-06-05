//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

struct V {
    int v;
    int u;
    int w;
};

int main() {
    int n;
    cin >> n;
    vector<V> ed;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x != INF) {
                ed.push_back({i, j, x});
            }
        }
    }
    vector<int> dist(n, INF);
    vector<int> prev(n);
    int st = -1;
    for (int i = 0; i < n + 1; i++) {
        for (auto x : ed) {
            if (dist[x.u] > dist[x.v] + x.w) {
                dist[x.u] = dist[x.v] + x.w;
                prev[x.u] = x.v;
                if (i == n) {
                    st = x.u;
                }
            }
        }
    }

    if (st == -1) {
        cout << "NO";
        return 0;
    }
    set<int> set1;
    while (!set1.count(st)) {
        set1.insert(st);
        st = prev[st];
    }
    int fn = prev[st];
    vector<int> ans;
    while (st != fn) {
        ans.push_back(fn);
        fn = prev[fn];
    }
    ans.push_back(st);
    cout << "YES\n" << ans.size() + 1 << '\n';
    reverse(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i + 1 << ' ';
    }
    cout << ans[0] + 1;
}
