//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 25.05.2020
//

#include <bits/stdc++.h>

using namespace std;

unsigned a, b;
unsigned cur = 0;

unsigned nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    vector<unsigned> arr((1 << 24) + 2);
    vector<unsigned> pref((1 << 24) + 2);
    unsigned m, q;
    cin >> m >> q;
    cin >> a >> b;

    for (unsigned i = 0; i < m; i++) {
        unsigned add = nextRand();
        unsigned l = nextRand() + 1;
        unsigned r = nextRand() + 1;
        if (l > r) {
            swap(l, r);
        }
        arr[l] += add;
        arr[r + 1] -= add;
    }
    unsigned temp = 0;
    for (unsigned i = 1; i < arr.size(); i++) {
        temp += arr[i];
        pref[i] = pref[i - 1] + temp;
    }
    unsigned ans = 0;
    for (unsigned i = 0; i < q; i++) {
        unsigned l = nextRand() + 1;
        unsigned r = nextRand() + 1;
        if (l > r) {
            swap(l, r);
        }
        ans += pref[r] - pref[l - 1];
    }
    cout << ans;
}
