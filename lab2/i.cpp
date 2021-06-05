#include <bits/stdc++.h>

using namespace std;

struct Node {
    long long a, b, t;

    Node(long long a_, long long b_, long long t_) {
        a = a_;
        b = b_;
        t = t_;
    }
};

void sort(vector<long long> &a, int l, int r) {
    long long key = a[l + rand() % (r - l + 1)];
    int i = l;
    int j = r;
    do {
        while (a[i] < key) i++;
        while (a[j] > key) j--;
        if (i <= j) {
            long long buf = a[i];
            a[i] = a[j];
            a[j] = buf;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) {
        sort(a, l, j);
    }
    if (i < r) {
        sort(a, i, r);
    }
}

bool check(long long m, long long p, int n, vector<Node> &a) {
    long long ans = 0;
    vector<long long> cnt(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i].b + a[i].t > m) {
            cnt[i] = 0;
            continue;
        }
        if (a[i].a == 0) {
            return true;
        } else {
            cnt[i] = 1LL * (m - a[i].b - a[i].t) / a[i].a;
        }
    }
    sort(cnt, 0, (int) cnt.size() - 1);
    reverse(cnt.begin(), cnt.end());
    for (int i = 0; i < min((int) a.size(), n) && cnt[i] > 0; i++) {
        if (cnt[i] >= p) return true;
        ans += cnt[i];
        if (ans >= p) return true;
    }
    return ans >= p;
}

long long bin_find(long long r, int n, long long p, vector<Node> &a) {
    long long l = 0;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (check(m, p, n, a)) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    long long m;
    cin >> m;
    vector<Node> a;
    for (long long i = 0; i < m; i++) {
        long long a1, b, t;
        cin >> a1 >> b >> t;
        a.push_back({a1, b, t});
    }
    int n, p;
    cin >> n >> p;
    if (p == 0) {
        cout << 0;
        return 0;
    }
    long long ans = bin_find(p * a[0].a + a[0].b + a[0].t, n, p, a);
    cout << ans;
}
