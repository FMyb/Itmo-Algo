#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int kth_element(int k, int l, int r, vector<int> &a) {
//    if (r - l == 1) {
//        if (k == 0) {
//            return min(a[l], a[r]);
//        } else {
//            return max(a[l], a[r]);
//        }
//    }
//    default_random_engine generator;
//    uniform_int_distribution<int> distribution(l, r);
//    int dice_roll = distribution(generator);
//    int x = a[l + rand() % (r - l + 1)];
    if (r <= l && r == k) {
        return a[r];
    }
    int i = l;
    int j = r + 1;
//    while (i <= j) {
//        if (a[i] < x) i++;
//        else if (a[j] > x) j--;
//        else {
//            if (a[i] > a[j]) {
//                swap(a[i], a[j]);
//            }
//            i++;
//            j--;
//        }
//    }

    while (true) {
        while (a[++i] < a[l]) {
            if (i == r) break;
        }
        while (a[--j] > a[l]) {
            if (j == l) break;
        }
        if (i >= j) break;
        swap(a[i], a[j]);
    }
    swap(a[l], a[j]);
//    if (i - l >= k) {
//        return kth_element(k, l, i, a);
//    } else {
//        return kth_element(k - (i - l + 1), i + 1, r, a);
//    }
    if (j == k) {
        return a[k];
    }
    if (j < k) {
        return kth_element(k, j + 1, r, a);
    }
    if (j > k) {
        return kth_element(k, l, j - 1, a);
    }
    return -1;
}

int solve1(int n, int k, int A, int B, int C, int a1, int a2) {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
//    int n, k;
//    cin >> n >> k;
//    int A, B, C, a1, a2;
//    cin >> A >> B >> C >> a1 >> a2;
    vector<int> a(n);
    if (n == 1) {
//        cout << a1;
        return a1;
    }
//    if (n == 2) {
//        if (k == 1) {
//            cout << a1;
//        } else {
//            cout << a2;
//        }
//        return 0;
//    }
    a[0] = a1;
    a[1] = a2;
    for (int i = 2; i < n; i++) {
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }
    return kth_element(k - 1, 0, n - 1, a);
//    for (int i = 0; i < n; i++) {
//        int x;
//        cin >> x;
//        a[i].first = x;
//        a[i].second = i;
//    }
//    int m;
//    cin >> m;
//    for (int i = 0; i < m; i++) {
//        int l, r, k;
//        cin >> l >> r >> k;
//        vector<pair<int, int>> b = a;
//        pair<int, int> x = kth_element(k - 1, l - 1, r - 1, b);
//        cout << x.second + 1 << '\n';
//        l++;
//    }
}

int solve2(int n, int k, int A, int B, int C, int a1, int a2) {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    vector<int> a(n);
    a[0] = a1;
    a[1] = a2;
    for (int i = 2; i < n; i++) {
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }
    sort(a.begin(), a.end());
    return a[k - 1];
}

int main() {
//    int cnt;
//    cin >> cnt;
//    for (int i = 0; i < cnt; i++) {
//        int n = 1 + rand() % (3 * (int) 1e7);
//        int k = 1 + rand() % n;
//        int A = 1 + rand() % ((int) 1e9);
//        int B = 1 + rand() % ((int) 1e9);
//        int C = 1 + rand() % ((int) 1e9);
//        int a1 = 1 + rand() % ((int) 1e9);
//        int a2 = 1 + rand() % ((int) 1e9);
    int n, k, A, B, C, a1, a2;
    cin >> n >> k >> A >> B >> C >> a1 >> a2;
    int x1 = solve1(n, k, A, B, C, a1, a2);
    cout << x1;
//        int x2 = solve2(n, k, A, B, C, a1, a2);
//        if (i % 30 == 0) cout << i << '\n';
//        if (x1 != x2) {
//            cerr << x1 << ' ' << x2 << '\n';
//            return -1;
//        }
//    }
}
