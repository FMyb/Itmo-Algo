#include <bits/stdc++.h>

using namespace std;

void rec(int it, int n, int cur, int W, vector<int> &w, map<int, int> &mp) {
    if (it == n || cur > W) {
        if (cur <= W) {
            mp[cur]++;
        }
        return;
    }
    rec(it + 1, n, cur + w[it], W, w, mp);
    rec(it + 1, n, cur, W, w, mp);
}

const int INF = (1 << 30) + 2;

int main() {
    int n;
    cin >> n;
    int ln = n / 2;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    int C;
    cin >> C;
    if (n == 1) {
        if (w[0] > C) {
            cout << 1;
        } else {
            cout << 2;
        }
        return 0;
    }
    map<int, int> left;
    map<int, int> right;
    rec(0, ln, 0, C, w, left);
    rec(ln, n, 0, C, w, right);
    vector<pair<int, int>> lv;
    vector<pair<int, int>> rv;
    for (auto u : left) {
        lv.push_back(u);
    }
    for (auto u : right) {
        rv.push_back(u);
    }
    sort(lv.begin(), lv.end());
    sort(rv.begin(), rv.end());
    vector<int> sm(rv.size());
    sm[0] = rv[0].second;
    for (int i = 1; i < (int) rv.size(); i++) {
        sm[i] = sm[i - 1] + rv[i].second;
    }
    int ans = 0;
    for (int i = 0; i < (int) lv.size(); i++) {
        pair<int, int> tmp = {C - lv[i].first, INF};
        auto it = upper_bound(rv.begin(), rv.end(), tmp);
        ans += sm[(--it) - rv.begin()] * lv[i].second;
    }
    cout << ans;
}
