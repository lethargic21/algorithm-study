#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned long long ull;
 
ull power(ull x, ull y, ull p) {
    ull res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % p;
        }
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
 
bool miller_rabin(ull n, ull a) {
    ull r = 0;
    ull d = n - 1;
    while (d % 2 == 0) {
        r++;
        d = d >> 1;
    }
    ull x = power(a, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {
        x = power(x, 2, n);
        if (x == n - 1) return true;
    }
    return false;
    
 
}
 
void isPrime(ull n) {
    ull alist[5] = { 2, 3, 5, 7, 11 };

    for (int i = 0; i < 5; i++) {
        ull a = alist[i];
        miller_rabin(n, a);
    }
 
}
 
int main(void) {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, cnt = 0;
    cin >> n;
    vector<int> v;
    
    for(size_t i = 0; i < v.size(); i++)
        cout << v[i] << "\n";
    
    cout <<cnt;
}