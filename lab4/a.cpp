#include <bits/stdc++.h>

using namespace std;

const int INF = 2000000000;

string print(int l, int r, vector<vector<pair<int, pair<int, int>>>> &prev) {
    if (l == r - 1) {
        return "A";
    }
    string ans;
    int l1 = prev[l][r].first, m1 = prev[l][r].second.first, r1 = prev[l][r].second.second;
    if (l1 == r1 - 1) {
        return "A";
    }
    ans += l1 == m1 - 1 ? "A" : '(' + print(l1, m1, prev) + ')';
    ans += m1 == r1 - 1 ? "A" : '(' + print(m1, r1, prev) + ')';
    return ans;
}

int main() {
    ifstream fin;
    fin.open("matrix.in");
    ofstream fout("matrix.out");
    int n;
    fin >> n;
    if (n == 1) {
        fout << "A";
        return 0;
    }
    vector<int> p(n + 1);
    fin >> p[0];
    fin >> p[1];
    for (int i = 2; i <= n; i++) {
        int x, y;
        fin >> x >> y;
        p[i] = y;
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    vector<vector<pair<int, pair<int, int>>>> prev(n + 1, vector<pair<int, pair<int, int>>>(n + 1));
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len <= n; l++) {
            int r = l + len;
            if (l == r - 1) {
                dp[l][r] = 0;
            } else {
                dp[l][r] = INF;
                int x = 0, y = 0, m = 0;
                for (int i = l + 1; i < r; i++) {
                    if (dp[l][i] == INF || dp[i][r] == INF) continue;
                    int c = p[l] * p[i] * p[r] + dp[l][i] + dp[i][r];
                    if (dp[l][r] > c) {
                        dp[l][r] = c;
                        x = l;
                        m = i;
                        y = r;
                    }
                    prev[l][r].first = x;
                    prev[l][r].second.first = m;
                    prev[l][r].second.second = y;
                }
            }
        }
    }
    fout << '(' << print(0, n, prev) << ')';
}
