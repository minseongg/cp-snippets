#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vvpii = vector<vector<pii>>;

vi dijkstra(int v, int s, vvpii &e) {
    auto cmp = [](pii left, pii right) { return left.second > right.second; };
    priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
    vi ans(v), visited(v);
    pq.push({ s, 0 });
    while (!pq.empty()) {
        auto [ now, cost ] = pq.top();
        pq.pop();
        if (visited[now]) { continue; }
        visited[now] = 1;
        ans[now] = cost;
        for (auto &[ to, to_cost ] : e[now]) {
            if (visited[to]) { continue; }
            pq.push({ to, cost + to_cost });
        }
    }
    return ans;
}

int main() {
    // 5 vertices, 8 edges
    // 0 -> 1 : 2
    // 0 -> 2 : 3
    // 0 -> 3 : 1
    // 0 -> 4 : 10
    // 1 -> 3 : 2
    // 2 -> 3 : 1
    // 2 -> 4 : 1
    // 3 -> 4 : 3
    // Expected outcome: { 0, 2, 3, 1, 4 }
    vvpii e(5);
    e[0].emplace_back(1, 2);
    e[0].emplace_back(2, 3);
    e[0].emplace_back(3, 1);
    e[0].emplace_back(4, 10);
    e[1].emplace_back(3, 2);
    e[2].emplace_back(3, 1);
    e[2].emplace_back(4, 1);
    e[3].emplace_back(4, 3);
    
    auto ans = dijkstra(5, 0, e);
    for (int x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}