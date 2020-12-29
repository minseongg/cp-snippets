#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point {
public:
    int x, y;

    Point(int _x = 0, int _y = 0) : x(_x), y(_y) { }

    bool operator<(const Point &rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }

    static int ccw(const Point &a, const Point &b, const Point &c) {
        return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    }
};

vector<Point> convex_hull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    vector<Point> ret;

    for (int step = 0; step < 2; step++) {
        auto start = ret.size();
        for (Point p : pts) {
            while (ret.size() >= start + 2 && Point::ccw(ret[ret.size() - 2], ret[ret.size() - 1], p) <= 0) { ret.pop_back(); }
            ret.push_back(p);
        }
        ret.pop_back();
        reverse(pts.begin(), pts.end());
    }

    return ret;
}

int main() {
    // . . . . . + . . . . .
    // . . . . . + . . . D .
    // . . . A . + . . . . .
    // . . . . . + . H . . .
    // + + F + + + + + + + +
    // . . . . . B . C G . .
    // . . . E . + . . . . .
    // . . . . . + . . . . .
    // . . . . . + . . . . .
    // Expected outcome : {(-3, 0), (-2, -2), (3, -1), (4, 3), (-2, 2)}
    vector<Point> pts;
    pts.emplace_back(-2, 2);
    pts.emplace_back(0, -1);
    pts.emplace_back(2, -1);
    pts.emplace_back(4, 3);
    pts.emplace_back(-2, -2);
    pts.emplace_back(-3, 0);
    pts.emplace_back(3, -1);
    pts.emplace_back(2, 1);

    vector<Point> ans = convex_hull(pts);
    for (auto pt : ans) {
        cout << pt.x << " " << pt.y << "\n";
    }
}
