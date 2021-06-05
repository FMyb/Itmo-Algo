#include <bits/stdc++.h>

#define null NULL

using namespace std;

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
    if (t == null) return -1;
    if (t->L == null) return t->x;
    return min(t->L);
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

int main() {
    long long n;
    cin >> n;
    Node *t = null;
    map<pair<int, int>, int> m;
    vector<Node *> arr((size_t) n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        arr[i] = new Node(x, y);
        m[{x, y}] = i;
    }
    sort(arr.begin(), arr.end(), cmp);
    t = build(arr);
    vector<vector<int>> ans((size_t) n);
    print(t, null, m, ans);
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (auto u : ans[i]) {
            cout << u + 1 << ' ';
        }
        cout << '\n';
    }
}
