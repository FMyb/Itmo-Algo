#include <vector>
#include <stdio.h>
#include <assert.h>

using namespace std;

struct snm {
    vector<vector<int>> set;
    vector<int> ind;
    vector<int> message;
    vector<int> cnt;

    snm(int n) {
        set.resize(n);
        ind.resize(n);
        message.resize(n);
        cnt.resize(n);
        for (int i = 0; i < n; i++) {
            set[i].push_back(i);
            ind[i] = i;
            message[i] = 0;
            cnt[i] = 0;
        }
    }

    int ask(int x, int y) {
        return x == y;
    }

    int read(int x) {
        int ans = cnt[ind[x]] - message[x];
        assert(ans >= 0);
        message[x] = cnt[ind[x]];
        return ans;
    }

    void add(int x) {
        cnt[ind[x]]++;
    }

    bool union_snm(int x, int y) {
        x = ind[x];
        y = ind[y];
        if (x == y) {
            return false;
        }
        if (set[x].size() < set[y].size()) {
            for (int i : set[x]) {
                set[y].push_back(i);
                message[i] += cnt[y] - cnt[x];
                ind[i] = y;
            }
            set[x].clear();
        } else {
            for (int i : set[y]) {
                set[x].push_back(i);
                message[i] += cnt[x] - cnt[y];
                ind[i] = x;
            }
            set[y].clear();
        }
        return true;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    snm s(n);
    int p = 1000003;
    int zerg = 0;
    for (int i = 0; i < m; i++) {
        int t, x;
        scanf("%d%d", &t, &x);
        if (t == 1) {
            s.add((x + zerg) % n);
            zerg = (30 * zerg + 239) % p;
        }
        if (t == 2) {
            int y;
            scanf("%d", &y);
            if (s.union_snm((x + zerg) % n, (y + zerg) % n)) {
                zerg = (13 * zerg + 11) % p;
            }
        }
        if (t == 3) {
            int q = s.read((x + zerg) % n);
            printf("%d\n", q);
            zerg = ((int) ((1LL * 100500 * zerg) % p) + q) % p;
        }
    }
}
