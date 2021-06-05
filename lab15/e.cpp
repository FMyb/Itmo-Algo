#include <bits/stdc++.h>

using namespace std;

bool ans = true;

void dfs(int v, int color, vector<vector<int>> &ed, vector<int> &used) {
    if (!ans) return;
    used[v] = color;
    for (auto u : ed[v]) {
        if (!used[u]) {
            dfs(u, 3 - color, ed, used);
        } else if (used[v] == used[u]) {
            ans = false;
            return;
        }
    }
}

int try_two(int n, vector<vector<int>> &ed) {
    vector<int> used(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, 1, ed, used);
        }
    }
    if (ans) {
        cout << "YES\n";
        for (auto u : used) {
            cout << u << ' ';
        }
        return true;
    } else {
        return false;
    }
}

bool try_three(int n, vector<vector<int>> &ed) {
    std::random_device rd;
    std::mt19937 g(rd());
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    for (int test = 0; test < 100000; test++) {
        vector<int> col(n, 0);
        bool f = true;
        for (auto i : a) {
            vector<bool> c(4);
            c[0] = true;
            for (auto u : ed[i]) {
                c[col[u]] = true;
            }
            for (int j = 1; j < 4; j++) {
                if (!c[j]) {
                    col[i] = j;
                    break;
                }
            }
            if (col[i] == 0) {
                f = false;
                break;
            }
        }
        if (f) {
            cout << "YES\n";
            for (int i = 0; i < n; i++) {
                cout << col[i] << ' ';
            }
            return true;
        }
        shuffle(a.begin(), a.end(), g);
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> ed1(n);
    vector<vector<int>> ed(m);
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({--u, --v});
        ed1[u].push_back({v, i});
        ed1[v].push_back({u, i});
    }
    for (int i = 0; i < m; i++) {
        int v = edges[i].first;
        for (auto u : ed1[v]) {
            if (u.second != i) {
                ed[i].push_back(u.second);
            }
        }
        v = edges[i].second;
        for (auto u : ed1[v]) {
            if (u.second != i) {
                ed[i].push_back(u.second);
            }
        }
    }
    if (!try_two(m, ed)) {
        if (!try_three(m, ed)) {
            cout << "NO";
        }
    }
}
