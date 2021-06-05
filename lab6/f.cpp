//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 25.03.2020
//

#include <bits/stdc++.h>

using namespace std;

const string f1 = "Aa";
const string f2 = "BB";

int bit(int val, int ind) {
    return (val >> ind) & 1;
}

string gen(int val, int len) {
    string ans = "";
    for (int i = 0; i < len; i++) {
        if (bit(val, i) == 1) {
            ans += f2;
        } else {
            assert(bit(val, i) == 0);
            ans += f1;
        }
    }
    return ans;
}

int main() {
    int k;
    cin >> k;
    int temp = 1;
    int len = 1;
    while (temp * 2 <= k) {
        temp *= 2;
        len++;
    }
    for (int i = 0; i < k; i++) {
        cout << gen(i, len) << endl;
    }
}
