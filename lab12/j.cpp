//
// Created by Yarolsav Ilin CT ITMO M3238 on 20.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

int ans(int prev, string s) {
    reverse(s.begin(), s.end());
    int n = s.size();
    vector<int> ans(n);
    for (int i = 1; i < n; i++) {
        int j = ans[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = ans[j - 1];
        }
        if (s[i] == s[j]) j++;
        ans[i] = j;
    }
    int mx = 0;
    for (int i = 1; i < n; i++) {
        mx = max(mx, ans[i]);
    }
    return prev + (n - mx);
}

int main() {
    string s;
    cin >> s;
    int n = s.size();
    int x = 0;
    for (int i = 1; i <= n; i++) {
        x = ans(x, s.substr(0, i));
        cout << x << '\n';
    }
}
