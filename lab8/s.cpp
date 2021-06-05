//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 03.10.2020
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> ed;
    vector<int> st;
    vector<bool> in(n + 1, false);
    vector<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        if (in[a[i]]) {
            for (int j = (int) st.size() - 1; j >= 0 && st[j] != a[i]; j--) {
                st.pop_back();
            }
            bool p = false;
            for (int j = i + 1; j < m; j++) {
                if (a[j] == a[i]) {
                    p = true;
                }
            }
            if (!p) {
                st.pop_back();
            }
            continue;
        }
        if (!st.empty()) {
            ed.push_back({a[i], st[st.size() - 1]});
        }
        for (int j = (int) st.size() - 2; j >= 0; j--) {
            if (st[j + 1] < a[i]) {
                ed.push_back({a[i], st[j]});
            }
        }
        bool p = false;
        for (int j = i + 1; j < m; j++) {
            if (a[j] == a[i]) {
                p = true;
            }
        }
        if (p) {
            st.push_back(a[i]);
            in[a[i]] = true;
        }
    }
    cout << ed.size() << '\n';
    for (auto u : ed) {
        cout << u.first << ' ' << u.second << '\n';
    }
}
