//
// Created by Yarolsav Ilin CT ITMO M3238 on 07.03.2021.
//

#include <bits/stdc++.h>

using namespace std;

const int k = 26;
struct Node {
    Node *son[k];
    Node *go[k];
    Node *parent;
    Node *suff_link;
    Node *up;
    char par;
    bool leaf;
    vector<int> leaf_num;
};

Node *root;

Node *get_sufflink(Node *v);

Node *get_link(Node *v, char c) {
    int b = (int) c;
    if (v->go[b] == NULL) {
        if (v->son[b]) {
            v->go[b] = v->son[b];
        } else if (v == root) {
            v->go[b] = root;
        } else {
            v->go[b] = get_link(get_sufflink(v), (char) b);
        }
    }
    return v->go[b];

}

Node *get_sufflink(Node *v) {
    if (v->suff_link == NULL) {
        if (v == root || v->parent == root) {
            v->suff_link = root;
        } else {
            v->suff_link = get_link(get_sufflink(v->parent), v->par);
        }
    }
    return v->suff_link;
}

Node *up(Node *v) {
    if (v->up == NULL) {
        Node *sufflink = get_sufflink(v);
        if (sufflink->leaf) {
            v->up = sufflink;
        } else if (sufflink == root) {
            v->up = root;
        } else {
            v->up = up(sufflink);
        }
    }
    return v->up;
}

void add(string &s, int num) {
    Node *cur = root;
    for (char b : s) {
        int c = ((int) b) - 97;
        if (cur->son[c] == NULL) {
            cur->son[c] = new Node();
            cur->son[c]->suff_link = NULL;
            cur->son[c]->up = NULL;
            cur->son[c]->parent = cur;
            cur->son[c]->par = (char) c;
            cur->son[c]->leaf = false;
        }
        cur = cur->son[c];
    }
    cur->leaf = true;
    cur->leaf_num.push_back(num);
}

void proc(string &t, vector<bool> &ans) {
    Node *cur = root;
    for (char i : t) {
        int c = i - 97;
        cur = get_link(cur, (char) c);
        Node *a = cur;
        bool is_end = false;
        while (a != root){
            if (!a->leaf_num.empty()) {
                for (auto u: a->leaf_num) {
                    if (ans[u]) {
                        is_end = true;
                        break;
                    }
                    ans[u] = true;
                }
            }
            if (is_end) {
                break;
            }
            a = up(a);
        }
    }
}

int main() {
    int n;
    cin >> n;
    root = new Node();
    root->suff_link = NULL;
    root->up = NULL;
    root->parent = root;
    root->leaf = false;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        add(s, i);
    }
    string t;
    cin >> t;
    vector<bool> ans(n);
    proc(t, ans);
    for (auto b : ans) {
        cout << (b ? "YES\n" : "NO\n");
    }
}
