//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 17.03.2020
//

#include <bits/stdc++.h>

using namespace std;

const int a = 10;
const int b = 25;
const int p = 1000000007;
const int len = 100000;

int hashf(int x) {
    return ((a * x + p) % p + b + p) % p % len;
}

int find(int x, vector<vector<int>> &_set) {
    int h = hashf(x);
    for (size_t i = 0; i < _set[h].size(); i++) {
        if (_set[h][i] == x) {
            return (int) i;
        }
    }
    return -1;
}

void swap1(vector<vector<int>> &a, int h, int ind1, int ind2) {
    int c = a[h][ind1];
    a[h][ind1] = a[h][ind2];
    a[h][ind2] = c;
}

int main() {
    ifstream fin;
    fin.open("set.in");
    ofstream fout("set.out");
    vector<vector<int>> _set(len);
    string s;
    while (fin >> s) {
        int x;
        fin >> x;
        if (s == "insert") {
            if (find(x, _set) == -1) {
                int h = hashf(x);
                _set[h].push_back(x);
            }
            continue;
        }
        if (s == "exists") {
            if (find(x, _set) != -1) {
                fout << "true\n";
            } else {
                fout << "false\n";
            }
        }
        if (s == "delete") {
            int ind = find(x, _set);
            if (ind != -1) {
                int h = hashf(x);
                swap1(_set, h, ind, (int) _set[h].size() - 1);
                _set[h].pop_back();
            }
        }
    }
}
