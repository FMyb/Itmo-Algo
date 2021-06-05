#include <bits/stdc++.h>

using namespace std;

vector<int> ls(17);
int lastlevel = 0;

void bs1(int l, int r, int level, vector<vector<pair<int, int>>> &a) {
    lastlevel = max(level, lastlevel);
    while ((int) a.size() <= level) {
        vector<pair<int, int>> temp;
        a.push_back(temp);
    }
    if (l == r - 1) {
        a[level].push_back({l, r});
        return;
    }
    for (int i = 0; i < (r - l + 1) / 2; i++) {
        a[level].push_back({i + l, (r - l + 1) / 2 + +l + i});
    }
}

void bs(int l, int r, int level, vector<vector<pair<int, int>>> &a) {
    if (l == r) {
        return;
    }
    lastlevel = max(level, lastlevel);
    while ((int) a.size() <= level) {
        vector<pair<int, int>> temp;
        a.push_back(temp);
    }
    bs1(l, r, level, a);
    bs(l, (l + r) / 2, level + 1, a);
    bs((l + r) / 2 + 1, r, level + 1, a);
}

void merge1(int l, int r, int level, vector<vector<pair<int, int>>> &a) {
    if (l == r - 1) return;
    while ((int) a.size() <= level) {
        vector<pair<int, int>> temp;
        a.push_back(temp);
    }
    lastlevel = max(level, lastlevel);
    for (int i = 0; i <= (r - l) / 2; i++) {
        a[level].push_back({i + l, r - i});
    }
    bs(l, (l + r) / 2, level + 1, a);
    bs((l + r) / 2 + 1, r, level + 1, a);
}

void merge(int l, int r, int level, vector<vector<pair<int, int>>> &a) {
    if (l == r - 3) {
        merge1(l, r, level, a);
        return;
    }
    merge(l, (l + r) / 2, level + 1, a);
    merge((l + r) / 2 + 1, r, level + 1, a);
    if (ls[r - l + 1] == 0) {
        ls[r - l + 1] = lastlevel + 1;
    }
    merge1(l, r, ls[r - l + 1], a);
}

void sort(int l, int r, vector<vector<pair<int, int>>> &a) {
    vector<pair<int, int>> temp;
    a.push_back(temp);
    for (int i = l; i <= r; i += 2) {
        a[0].push_back({i, i + 1});
    }
    merge(l, r, 1, a);
}


int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << ' ' << 0 << ' ' << 0;
        return 0;
    }
    if (n == 2) {
        cout << 2 << ' ' << 1 << ' ' << 1 << '\n';
        cout << 1 << ' ' << 1 << ' ' << 2;
        return 0;
    }
    int x = 1;
    while (x < n) {
        x *= 2;
    }
    vector<vector<pair<int, int>>> a;
    sort(0, x - 1, a);
    vector<vector<pair<int, int>>> ans;
    int cnt = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i].size() > 0) {
            vector<pair<int, int>> temp;
            ans.push_back(temp);
        }
        for (size_t j = 0; j < a[i].size(); j++) {
            if (a[i][j].first < n && a[i][j].second < n) {
                ans[ans.size() - 1].push_back(a[i][j]);
                cnt++;
            }
        }
    }
    cout << n << ' ' << cnt << ' ' << ans.size() << '\n';
    for (size_t i = 0; i < ans.size(); i++) {
        cout << ans[i].size() << ' ';
        for (size_t j = 0; j < ans[i].size(); j++) {
            cout << ans[i][j].first + 1 << ' ' << ans[i][j].second + 1 << ' ';
        }
        cout << '\n';
    }
}
