#include <bits/stdc++.h>

#define null NULL

using namespace std;

const int INF = 1e9 + 1;

struct Node {
    long long x;
    long long size;
    Node *L;
    Node *R;
    Node *P;

    Node(long long x_) {
        x = x_;
        size = 1;
        L = null;
        R = null;
        P = null;
    }
};

long long sz(Node *t) {
    if (t == null) return 0;
    return t->size;
}

void update(Node *t) {
    if (t == null) return;
    t->size = max(sz(t->L), sz(t->R)) + 1;
}

pair<Node *, Node *> find(Node *t, long long x, Node *p) {
    if (t == null) return {null, p};
    if (t->x == x) return {t, p};
    if (x < t->x) return find(t->L, x, t);
    else return find(t->R, x, t);
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

long long lower_bound(Node *t, long long x) {
    auto temp1 = find(t, x, null);
    Node *temp = temp1.first;
    if (temp == null || temp->R == null) {
        while (temp1.second != null && x > temp1.second->x) {
            temp = temp1.second;
            temp1.second = temp->P;
        }
        if (temp1.second == null) {
            return INF;
        }
        if (temp1.second->x > x) {
            temp = temp1.second;
            temp1.second = temp->P;
        }
        return temp->x;
    }
    return min(temp->R);
}

long long prev(Node *t, long long x) {
    auto temp1 = find(t, x, null);
    Node *temp = temp1.first;
    if (temp == null || temp->L == null) {
        while (temp1.second != null && temp1.second->x > x) {
            temp = temp1.second;
            temp1.second = temp->P;
        }
        if (temp1.second == null) {
            return INF;
        }
        if (temp1.second->x < x) {
            temp = temp1.second;
            temp1.second = temp->P;
        }
        return temp->x;
    }
    return max(temp->L);
}

Node *smallRotateRight(Node *t) {
    if (t == null) return null;
    Node *temp = t->L;
    if (t->P != null) {
        if (t->P->L == t) {
            t->P->L = temp;
        } else {
            t->P->R = temp;
        }
    }
    temp->P = t->P;
    t->L = temp->R;
    if (t->L != null) {
        t->L->P = t;
    }
    temp->R = t;
    t->P = temp;
    update(t);
    update(temp);
    return temp;
}

Node *smallRotateLeft(Node *t) {
    if (t == null) {
        return null;
    }
    Node *temp = t->R;
    if (t->P != null) {
        if (t->P->L == t) {
            t->P->L = temp;
        } else {
            t->P->R = temp;
        }
    }
    temp->P = t->P;
    t->R = temp->L;
    if (t->R != null) {
        t->R->P = t;
    }
    temp->L = t;
    t->P = temp;
    update(t);
    update(temp);
    return temp;
}

Node *bigRotateRight(Node *t) {
    if (t == null) return t;
    Node *temp = t->L;
    temp = smallRotateLeft(temp);
    t->L = temp;
    return smallRotateRight(t);
}

Node *bigRotateLeft(Node *t) {
    if (t == null) return t;
    Node *temp = t->R;
    temp = smallRotateRight(temp);
    t->R = temp;
    return smallRotateLeft(t);
}


Node *fix(Node *t) {
    if (t == null) {
        return null;
    }
    if (abs(sz(t->L) - sz(t->R)) > 1) {
        if (sz(t->L) + 1 >= sz(t->R)) {
            if (sz(t->L->R) <= sz(t->L->L)) {
                t = smallRotateRight(t);
            } else {
                t = bigRotateRight(t);
            }
        } else {
            if (sz(t->R->L) <= sz(t->R->R)) {
                t = smallRotateLeft(t);
            } else {
                t = bigRotateLeft(t);
            }
        }
    }
    update(t);
    if (t->P == null) {
        return t;
    }
    return fix(t->P);
}

Node *insert(Node *t, long long x) {
    auto temp = find(t, x, null);
    if (temp.first != null) {
        return t;
    }
    if (temp.second == null) {
        return new Node(x);
    }
    if (temp.second->x > x) {
        temp.second->L = new Node(x);
        temp.second->L->P = temp.second;
    } else {
        temp.second->R = new Node(x);
        temp.second->R->P = temp.second;
    }
    return fix(temp.second);
}

void swap1(Node *first, Node *second) {
    swap(first->x, second->x);
}

Node *del(Node *t, long long x) {
    auto temp = find(t, x, null);
    if (temp.first == null) {
        return t;
    }
    if (sz(temp.first) == 1) {
        if (temp.second == null) {
            return null;
        }
        Node *p = temp.second;
        if (temp.second->x < x) {
            temp.second->R = null;
        } else {
            temp.second->L = null;
        }
        t = fix(p);
        return t;
    }
    long long c = lower_bound(t, x);
    long long m = prev(t, x);
    if (c == INF) {
        if (temp.first->P == null) {
            temp.first->L->P = null;
            return temp.first->L;
        } else {
            temp.first->P->R = temp.first->L;
            temp.first->L->P = temp.first->P;
            return fix(temp.first->P);
        }
    }
    if (m == INF) {
        if (temp.first->P == null) {
            temp.first->R->P = null;
            return temp.first->R;
        } else {
            temp.first->P->L = temp.first->R;
            temp.first->R->P = temp.first->P;
            return fix(temp.first->P);
        }
    }
    auto temp1 = find(t, c, null);
    auto temp2 = find(t, m, null);
    if (temp1.first->L == null) {
        swap1(temp.first, temp1.first);
        Node *p = temp1.first->P;
        if (temp1.first->R != null) {
            temp1.first->R->P = p;
        }
        if (p == null) {
            return temp1.first->R;
        }
        if (p->L == temp1.first) {
            p->L = temp1.first->R;
            return fix(p);
        }
        if (p->R == temp1.first) {
            p->R = temp1.first->R;
            return fix(p);
        }
    } else {
        swap1(temp.first, temp2.first);
        Node *p = temp2.first->P;
        if (temp2.first->L != null) {
            temp.first->L->P = p;
        }
        if (p == null) {
            return temp2.first->L;
        }
        if (p->L == temp2.first) {
            p->L = temp2.first->L;
            return fix(p);
        }
        if (p->R == temp2.first) {
            p->R = temp2.first->L;
            return fix(p);
        }
    }
    fix(t);
    return t;
}

void print(Node *t) {
    if (t == null) return;
    print(t->L);
    cerr << t->x << ' ';
    print(t->R);
}

int main() {
    srand(1234);
    string s;
    Node *t = null;
    while (cin >> s) {
        long long x;
        cin >> x;
        if (s == "insert") {
            t = insert(t, x);
        }
        if (s == "delete") {
            t = del(t, x);
        }
        if (s == "exists") {
            if (find(t, x, null).first) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
        if (s == "next") {
            long long a = lower_bound(t, x);
            if (a == INF) cout << "none\n";
            else cout << a << '\n';
        }
        if (s == "prev") {
            long long a = prev(t, x);
            if (a == INF) cout << "none\n";
            else cout << a << '\n';
        }
        if (s == "pr") {
            print(t);
            cerr << '\n';
        }
    }
}


