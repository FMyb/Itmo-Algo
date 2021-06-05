#include <bits/stdc++.h>

using namespace std;

struct Node {
    int depth;
    int start;
    Node *parent;
    vector<Node *> link;
    Node *suf_link;

    Node(int depth, int start, Node *parent) : depth(depth), start(start), parent(parent) {
        link = vector<Node *>(11);
        suf_link = nullptr;
    }
};

Node *root;
Node *cur;
int L, R;
vector<int> s;

bool go_down(int r) {
    int letter = s[r];
    if (cur->depth != r - L) {
        int edgeShift = r - L - cur->parent->depth;
        int letterOnEdge = s[cur->start + edgeShift];
        if (letterOnEdge != letter) {
            Node *new_node = new Node(r - L, cur->start, cur->parent);
            cur->parent->link[s[cur->start]] = new_node;
            cur->parent = new_node;
            cur->start += edgeShift;
            new_node->link[letterOnEdge] = cur;
            cur = new_node;
        }
    }
    if (cur->depth == r - L) {
        if (cur->link[letter] == nullptr) {
            Node *new_leaf = new Node(s.size(), r, cur);
            cur->link[letter] = new_leaf;
            cur = new_leaf;
            return true;
        } else {
            cur = cur->link[letter];
        }
    }
    return false;
}

void suff_tree(vector<int> &str) {
    s = vector<int>(str.size() + 1);
    for (int i = 0; i < (int) str.size(); i++) {
        s[i] = str[i];
    }
    L = 0;
    R = 0;
    root = new Node(0, -1, nullptr);
    cur = root;
    root->suf_link = root;
    Node *no_suf_link = nullptr;
    while (R < (int) s.size()) {
        while (L <= R) {
            bool created = go_down(R);
            if (no_suf_link != nullptr) {
                no_suf_link->suf_link = cur->parent;
                no_suf_link = nullptr;
            }
            if (!created) {
                break;
            }
            cur = cur->parent;
            if (cur->suf_link == nullptr) {
                no_suf_link = cur;
                cur = cur->parent;
            }
            cur = cur->suf_link;
            L++;
            while (cur->depth < R - L) {
                go_down(L + cur->depth);
            }
        }
        R++;
    }
}

int n;

Node *mx;
long long mxs = -1;

long long dfs(Node *v) {
    if (v->depth == (int) s.size()) {
        if (v->depth - v->start - 1 + v->parent->depth > mxs) {
            mxs = v->depth - v->start - 1 + v->parent->depth;
            mx = v;
        }
        return 1;
    }
    long long sm = 0;
    for (auto u : v->link) {
        if (u != nullptr) {
            sm += dfs(u);
        }
    }
    if (mxs < sm * v->depth) {
        mxs = sm * v->depth;
        mx = v;
    }
    return sm;
}

int main() {
    int m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    suff_tree(a);
    dfs(root);
    cout << mxs << '\n' << (mx->depth == (int) s.size() ? mxs : mx->depth) << '\n';
    vector<long long> ans;
    while (mx != root) {
        vector<long long> tmp;
        for (int i = 0; i < (mx->depth == (int) s.size() ? mx->depth - mx->start - 1 : mx->depth - mx->parent->depth); i++) {
            tmp.push_back(a[mx->start + i]);
        }
        for (int i = (int) tmp.size() - 1; i >= 0; i--) {
            ans.push_back(tmp[i]);
        }
        mx = mx->parent;
    }
    reverse(ans.begin(), ans.end());
    for (auto u : ans) {
        cout << u << ' ';
    }
}
