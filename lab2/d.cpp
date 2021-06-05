#include <iostream>
#include <vector>

using namespace std;

bool check(int n, long double a, long double a1) {
    vector<long double> arr(n);
    arr[0] = a;
    arr[1] = a1;
    long double mn = min(a, a1);
    for (int i = 2; i < n; i++) {
        arr[i] = 2 * arr[i - 1] + 2 - arr[i - 2];
        mn = min(arr[i], mn);
    }
    return mn <= 0;
}

long double find(int n, long double a) {
    long double l = 0, r = a;
    for (int k = 0; k < 100; k++) {
        long double m = (l + r) / 2;
        if (check(n, a, m)) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    int n;
    long double a;
    cin >> n >> a;
    vector<long double> arr(n);
    arr[0] = a;
    arr[1] = find(n, a);
    for (int i = 2; i < n; i++) {
        arr[i] = 2 * arr[i - 1] + 2 - arr[i - 2];
    }
    cout << fixed << arr[n - 1];
}
