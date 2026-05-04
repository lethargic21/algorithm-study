#include <bits/stdc++.h> // 백준 1753
using namespace std;
using ll = long long;
const ll INF = 1e18;

struct Dijkstra {
    int n;
    vector<vector<pair<int, ll>>> adj;
    vector<ll> dist;

    Dijkstra(int n_) {
        n = n_;
        adj.resize(n);
        dist.assign(n, INF);
    }

    void addEdge(int u, int v, ll w) {
        adj[u].push_back({v, w});
    }

    void run(int src) {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, start;
    cin >> n >> m >> start;
    start--;

    Dijkstra dijk(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--; v--;
        dijk.addEdge(u, v, w);
    }

    dijk.run(start);

    for (int i = 0; i < n; i++) {
        if (dijk.dist[i] == INF)
            cout << "INF\n";
        else
            cout << dijk.dist[i] << '\n';
    }

    return 0;
}
