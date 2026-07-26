#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int N;
    cin >> N;
    char c;
    do {
        cout << "? 1" << '\n';
        // 주의) N이 1인 경우에는 반드시 ? 1을 질문해야 한다.
        cout << flush;
        cin >> c;
    } while (c == 'N');
    cout << "! 1";
    cout << flush;
    return 0;
}