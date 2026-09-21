/*
========================================================
Sliding Window Sum
========================================================

Đề bài:
Cho một dãy n phần tử và kích thước cửa sổ k.
Xét tất cả các cửa sổ liên tiếp có đúng k phần tử.

Ví dụ:
arr = [3, 0, 1, 8, 2, 4, 7, 6]
k = 5

Các cửa sổ:

Window 1: [3, 0, 1, 8, 2]       -> sum = 14
Window 2: [0, 1, 8, 2, 4]       -> sum = 15
Window 3: [1, 8, 2, 4, 7]       -> sum = 22
Window 4: [8, 2, 4, 7, 6]       -> sum = 27

Sau đó XOR tất cả các tổng lại.


--------------------------------------------------------
CÁCH MÌNH TỰ NGHĨ RA SLIDING WINDOW
--------------------------------------------------------

Ban đầu mình nghĩ:

Có nhiều window -> phải lấy từng window ra -> cộng từng
window -> lưu từng tổng lại.

Ví dụ:

[3,0,1,8,2] -> 14
[0,1,8,2,4] -> 15
[1,8,2,4,7] -> 22
[8,2,4,7,6] -> 27

Nhưng cách này đang tính lại rất nhiều phần tử đã được tính.


Sau khi nhìn kỹ hai window liên tiếp:

Window 1:
[3, 0, 1, 8, 2]

Window 2:
[0, 1, 8, 2, 4]

Ta thấy:

- 3 vừa đi ra khỏi cửa sổ.
- 4 vừa đi vào cửa sổ.
- Các phần tử còn lại vẫn giữ nguyên.

Vì vậy không cần cộng lại toàn bộ Window 2.

Nếu:
sum Window 1 = 14

thì:

sum Window 2
= 14 - 3 + 4
= 15


Tiếp tục:

Window 3:
[1, 8, 2, 4, 7]

= 15 - 0 + 7
= 22


Window 4:
[8, 2, 4, 7, 6]

= 22 - 1 + 6
= 27


=> Cửa sổ mới được tạo từ cửa sổ cũ bằng cách:

    1. Bỏ phần tử vừa rời khỏi bên trái.
    2. Thêm phần tử mới vừa đi vào bên phải.

Do đó:

    sum = sum - arr[i-k] + arr[i]


--------------------------------------------------------
Ý NGHĨA CỦA i VÀ i-k
--------------------------------------------------------

Khi i chạy từ k đến n-1:

arr[i]
    = phần tử mới vừa bước vào cửa sổ.

arr[i-k]
    = phần tử vừa bước ra khỏi cửa sổ.

Ví dụ k = 5, i = 5:

arr[i-k] = arr[5-5] = arr[0]
           = phần tử đầu tiên, vừa bị loại khỏi window.

arr[i] = arr[5]
       = phần tử mới được thêm vào.


--------------------------------------------------------
TẠI SAO KHÔNG CẦN LƯU TỪNG WINDOW / TỪNG SUM?
--------------------------------------------------------

Ban đầu mình định dùng vector để lưu từng window và từng sum.

Nhưng sau khi nhận ra:

    sum mới = sum cũ - phần tử đi ra + phần tử đi vào

thì chỉ cần giữ lại:

    sum = tổng của cửa sổ hiện tại

Không cần lưu toàn bộ các window.

Nếu đề yêu cầu XOR các tổng:

    ans ^= sum;

Mỗi lần có một window mới, cập nhật XOR ngay.


--------------------------------------------------------
ĐỘ PHỨC TẠP
--------------------------------------------------------

Cách ngây thơ:

Mỗi window cộng lại k phần tử
=> O(n * k)

Sliding Window:

- Tính window đầu tiên: O(k)
- Mỗi window tiếp theo: 1 phép trừ + 1 phép cộng
=> O(n)

Bộ nhớ xử lý cửa sổ:
=> O(1) nếu đã có mảng arr.


--------------------------------------------------------
ĐIỀU QUAN TRỌNG NHẤT MÌNH HỌC ĐƯỢC
--------------------------------------------------------

Không phải nhớ công thức:

    sum = sum - arr[i-k] + arr[i]

Mà phải nhìn vào sự thay đổi giữa hai cửa sổ liên tiếp:

    Window mới
    = Window cũ
    - phần tử đi ra
    + phần tử đi vào

Sliding Window không tính lại từ đầu.
Nó tận dụng kết quả của cửa sổ trước để xây dựng
kết quả của cửa sổ tiếp theo.

========================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k, x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<long long> arr(n);

    arr[0] = x;

    for (int i = 1; i < n; i++) {
        arr[i] = (a * arr[i-1] + b) % c;
    }

    /*
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;*/

    long long sum = 0, ans = 0;

    for (int i = 0; i < k; i++) {
        /* cout << "sum = sum + arr[i=" << i << "] \n= "
            << "sum = " << sum << " + " << arr[i] << " \n= "; */
        sum += arr[i];
        //cout << sum << endl << endl;
    }

    ans ^= sum;
    //00000 -> 0
    //^
    //10110 -> 14
    //
    //=> 14

    for (int i = k; i < n; i++) {
        /*cout << "sum = sum - arr[i - k" << "] + arr[i=" << i << "] \n= "
            << "sum - arr[" << i << " - " << k << "] + arr[i=" << i << "] \n= "
            << sum << " - " << arr[i-k] << " + " << arr[i] << " \n= ";*/
        sum = sum - arr[i - k] + arr[i];

        ans ^= sum;
    }

    cout << ans;

    return 0;
}