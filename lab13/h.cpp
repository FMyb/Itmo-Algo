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
        link = vector<Node *>(26);
        suf_link = nullptr;
    }
};

const int INF = 1e9;

Node *root;
Node *cur;
int L, R;
vector<int> s;

bool go_down(int R) {
    int letter = s[R];
    if ((cur->depth == INF ? (int) s.size() : cur->depth) != R - L) {
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
    if ((cur->depth == INF ? (int) s.size() : cur->depth) == R - L) {
        if (cur->link[letter] == nullptr) {
            Node *new_leaf = new Node(INF, R, cur);
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
            while ((cur->depth == INF ? (int) s.size() : cur->depth) < R - L) {
                go_down(L + (cur->depth == INF ? (int) s.size() : cur->depth));
            }
        }
        R++;
    }
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
    no_suf_link = nullptr;
    add();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string str;
    suff_tree(str);
    int t;
    long long result = 0;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> str;
        if (str == "?") {
            bool f = false;
            if ((cur->depth == INF ? (int) s.size() : cur->depth) != R - L) {
                int edgeShift = R - L - cur->parent->depth;
                int letterOnEdge = s[cur->start + edgeShift];
                s.push_back(letterOnEdge);
                f = true;
            } else {
                for (int j = 0; j < 26; j++) {
                    if (cur->link[j] != nullptr) {
                        s.push_back(j);
                        f = true;
                        break;
                    }
                }
            }
            if (!f) {
                s.push_back(0);
            }
            add();
            result += L;
            cout << (char) (s.back() + 'a') << ' ' << result << '\n';
        } else {
            s.push_back(str[0] - 'a');
            add();
            result += L;
        }
    }
}
