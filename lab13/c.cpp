#include <bits/stdc++.h>

using namespace std;

struct Node {
    int depth;
    int start;
    Node *parent;
    vector<Node *> link;
    Node *suf_link;
    int ind;

    Node(int depth, int start, Node *parent) : depth(depth), start(start), parent(parent) {
        link = vector<Node *>(27);
        suf_link = nullptr;
    }
};

Node *root;
Node *cur;
int L, R;
vector<int> s;

bool go_down(int R) {
    int letter = s[R];
    if (cur->depth != R - L) {
        int edgeShift = R - L - cur->parent->depth;
        int letterOnEdge = s[cur->start + edgeShift];
        if (letterOnEdge != letter) {
            Node *new_node = new Node(R - L, cur->start, cur->parent);
            cur->parent->link[s[cur->start]] = new_node;
            cur->parent = new_node;
            cur->start += edgeShift;
            new_node->link[letterOnEdge] = cur;
            cur = new_node;
        }
    }
    if (cur->depth == R - L) {
        if (cur->link[letter] == nullptr) {
            Node *new_leaf = new Node(s.size(), R, cur);
            cur->link[letter] = new_leaf;
            cur = new_leaf;
            return true;
        } else {
            cur = cur->link[letter];
        }
    }
    return false;
}

void suff_tree(string &str) {
    s = vector<int>(str.length());
    for (int i = 0; i < (int) str.length(); i++) {
        s[i] = str[i] - 'a';
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

int cnt = 1;
string res;
string str1;

void dfs(Node *v) {
    for (int i = 0; i < (int) v->link.size(); i++) {
        Node *u = v->link[i];
        if (u != nullptr) {
            u->ind = ++cnt;
            res += to_string(v->ind) + ' ' + to_string(u->ind) + ' ' + to_string(u->start + 1) + ' '
                   + to_string(
                    u->start + (u->depth == (int) s.size() ? u->depth - u->start : u->depth - v->depth)) + '\n';
            dfs(u);
        }
    }
}

int main() {
    cin >> str1;
    suff_tree(str1);
    root->ind = cnt;
    dfs(root);
    cout << cnt << ' ' << cnt - 1 << '\n' << res;
}