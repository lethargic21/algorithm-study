#include<bits/stdc++.h>
using namespace std;

int main() 
{
	int N;
	cin >> N;

    while(N--)
    {
        int ans = 0;
        int k;
        cin >> k;
        int arr[30002] = {0,};

        for(int i = 0; i < k; i++)
            cin >> arr[i];

        int flag = 0;

        for(int i = 0; i < k; i++)
        {
            if (flag == 0 && arr[i] > arr[i+1]){
            flag = 1;
            ans += 1;
            }
            else if (flag == 1 && arr[i] < arr[i+1]){
            flag = 0;
            ans += 1;
            }
        }
        ans++;
        cout << ans << endl; 
        

    }

    return 0;
}