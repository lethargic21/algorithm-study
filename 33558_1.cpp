// N * M 평면의 좌표를 U * V 텍스처에 대응시키는 방법
// 관찰을 통해 규칙성을 발견하고 수식으로 표현하기

#include <iostream>

using namespace std;

char board[200][200];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int N, M;
    cin >> N >> M;
    int U, V;
    cin >> U >> V;
    for (int i = 0; i < U; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < V; j++) {
            board[i][j] = s[j];
        }
    }
    string s;
    cin >> s;
    if (s == "clamp-to-edge") {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << board[min(i, U - 1)][min(j, V - 1)];
            }
            cout << '\n';
        }
    } else if (s == "repeat") {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << board[i % U][j % V];
            }
            cout << '\n';
        }
    } else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << board[i / U % 2 ? U - 1 - i % U : i % U][j / V % 2 ? V - 1 - j % V : j % V];
                // 삼항 연산자 (조건식 ? true일 때 : false일 때)
                // i를 U로 나눈 몫이 홀수 (MOD 2 = 1) 일 때 뒤 (U - 1) 에서 i % U 번째, 짝수 (MOD 2 = 0) 일 때 앞 0 에서 i % U 번째
                // j를 V로 나눈 몫이 홀수 (MOD 2 = 1) 일 때 뒤 (V - 1) 에서 j % V 번째, 짝수 (MOD 2 = 0) 일 때 앞 0 에서 j % V 번째
            }
            cout << '\n';
        }
    }
    return 0;
}