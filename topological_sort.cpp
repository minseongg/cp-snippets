#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vi topological_sort(int v, vvi &e) {
    vi ans, in(v);
    for (int x = 0; x < v; x++) {
        for (int &y : e[x]) {
            in[y]++;
        }
    }

    for (int x = 0; x < v; x++) {
        if (!in[x]) {
            ans.emplace_back(x);
        }
    }

    for (int i = 0; i < v; i++) {
        int x = ans[i];
        for (int &y : e[x]) {
            in[y]--;
            if (!in[y]) {
                ans.emplace_back(y);
            }
        }
    }
    return ans;
}

int main() {
    // 7 vertices, 8 edges
    // 0 -> 1
    // 0 -> 2
    // 0 -> 3
    // 1 -> 4
    // 2 -> 4
    // 2 -> 5
    // 4 -> 6
    // 5 -> 1
    // Expected outcome: 0 2 3 5 1 4 6
    int v = 7;
    vvi e(v);
    e[0].emplace_back(1);
    e[0].emplace_back(2);
    e[0].emplace_back(3);
    e[1].emplace_back(4);
    e[2].emplace_back(4);
    e[2].emplace_back(5);
    e[4].emplace_back(6);
    e[5].emplace_back(1);

    auto ans = topological_sort(v, e);
    for (auto &x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}