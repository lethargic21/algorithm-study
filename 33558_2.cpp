// U * V 텍스처에서의 움직임을 추적하는 방법 (구현이 까다로움)
// N * M 평면에서 i(j)가 0 ~ N(M)까지 바뀔 때 U * V 텍스처에서 i(j)가 어떻게 움직이는지 또는 언제 방향을 바꾸는지 관찰하고 구현하기

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
    // x = 현재 행 번호, y = 현재 열 번호
    // dx = 평면에서의 다음 행에서 텍스처의 행은 얼마나 변화하는지
    // dy = 평면에서의 다음 열에서 텍스처의 열은 얼마나 변화하는지
    // nx = 다음 행 번호 (예측), ny = 다음 열 번호 (예측)
    if (s == "clamp-to-edge") {
        int x = 0, dx = 1;
        for (int i = 0; i < N; i++) {
            int y = 0, dy = 1;
            for (int j = 0; j < M; j++) {
                cout << board[x][y];
                int ny = y + dy;
                if (ny == V) dy = 0;
                else y = ny;
            }
            int nx = x + dx;
            if (nx == U) dx = 0;
            else x = nx;
            cout << '\n';
        }
    } else if (s == "repeat") {
        int x = 0, dx = 1;
        for (int i = 0; i < N; i++) {
            int y = 0, dy = 1;
            for (int j = 0; j < M; j++) {
                cout << board[x][y];
                int ny = y + dy;
                if (ny == V) y = 0;
                else y = ny;
            }
            int nx = x + dx;
            if (nx == U) x = 0;
            else x = nx;
            cout << '\n';
        }
    } else {
        int x = 0, dx = 1;
        for (int i = 0; i < N; i++) {
            int y = 0, dy = 1;
            for (int j = 0; j < M; j++) {
                cout << board[x][y];
                int ny = y + dy;
                if (ny < 0 || ny >= V) dy = -dy;
                else y = ny;
            }
            int nx = x + dx;
            if (nx < 0 || nx >= U) dx = -dx;
            else x = nx;
            cout << '\n';
        }
    }
    return 0;
}