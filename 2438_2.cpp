#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int N;
    cin >> N;
    string s;
    for (int i = 1; i <= N; i++) {
        s += "*";
        cout << s << '\n';
    }
    return 0;
}

/*
1번째 반복문 : 별 0 + 1개       *
2번째 반복문 : 별 1 + 1개       * + *
...
i번째 반복문 : 별 (i - 1) + 1개 ***...* + *
...
N번째 반복문 : 별 (N - 1) + 1개 *****...* + *

직전 반복문에서의 별 개수 + 1개
*/