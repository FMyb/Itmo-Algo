#include <vector>
#include <stdio.h>


using namespace std;

struct snm {
    vector<vector<int>> set;
    vector<int> ind;
    vector<int> color;

    snm(int n) {
        set.resize(n);
        ind.resize(n);
        color.resize(n);
        for (int i = 0; i < n; i++) {
            set[i].push_back(i);
            ind[i] = i;
            color[i] = 0;
        }
    }

    int ask(int x, int y) {
        return x == y;
    }

    void union_snm(int x, int y) {
        bool f = false;
        if (color[x] == color[y]) f = true;
        x = ind[x];
        y = ind[y];
        if (set[x].size() < set[y].size()) {
            for (int i : set[x]) {
                set[y].push_back(i);
                if (f) {
                    color[i] = 1 - color[i];
                }
                ind[i] = y;
            }
            set[x].clear();
        } else {
            for (int i : set[y]) {
                set[x].push_back(i);
                ind[i] = x;
                if (f) {
                    color[i] = 1 - color[i];
                }
            }
            set[y].clear();
        }
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    snm s(n);
    int shift = 0;
    for (int i = 0; i < m; i++) {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        int x = (a % n + shift % n) % n;
        int y = (b % n + shift % n) % n;
        if (t == 0) {
            s.union_snm(x, y);
        } else {
            if (s.color[x] == s.color[y]) {
                printf("YES\n");
                shift++;
            } else {
                printf("NO\n");
            }
        }
    }
}
