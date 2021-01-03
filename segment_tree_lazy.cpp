#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vpii = vector<pair<int, int>>;

class SegmentTree {
public:
    int p = 1;
    vpii v;

    SegmentTree() = default;
    SegmentTree(int n) {
        while (p < n) { p <<= 1; }
        v.resize(p << 1);
    }

    void init(vi &w) {
        int sz = (int)w.size();
        for (int i = 0; i < sz; i++) { v[p + i] = { w[i], 0 }; }
        for (int i = p - 1; i > 0; i--) { v[i] = { v[i << 1].first + v[(i << 1) + 1].first, 0 }; }
    }

    void update(int s, int e, int k) {
        update_lazy(s, e, 0, p - 1, 1, k);
    }

    void update_lazy(int s, int e, int ts, int te, int x, int k) {
        propagate(x);
        if (s <= ts && te <= e) { v[x].second += (te - ts + 1) * k; }
        else if (te < s || ts > e) { return; }
        else {
            v[x].first += (min(e, te) - max(s, ts) + 1) * k;
            int tm = (ts + te) / 2;
            update_lazy(s, e, ts, tm, x << 1, k);
            update_lazy(s, e, tm + 1, te, (x << 1) + 1, k);
        }
    }

    int get(int s, int e) {
        return get_lazy(s, e, 0, p - 1, 1);
    }

    int get_lazy(int s, int e, int ts, int te, int x) {
        propagate(x);
        if (s <= ts && te <= e) { return v[x].first; }
        else if (te < s || ts > e) { return 0; }
        else {
            int tm = (ts + te) / 2;
            return get_lazy(s, e, ts, tm, x << 1) + get_lazy(s, e, tm + 1, te, (x << 1) + 1);
        }
    }

    void propagate(int x) {
        v[x].first += v[x].second;
        if (x < p) {
            v[x << 1].second += v[x].second / 2;
            v[(x << 1) + 1].second += v[x].second / 2;
        }
        v[x].second = 0;
    }
};

int main() {
    vi w = { 1, 1, 1, 1, 1 };
    SegmentTree segtree(5);
    segtree.init(w);
    cout << segtree.get(0, 4) << "\n";
    segtree.update(1, 1, 1);
    segtree.update(2, 2, 2);
    segtree.update(3, 3, 3);
    segtree.update(4, 4, 4);
    cout << segtree.get(0, 4) << "\n";
}
