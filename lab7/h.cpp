//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 24.05.2020
//

#include <bits/stdc++.h>

using namespace std;

struct Node {
    int sum;
};

const size_t N = 500001;
const int INF = 1e9;

vector<Node> t(4 * (N + 1));
vector<int> vec(N + 1);

void update(int x) {
    t[x].sum = t[2 * x + 1].sum + t[2 * x + 2].sum;
}

void update_elem(int x, int l, int r, int i, int v) {
    if (i < l || i >= r) {
        return;
    }
    if (r - l == 1) {
        t[x].sum = 1 - v;
        return;
    }
    int m = (l + r) / 2;
    update_elem(2 * x + 1, l, m, i, v);
    update_elem(2 * x + 2, m, r, i, v);
    update(x);
}

int calc_sum(int x, int l, int r, int a, int b) {
    if (r <= a || b <= l) {
        return 0;
    }
    if (a <= l && r <= b) {
        return t[x].sum;
    }
    int m = (l + r) / 2;
    return calc_sum(2 * x + 1, l, m, a, b) + calc_sum(2 * x + 2, m, r, a, b);
}

int find_kth(int x, int l, int r, int k) {
    if (k > t[x].sum)
        return -1;
    if (l == r - 1)
        return l;
    int m = (l + r) / 2;
    if (t[2 * x + 1].sum >= k)
        return find_kth(2 * x + 1, l, m, k);
    else
        return find_kth(2 * x + 2, m, r, k - t[2 * x + 1].sum);
}

void build(int x, int l, int r) {
    if (r - l == 1) {
        t[x].sum = 1 - vec[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * x + 1, l, m);
    build(2 * x + 2, m, r);
    update(x);
}

int main() {
    int n, m;
    cin >> n >> m;
    fill(vec.begin(), vec.end(), 0);
    build(0, 0, n);
    for (int i = 0; i < m; i++) {
        int pos;
        string s;
        cin >> s >> pos;
        if (s == "enter") {
            int x = calc_sum(0, 0, n, 0, pos - 1);
            int ind = find_kth(0, 0, n, x + 1);
            if (ind == -1) {
                ind = find_kth(0, 0, n, 1);
            }
            cout << ind + 1 << endl;
            update_elem(0, 0, n, ind, 1);
        } else {
            update_elem(0, 0, n, pos - 1, 0);
        }
    }
}
