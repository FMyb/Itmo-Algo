#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000001;

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin;
    fin.open("lis.in");
    ofstream fout("lis.out");
    int n;
    fin >> n;
    vector<int> a(n);
    vector<int> dp(n + 1, INF);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    dp[0] = -INF;
    vector<int> pred(n + 1, -1);
    vector<int> pred1(n + 1, -1);
    for (int i = 0; i < n; i++) {
        int j = int(upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin());
        if (a[i] < dp[j] && a[i] > dp[j - 1]) {
            dp[j] = a[i];
            pred[j] = i;
            pred1[i] = pred[j - 1];
        }
    }
    int x = -1;
    for (int i = n; i >= 0; i--) {
        if (dp[i] != INF) {
            x = pred[i];
            break;
        }
    }
    vector<int> ans;
    ans.push_back(a[x]);
    while (x != -1) {
        x = pred1[x];
        if (x == -1) break;
        ans.push_back(a[x]);
    }
    fout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (auto i : ans) {
        fout << i << ' ';
    }
}
