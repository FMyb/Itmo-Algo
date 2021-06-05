#include <bits/stdc++.h>

using namespace std;

struct Num {
    vector<int> a;
    int n;
    int x;

    Num(int x_, int n_) {
        x = x_;
        n = n_;
        while (x_ > 0) {
            a.push_back(x_ % 2);
            x_ /= 2;
        }
        while ((int) a.size() < n) {
            a.push_back(0);
        }
    }

    Num operator+(int other) const {
        return Num(x + other, n);
    }
};

bool check(vector<int> &a) {
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] < a[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> a(k);
    for (int i = 0; i < k; i++) {
        int t;
        cin >> t;
        for (int j = 0; j < t; j++) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            if (x > y) swap(x, y);
            a[i].push_back({x, y});
        }
    }
    Num x(0, n);
    for (int i = 0; i < (1 << n); i++) {
        vector<int> temp = x.a;
        for (int j = 0; j < k; j++) {
            for (size_t g = 0; g < a[j].size(); g++) {
                if (temp[a[j][g].first] > temp[a[j][g].second]) {
                    swap(temp[a[j][g].first], temp[a[j][g].second]);
                }
            }
        }
        if (!check(temp)) {
            cout << "No";
            return 0;
        }
        x = x + 1;
    }
    cout << "Yes";
}
