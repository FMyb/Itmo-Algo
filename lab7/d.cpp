//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 27.04.2020
//

#include <bits/stdc++.h>

using namespace std;

struct Node {
    long long sum;
    long long add;
    long long min;
    long long max;
};

const size_t N = 500001;
const long long INF = 1e9;

vector<Node> t(4 * (N + 1));
vector<long long> vec(N + 1);

void full(int x, long long l, long long r, long long v) {
    t[x].add += v;
    t[x].sum += (r - l) * v;
    t[x].min += v;
    t[x].max += v;
}

void update(int x) {
    t[x].sum = t[2 * x + 1].sum + t[2 * x + 2].sum;
    t[x].min = min(t[2 * x + 1].min, t[2 * x + 2].min);
    t[x].max = max(t[2 * x + 1].max, t[2 * x + 2].max);
}

void relax(int x, long long l, long long m, long long r) {
    full(2 * x + 1, l, m, t[x].add);
    full(2 * x + 2, m, r, t[x].add);
    t[x].add = 0;
}

void add(int x, long long l, long long r, long long a, long long b, long long v) {
    if (r <= a || b <= l) {
        return;
    }
    if (a <= l && r <= b) {
        full(x, l, r, v);
        return;
    }
    long long m = (l + r) / 2;
    relax(x, l, m, r);
    add(2 * x + 1, l, m, a, b, v);
    add(2 * x + 2, m, r, a, b, v);
    update(x);
}

void update_elem(int x, long long l, long long r, long long i, long long v) {
    if (i < l || i >= r) {
        return;
    }
    if (r - l == 1) {
        t[x].sum = v;
        t[x].min = v;
        t[x].max = v;
        return;
    }
    long long m = (l + r) / 2;
    relax(x, l, m, r);
    update_elem(2 * x + 1, l, m, i, v);
    update_elem(2 * x + 2, m, r, i, v);
    update(x);
}

long long calc_sum(int x, long long l, long long r, long long a, long long b) {
    if (r <= a || b <= l) {
        return 0;
    }
    if (a <= l && r <= b) {
        return t[x].sum;
    }
    long long m = (l + r) / 2;
    relax(x, l, m, r);
    return calc_sum(2 * x + 1, l, m, a, b) + calc_sum(2 * x + 2, m, r, a, b);
}

long long calc_min(int x, long long l, long long r, long long a, long long b) {
    if (r <= a || b <= l) {
        return INF;
    }
    if (a <= l && r <= b) {
        return t[x].min;
    }
    long long m = (l + r) / 2;
    relax(x, l, m, r);
    return min(calc_min(2 * x + 1, l, m, a, b), calc_min(2 * x + 2, m, r, a, b));
}

long long calc_max(int x, long long l, long long r, long long a, long long b) {
    if (r <= a || b <= l) {
        return -INF;
    }
    if (a <= l && r <= b) {
        return t[x].max;
    }
    long long m = (l + r) / 2;
    relax(x, l, m, r);
    return max(calc_max(2 * x + 1, l, m, a, b), calc_max(2 * x + 2, m, r, a, b));
}


Node build(int x, int L, int R) {
    if (R - L == 1) {
        t[x].max = vec[L];
        t[x].min = vec[L];
        t[x].sum = vec[L];
        return t[x];
    }
    int m = (L + R) / 2;
    Node b = build(2 * x + 1, L, m), c = build(2 * x + 2, m, R);
    t[x].max = max(b.max, c.max);
    t[x].min = min(b.min, c.min);
    t[x].sum = b.sum + c.sum;
    return t[x];
}


int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }
    build(0, 0, n);
    string s;
    while (cin >> s) {
        int l, r;
        cin >> l >> r;
        if (s == "set") {
            update_elem(0, 0, n, l - 1, r);
        } else {
            cout << calc_min(0, 0, n, l - 1, r) << '\n';
        }
    }
}
