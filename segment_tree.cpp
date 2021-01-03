#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;

class SegmentTree {
public:
    int p = 1;
    vi v;

    SegmentTree() = default;
    SegmentTree(int n) {
        while (p < n) { p <<= 1; }
        v.resize(p << 1);
    }

    void init(vi &w) {
        int sz = (int)w.size();
        for (int i = 0; i < sz; i++) { v[p + i] = w[i]; }
        for (int i = p - 1; i > 0; i--) { v[i] = v[i << 1] + v[(i << 1) + 1]; }
    }

    void update(int s, int k) {
        int l = p + s;
        while (l) { v[l] += k; l >>= 1; }
    }

    int get(int s, int e) {
        int ans = 0, l = p + s, r = p + e;
        while (l <= r) {
            if (l % 2 == 1) { ans += v[l]; l++; }
            if (r % 2 == 0) { ans += v[r]; r--; }
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

int main() {
    vi w = { 1, 1, 1, 1, 1 };
    SegmentTree segtree(5);
    segtree.init(w);
    cout << segtree.get(0, 4) << "\n";
    segtree.update(1, 1);
    segtree.update(2, 2);
    segtree.update(3, 3);
    segtree.update(4, 4);
    cout << segtree.get(0, 4) << "\n";
}
