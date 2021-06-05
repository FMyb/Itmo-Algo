//
// Created by Yarolsav Ilin CT ITMO M3238 on 23.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

const int maxN = 100001;
const int p = 29;

int getHash(vector<int> &h, int L, int R) {
    long result = h[R];
    if (L > 0) result -= h[L - 1];
    return result;
}

int main() {
    vector<int> pow(maxN);
    pow[0] = 1;
    for (int i = 1; i <= maxN; i++) {
        pow[i] = pow[i - 1] * p;
    }
    string s;
    cin >> s;
    int n = s.size();
    vector<int> h(n);
    h[0] = s[0];
    for (int i = 1; i < n; i++) {
        h[i] = (h[i - 1] + pow[i] * s[i]);
    }
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--;
        b--;
        c--;
        d--;
        if (b - a == d - c && getHash(h, a, b) * pow[c] == getHash(h, c, d) * pow[a]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
