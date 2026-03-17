#include <bits/stdc++.h> // 백준 16975
using namespace std;
using ll = long long;

struct LazySegTree{
    int n;
    vector<ll> tree;
    vector<ll> lazy;

    LazySegTree(int n_){
        n = n_;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
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

    void push(int node, int s, int e){
        if(lazy[node] == 0)
            return;

        tree[node] += (ll)(e - s + 1) * lazy[node];

        if(s != e){
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }

        lazy[node] = 0;
    }

    void update(int l, int r, ll val, int node, int s, int e){
        push(node, s, e);

        if(r < s || e < l)
            return;

        if(l <= s && e <= r){
            lazy[node] += val;
            push(node, s, e);
            return;
        }

        int mid = (s + e) / 2;
        update(l, r, val, node * 2, s, mid);
        update(l, r, val, node * 2 + 1, mid + 1, e);

        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int l, int r, ll val){
        update(l, r, val, 1, 0, n - 1);
    }

    ll query(int l, int r, int node, int s, int e){
        push(node, s, e);

        if(r < s || e < l)
            return 0;

        if(l <= s && e <= r)
            return tree[node];

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
    cin >> n;

    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    cin >> q;

    LazySegTree st(n);
    st.build(a);


    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int i, j;
            ll k;
            cin >> i >> j >> k;
            i--; j--;
            if(i > j)
                swap(i, j);

            st.update(i, j, k);
        } else {
            int x;
            cin >> x;
            x--;
            cout << st.query(x, x) << '\n';
        }
    }

    return 0;
}