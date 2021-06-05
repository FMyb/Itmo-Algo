#include <bits/stdc++.h>

using namespace std;

const long long INF = 1000000000000000000;

bool bit(long long x, long long j) {
    return (x >> j) & 1;
}

int main() {
    ifstream fin;
    fin.open("salesman.in");
    ofstream fout("salesman.out");
    int n, m;
    fin >> n >> m;
    vector<vector<long long>> ed(n, vector<long long>(n, INF));
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        fin >> u >> v >> w;
        u--;
        v--;
        ed[u][v] = w;
        ed[v][u] = w;
    }
    vector<vector<long long>> dp(n, vector<long long>((1 << n), INF));
    for (int i = 0; i < n; i++) {
        dp[i][(1 << i)] = 0;
    }
    for (int mask = 0; mask < (1 << n) - 1; mask++) {
        for (int i = 0; i < n; i++) {
            if (bit(mask, i)) {
                for (int j = 0; j < n; j++) {
                    if (ed[i][j] > 0 && !bit(mask, j)) {
                        dp[j][mask + (1 << j)] = min(dp[j][mask + (1 << j)],
                                                     dp[i][mask] + ed[i][j]);
                    }
                }
            }
        }
    }
    long long cost = INF;
    for (int i = 0; i < n; i++) {
        cost = min(dp[i][(1 << n) - 1], cost);
    }
    if (cost == INF) {
        fout << -1;
        return 0;
    }
    fout << cost;
}
