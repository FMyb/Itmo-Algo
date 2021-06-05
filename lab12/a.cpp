//
// Created by Yarolsav Ilin CT ITMO M3238 on 20.02.2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    string s, t;
    cin >> t >> s;
    vector<int> in;
    for (size_t i = 0; i < s.size(); i++) {
        bool f = true;
        for (size_t j = 0; j < t.size(); j++) {
            if (s[i + j] != t[j]) {
                f = false;
                break;
            }
        }
        if (f) {
            in.push_back(i);
        }
    }
    cout << in.size() << '\n';
    for (auto x : in) {
        cout << x + 1 << ' ';
    }
}
