#include <bits/stdc++.h>

using namespace std;

void sort(vector<double> &a, int l, int r) {
    double key = a[l + rand() % (r - l + 1)];
    int i = l;
    int j = r;
    do {
        while (a[i] < key) i++;
        while (a[j] > key) j--;
        if (i <= j) {
            double buf = a[i];
            a[i] = a[j];
            a[j] = buf;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) {
        sort(a, l, j);
    }
    if (i < r) {
        sort(a, i, r);
    }
}

void sort(vector<pair<double, int>> &a, int l, int r) {
    double key = a[l + rand() % (r - l + 1)].first;
    int i = l;
    int j = r;
    do {
        while (a[i].first < key) i++;
        while (a[j].first > key) j--;
        if (i <= j) {
            auto buf = a[i];
            a[i] = a[j];
            a[j] = buf;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) {
        sort(a, l, j);
    }
    if (i < r) {
        sort(a, i, r);
    }
}

bool check(double m, int n, int k, vector<int> &v, vector<int> &w) {
    vector<double> temp(n);
    for (int i = 0; i < n; i++) {
        temp[i] = v[i] - m * w[i];
    }
    sort(temp, 0, n - 1);
    double sum = 0;
    for (int i = n - 1; i >= n - k; i--) {
        sum += temp[i];
    }
    return sum >= 0;
}

double bin_find(int n, int k, vector<int> &v, vector<int> &w) {
    double l = 0;
    double r = 10000001;
    for (int i = 0; i < 64; i++) {
        double m = (l + r) / 2;
        if (check(m, n, k, v, w)) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> w[i];
    }
    double x = bin_find(n, k, v, w);
    vector<pair<double, int>> temp(n);
    for (int i = 0; i < n; i++) {
        temp[i].first = v[i] - x * w[i];
        temp[i].second = i;
    }
    sort(temp, 0, n - 1);
    for (int i = n - k; i < n; i++) {
        cout << temp[i].second + 1 << ' ';
    }
}
