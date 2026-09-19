#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    for (long long k = 1; k <= n; k++) {
        long long total = (k*k) * (k*k - 1) / 2; //Tổng số cách đặt 2 quân mã bất kỳ
        long long ans = 4 * (k - 1) * (k - 2); //Số cách đặt 2 quân mã tấn công nhau
        cout << total - ans << "\n";
    }

    return 0;
}