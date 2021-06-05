#include <bits/stdc++.h>
#include <ostream>

using namespace std;

struct Node {
    int val;
    int pos;

    bool operator<(const Node &rhs) const {
        return val < rhs.val;
    }

    bool operator>(const Node &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Node &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Node &rhs) const {
        return !(*this < rhs);
    }

    friend ostream &operator<<(ostream &os, const Node &node) {
        if (node.pos == -1) {
            os << '*';
        } else {
            os << node.val << ' ' << node.pos;
        }
        return os;
    }
};

struct priority_queue1 {
    vector<Node> a;
    map<int, int> pos;

    void swap1(int i, int j) {
        pos[a[i].pos] = j;
        pos[a[j].pos] = i;
        swap(a[i], a[j]);
    }

    void sift_down(int i) {
        while (2 * i + 1 < (int) a.size()) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int j = left;
            if (right < (int) a.size() && a[right] < a[left]) {
                j = right;
            }
            if (a[i] <= a[j]) {
                break;
            }
            swap1(i, j);
            i = j;
        }
    }

    void sift_up(int i) {
        while (a[i] < a[(i - 1) / 2]) {
            swap1(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    Node extractMin() {
        if ((int) a.size() == 0) {
            return Node{-1, -1};
        }
        Node min = a[0];
        swap1(0, a.size() - 1);
        a.pop_back();
        sift_down(0);
        return min;
    }

    void insert(Node val) {
        a.push_back(val);
        pos[val.pos] = a.size() - 1;
        sift_up(a.size() - 1);
    }

    void decreaseKey(int ind, int val) {
        assert(a[pos[ind]].pos == ind);
        a[pos[ind]].val = val;
        sift_up(pos[ind]);
        sift_down(pos[ind]);
    }
};

int main() {
    string s;
    priority_queue1 pq;
    int i = 0;
    while (cin >> s) {
        i++;
        if (s == "push") {
            int x;
            cin >> x;
            pq.insert({x, i});
        } else if (s == "extract-min") {
            cout << pq.extractMin() << '\n';
        } else {
            int ind, val;
            cin >> ind >> val;
            pq.decreaseKey(ind, val);
        }
    }
}
