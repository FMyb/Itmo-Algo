//
// Created by Yarolsav Ilin CT ITMO M3238 on 16.11.2020.
//

#include <bits/stdc++.h>

using namespace std;


vector<int> euler(int n, vector<vector<int>> &ed1) {
//    ifstream fin;
//    fin.open("in.txt");
//    ofstream fout("out.txt");
    vector<int> in(n);
    vector<int> out(n);
    vector<multiset<int>> ed(n);
    for (int i = 0; i < n; i++) {
        for (auto u : ed1[i]) {
            ed[i].insert(u);
            out[i]++;
            in[u]++;
        }
    }

    int v = 0;
    for (int i = 0; i < n; i++) {
        if (in[i] > out[i]) {
            v = i;
            break;
        }
    }
    stack<int> s;
    s.push(v);
    vector<int> ans;
    while (!s.empty()) {
        int w = s.top();
        if (out[w] == 0) {
            s.pop();
            ans.push_back(w);
            continue;
        }
        for (auto u : ed1[w]) {
            auto itr = ed[w].find(u);
            if (itr != ed[w].end()) {
                s.push(u);
                out[w]--;
                in[u]--;
                ed[w].erase(itr);
                break;
            }
        }
    }
    return ans;
}


int tmp = 0;

void rec(int n, int d, int k, const string &s, map<string, int> &per,
         vector<string> &per1, vector<vector<int>> &ed) {
    if (n == k) {
        string s1 = s.substr(0, s.size() - 1);
        string s2 = s.substr(1, s.size());
        if (per.count(s1) == 0) {
            per1.push_back(s1);
            per[s1] = tmp++;
        }
        if (per.count(s2) == 0) {
            per1.push_back(s2);
            per[s2] = tmp++;
        }
        ed[per[s1]].push_back(per[s2]);
        return;
    }
    for (int i = 0; i < d; i++) {
        rec(n + 1, d, k, s + to_string(i), per, per1, ed);
    }
}

int main() {
    int d, k;
    cin >> d >> k;
    if (k == 1) {
        for (int i = 0; i < d; i++) {
            cout << i;
        }
        return 0;
    }
    map<string, int> per;
    vector<string> per1;
    vector<vector<int>> ed((int) pow(d, k - 1));
    rec(0, d, k, "", per, per1, ed);
    auto ans = euler(ed.size(), ed);
    reverse(ans.begin(), ans.end());
    cout << per1[ans[0]];
    for (size_t i = 1; i < ans.size(); i++) {
        cout << per1[ans[i]].back();
    }
}
