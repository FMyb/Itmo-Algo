#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int depth;
    int start;
    Node *parent;
    vector<Node *> link;
    Node *suf_link;

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

Node *no_suf_link;

void add() {
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

void suff_tree(string &str) {
    s = vector<int>(str.length());
    for (int i = 0; i < (int) str.length(); i++) {
        s[i] = tolower(str[i]) - 'a' + 1;
    }
    L = 0;
    R = 0;
    root = new Node(0, -1, nullptr);
    cur = root;
    root->suf_link = root;
    no_suf_link = nullptr;
    add();
}

bool find(string &str) {
    Node *v = root;
    int i = 0;
    while (i < (int) str.size()) {
        if (v == nullptr) {
            return false;
        }
        Node *u = v->link[tolower(str[i]) - 'a' + 1];
        if (u == nullptr) {
            return false;
        } else {
            for (int j = 0; j < u->depth - v->depth; j++) {
                if (tolower(str[i]) - 'a' + 1 == s[u->start + j]) {
                    i++;
                    if (i == (int) str.size()) {
                        return true;
                    }
                } else {
                    return false;
                }
            }
            v = u;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string q;
    string str;
    suff_tree(str);
    while (cin >> q) {
        cin >> str;
        if (q == "?") {
            cout << (find(str) ? "YES" : "NO") << '\n';
        } else {
            for (auto u : str) {
                s.push_back(tolower(u) - 'a' + 1);
            }
            add();
        }
    }
}
