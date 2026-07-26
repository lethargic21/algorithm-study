#include <iostream>

using namespace std;

int A[100001], psum[100001];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        psum[i] = psum[i - 1] + A[i];
        // psum[i] = A[1] + ... + A[i - 1] + A[i] = psum[i - 1] + A[i]
    }
    while (M--) {
        int i, j;
        cin >> i >> j;
        cout << psum[j] - psum[i - 1] << '\n';
        // A[i] + ... + A[j] = (A[1] + ... + A[i - 1] + A[i] + ... + A[j]) - (A[1] + ... + A[i - 1]) = psum[j] - psum[i - 1]
    }
    return 0;
}