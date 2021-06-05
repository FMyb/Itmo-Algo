#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = (int) s.size() / 2;
    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        a[i] = (s[i] == 'x' ? 1 : 0);
    }
    map<vector<int>, long long> suf;
    map<vector<int>, long long> pref;
    for (int i = 0; i < (1 << n); i++) {
        vector<int> red;
        vector<int> blue;
        for (int j = 0; j < n; j++) {
            if ((i >> (n - j - 1)) & 1) {
                red.push_back(a[j]);
            } else {
                blue.push_back(a[j]);
            }
        }
        bool f = false;
        for (int j = 0; j < min((int) red.size(), (int) blue.size()); j++) {
            if (red[j] != blue[j]) {
                f = true;
            }
        }
        if (!f) {
            vector<int> c;
            if (red.size() > blue.size()) {
                for (int j = (int) blue.size(); j < (int) red.size(); j++) {
                    c.push_back(red[j]);
                }
            } else {
                for (int j = (int) red.size(); j < (int) blue.size(); j++) {
                    c.push_back(blue[j]);
                }
            }
            suf[c]++;
        }
    }
    for (int i = 0; i < (1 << n); i++) {
        vector<int> red;
        vector<int> blue;
        for (int j = 0; j < n; j++) {
            if ((i >> (n - j - 1)) & 1) {
                red.push_back(a[j + n]);
            } else {
                blue.push_back(a[j + n]);
            }
        }
        bool f = false;
        int delta = abs((int) red.size() - (int) blue.size());
        if (red.size() > blue.size()) {
            for (int j = 0; j < min((int) red.size(), (int) blue.size()); j++) {
                if (red[j + delta] != blue[j]) {
                    f = true;
                }
            }
        } else {
            for (int j = 0; j < min((int) red.size(), (int) blue.size()); j++) {
                if (red[j] != blue[j + delta]) {
                    f = true;
                }
            }
        }
        if (!f) {
            vector<int> c;
            if (red.size() > blue.size()) {
                for (int j = 0; j < delta; j++) {
                    c.push_back(red[j]);
                }
            } else {
                for (int j = 0; j < delta; j++) {
                    c.push_back(blue[j]);
                }
            }
            pref[c]++;
        }
    }
    long long ans = 0;
    for (const auto& u : suf) {
        if (!u.first.empty()) {
            ans += (u.second * pref[u.first]) / 2;
        } else {
            ans += (u.second * pref[u.first]);
        }
    }
    cout << ans;
}
