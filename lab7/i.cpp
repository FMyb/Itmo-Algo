//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 29.05.2020
//

#include <bits/stdc++.h>

using namespace std;

int K;

struct item {
    int l;
    int r;
    int index;

    bool operator<(const item &other) const {
        if (l / K == other.l / K) {
            return r < other.r;
        }
        return l < other.l;
    }
};

long long add(int ind, long long ans, vector<int> &a, vector<int> &cnt) {
    ans -= 1LL * a[ind] * cnt[a[ind]] * cnt[a[ind]];
    cnt[a[ind]]++;
    ans += 1LL * a[ind] * cnt[a[ind]] * cnt[a[ind]];
    return ans;
}

long long del(int ind, long long ans, vector<int> &a, vector<int> &cnt) {
    ans -= 1LL * a[ind] * cnt[a[ind]] * cnt[a[ind]];
    cnt[a[ind]]--;
    ans += 1LL * a[ind] * cnt[a[ind]] * cnt[a[ind]];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    K = (int) sqrt(n);
    int l = 1;
    int r = 0;
    vector<item> quest;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        quest.push_back({--u, --v, i});
    }
    sort(quest.begin(), quest.end());
    vector<long long> result(m);
    vector<int> cnt(1000001);
    long long ans = 0;
    for (auto &i : quest) {
        while (l > i.l) {
            ans = add(--l, ans, a, cnt);
        }
        while (r < i.r) {
            ans = add(++r, ans, a, cnt);
        }
        while (l < i.l) {
            ans = del(l++, ans, a, cnt);
        }
        while (r > i.r) {
            ans = del(r--, ans, a, cnt);
        }
        result[i.index] = ans;
    }
    for (int i = 0; i < m; i++) {
        cout << result[i] << '\n';
    }
}
