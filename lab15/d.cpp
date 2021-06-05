#include <bits/stdc++.h>

using namespace std;

int getnot(int c1, int c2) {
    for (int i = 0; i < 3; i++) {
        if (i != c1 && i != c2) {
            return i;
        }
    }
    return -1;
}

struct Vert {
    int prevcol = -1;
    int newcol = -1;
    vector<Vert *> neig;
    bool mark;

    Vert(int prevcol) : prevcol(prevcol) {}

    bool trySet(int color) {
        mark = true;
        if (color == prevcol) {
            return false;
        } else {
            int c = newcol;
            newcol = color;
            bool ok = true;
            for (auto v : neig) {
                if (v->mark) {
                    if (v->newcol == color) {
                        ok = false;
                    }
                } else {
                    if (v->prevcol != color) {
                        if (!v->trySet(getnot(v->prevcol, color))) {
                            ok = false;
                        }
                    }
                }
            }
            if (!ok) {
                newcol = c;
            }
            return ok;
        }
    }
};

int col(char c) {
    return c == 'R' ? 0 : c == 'G' ? 1 : 2;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Vert *> v;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        v.push_back(new Vert(col(s[i])));
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        v[--a]->neig.push_back(v[--b]);
        v[b]->neig.push_back(v[a]);
    }
    for (int i = 0; i < n; i++) {
        if (v[i]->newcol == -1) {
            for (int j = 0; j < 3; j++) {
                for (auto vert : v) {
                    vert->mark = false;
                }
                if (v[i]->trySet(j)) {
                    break;
                }
            }
        }
    }
    bool ok = true;
    for (auto vert : v) {
        if (vert->newcol == -1) {
            ok = false;
        }
    }
    if (ok) {
        for (auto vert : v) {
            cout << (vert->newcol == 0 ? 'R' : vert->newcol == 1 ? 'G' : 'B');
        }
    } else {
        cout << "Impossible";
    }
}