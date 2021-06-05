#include <bits/stdc++.h>

using namespace std;

bool check(string &s1, string &s2) {
    if (s1.size() != s2.size()) {
        return false;
    }
    for (int i = 0; i < (int) s1.size(); i++) {
        if (s1[i] != s2[i] && s1[i] != '?') {
            return false;
        }
    }
    return true;
}

pair<int, int> find(int start, string s, string blank) {
    string temp = s.substr(start, blank.size());
    while (start + (int) blank.size() <= (int) s.size() && !check(blank, temp)) {
        start++;
        temp = s.substr(start, blank.size());
    }
    if (start + (int) blank.size() > (int) s.size()) {
        return {-1, -1};
    }
    return {start, start + blank.size() - 1};
}

int main() {
    ios_base::sync_with_stdio(false);
    string s1, s2;
    cin >> s1 >> s2;
    int i = 0;
    if (s1.empty() && s2.empty()) {
        cout << "YES";
        return 0;
    }
    string blank = "";
    while (i < (int) s1.size() && s1[i] != '*') {
        blank += s1[i];
        i++;
    }
    if (i == (int) s1.size()) {
        cout << (check(s1, s2) ? "YES" : "NO");
        return 0;
    }
    if (!blank.empty()) {
        string temp = s2.substr(0, blank.size());
        if (!check(blank, temp)) {
            cout << "NO";
            return 0;
        }
    }
    i++;
    int j = (int) blank.size();
    blank = "";
    while (i < (int) s1.size()) {
        while (i < (int) s1.size() && s1[i] != '*') {
            blank += s1[i];
            i++;
        }
        if (i == (int) s1.size()) break;
        auto c = find(j, s2, blank);
        if (c.first == -1) {
            cout << "NO";
            return 0;
        }
        j = c.second + 1;
        i++;
        blank = "";
    }
    if (blank.empty()) {
        cout << "YES";
        return 0;
    }
    if (j > (int) s2.size() - (int) blank.size()) {
        cout << "NO";
        return 0;
    }
    string temp = s2.substr((int) s2.size() - (int) blank.size());
    if (!check(blank, temp)) {
        cout << "NO";
        return 0;
    }
    cout << "YES";
}
