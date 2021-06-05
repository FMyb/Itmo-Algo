#include <vector>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <assert.h>

using namespace std;

long long INF = 3000000000;

struct Event {
    int i;
    long long min;
    int k;
    int type;

    Event(int i_, long long min_, int k_, int type_) {
        i = i_;
        min = min_;
        k = k_;
        type = type_;
    }

    bool operator<(const Event other) const {
        if (i == other.i) {
            return type < other.type;
        }
        return i < other.i;
    }
};

struct Node {
    long long val;
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
            if (right < (int) a.size() && a[right] > a[left]) {
                j = right;
            }
            if (a[i] >= a[j]) {
                break;
            }
            swap1(i, j);
            i = j;
        }
    }

    void sift_up(int i) {
        while (a[i] > a[(i - 1) / 2]) {
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

    Node Max() {
        if (a.size() == 0) {
            return {0, 0};
        }
        return a[0];
    }

    void insert(Node val) {
        a.push_back(val);
        pos[val.pos] = a.size() - 1;
        sift_up(a.size() - 1);
    }

    void decreaseKey(int ind, long long val) {
        assert(a[pos[ind]].pos == ind);
        a[pos[ind]].val = val;
        sift_up(pos[ind]);
        sift_down(pos[ind]);
    }

    void del(int ind) {
        int i = pos[ind];
        swap1(pos[ind], a.size() - 1);
        a.pop_back();
        sift_down(i);
        sift_up(i);
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<long long> a(n);
    vector<Event> zap;
    priority_queue1 pq;
    for (int i = 0; i < m; i++) {
        int l, r;
        long long min;
        scanf("%d%d%lld", &l, &r, &min);
        l--;
        r--;
        zap.push_back({l, min, i, 0});
        zap.push_back({r, min, i, 1});
    }
    sort(zap.begin(), zap.end());
    int ind = 0;
    long long last_mn = 0;
    for (int i = 0; i < n; i++) {
        long long mn = -INF;
        while (ind < (int) zap.size() && i > zap[ind].i && zap[ind].type == 1) {
            pq.del(zap[ind].k);
            ind++;
        }
        while (ind < (int) zap.size() && i >= zap[ind].i && zap[ind].type == 0) {
            pq.insert({zap[ind].min, zap[ind].k});
            ind++;
        }
        mn = pq.Max().val;
        if (mn == -INF) {
            a[i] = last_mn;
        } else {
            a[i] = mn;
            last_mn = mn;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%lld ", a[i]);
    }
}
