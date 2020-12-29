#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vvi scc_get_rev_e(int v, vvi &e) {
    vvi rev_e(v);
    for (int x = 0; x < v; x++) {
        for (int &y : e[x]) {
            rev_e[y].emplace_back(x);
        }
    }
    return rev_e;
}

void scc_dfs(int now, vvi &e, vi &visited, vi &order) {
    visited[now] = 1;
    for (int x : e[now]) {
        if (visited[x]) { continue; }
        scc_dfs(x, e, visited, order);
    }
    order.emplace_back(now);
}

void scc_dfs_rev(int now, vvi &e, vi &visited, vi &ans) {
    visited[now] = 1;
    ans.emplace_back(now);
    for (int x : e[now]) {
        if (visited[x]) { continue; }
        scc_dfs_rev(x, e, visited, ans);
    }
}

vvi scc(int v, vvi &e) {
    vi visited(v), rev_visited(v), order;
    vvi rev_e = scc_get_rev_e(v, e);
    vvi ans;
    
    for (int i = 0; i < v; i++) {
        if (visited[i]) { continue; }
        scc_dfs(i, e, visited, order);
    }

    for (int i = v - 1; i >= 0; i--) {
        if (rev_visited[order[i]]) { continue; }
        ans.push_back({});
        scc_dfs_rev(order[i], rev_e, rev_visited, ans[ans.size() - 1]);
    }

    return ans;
}

int main() {
    // 6 vertices, 9 edges
    // 0 -> 3
    // 1 -> 0
    // 1 -> 2
    // 3 -> 1
    // 3 -> 4
    // 3 -> 5
    // 4 -> 5
    // 5 -> 2
    // 5 -> 4
    // Expected outcome: {{0, 1, 3}, {4, 5}, {2}}
    int v = 6;
    vvi e(v);
    e[0].emplace_back(3);
    e[1].emplace_back(0);
    e[1].emplace_back(2);
    e[3].emplace_back(1);
    e[3].emplace_back(4);
    e[3].emplace_back(5);
    e[4].emplace_back(5);
    e[5].emplace_back(2);
    e[5].emplace_back(4);

    auto ans = scc(v, e);
    for (auto &comp : ans) {
        for (auto &x : comp) {
            cout << x << " ";
        }
        cout << "\n";
    }
}