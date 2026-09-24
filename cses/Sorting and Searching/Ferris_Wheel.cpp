#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end());

     for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    int l = 0, r = n - 1, ans = 0;

    // Khi l == r: chỉ còn 1 đứa trẻ chưa được xếp thuyền.
    // Khi l > r: hai con trỏ đã đi xuyên qua nhau => tất cả đã được xử lý.
    // Vì vậy phải dùng l < r, KHÔNG dùng l != r (dễ chạy thêm 1 vòng và sai logic).
    while (l < r) {
        int sum = a[l] + a[r];

        cout << "[l=" << l << ", r=" << r << "] "
            << a[l] << " + " << a[r] << " = " << sum << '\n';

        if (sum <= x) {
            cout << "-> Ghep duoc, left++\n";
            l++;
        } else {
            cout << "-> Khong ghep duoc\n";
        }

        ans++;
        cout << "-> Them 1 thuyen, ans = " << ans << '\n';

        r--;
        cout << "-> right--\n\n";
    }
    if (l == r) {
        ans++; // Đứa trẻ cuối đi 1 mình
    }
    cout << ans;
    return 0;
}