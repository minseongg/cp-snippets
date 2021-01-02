#include <iostream>
#include <vector>
#include <algorithm>

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

void topological_sort_dfs(int now, vvi &e, vi &visited, vi &order) {
    visited[now] = 1;
    for (int &to : e[now]) {
        if (visited[to]) { continue; }
        topological_sort_dfs(to, e, visited, order);
    }
    order.emplace_back(now);
}

vi topological_sort(int v, vvi &e) {
    vi visited(v), order;
    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            topological_sort_dfs(i, e, visited, order);
        }
    }
    reverse(order.begin(), order.end());
    return order;
}

pair<int, vi> two_sat(int v, vector<pair<int, int>> clauses) {
    vvi e(v << 1);
    for (auto &[ v1, v2 ] : clauses) {
        int mod_v1 = (v1 < 0 ? -v1 - 1 + v : v1 - 1);
        int mod_v2 = (v2 < 0 ? -v2 - 1 + v : v2 - 1);
        e[(mod_v1 + v) % (v << 1)].emplace_back(mod_v2);
        e[(mod_v2 + v) % (v << 1)].emplace_back(mod_v1);
    }
    auto comps = scc(v << 1, e);
    vi comp_map(v << 1);
    for (int i = 0; i < (int)comps.size(); i++) {
        for (int &x : comps[i]) {
            comp_map[x] = i;
        }
    }
    for (int x = 0; x < v; x++) {
        if (comp_map[x] == comp_map[x + v]) {
            return { 0, { } };
        }
    }
    vvi comp_e((int)comps.size());
    for (int x = 0; x < (v << 1); x++) {
        for (int &y : e[x]) {
            if (comp_map[x] == comp_map[y]) { continue; }
            comp_e[comp_map[x]].emplace_back(comp_map[y]);
        }
    }
    vi order = topological_sort((int)comps.size(), comp_e), visited(v), ans(v);
    reverse(order.begin(), order.end());
    for (int &i : order) {
        if (visited[comps[i][0] % v]) { continue; }
        for (int &x : comps[i]) {
            visited[x % v] = 1;
            ans[x % v] = (x < v ? 1 : 0);
        }
    }
    return { 1, ans };
}

int main() {
    // 3 variables, 4 clauses
    // -1 2
    // -2 3
    // 1 3
    // 3 2
    vector<pair<int, int>> clauses;
    clauses.emplace_back(-1, 2);
    clauses.emplace_back(-2, 3);
    clauses.emplace_back(1, 3);
    clauses.emplace_back(3, 2);

    auto [ is_avail, ans ] = two_sat(3, clauses);
    cout << is_avail << "\n";
    if (is_avail) {
        for (auto &x : ans) {
            cout << x << " ";
        }
        cout << "\n";
    }
}