#include <bits/stdc++.h>

#define null NULL

using namespace std;

struct Node {
    long long x;
    long long y;
    int size;
    Node *L;
    Node *R;
    bool isFree;
    bool isFreeTree;

    Node(long long x_, long long y_) {
        x = x_;
        y = y_;
        size = 1;
        L = null;
        R = null;
        isFree = true;
        isFreeTree = true;
    }
};

int sz(Node *t) {
    if (t == null) return 0;
    return t->size;
}

bool isFreeTree(Node *t) {
    if (t == null) return false;
    return t->isFreeTree;
}

void update(Node *t) {
    if (t == null) return;
    t->size = sz(t->L) + sz(t->R) + 1;
    t->isFreeTree = isFreeTree(t->L) || isFreeTree(t->R) || t->isFree;
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

int countNotFree(Node *t) {
    if (!isFreeTree(t)) {
        return sz(t);
    }
    if (isFreeTree(t->L)) {
        return countNotFree(t->L);
    }
    if (t->isFree) {
        return sz(t->L);
    }
    assert(isFreeTree(t->R));
    if (isFreeTree(t->R)) {
        return countNotFree(t->R) + sz(t->L) + 1;
    }
    return -42;
}

Node *insertk(Node *t, int k, int x, bool f) {
    auto r = splitk(t, k);
    auto n = new Node(x, rand());
    if (f && r.second->x == 0) {
        auto r1 = splitk(r.second, 0);
        return merge(r.first, merge(n, r1.second));
    }
    return merge(r.first, merge(n, r.second));
}

void print(Node *t, vector<long long> &a) {
    if (t == null) return;
    print(t->L, a);
    a.push_back(t->x);
    print(t->R, a);
}

void print(Node *t) {
    if (t == null) return;
    print(t->L);
    cerr << t->x << ' ';
    print(t->R);
}

pair<int, vector<long long>> solve_main(int n, int m, vector<int> &b) {
    Node *t = null;
    for (int i = 0; i < n + m + 1; i++) {
        t = insertk(t, i, 0, false);
    }
    for (int i = 0; i < n; i++) {
        int k;
        k = b[i] - 1;
        auto temp = splitk(t, k - 1);
        Node *find_it = temp.second;
        int size = countNotFree(find_it);
        auto find_it_temp = splitk(find_it, size - 1);
        auto x = splitk(find_it_temp.second, 0);
        assert(isFreeTree(x.first));
        x.first->x = i + 1;
        x.first->isFreeTree = false;
        x.first->isFree = false;
        t = merge(temp.first, merge(merge(x.first, find_it_temp.first), x.second));
    }
    assert(t != null);
    vector<long long> a;
    print(t, a);
    int ans = a.size();
    for (int i = (int) a.size() - 1; i >= 0 && a[i] == 0; i--) {
        ans = i;
    }
    vector<long long> ans1;
    for (int i = 0; i < ans; i++) {
        ans1.push_back(a[i]);
    }
    return {ans, ans1};
}

void start_main() {
    int n, m;
    cin >> n >> m;
    vector<int> b;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b.push_back(x);
    }
    auto x = solve_main(n, m, b);
    cout << x.first << '\n';
    for (int i = 0; i < (int) x.second.size(); i++) {
        cout << x.second[i] << ' ';
    }
}

int main() {
    start_main();
}
