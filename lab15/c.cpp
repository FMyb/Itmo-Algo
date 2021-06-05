#include <bits/stdc++.h>

using namespace std;


void add(int v, int x, vector<vector<int>> &ed, vector<int> &deg) {
    for (int i : ed[v]) {
        deg[i] += x;
    }
}

int cc = 1;
int k;

void go(int depth, int n, vector<int> &u, vector<int> &deg, vector<vector<int>> &ed) {
    int ind = -1;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += !!u[i];
    }
    for (int i = 0; i < n; i++) {
        if (!u[i] && (ind == -1 || deg[ind] < deg[i])) {
            ind = i;
        }
    }
    if (ind == -1 || deg[ind] == 0) {
        cout << "Yes\n";
        for (int i = 0; i < n; i++) {
            if (!u[i] && depth < k) {
                u[i] = -1;
                depth++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (u[i]) {
                cout << i + 1 << ' ';
            }
        }
        exit(0);
    }
    int e = 0;
    for (int i = 0; i < n; i++) {
        if (!u[i]) {
            e += deg[i];
        }
    }
    if (2 * deg[ind] * (k - depth) < e) {
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!u[i] && deg[i] == 1) {
            for (int j : ed[i]) {
                if (!u[j]) {
                    ind = j;
                }
            }
            u[ind] = 1;
            add(ind, -1, ed, deg);
            go(depth + 1, n, u, deg, ed);
            u[ind] = 0;
            add(ind, 1, ed, deg);
            return;
        }
    }
    u[ind] = 1;
    add(ind, -1, ed, deg);
    go(depth + 1, n, u, deg, ed);
    u[ind] = 0;
    add(ind, 1, ed, deg);
    if (depth + deg[ind] <= k) {
        int x;
        cc++;
        for (int i = 0; i < (int) ed[ind].size(); i++) {
            if (u[x = ed[ind][i]] == 0) {
                u[x] = cc;
                add(x, -1, ed, deg);
                depth++;
            }
        }
        go(depth, n, u, deg, ed);
        for (int i = 0; i < (int) ed[ind].size(); i++) {
            if (u[x = ed[ind][i]] == cc) {
                u[x] = 0;
                add(x, 1, ed, deg);
            }
        }
        cc--;
    }

}


int main() {
    int n, m;
    cin >> n >> m >> k;
    vector<vector<int>> ed(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        ed[--a].push_back(--b);
        ed[b].push_back(a);
    }
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        deg[i] = (int) ed[i].size();
    }
    vector<int> u(n);
    go(0, n, u, deg, ed);
    cout << "No";
}
