#include <iostream>
#include <string>

using namespace std;

string m;
int s;

// m, s가 전역변수로 선언되었기 때문에 지역변수인 w, idx와 비교가 가능하다.
bool check(string w) {
    int idx = 0;
    for (auto c : w) { // auto 키워드는 자동으로 자료형을 확인해서 맞춰준다.
        // w가 문자열이기 때문에 auto c : w는 w 안의 각각의 문자를 의미하고, auto는 char과 동일시된다.
        if (c == m[idx])
            idx++;
        if (idx == s) // 순서대로 m에 있는 모든 문자가 등장했다면 해당 단어를 만들 수 있다.
            return 1;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string ans = "No Jam"; // 만들 수 있는 단어가 없을 때 (default 문자열)
    double maximum = 0; // maximum에 들어갈 가능성이 있는 최솟값보다 작은 값을 설정한다.
    cin >> m;
    s = m.length();
    int N;
    cin >> N;
    while (N--) {
        string w;
        int g, idx = 0;
        cin >> w >> g;
        if (check(w)) {
            double temp = (double) g / (w.length() - s);
            // 정수 / 정수 = 몫 이기 때문에 형변환을 한다. 나누는 쪽에 형변환을 해도 된다.
            if (temp > maximum) {
                maximum = temp;
                ans = w;
            }
        }
    }
    cout << ans;
    return 0;
}