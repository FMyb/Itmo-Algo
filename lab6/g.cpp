//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 28.03.2020
//

#include <bits/stdc++.h>

using namespace std;

const int m = 1000000007;

// ret: first - ind, second height
pair<int, int> dfs(int v, int p, vector<vector<int>> &ed, vector<bool> &used) {
    used[v] = true;
    int ind = v;
    int height = 0;
    for (auto u : ed[v]) {
        if (u == p) continue;
        if (!used[u]) {
            auto s = dfs(u, v, ed, used);
            if (height < s.second) {
                height = s.second;
                ind = s.first;
            }
        }
    }
    return {ind, height + 1};
}

vector<int> path;
bool f = false;

void find(int v, int p, vector<vector<int>> &ed, vector<bool> &used, int ind) {
    if (f) return;
    path.push_back(v);
    if (v == ind) {
        f = true;
        return;
    }
    used[v] = true;
    for (auto u : ed[v]) {
        if (u != p && !used[u]) {
            find(u, v, ed, used, ind);
            if (f) return;
        }
    }
    path.pop_back();
}

// ret first - hash, second - height
pair<int, int> hash_tree(int v, int p, vector<vector<int>> &ed, vector<bool> &used) {
    used[v] = true;
    int height = 0;
    vector<int> hashs;
    for (auto u : ed[v]) {
        if (u != p && !used[u]) {
            auto s = hash_tree(u, v, ed, used);
            hashs.push_back(s.first);
            if (s.second > height) {
                height = s.second;
            }
        }
    }
    height++;
    int hasht = height * 23;
    for (size_t i = 0; i < hashs.size(); i++) {
        hasht += hashs[i];
        hasht %= m;
    }
    return {hasht, height};
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> ed(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        ed[u].push_back(v);
        ed[v].push_back(u);
    }
    vector<bool> used(n, false);
    auto v1 = dfs(0, -1, ed, used);
    used = vector<bool>(n, false);
    auto v2 = dfs(v1.first, -1, ed, used);
    used = vector<bool>(n, false);
    find(v1.first, -1, ed, used, v2.first);
    if (path.size() % 2 == 0) {
        cout << "NO";
        return 0;
    }
    int head = path[path.size() / 2];
    if (ed[head].size() != 2) {
        cout << "NO";
        return 0;
    }
    used = vector<bool>(n, false);
    pair<int, int> h1 = hash_tree(ed[head][0], head, ed, used);
    used = vector<bool>(n, false);
    pair<int, int> h2 = hash_tree(ed[head][1], head, ed, used);
    if (h1.first == h2.first) {
        assert(h1.second == h2.second);
        cout << "YES";
    } else {
        cout << "NO";
    }
}
