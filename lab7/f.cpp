//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 27.04.2020
//

#include <vector>
#include <stdio.h>

using namespace std;

long long modR;

struct Matrix {
    vector<long long> val;

    Matrix() {
        Matrix(1, 0, 0, 1);
    }

    Matrix(long long a1, long long a2, long long a3, long long a4) {
        val = vector<long long>(4);
        val[0] = a1;
        val[1] = a2;
        val[2] = a3;
        val[3] = a4;
    }

    Matrix operator*(const Matrix &other) const {
        return Matrix(((val[0] * other.val[0]) % modR + (val[1] * other.val[2]) % modR) % modR,
                      ((val[0] * other.val[1]) % modR + (val[1] * other.val[3]) % modR) % modR,
                      ((val[2] * other.val[0]) % modR + (val[3] * other.val[2]) % modR) % modR,
                      ((val[2] * other.val[1]) % modR + (val[3] * other.val[3]) % modR) % modR);
    }
};

const size_t N = 500001;
const Matrix E = Matrix(1, 0, 0, 1);

struct Node {
    Matrix prod;
};

vector<Node> t(4 * (N + 1));
vector<Matrix> vec(N + 1);

void update(int x) {
    t[x].prod = t[2 * x + 1].prod * t[2 * x + 2].prod;
}


void update_elem(int x, int l, int r, int i, Matrix &v) {
    if (i < l || i >= r) {
        return;
    }
    if (r - l == 1) {
        t[x].prod = v;
        return;
    }
    int m = (l + r) / 2;
    update_elem(2 * x + 1, l, m, i, v);
    update_elem(2 * x + 2, m, r, i, v);
    update(x);
}

Matrix calc_prod(int x, int l, int r, int a, int b) {
    if (r <= a || b <= l) {
        return E;
    }
    if (a <= l && r <= b) {
        return t[x].prod;
    }
    int m = (l + r) / 2;
    return calc_prod(2 * x + 1, l, m, a, b) * calc_prod(2 * x + 2, m, r, a, b);
}


Node build(int x, int L, int R) {
    if (R - L == 1) {
        t[x].prod = vec[L];
        return t[x];
    }
    int m = (L + R) / 2;
    Node b = build(2 * x + 1, L, m);
    Node c = build(2 * x + 2, m, R);
    t[x].prod = b.prod * c.prod;
    return t[x];
}


int main() {
    scanf("%d", &modR);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        int a1, a2, a3, a4;
        scanf("%d%d%d%d", &a1, &a2, &a3, &a4);
        vec[i] = Matrix(a1, a2, a3, a4);
    }
    build(0, 0, n);
    for (int i = 0; i < m; i++) {
        int left, right;
        scanf("%d%d", &left, &right);
        Matrix t = calc_prod(0, 0, n, left - 1, right);
        printf("%lld %lld\n%lld %lld \n\n", t.val[0], t.val[1], t.val[2], t.val[3]);
    }
}
