#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> &l, vector<int> &r) {
    vector<int> ans;
    size_t i = 0, j = 0;
    while (i < l.size() && j < r.size()) {
        if (l[i] < r[j]) {
            ans.push_back(l[i]);
            i++;
        } else {
            ans.push_back(r[j]);
            j++;
        }
    }
    for (; i < l.size(); i++) {
        ans.push_back(l[i]);
    }
    for (; j < r.size(); j++) {
        ans.push_back(r[j]);
    }
    return ans;
}

void sort(vector<int> &a) {
    if (a.size() == 1) {
        return;
    }
    vector<int> left;
    int m = (a.size()) / 2;
    for (int i = 0; i < m; i++) {
        left.push_back(a[i]);
    }
    vector<int> right;
    for (size_t i = m; i < a.size(); i++) {
        right.push_back(a[i]);
    }
    sort(left);
    sort(right);
    a = merge(left, right);
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
}
