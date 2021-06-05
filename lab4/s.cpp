#include <bits/stdc++.h>

using namespace std;

const int MOD = 999999937;

struct Matrix {
    int n;
    int m;
    vector<vector<long long>> a;

    Matrix(int n, int m, vector<vector<long long>> a) : n(n), m(m), a(a) {}

    Matrix operator*(const Matrix &other) const {
        vector<vector<long long>> temp(n, vector<long long>(other.m));
        Matrix ans = Matrix(n, other.m, temp);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < other.m; j++) {
                for (int k = 0; k < m; k++) {
                    ans.a[i][j] += a[i][k] * other.a[k][j] % MOD;
                    ans.a[i][j] %= MOD;
                }
            }
        }
        return ans;
    }

    Matrix operator^(long long power) const {
        if (power == 0) {
            vector<vector<long long>> temp(n, vector<long long>(m, 0));
            for (int i = 0; i < n; i++) {
                temp[i][i] = 1;
            }
            return Matrix(n, m, temp);
        }
        if (power == 1) {
            return *this;
        }
        if (power % 2) {
            return (*this ^ (power - 1)) * *this;
        } else {
            Matrix ans = *this ^(power / 2);
            return ans * ans;
        }
    }

    long long sum() {
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans += a[i][j];
                ans %= MOD;
            }
        }
        return ans;
    }
};

int main() {
    ifstream fin;
    fin.open("sequences.in");
    ofstream fout("sequences.out");
    long long n;
    vector<vector<long long>> a(5, vector<long long>(5));
    vector<vector<long long>> b(5, vector<long long>(1));
    for (int i = 0; i < 5; i++) {
        b[i][0] = 1;
        a[0][i] = 1;
        a[1][i] = 1;
        a[2][i] = 1;
        a[3][i] = 1;
        a[4][i] = 1;
    }
    a[3][2] = 0;
    a[3][4] = 0;
    a[4][2] = 0;
    a[4][4] = 0;
    const Matrix A(5, 5, a);
    const Matrix B(5, 1, b);
    fin >> n;
    while (n) {
        Matrix ans = (A ^ (n - 1)) * B;
        fout << ans.sum() << '\n';
        fin >> n;
    }
}
