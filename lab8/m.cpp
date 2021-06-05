//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 03.10.2020
//

#include <bits/stdc++.h>

using namespace std;

bool is_cycle = false;

void dfs(int v, vector<vector<int>> &ed, vector<int> &used) {
    used[v] = 1;
    for (auto u : ed[v]) {
        if (used[u] == 1) {
            is_cycle = true;
            return;
        }
        if (!used[u]) {
            dfs(u, ed, used);
        }
    }
    used[v] = 2;
}

void top_sort(int v, vector<vector<int>> &ed, vector<int> &used, vector<int> &tin) {
    used[v] = 1;
    for (auto u : ed[v]) {
        if (!used[u]) {
            top_sort(u, ed, used, tin);
        }
    }
    tin.push_back(v);
}

int num = 25;

void paint(int v, bool col, vector<vector<int>> &ed, vector<int> &used, vector<int> &ans) {
    used[v] = 1;
    for (auto u : ed[v]) {
        if (!used[u]) {
            paint(u, true, ed, used, ans);
        }
    }
    if (col) ans[v] = num--;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    vector<vector<int>> ed(26);
    cin >> n;
    vector<string> inp(n);
    for (int i = 0; i < n; i++) {
        cin >> inp[i];
    }
    vector<bool> can_zero(26, true);
    if (inp[0].size() > 1) {
        can_zero[inp[0][0] - 'a'] = false;
    }
    for (int i = 1; i < n; i++) {
        if (inp[i].size() < inp[i - 1].size()) {
            cout << "No";
            return 0;
        }
        if (inp[i].size() > 1) {
            can_zero[inp[i][0] - 'a'] = false;
        }
        if (inp[i].size() > inp[i - 1].size()) {
            can_zero[inp[i][0] - 'a'] = false;
            continue;
        }
        for (size_t j = 0; j < inp[i].size(); j++) {
            if (inp[i][j] != inp[i - 1][j]) {
                ed[inp[i - 1][j] - 'a'].push_back(inp[i][j] - 'a');
                break;
            } else if (j == inp[i].size() - 1) {
                cout << "No";
                return 0;
            }
        }
    }
    vector<int> used(26);
    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            dfs(i, ed, used);
        }
    }
    if (is_cycle) {
        cout << "No";
        return 0;
    }
    bool p = false;
    for (int i = 0; i < 26; i++) {
        if (can_zero[i]) {
            p = true;
            break;
        }
    }
    if (!p) {
        cout << "No";
        return 0;
    }
    vector<int> tin;
    fill(used.begin(), used.end(), 0);
    for (int i = 0; i < 26; i++) {
        if (!used[i]) {
            top_sort(i, ed, used, tin);
        }
    }
    reverse(tin.begin(), tin.end());
    fill(used.begin(), used.end(), 0);
    vector<int> ans(26);
    bool is_zero = false;
    for (int i = 0; i < 26; i++) {
        if (!used[tin[i]]) {
            if (!is_zero && can_zero[tin[i]]) {
                is_zero = true;
                ans[tin[i]] = 0;
                paint(tin[i], false, ed, used, ans);
            } else {
                paint(tin[i], true, ed, used, ans);
            }
        }
    }
    if (!is_zero) {
        cout << "No";
        return 0;
    }
    cout << "Yes\n";
    for (int i = 0; i < 26; i++) {
        cout << ans[i] << ' ';
    }
}
