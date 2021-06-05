//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 18.03.2020
//

#include <bits/stdc++.h>

using namespace std;

const int a = 'a';
const int p = 43;
const int m = 1000000007;
const int len = 100000;
vector<int> power(21);

void init_power() {
    power[0] = 1;
    for (int i = 1; i < 20; i++) {
        power[i] = power[i - 1] * p;
        power[i] %= m;
    }
}

int hashf(string s) {
    int ans = 0;
    for (size_t i = 0; i < s.size(); i++) {
        ans += (((s[i] - 'a') * power[i]) % m + m) % m;
        ans %= m;
    }
    return ans % len;
}

int find(string x, vector<vector<pair<string, string>>> &_map) {
    int h = hashf(x);
    for (size_t i = 0; i < _map[h].size(); i++) {
        if (_map[h][i].first == x) {
            return (int) i;
        }
    }
    return -1;
}

void swap1(vector<vector<pair<string, string>>> &a, int h, int ind1, int ind2) {
    auto c = a[h][ind1];
    a[h][ind1] = a[h][ind2];
    a[h][ind2] = c;
}

int main() {
    init_power();
    ifstream fin;
    fin.open("map.in");
    ofstream fout("map.out");
    vector<vector<pair<string, string>>> _map(len);
    string s;
    while (fin >> s) {
        if (s == "put") {
            string key, value;
            fin >> key >> value;
            int ind = find(key, _map);
            int h = hashf(key);
            if (ind == -1) {
                _map[h].push_back({key, value});
            } else {
                _map[h][ind] = {key, value};
            }
            continue;
        }
        if (s == "get") {
            string key;
            fin >> key;
            int ind = find(key, _map);
            if (ind != -1) {
                int h = hashf(key);
                fout << _map[h][ind].second << '\n';
            } else {
                fout << "none\n";
            }
        }
        if (s == "delete") {
            string key;
            fin >> key;
            int ind = find(key, _map);
            if (ind != -1) {
                int h = hashf(key);
                swap1(_map, h, ind, (int) _map[h].size() - 1);
                _map[h].pop_back();
            }
        }
    }
}
