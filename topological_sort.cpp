#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

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