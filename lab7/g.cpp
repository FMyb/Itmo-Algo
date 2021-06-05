#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
struct block {
    long long sum;
    long long plus;
    long long min;
    long long element;
};

long long INF = 1000000000000000001;
int const Len = 317, maxN = 100001;
long long a[maxN];
block b[maxN / Len + 1];
int n;

void relax(int t) {
    t = t / Len * Len;
    if (b[t / Len].element == -INF && b[t / Len].plus == 0)
        return;
    for (int i = t; i < t + Len && i < n; i++)
        if (b[t / Len].element == -INF)
            a[i] += b[t / Len].plus;
        else
            a[i] = b[t / Len].element + b[t / Len].plus;
    b[t / Len].element = -INF;
    b[t / Len].plus = 0;
}

void relaxMin(int t) {
    t = t / Len * Len;
    long long minim = INF;
    for (int i = t; i < t + Len && i < n; i++)
        minim = min(a[i], minim);
    b[t / Len].min = minim;
}

void update(int L, int R, long long x) {
    int t;
    if (L % Len > 0) {
        relax(L);
        t = L;
        while (L <= R && L % Len > 0) {
            b[L / Len].sum += x - a[L];
            a[L] = x;
            L++;
        }
        relaxMin(t);
    }
    if (R % Len != Len - 1) {
        relax(R);
        t = R;
        while (R >= L && R % Len != Len - 1) {
            b[R / Len].sum += x - a[R];
            a[R] = x;
            R--;
        }
        relaxMin(t);
    }
    while (L <= R) {
        b[L / Len].min = x;
        b[L / Len].sum = x * Len;
        b[L / Len].element = x;
        b[L / Len].plus = 0;
        L += Len;
    }
}

void add(int L, int R, long long x) {
    int t;
    if (L % Len > 0) {
        relax(L);
        t = L;
        while (L <= R && L % Len > 0) {
            a[L] += x;
            b[L / Len].sum += x;
            L++;
        }
        relaxMin(t);
    }
    if (R % Len != Len - 1) {
        relax(R);
        t = R;
        while (R >= L && R % Len != Len - 1) {
            a[R] += x;
            b[R / Len].sum += x;
            R--;
        }
        relaxMin(t);
    }
    while (L <= R) {
        b[L / Len].plus += x;
        b[L / Len].sum += x * Len;
        b[L / Len].min += x;
        L += Len;
    }
}

long long rmq(int L, int R) {
    long long m = INF;
    if (b[L / Len].element > -INF) {
        m = b[L / Len].min;
        L = (L / Len + 1) * Len;
    } else {
        while (L <= R && L % Len > 0) {
            m = min(m, a[L] + b[L / Len].plus);
            L++;
        }
    }
    if (b[R / Len].element != -INF) {
        m = min(m, b[R / Len].min);
        R = R / Len * Len - 1;
    } else {
        while (R >= L && R % Len != Len - 1) {
            if (b[R / Len].element == -INF) {
                m = min(m, a[R] + b[R / Len].plus);
            }
            R--;
        }
    }
    while (L <= R) {
        m = min(m, b[L / Len].min);
        L += Len;
    }
    return m;
}


int main() {
    ios_base::sync_with_stdio(false);
    int i, L, R;
    long long x;
    string st;
    cin >> n;
    for (i = 0; i < n / Len + 1; i++)
        b[i].min = INF;
    for (i = 0; i < n; i++) {
        cin >> a[i];
        b[i / Len].sum += a[i];
        b[i / Len].min = min(b[i / Len].min, a[i]);
        b[i / Len].element = -INF;
    }
    while (cin >> st) {
        if (st == "set") {
            cin >> L >> R >> x;
            update(L - 1, R - 1, x);
        }
        if (st == "add") {
            cin >> L >> R >> x;
            add(L - 1, R - 1, x);
        }
        if (st == "min") {
            cin >> L >> R;
            cout << rmq(L - 1, R - 1) << endl;
        }
    }
    return 0;
}
