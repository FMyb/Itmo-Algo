#include <iostream>
#include <vector>

using namespace std;

int right_find(vector<int> &a, int val) {
    int l = 0;
    int r = a.size();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (a[m] <= val) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int left_find(vector<int> &a, int val) {
    int l = -1;
    int r = a.size() - 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (a[m] >= val) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        int l = left_find(a, x);
        int r = right_find(a, x);
        if (a[l] != x) {
            cout << -1 << ' ' << -1 << '\n';
            continue;
        }
        cout << l + 1 << ' ' << r + 1 << '\n';
    }
}
