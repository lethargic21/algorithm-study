#include <bits/stdc++.h> // 2차원 세그 11658
using namespace std;
using ll = long long;

struct SegTree2D {
    int n, m;
    vector<vector<ll>> tree; 

    SegTree2D(int n_, int m_) {
        n = n_;
        m = m_;
        tree.assign(4 * n, vector<ll>(4 * m, 0));
    }

    void buildY(int vx, int vy, int ly, int ry, const vector<vector<ll>> &a, int lx, int rx) {
        if (ly == ry) {
            if (lx == rx) tree[vx][vy] = a[lx][ly];
            else tree[vx][vy] = tree[vx * 2][vy] + tree[vx * 2 + 1][vy];
            return;
        }
        int my = (ly + ry) / 2;
        buildY(vx, vy * 2, ly, my, a, lx, rx);
        buildY(vx, vy * 2 + 1, my + 1, ry, a, lx, rx);
        tree[vx][vy] = tree[vx][vy * 2] + tree[vx][vy * 2 + 1];
    }

    void buildX(int vx, int lx, int rx, const vector<vector<ll>> &a) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            buildX(vx * 2, lx, mx, a);
            buildX(vx * 2 + 1, mx + 1, rx, a);
        }
        buildY(vx, 1, 0, m - 1, a, lx, rx);
    }

    void build(const vector<vector<ll>> &a) {
        buildX(1, 0, n - 1, a);
    }

    void updateY(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, ll val) {
        if (ly == ry) {
            if (lx == rx) tree[vx][vy] = val;
            else tree[vx][vy] = tree[vx * 2][vy] + tree[vx * 2 + 1][vy];
            return;
        }
        int my = (ly + ry) / 2;
        if (y <= my) updateY(vx, lx, rx, vy * 2, ly, my, x, y, val);
        else updateY(vx, lx, rx, vy * 2 + 1, my + 1, ry, x, y, val);
        tree[vx][vy] = tree[vx][vy * 2] + tree[vx][vy * 2 + 1];
    }

    void updateX(int vx, int lx, int rx, int x, int y, ll val) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx) updateX(vx * 2, lx, mx, x, y, val);
            else updateX(vx * 2 + 1, mx + 1, rx, x, y, val);
        }
        updateY(vx, lx, rx, 1, 0, m - 1, x, y, val);
    }

    void update(int x, int y, ll val) {
        updateX(1, 0, n - 1, x, y, val);
    }

    ll queryY(int vx, int vy, int ly, int ry, int y1, int y2) {
        if (y2 < ly || ry < y1) return 0;
        if (y1 <= ly && ry <= y2) return tree[vx][vy];
        int my = (ly + ry) / 2;
        return queryY(vx, vy * 2, ly, my, y1, y2)
             + queryY(vx, vy * 2 + 1, my + 1, ry, y1, y2);
    }

    ll queryX(int vx, int lx, int rx, int x1, int x2, int y1, int y2) {
        if (x2 < lx || rx < x1) return 0;
        if (x1 <= lx && rx <= x2) return queryY(vx, 1, 0, m - 1, y1, y2);
        int mx = (lx + rx) / 2;
        return queryX(vx * 2, lx, mx, x1, x2, y1, y2)
             + queryX(vx * 2 + 1, mx + 1, rx, x1, x2, y1, y2);
    }

    ll query(int x1, int x2, int y1, int y2) {
        return queryX(1, 0, n - 1, x1, x2, y1, y2);
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<vector<ll>> a(n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            int p;
            cin >> p;

            a[i].push_back(p);
        }

    

    SegTree2D st(n,n);
    st.build(a);

    while(q--){
        int type;
        cin >> type;

        if(type == 0){
            int x, y, c;
            cin >> x >> y >> c;
            x--; y--;
            st.update(x, y, c);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--; y1--; x2--; y2--;

            if (x1 > x2) swap(x1, x2);
            if (y1 > y2) swap(y1, y2);

            cout << st.query(x1, x2, y1, y2) << '\n';
        }       
    }


    return 0;
}