//
// Created by Yaroslav Ilin, M3138, KT ITMO y2019. 20.03.2020
//

#include <bits/stdc++.h>

#define null NULL

using namespace std;

const int p = 43;
const int m = 1000000007;
const int len = 100000;
vector<int> power(21);

void init_power() {
    power[0] = 1;
    for (int i = 1; i <= 20; i++) {
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

struct Node {
    Node *prev = null;
    Node *next = null;
    string value;

    Node(string value_) {
        value = value_;
    }
};

Node *top = null;

int find(string x, vector<vector<pair<string, Node *>>> &_map) {
    int h = hashf(x);
    for (size_t i = 0; i < _map[h].size(); i++) {
        if (_map[h][i].first == x) {
            return (int) i;
        }
    }
    return -1;
}

void swap1(vector<vector<pair<string, Node *>>> &a, int h, int ind1, int ind2) {
    auto c = a[h][ind1];
    a[h][ind1] = a[h][ind2];
    a[h][ind2] = c;
}

void delete_node(Node *x) {
    if (x == top) {
        if (top->prev != null) {
            top->prev->next = null;
            top = top->prev;
        } else {
            top = null;
        }
        return;
    }
    Node *prev = x->prev;
    Node *next = x->next;
    if (prev != null) {
        prev->next = next;
    }
    if (next != null) {
        next->prev = prev;
    }
}


void add_top(Node *x) {
    if (top == null) {
        top = x;
    } else {
        Node *prev = top;
        top->next = x;
        top = x;
        top->prev = prev;
    }
}

int main() {
    init_power();
    ifstream fin;
    fin.open("linkedmap.in");
    ofstream fout("linkedmap.out");
    string s;
    vector<vector<pair<string, Node *>>> _map(len);
    while (fin >> s) {
        string key;
        fin >> key;
        if (s == "put") {
            string value;
            fin >> value;
            int ind = find(key, _map);
            int h = hashf(key);
            if (ind == -1) {
                add_top(new Node(value));
                _map[h].push_back({key, top});
            } else {
                _map[h][ind].second->value = value;
            }
        }
        if (s == "delete") {
            int ind = find(key, _map);
            if (ind == -1) {
                continue;
            }
            int h = hashf(key);
            delete_node(_map[h][ind].second);
            swap1(_map, h, ind, (int) _map[h].size() - 1);
            _map[h].pop_back();
        }
        if (s == "get") {
            int ind = find(key, _map);
            if (ind == -1) {
                fout << "none\n";
            } else {
                int h = hashf(key);
                fout << _map[h][ind].second->value << '\n';
            }
        }
        if (s == "prev") {
            int ind = find(key, _map);
            if (ind == -1) {
                fout << "none\n";
            } else {
                int h = hashf(key);
                assert(ind < (int) _map[h].size() && _map[h][ind].second != null);
                if (_map[h][ind].second->prev == null) {
                    fout << "none\n";
                } else {
                    fout << _map[h][ind].second->prev->value << '\n';
                }
            }
        }
        if (s == "next") {
            int ind = find(key, _map);
            if (ind == -1) {
                fout << "none\n";
            } else {
                int h = hashf(key);
                if (_map[h][ind].second->next == null) {
                    fout << "none\n";
                } else {
                    fout << _map[h][ind].second->next->value << '\n';
                }
            }
        }
    }
}
