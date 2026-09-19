#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //while (true) {
    int n;
    cin >> n;

    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) { // tính số cách tạo ra tổng i 
        for (int j = 1; j <= 6 && j <= i; j++) { // để tạo ra tổng i, viên xúc xắc cuối có thể là bao nhiêu?
            /*cout << "dp[i=" << i << "] = "
                << "(dp[i=" << i << "] + dp[i-j=" << i << "-" << j << "=" << i-j << "]) % 1000000007LL = "
                << "(" << dp[i] << " + " << dp[i-j] << ") % 1000000007LL = ";*/
            dp[i] = (dp[i] + dp[i - j]) % 1000000007LL;
            //cout << dp[i] << endl;
        }
    }
    //cout << endl;
    cout << dp[n];
    //}
    return 0;
}