#include <bits/stdc++.h>

using namespace std;

const int INF = 1000001;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i + 1][j + 1];
        }
    }
    vector<int> b(n + 1);
    vector<int> c(n + 1);
    vector<int> p(n + 1);
    vector<int> way(n + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int g = 0;
        vector<int> minc(n + 1, INF);
        vector<char> used(n + 1, false);
        while (true) {
            used[g] = true;
            int i0 = p[g];
            int delta = INF;
            int k = 0;
            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    int cur = a[i0][j] - b[i0] - c[j];
                    if (cur < minc[j]) {
                        minc[j] = cur;
                        way[j] = g;
                    }
                    if (minc[j] < delta) {
                        delta = minc[j];
                        k = j;
                    }
                }
            }
            for (int j = 0; j <= n; ++j) {
                if (used[j]) {
                    b[p[j]] += delta;
                    c[j] -= delta;
                } else {
                    minc[j] -= delta;
                }
            }
            g = k;
            if (p[g] == 0) {
                break;
            }
        }
        while (true) {
            int k = way[g];
            p[g] = p[k];
            g = k;
            if (g == 0) {
                break;
            }
        }
    }
    cout << -c[0] << '\n';
    vector<int> ans(n + 1);
    for (int j = 1; j <= n; j++) {
        ans[p[j]] = j;
    }
    for (int i = 1; i <= n; i++) {
        cout << i << ' ' << ans[i] << '\n';
    }
}
