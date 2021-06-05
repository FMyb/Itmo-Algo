#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(i + 1);
        if (i == 1) continue;
        swap(a[i], a[i / 2]);
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}
