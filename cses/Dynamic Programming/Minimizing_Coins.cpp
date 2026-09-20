/*
Đề bài:
Cho n đồng xu và số tiền x.
Cần tìm số đồng xu ít nhất để cộng lại đúng bằng x.
Nếu không thể tạo ra x thì in -1.


* Hiểu theo kiểu người:

Muốn tạo được đúng x tiền thì mình phải làm gì?

=> Thử chọn một đồng xu làm đồng xu cuối cùng.


Nếu đã chọn đồng xu cuối cùng rồi mà vẫn chưa đủ x tiền
thì trước đồng xu đó mình còn thiếu bao nhiêu tiền?

=> Lấy x - giá trị đồng xu cuối.


Vậy số tiền còn thiếu đó thì làm gì?

=> Tiếp tục tìm cách tạo ra số tiền còn thiếu
bằng ít đồng xu nhất.


Nếu tiếp tục bóc đồng xu như vậy thì khi nào dừng?

=> Khi số tiền còn lại = 0.
   Khi đó không cần bóc thêm đồng xu nào.


Nhưng có nhiều loại đồng xu khác nhau,
vậy phải làm sao?

=> Thử từng đồng xu xem nếu nó là đồng xu cuối
thì cần tổng cộng bao nhiêu đồng xu.


Sau khi thử hết:

=> Giữ lại cách dùng ít đồng xu nhất.


Nói ngắn gọn:

Muốn tạo x tiền
=> chọn một đồng xu cuối
=> giải tiếp phần tiền còn lại
=> cộng thêm 1 đồng xu vừa chọn
=> thử với tất cả đồng xu
=> lấy phương án ít đồng xu nhất.


Ví dụ:
x = 6, coins = {1, 3, 4}

Nếu chọn 3 làm đồng cuối:
=> còn 6 - 3 = 3 tiền
=> 3 tiền cần 1 đồng (3)
=> thêm đồng 3 cuối
=> tổng = 2 đồng: 3 + 3


Nếu chọn 4 làm đồng cuối:
=> còn 6 - 4 = 2 tiền
=> 2 tiền cần 2 đồng (1 + 1)
=> thêm đồng 4 cuối
=> tổng = 3 đồng: 1 + 1 + 4


=> So sánh các cách
=> giữ cách ít đồng xu nhất.


* Hiểu theo kiểu máy:

“số tiền còn lại”
        ↓
i - coins[j]

“số đồng xu ít nhất để tạo phần còn lại”
        ↓
dp[i - coins[j]]

“thêm đồng xu cuối”
        ↓
+ 1

“thử mọi đồng xu rồi lấy ít nhất”
        ↓
min(...)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);

   while (true) {
   int n, x;
   cin >> n >> x;

   vector<int> coins(n);
   for (int i = 0; i < n; i++) {
       cin >> coins[i];
   }

   vector<int> dp(x + 1, x + 1);
   dp[0] = 0;
   cout << "Cho dp[0] = 0\n\n"; 
   
   for (int i = 1; i <= x; i++) {
       for (int j = 0; j < coins.size(); j++) { 
           if (i >= coins[j]) {
               cout << "Vi i = " << i << " >= coins[j=" << j << "] = " << coins[j] << " nen:\n";
               cout << "dp[i=" << i << "] = min(dp[i=" << i << "], dp[i - coins[j=" << j << "]] + 1) \n= "
                    << "min(dp[i=" << i << "], dp[" << i << " - " << coins[j] << "] + 1) \n= "
                    << "min(dp[i=" << i << "], dp[" << i - coins[j] << "] + 1) \n= "
                    << "min(dp[i=" << i << "], " << dp[i - coins[j]] << " + 1) \n= "
                    << "min(" << dp[i] << ", " << dp[i - coins[j]] + 1 << ") \n= ";
               dp[i] = min(dp[i], dp[i - coins[j]] + 1);
               cout << dp[i] << endl << endl;
           }
       }
   }

   if (dp[x] > x)  {
       cout << "Do dp[x=" << x << "] > x = " << x << " nen in ra: ";
       cout << -1 << endl << endl;
   } else {
       cout << "Do dp[x=" << x << "] < x = " << x << " nen so dong xu toi thieu de co the tong lai bang x = " << x << " la: ";
       cout << dp[x] << endl << endl;
   }
   }
       
   return 0;
}
