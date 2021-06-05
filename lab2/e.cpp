#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

char letter(string s, int x) {
    return s[s.size() - x - 1];
}

const int abc = 26;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<string> b(n);
    vector<int> c(abc);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < abc; j++) {
            c[j] = 0;
        }
        for (int j = 0; j < n; j++) {
            assert(letter(a[j], i) >= 'a' && letter(a[j], i) <= 'z');
            int d = letter(a[j], i) - 'a';
            c[d]++;
        }
        int count = 0;
        for (int j = 0; j < abc; j++) {
            int tmp = c[j];
            c[j] = count;
            count += tmp;
        }
        for (int j = 0; j < n; j++) {
            int d = letter(a[j], i) - 'a';
            b[c[d]] = a[j];
            c[d]++;
        }
        a = b;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }
}
