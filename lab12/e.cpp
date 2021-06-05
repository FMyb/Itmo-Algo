//
// Created by Yarolsav Ilin CT ITMO M3238 on 28.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<int> z_fun(string s) {
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
    return z;
}

int main() {
    string p, t;
    cin >> p >> t;
    vector<int> z1 = z_fun(p + "#" + t);
    reverse(p.begin(), p.end());
    reverse(t.begin(), t.end());
    vector<int> z2 = z_fun(p + "#" + t);
    int n = (int) p.size() + (int) t.size() + 1;
    vector<int> in;
    for (int i = p.size() + 1; i < n - (int) p.size() + 1; i++) {
        if (z1[i] + z2[n - i + 1] >= (int) p.size() - 1) {
            in.push_back(i - (int) p.size());
        }
    }
    cout << in.size() << '\n';
    for (auto x : in) {
        cout << x << ' ';
    }
}
