//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 23.05.2020
//

#include <bits/stdc++.h>

using namespace std;

struct Node {
    int add;
    int max;
    int max_ind;
};

const size_t N = 2000001;
const int INF = 1e9;

vector<Node> t(4 * (N + 1));
vector<int> vec(N + 1);

void full(int x, int v) {
    t[x].add += v;
    t[x].max += v;
}

void update(int x) {
    if (t[2 * x + 1].max > t[2 * x + 2].max) {
        t[x].max = t[2 * x + 1].max;
        t[x].max_ind = t[2 * x + 1].max_ind;
    } else {
        t[x].max = t[2 * x + 2].max;
        t[x].max_ind = t[2 * x + 2].max_ind;
    }
}

void relax(int x) {
    full(2 * x + 1, t[x].add);
    full(2 * x + 2, t[x].add);
    t[x].add = 0;
}

void add(int x, int l, int r, int a, int b, int v) {
    if (r <= a || b <= l) {
        return;
    }
    if (a <= l && r <= b) {
        full(x, v);
        return;
    }
    int m = (l + r) / 2;
    relax(x);
    add(2 * x + 1, l, m, a, b, v);
    add(2 * x + 2, m, r, a, b, v);
    update(x);
}

void update_elem(int x, int l, int r, int i, int v) {
    if (i < l || i >= r) {
        return;
    }
    if (r - l == 1) {
        t[x].max = v;
        t[x].max_ind = l;
        return;
    }
    int m = (l + r) / 2;
    relax(x);
    update_elem(2 * x + 1, l, m, i, v);
    update_elem(2 * x + 2, m, r, i, v);
    update(x);
}

pair<int, int> calc_max(int x, int l, int r, int a, int b) {
    if (r <= a || b <= l) {
        return {-INF, -1};
    }
    if (a <= l && r <= b) {
        return {t[x].max, t[x].max_ind};
    }
    int m = (l + r) / 2;
    relax(x);
    return max(calc_max(2 * x + 1, l, m, a, b), calc_max(2 * x + 2, m, r, a, b));
}


void build(int x, int L, int R) {
    if (R - L == 1) {
        t[x].max = vec[L];
        t[x].max_ind = L;
        return;
    }
    int m = (L + R) / 2;
    build(2 * x + 1, L, m);
    build(2 * x + 2, m, R);
    update(x);
}

struct Inter {
    int x;
    int type;
    int y1;
    int y2;

    bool operator<(const Inter &other) const {
        if (x == other.x) {
            return type < other.type;
        }
        return x < other.x;
    }
};

int main() {
    int n;
    cin >> n;
    vector<Inter> a;
    int maxy = 0;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += 1000000;
        x2 += 1000000;
        y1 += 1000000;
        y2 += 1000000;
        maxy = max(maxy, y2);
        a.push_back({x1, 0, y1, y2});
        a.push_back({x2, 1, y1, y2});
    }
    fill(vec.begin(), vec.end(), 0);
    build(0, 0, maxy + 1);
    sort(a.begin(), a.end());
    int maxim = 0;
    int ansx = 0;
    int ansy = 0;
    for (auto i : a) {
        if (i.type == 0) {
            add(0, 0, maxy + 1, i.y1, i.y2 + 1, 1);
            auto clcmx = calc_max(0, 0, maxy + 1, i.y1, i.y2 + 1);
            if (maxim < clcmx.first) {
                maxim = clcmx.first;
                ansx = i.x;
                ansy = clcmx.second;
            }
        } else {
            add(0, 0, maxy + 1, i.y1, i.y2 + 1, -1);
        }
    }
    cout << maxim << endl << ansx - 1000000 << ' ' << ansy - 1000000;
}
