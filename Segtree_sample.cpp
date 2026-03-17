#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegTree {
    int n;
    vector<ll> tree;

    SegTree(int n_) {
        n = n_;
        tree.assign(4 * n, 0);
    }

    void build(const vector<ll> &a, int node, int s, int e){
        if(s == e){
            tree[node] = a[s];
            return;
        }
        int mid = (s + e) / 2;
        build(a, node * 2, s, mid);
        build(a, node * 2 + 1, mid + 1, e);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void build(const vector<ll> &a){
        build(a, 1, 0, n - 1);
    }

    void update(int idx, ll val, int node, int s, int e){
        if(s == e){
            tree[node] = val;
            return;
        }
        int mid = (s + e) / 2;
        if(idx <= mid){
            update(idx, val, node * 2, s, mid);
        } else {
            update(idx, val, node * 2 + 1, mid + 1, e);
        }
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int idx, ll val){
        update(idx, val, 1, 0, n - 1);
    }

    ll query(int l, int r, int node, int s, int e){
        if(r < s || e < l){
            return 0;
        }
        if(l <= s && e <= r){
            return tree[node];
        }
        int mid = (s + e) / 2;
        return query(l, r, node * 2, s, mid) + query(l, r, node * 2 + 1, mid + 1, e);
    }

    ll query(int l, int r){
        return query(l, r, 1, 0, n - 1);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    SegTree st(n);
    st.build(a);

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int idx;
            ll val;
            cin >> idx >> val;
            idx--; // 입력이 1-indexed면
            st.update(idx, val);
        } else {
            int l, r;
            cin >> l >> r;
            l--; r--;
            cout << st.query(l, r) << '\n';
        }
    }

    return 0;
}
