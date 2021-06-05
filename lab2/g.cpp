#include <bits/stdc++.h>

using namespace std;

unsigned int digit(unsigned int x, unsigned int i) {
    if (i == 0) {
        return x % 100000;
    }
    return x / 100000;
}

unsigned int cur = 0;

unsigned int nextRand24(unsigned int a, unsigned int b) {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int nextRand32(unsigned int a1, unsigned int b1) {
    unsigned int a = nextRand24(a1, b1), b = nextRand24(a1, b1);
    return (a << 8) ^ b;
}

void solve(unsigned int n, unsigned int a, unsigned int b) {
    vector<unsigned int> arr(n);
    for (unsigned int i = 0; i < n; i++) {
        arr[i] = nextRand32(a, b);
    }
    vector<unsigned int> brr(n);
    vector<unsigned int> c(100000);
    for (unsigned int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < 100000; j++) {
            c[j] = 0;
        }
        for (unsigned int j = 0; j < n; j++) {
            unsigned int d = digit(arr[j], i);
            c[d]++;
        }
        unsigned int count = 0;
        for (unsigned int j = 0; j < 100000; j++) {
            unsigned int tmp = c[j];
            c[j] = count;
            count += tmp;
        }
        for (unsigned int j = 0; j < n; j++) {
            unsigned int d = digit(arr[j], i);
            brr[c[d]] = arr[j];
            c[d]++;
        }
        arr = brr;
    }
    unsigned long long ans = 0;
    for (unsigned int i = 0; i < n; i++) {
        ans += (unsigned long long) arr[i] * (i + 1);
    }
    cout << ans << '\n';
}

int main() {
    unsigned int t, n;
    cin >> t >> n;
    for (unsigned int i = 0; i < t; i++) {
        unsigned int a, b;
        cin >> a >> b;
        solve(n, a, b);
    }
}
