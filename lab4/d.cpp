#include <bits/stdc++.h>

using namespace std;

int main() {
    ifstream fin;
    fin.open("knapsack.in");
    ofstream fout("knapsack.out");
    ios_base::sync_with_stdio(false);
    int n, m;
    fin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> w[i];
    }
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        fin >> c[i];
    }
    a[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            a[i][j] = a[i - 1][j];
            if (j - w[i] >= 0) {
                a[i][j] = max(a[i][j], a[i - 1][j - w[i]] + c[i]);
            }
        }
    }
    vector<int> ans;
    int k = m;
    int i = n;
    while (a[i][k] != 0) {
        if (a[i][k] == a[i - 1][k]) {
            i--;
        } else {
            ans.push_back(i);
            k -= w[i];
            i--;
        }
    }
    fout << ans.size() << '\n';
    for (int i = ans.size() - 1; i >= 0; i--) {
        fout << ans[i] << ' ';
    }
}
