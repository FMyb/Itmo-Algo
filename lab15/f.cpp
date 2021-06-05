#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ed(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        ed[--u].push_back(--v);
        ed[v].push_back(u);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    while (true) {
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
            for (int i = 0; i < n; i++) {
                cout << col[i] << ' ';
            }
            break;
        }
        shuffle(a.begin(), a.end(), g);
    }
}
