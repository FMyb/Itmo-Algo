#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n / 2 + 1; i++) {
        if ((2 * i <= n && a[i] > a[2 * i]) || (2 * i + 1 <= n && a[i] > a[2 * i + 1])) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
}
