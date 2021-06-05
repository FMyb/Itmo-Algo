//
// Created by Yarolsav Ilin CT ITMO M3238 on 14.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> zf(5000);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    string t;
    cin >> t;
    int n = t.size();
    reverse(t.begin(), t.end());
    for (int k = 0; k < n; k++) {
        int m = n - k;
        vector<int> mz(m);
        vector<int> ans(m);
        for (int i = 1; i < m; i++) {
            int j = ans[i - 1];
            while (j > 0 && t[i + k] != t[j + k]) {
                j = ans[j - 1];
            }
            if (t[i + k] == t[j + k]) j++;
            ans[i] = j;
            mz[i] = max(mz[i - 1], ans[i]);
        }
        zf[k] = mz;
    }
    int q;
    cin >> q;
    for (int k = 0; k < q; k++) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        int sz = r - l + 1;
        for (int i = 0; i < sz; i++) {
            ans += i + 1 - zf[n - l - i][i];
        }
        cout << ans << '\n';
    }
}
