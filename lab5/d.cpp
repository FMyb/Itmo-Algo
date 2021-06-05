#include <bits/stdc++.h>

#define null NULL

using namespace std;

const long long INF = 1e9;

struct Node {
    long long x;
    long long y;
    long long size;
    long long sum;
    Node *L;
    Node *R;
    Node *P;

    Node(long long x_, long long y_) {
        x = x_;
        y = y_;
        size = 1;
        sum = x;
        L = null;
        R = null;
        P = null;
    }
};

bool cmp(Node *a, Node *b) {
    return a->x > b->x;
}

long long sz(Node *t) {
    if (t == null) return 0;
    return t->size;
}

long long sm(Node *t) {
    if (t == null) return 0;
    return t->sum;
}

void update(Node *t) {
    if (t == null) return;
    t->size = sz(t->L) + sz(t->R) + 1;
    t->sum = t->x + sm(t->L) + sm(t->R);
}

bool find(Node *t, long long x) {
    if (t == null) return false;
    if (t->x == x) return true;
    if (x < t->x) return find(t->L, x);
    else return find(t->R, x);
}

long long find_k(Node *t, long long k) {
    if (t == null) return -1;
    if (sz(t->L) == k - 1) return t->x;
    if (sz(t->L) < k) {
        return find_k(t->R, k - sz(t->L) - 1);
    } else {
        return find_k(t->L, k);
    }
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

long long max(Node *t) {
    if (t == null) return -INF;
    if (t->R == null) return t->x;
    return max(t->R);
}

long long min(Node *t) {
    if (t == null) return INF;
    if (t->L == null) return t->x;
    return min(t->L);
}

pair<Node *, long long> sum(Node *t, long long l, long long r) {
    if (t == null) return {null, 0};
    if (max(t) < l) return {t, 0};
    if (min(t) > r) return {t, 0};
    auto u = split(t, r + 1);
    auto v = split(u.first, l);
    long long ans = sm(v.second);
    return {merge(merge(v.first, v.second), u.second), ans};
}

pair<Node *, long long> lower_bound(Node *t, long long x) {
    auto r = split(t, x + 1);
    long long ans = min(r.second);
    t = merge(r.first, r.second);
    return {t, ans};
}

pair<Node *, long long> prev(Node *t, long long x) {
    auto r = split(t, x);
    long long ans = max(r.first);
    t = merge(r.first, r.second);
    return {t, ans};
}

Node *insert(Node *t, long long x, long long y) {
    if (!find(t, x)) {
        Node *n = new Node(x, y);
        auto r = split(t, x);
        return merge(merge(r.first, n), r.second);
    } else {
        return t;
    }
}

Node *del(Node *t, long long x) {
    if (t == null) return null;
    if (t->x == x) {
        return merge(t->L, t->R);
    }
    if (t->x > x) {
        t->L = del(t->L, x);
        update(t->L);
    } else {
        t->R = del(t->R, x);
        update(t->L);
    }
    update(t);
    return t;
}

Node *build(vector<Node *> arr) {
    stack<Node *> st;
    Node *root = null;
    for (Node *v : arr) {
        Node *pref = null;
        while (!st.empty() && st.top()->y > v->y) {
            pref = st.top();
            st.pop();
        }
        v->R = pref;
        if (st.empty()) {
            st.push(v);
            root = v;
        } else {
            st.top()->L = v;
            st.push(v);
        }
    }
    return root;
}

long long my_random() {
    return (rand() << 16) + rand();
}

int main() {
    int n;
    cin >> n;
    Node *t = null;
    for (int i = 0; i < n; i++) {
        int c, k;
        cin >> c >> k;
        if (c == -1) {
            t = del(t, k);
        }
        if (c == 0) {
            cout << find_k(t, sz(t) - k + 1) << '\n';
        }
        if (c == 1) {
            t = insert(t, k, my_random());
        }
    }
}
