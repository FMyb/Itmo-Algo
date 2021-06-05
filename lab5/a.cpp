#include <bits/stdc++.h>

#define null NULL

using namespace std;

const int INF = 1e9 + 1;

struct Node {
    long long x;
    long long y;
    long long size;
    Node *L;
    Node *R;
    Node *P;

    Node(long long x_, long long y_) {
        x = x_;
        y = y_;
        size = 1;
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
        return a;
    } else {
        b->L = merge(a, b->L);
        return b;
    }
}

pair<Node *, Node *> split(Node *t, long long x) {
    if (t == null) return {null, null};
    if (t->x < x) {
        auto r = split(t->R, x);
        t->R = r.first;
        return {t, r.second};
    } else {
        auto l = split(t->L, x);
        t->L = l.second;
        return {l.first, t};
    }
}

long long min(Node *t) {
    if (t == null) return INF;
    if (t->L == null) return t->x;
    return min(t->L);
}

long long max(Node *t) {
    if (t == null) return -INF;
    if (t->R == null) return t->x;
    return max(t->R);
}

pair<Node *, long long> lower_bound(Node *t, long long x) {
    auto r = split(t, x + 1);
    long long ans = min(r.second);
    t = merge(r.first, r.second);
    return {t, ans};
}

pair<Node *, long long> prev(Node *t, int x) {
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
    } else {
        t->R = del(t->R, x);
    }
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

void print_node(Node *t, map<pair<int, int>, int> &m, int i, vector<vector<int>> &ans) {
    if (t == null) ans[i].push_back(-1);
    else ans[i].push_back(m[{t->x, t->y}]);
}

void print(Node *t, Node *p, map<pair<int, int>, int> &m, vector<vector<int>> &ans) {
    if (t == null) return;
    int i = m[{t->x, t->y}];
    print(t->L, t, m, ans);
    print_node(p, m, i, ans);
    print_node(t->L, m, i, ans);
    print_node(t->R, m, i, ans);
    print(t->R, t, m, ans);
}

long long my_random() {
    return (rand() << 16) + rand();
}

int main() {
    srand(1234);
    string s;
    Node *t = null;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert") {
            t = insert(t, x, my_random());
        }
        if (s == "delete") {
            t = del(t, x);
        }
        if (s == "exists") {
            if (find(t, x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
        if (s == "next") {
            auto a = lower_bound(t, x);
            t = a.first;
            if (a.second == INF) cout << "none\n";
            else cout << a.second << '\n';
        }
        if (s == "prev") {
            auto a = prev(t, x);
            t = a.first;
            if (a.second == -INF) cout << "none\n";
            else cout << a.second << '\n';
        }
    }
}
