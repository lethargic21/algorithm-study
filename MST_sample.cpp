#include <bits/stdc++.h> // 백준 1197 (크루스칼)
using namespace std;
using ll = long long;

struct DSU {
    vector<int> parent, rank_;

    DSU(int n) {
        parent.resize(n);
        rank_.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};

struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge &o) const {
        return w < o.w;
    }
};

ll kruskal(int n, vector<Edge> &edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll totalCost = 0;
    int cnt = 0;

    for (auto &[u, v, w] : edges) {
        if (dsu.unite(u, v)) {
            totalCost += w;
            cnt++;
            if (cnt == n - 1) break;
        }
    }

    return totalCost;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--;
        edges[i].v--;
    }

    cout << kruskal(n, edges) << '\n';

    return 0;
}
