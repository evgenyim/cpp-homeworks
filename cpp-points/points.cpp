#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

struct point {
    int x, y;
};

bool compare_by_x(point &a, point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool compare_by_y(point &a, point &b) {
    return a.y < b.y;
}

double mind = 1e12;
const int MAXN = 100500;
point points[MAXN];

void upd(point &a, point &b) {
    double d = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    if (d < mind) {
        mind = d;
    }
}

void solve(int l, int r) {
    if (r - l <= 3) {
        for (int i = l; i <= r; i++) {
            for (int j = i + 1; j <= r; j++) {
                upd(points[i],points[j]);
            }
        }
        sort(points + l, points + r + 1, &compare_by_y);
        return;
    }
    int m = (l + r) / 2;
    int middle_x = points[m].x;
    solve(l, m);
    solve(m + 1, r);
    point tmp[MAXN];
    merge(points + l, points + m + 1, points + m + 1, points + r + 1, tmp, &compare_by_y);
    copy(tmp, tmp + r - l + 1, points + l);
    int sz = 0;
    for (int i = l; i <= r; i++) {
        if (abs(points[i].x - middle_x) < mind) {
            for (int j = sz - 1; j >= 0 && points[i].y - tmp[j].y < mind; j--) {
                upd(points[i], tmp[j]);
            }
            tmp[sz++] = points[i];
        }
    }

}

int main() {
    int n;
    cin >> n;
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        points[i] = {x, y};
    }
    sort(points, points + n, &compare_by_x);
    mind = 1e9;
    solve(0, n - 1);
    cout << mind;
    return 0;
}