#include <bits/stdc++.h>

using namespace std;

struct Node {
    map<char, Node*> child;
    int ind;

    Node(int ind) : ind(ind) {}
};

Node *root;

int cntv = 0;

void add(const string& s) {
    Node *cur = root;
    for (auto c : s) {
        if (cur->child[c] == nullptr) {
            cur->child[c] = new Node(cntv++);
        }
        cur = cur->child[c];
    }
}

void build(const string& s) {
    root = new Node(cntv++);
    int n = s.size();
    for (int i = 0; i < n; i++) {
        add(s.substr(i, n));
    }
}

void dfs(Node *v) {
    for (auto u: v->child) {
        cout << v->ind + 1 << ' ' << u.second->ind + 1 << ' ' << u.first << '\n';
        dfs(u.second);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    build(s);
    cout << cntv << ' ' << cntv - 1 << '\n';
    dfs(root);
}
