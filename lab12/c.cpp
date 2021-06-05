//
// Created by Yarolsav Ilin CT ITMO M3238 on 20.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    vector<int> ans(s.size());
    for (int i = 1; i < (int) s.size(); i++) {
        int j = ans[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = ans[j - 1];
        }
        if (s[i] == s[j]) j++;
        ans[i] = j;
    }
    for (auto x : ans) {
        cout << x << ' ';
    }
}
