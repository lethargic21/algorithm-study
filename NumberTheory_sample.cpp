#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// ── GCD / LCM ──────────────────────────────────────────────
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// ── 빠른 거듭제곱 (mod pow) ─────────────────────────────────
ll modpow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// ── 확장 유클리드 (ax + by = gcd(a,b)) ─────────────────────
// 반환값: gcd, x와 y는 참조로 받음
ll extGcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// ── 모듈러 역원 (mod이 소수일 때: 페르마 소정리) ────────────
ll modInvFermat(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

// ── 모듈러 역원 (mod이 소수가 아닐 때: 확장 유클리드) ───────
ll modInv(ll a, ll mod) {
    ll x, y;
    ll g = extGcd(a, mod, x, y);
    if (g != 1) return -1; // 역원 없음
    return (x % mod + mod) % mod;
}

// ── 에라토스테네스의 체 ─────────────────────────────────────
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; (ll)i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    return is_prime;
}

// ── 오일러 피 함수 (phi) ────────────────────────────────────
// phi[i] = 1~i 중 i와 서로소인 수의 개수
vector<int> eulerPhi(int n) {
    vector<int> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) { // i가 소수
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}

// ── Miller-Rabin 소수 판별 ──────────────────────────────────
ull mulmod(ull a, ull b, ull m) {
    return (__uint128_t)a * b % m;
}

bool millerTest(ull n, ull a) {
    if (n % a == 0) return n == a;
    ull d = n - 1;
    int r = 0;
    while (d % 2 == 0) { d /= 2; r++; }
    ull x = modpow(a % n, d, n);
    if (x == 1 || x == n - 1) return true;
    for (int i = 0; i < r - 1; i++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return true;
    }
    return false;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    for (ull a : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL})
        if (!millerTest(n, a)) return false;
    return true;
}

// ── Pollard-Rho 소인수분해 ───────────────────────────────────
ull pollardRho(ull n) {
    if (n % 2 == 0) return 2;
    ull x = rand() % (n - 2) + 2;
    ull y = x;
    ull c = rand() % (n - 1) + 1;
    ull d = 1;
    while (d == 1) {
        x = (mulmod(x, x, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        d = gcd((ll)abs((ll)x - (ll)y), (ll)n);
    }
    return d;
}

map<ull, int> factorize(ull n) {
    map<ull, int> factors;
    if (n == 1) return factors;
    queue<ull> q;
    q.push(n);
    while (!q.empty()) {
        ull x = q.front(); q.pop();
        if (x == 1) continue;
        if (isPrime(x)) { factors[x]++; continue; }
        ull d = x;
        while (d == x) d = pollardRho(x);
        q.push(d);
        q.push(x / d);
    }
    return factors;
}

// ── 중국인의 나머지 정리 (CRT) ──────────────────────────────
// x ≡ r1 (mod m1), x ≡ r2 (mod m2) 를 만족하는 최소 양의 x
// 반환: {x, lcm(m1,m2)}, 해 없으면 {-1, -1}
pair<ll, ll> crt(ll r1, ll m1, ll r2, ll m2) {
    ll g = gcd(m1, m2);
    if ((r2 - r1) % g != 0) return {-1, -1};
    ll l = m1 / g * m2;
    ll x, y;
    extGcd(m1 / g, m2 / g, x, y);
    ll diff = ((r2 - r1) / g % (m2 / g) + m2 / g) % (m2 / g);
    ll ans = (r1 + m1 * (diff * x % (m2 / g))) % l;
    return {(ans + l) % l, l};
}

// ───────────────────────────────────────────────────────────
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 소수 판별 예시
    cout << isPrime(998244353) << '\n'; // 1

    // 소인수분해 예시
    auto factors = factorize(360);
    for (auto [p, e] : factors)
        cout << p << "^" << e << " ";
    cout << '\n'; // 2^3 3^2 5^1

    // CRT 예시: x ≡ 2 (mod 3), x ≡ 3 (mod 5) => x = 8
    auto [x, m] = crt(2, 3, 3, 5);
    cout << x << " " << m << '\n'; // 8 15

    return 0;
}
