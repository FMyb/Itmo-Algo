#include <bits/stdc++.h>

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

void suff_tree(string &str) {
    s = vector<int>(str.length() + 1);
    for (int i = 0; i < (int) str.length(); i++) {
        s[i] = str[i] - 'a' + 1;
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

void dfs(Node *v, vector<int> &a, int pdepth) {
    if (v->depth == (int) s.size()) {
        int elength = (int) s.size() - v->start;
        int ldepth = pdepth + elength;
        a.push_back((int) s.size() - ldepth);
        return;
    }
    for (auto u : v->link) {
        if (u != nullptr) {
            dfs(u, a, v->depth);
        }
    }
}

vector<int> convert() {
    vector<int> lists;
    dfs(root, lists, -1);
    vector<int> ans(lists.size());
    for (int i = 0; i < (int) ans.size(); i++) {
        ans[i] = lists[i];
    }
    return ans;
}

vector<int> lcp(string &str, vector<int> &suff) {
    int n = str.size();
    vector<int> lcp(n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[suff[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (k > 0) {
            k--;
        }
        if (pos[i] == n - 1) {
            lcp[n - 1] = -1;
            k = 0;
            continue;
        } else {
            int j = suff[pos[i] + 1];
            while (max(i + k, j + k) < n && str[i + k] == str[j + k]) {
                k++;
            }
            lcp[pos[i]] = k;
        }
    }
    return lcp;
}

int main() {
    string str;
    cin >> str;
    int n = str.size();
    suff_tree(str);
    vector<int> suff = convert();
    suff.erase(suff.begin());
//    for (auto u : suff) {
//        cout << u + 1 << ' ';
//    }
//    cout << '\n';
    vector<int> ans = lcp(str, suff);
//    for (int i = 0; i < (int) ans.size() - 1; i++) {
//        cout << ans[i] << ' ';
//    }
    long long sm = 0;
    for (int i = 0; i < (int) suff.size(); i++) {
        sm += n - suff[i];
    }
    for (int i = 0; i < (int) ans.size() - 1; i++) {
        sm -= ans[i];
    }
    cout << sm;
}
