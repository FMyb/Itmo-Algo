//
// Created by Yarolsav Ilin CT ITMO M3238 on 11.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x;
    int y;
};

const int INF = 1e9;

int distance(Point x, Point y) {
    return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y);
}

int main() {
    int n;
    cin >> n;
    vector<Point> ed(n);
    for (int i = 0; i < n; i++) {
        cin >> ed[i].x >> ed[i].y;
    }
    vector<int> dist(n, INF);
    vector<int> used(n, false);
    long double ans = 0;
    dist[0] = 0;
    for (int i = 0; i < n; i++) {
        int min_dist = INF;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        ans += sqrt(dist[u]);
        used[u] = true;
        for (int v = 0; v < n; v++) {
            int x = distance(ed[u], ed[v]);
            if (x < dist[v] && !used[v]) {
                dist[v] = x;
            }
        }
    }
    cout << fixed << setprecision(4) << ans;
}
