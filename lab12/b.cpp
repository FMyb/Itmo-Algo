//
// Created by Yarolsav Ilin CT ITMO M3238 on 20.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    string t, s;
    cin >> t >> s;
    s = t + '#' + s;
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(r - i, z[i - l]));
        while (s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    vector<int> in;
    for (int i = 0; i < n; i++) {
        if (z[i] == (int) t.size()) {
            in.push_back(i - ((int) t.size()));
        }
    }
    cout << in.size() << '\n';
    for (auto x : in) {
        cout << x << ' ';
    }
}
