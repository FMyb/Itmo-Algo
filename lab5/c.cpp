#include <bits/stdc++.h>

#define null NULL

using namespace std;

struct Node {
    long long x;
    long long y;
    int size;
    Node *L;
    Node *R;

    Node(long long x_, long long y_) {
        x = x_;
        y = y_;
        size = 1;
        L = null;
        R = null;
    }
};

int sz(Node *t) {
    if (t == null) return 0;
    return t->size;
}

void update(Node *t) {
    if (t == null) return;
    t->size = sz(t->L) + sz(t->R) + 1;
}

bool find(Node *t, long long x) {
    if (t == null) return false;
    if (t->x == x) return true;
    if (x < t->x) return find(t->L, x);
    else return find(t->R, x);
}

Node *merge(Node *a, Node *b) {
    if (a == null) return b;
    if (b == null) return a;
    if (a->y < b->y) {
        a->R = merge(a->R, b);
        update(a);
        return a;
    } else {
        b->L = merge(a, b->L);
        update(b);
        return b;
    }
}

pair<Node *, Node *> splitk(Node *t, int k) {
    if (t == null) return {null, null};
    if (sz(t->L) <= k) {
        auto r = splitk(t->R, k - sz(t->L) - 1);
        t->R = r.first;
        update(t);
        return {t, r.second};
    } else {
        auto l = splitk(t->L, k);
        t->L = l.second;
        update(t);
        return {l.first, t};
    }
}

pair<Node *, Node *> split(Node *t, long long x) {
    if (t == null) return {null, null};
    if (t->x < x) {
        auto r = split(t->R, x);
        t->R = r.first;
        update(t);
        return {t, r.second};
    } else {
        auto l = split(t->L, x);
        t->L = l.second;
        update(t);
        return {l.first, t};
    }
}

long long min(Node *t) {
    if (t == null) return -1;
    if (t->L == null) return t->x;
    return min(t->L);
}

Node *insertk(Node *t, int x) {
    auto r = splitk(t, x);
    auto n = new Node(x, rand());
    return merge(r.first, merge(n, r.second));
}

void print(Node *t) {
    if (t == null) return;
    print(t->L);
    cout << t->x << ' ';
    print(t->R);
}

int main() {
    int n, m;
    cin >> n >> m;
    Node *t = null;
    for (int i = 1; i <= n; i++) {
        t = insertk(t, i);
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l -= 2;
        r--;
        auto x = splitk(t, r);
        auto y = splitk(x.first, l);
        t = merge(merge(y.second, y.first), x.second);
    }
    print(t);
}
