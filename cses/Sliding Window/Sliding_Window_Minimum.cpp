/*
================================================================================
                    SLIDING WINDOW MINIMUM + XOR
================================================================================

ĐỀ BÀI:
Cho một mảng arr gồm n phần tử và kích thước cửa sổ k.

Cửa sổ trượt từ trái sang phải:

Ví dụ:
arr = [3, 0, 1, 8, 2, 4, 7, 6]
k = 5

Các cửa sổ:

[3, 0, 1, 8, 2] -> min = 0
   [0, 1, 8, 2, 4] -> min = 0
      [1, 8, 2, 4, 7] -> min = 1
         [8, 2, 4, 7, 6] -> min = 2

Sau đó XOR tất cả các minimum lại với nhau.


================================================================================
                         QUÁ TRÌNH TÌM LỜI GIẢI
================================================================================

1. Ý TƯỞNG BAN ĐẦU
-------------------

Mỗi lần cửa sổ trượt, chỉ cần tìm minimum trong k phần tử.

Nhưng nếu mỗi cửa sổ lại quét toàn bộ k phần tử:

    O(k) cho mỗi cửa sổ
    Có khoảng O(n) cửa sổ

=> O(nk)

Nếu n và k lớn thì rất dễ TLE.


2. THỬ DÙNG MULTISET
---------------------

Ý tưởng:

    - Đưa toàn bộ phần tử của cửa sổ vào multiset.
    - *ms.begin() luôn là phần tử nhỏ nhất.
    - Khi cửa sổ trượt:
        + erase phần tử đi ra.
        + insert phần tử đi vào.

Ví dụ:

    [3, 0, 1, 8, 2]

    ms = {0, 1, 2, 3, 8}
           ^
           begin() = minimum

Cách này đúng về mặt logic.

Nhưng:

    insert -> O(log k)
    erase  -> O(log k)

=> Tổng O(n log k)

Với dữ liệu rất lớn có thể TLE.


3. THỬ SORT TOÀN BỘ MẢNG
-------------------------

Ý tưởng:

    sort(arr.begin(), arr.end());

Có vẻ như sau khi sort một lần thì có thể lấy minimum nhanh hơn.

Nhưng vấn đề:

    Sliding Window không chỉ quan tâm VALUE.
    Nó còn quan tâm POSITION.

Ví dụ:

    arr = [3, 0, 1, 8, 2, 4, 7, 6]

    sort ->
    [0, 1, 2, 3, 4, 6, 7, 8]

Sau khi sort, ta không còn biết phần tử nào thuộc
cửa sổ hiện tại nữa.

Ví dụ:

    Cửa sổ [3, 0, 1, 8, 2]

minimum = 0

Nhưng khi cửa sổ trượt:

    [0, 1, 8, 2, 4]

minimum vẫn = 0.

Sau đó:

    [1, 8, 2, 4, 7]

minimum = 1.

Chỉ nhìn mảng đã sort không đủ để biết phần tử nào
đang nằm trong cửa sổ.

=> Sort toàn bộ mảng không giải quyết được bài toán.


4. CÂU HỎI QUAN TRỌNG
----------------------

Nếu đã biết minimum hiện tại, khi cửa sổ trượt:

    "Mình có thể bỏ qua những phần tử nào chắc chắn
     không bao giờ trở thành minimum nữa?"

Ví dụ:

    [3, 0]

Khi gặp 0:

    3 > 0

Nếu 0 vẫn còn trong cửa sổ thì 3 không thể nào
là minimum trước 0 được.

=> 3 có thể bị loại.

Ví dụ:

    [0, 1, 8, 2]

Khi gặp 2:

    8 > 2
    => 8 không còn cơ hội làm minimum.
    => loại 8.

    1 < 2
    => 1 vẫn có thể là minimum.
    => giữ 1.

Ta chỉ cần giữ lại những phần tử còn "có khả năng thắng"
trong cuộc đua tìm minimum.


================================================================================
                         MONOTONIC DEQUE
================================================================================

Dùng deque để lưu INDEX của các phần tử ứng viên.

Ví dụ:

    arr = [3, 0, 1, 8, 2]

Sau khi xử lý:

    dq có thể chứa:

        [index của 0, index của 1, index của 2]

Giá trị tương ứng:

        [0, 1, 2]

Các giá trị trong deque luôn tăng dần:

        0 <= 1 <= 2

=> Phần tử đầu deque luôn là minimum của cửa sổ.


TẠI SAO LƯU INDEX MÀ KHÔNG LƯU VALUE?
---------------------------------------

Vì cần biết phần tử đã đi ra khỏi cửa sổ chưa.

Ví dụ:

    i = 5
    k = 3

Cửa sổ hiện tại bắt đầu từ:

    i - k + 1 = 3

Nếu:

    dq.front() < 3

thì index đó đã nằm ngoài cửa sổ.

=> pop_front().


================================================================================
                              3 BƯỚC CHÍNH
================================================================================

BƯỚC 1: LOẠI PHẦN TỬ ĐÃ RA KHỎI CỬA SỔ
-----------------------------------------

    if (!dq.empty() && dq.front() < i - k + 1)
        dq.pop_front();

Nếu index đầu deque nhỏ hơn vị trí bắt đầu
của cửa sổ hiện tại -> phần tử đã rời khỏi cửa sổ.


BƯỚC 2: LOẠI CÁC PHẦN TỬ KHÔNG CÒN KHẢ NĂNG LÀM MIN
-----------------------------------------------------

    while (!dq.empty() && arr[dq.back()] > arr[i])
        dq.pop_back();

Nếu phần tử mới nhỏ hơn phần tử cuối deque:

    arr[i] < arr[dq.back()]

thì phần tử cũ không còn cơ hội làm minimum
miễn là phần tử mới vẫn còn trong cửa sổ.

=> loại phần tử cũ.

Đây chính là lý do deque luôn giữ giá trị tăng dần.


BƯỚC 3: THÊM INDEX HIỆN TẠI
----------------------------

    dq.push_back(i);

Sau khi loại những phần tử không cần thiết,
đưa index hiện tại vào deque.


LẤY MINIMUM
-----------

Khi đã đủ k phần tử:

    if (i >= k - 1)
        ans ^= arr[dq.front()];

dq.front() luôn là index của phần tử nhỏ nhất.


================================================================================
                              TẠI SAO O(n)?
================================================================================

Nhìn vào:

    while (!dq.empty() && arr[dq.back()] > arr[i])
        dq.pop_back();

Có vẻ như có thể O(n^2), vì có while.

Nhưng thực tế:

Mỗi index chỉ:

    - được push vào deque tối đa 1 lần.
    - bị pop ra khỏi deque tối đa 1 lần.

=> Tổng số lần push + pop là O(n).

Vì vậy:

    Time Complexity  : O(n)
    Space Complexity : O(k)

Đây là lý do monotonic deque nhanh hơn multiset:

    Brute force       -> O(nk)
    multiset          -> O(n log k)
    monotonic deque   -> O(n)


================================================================================
                              BÀI HỌC
================================================================================

Không phải lúc nào cũng cần giữ toàn bộ dữ liệu.

Nếu một phần tử đã chắc chắn không thể trở thành đáp án
trong tương lai thì có thể loại nó ngay.

Với Sliding Window Minimum:

    "Không giữ tất cả phần tử.
     Chỉ giữ những phần tử còn có khả năng trở thành minimum."

Đây chính là ý tưởng của MONOTONIC DEQUE.

💡 Điều đáng nhớ không phải chỉ là:

    deque<int> dq;

mà là câu hỏi dẫn tới nó:

    "Khi cửa sổ trượt, phần tử nào chắc chắn không còn
     cơ hội trở thành minimum nữa?"

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k, x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;

    vector<int> arr(n);
    arr[0] = x;
    for (int i = 1; i < n; i++) {
        arr[i] = (a * arr[i-1] + b) % c;
    }

    //sort(arr.begin(), arr.end());

    
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    long long /*minNums = 1e9,*/ ans = 0;  

    /*
    multiset<long long> ms;
    
    for (int i = 0; i < k; i++) {
        ms.insert(arr[i]);
    }*/

    //cout << minNums << endl;

    //ans ^= minNums;

    /*
    for (int i = k; i < n; i++) {
        cout << "minNums = min(minNums, arr[i - k + 1] \n= "
            << "min(minNums" << ", arr[" << i << " - " << k << " + 1] \n= "
            << "min(" << minNums << ", " << arr[i - k + 1] << ") \n= ";
        minNums = min(arr[i - k + 1], arr[i]);
        cout << minNums << endl << endl;

        cout << "ans = ans ^ minNums \n= "
            << ans << " ^ " << minNums << " \n= ";
        ans ^= minNums;
        cout << ans << endl << endl;

        //minNums = min(minNums, ms);

        cout << "ans = ans ^ arr[i - k] \n= "
            << "ans ^ " << "arr[" << i << " - " << k << "] \n= "
            << ans << " ^ " << arr[i - k] << " \n= ";


        ans ^= *ms.begin(); // minNums; // arr[i - k];

        //minNums = 1e9;

        //cout << ans << endl << endl;

        ms.erase(ms.find(arr[i - k]));

        ms.insert(arr[i]);

    }*/

    //ans ^= *ms.begin();

    deque<int> dq;
    
    
    cout << "\n\n--- BAT DAU TRACE CODE ---\n";
    for (int i = 0; i < arr.size(); i++) {
        cout << "\n[Buoc i = " << i << "] Xet arr[" << i << "] = " << arr[i] << "\n";

        // 1. Thằng nào đã ra khỏi cửa sổ → đá ra
        if (!dq.empty() && dq.front() < i - k + 1) {
            cout << "   -> Da out cua so: Da phan tu arr[" << dq.front() << "]\n";
            dq.pop_front();
        }

        // 2. Thằng nào lớn hơn arr[i] → không còn cơ hội làm MIN
        while (!dq.empty() && arr[dq.back()] > arr[i]) {
            cout << "   -> Duoi khoi duoi: arr[" << dq.back() << "]=" << arr[dq.back()] 
                 << " vi no lon hon arr[" << i << "]=" << arr[i] << "\n";
            dq.pop_back();
        }

        // 3. Đưa i vào hàng
        dq.push_back(i);

        // In ra trang thai Deque hien tai de de quan sat
        cout << "   Trang thai Deque hien tai (Format: index->gia tri): [";
        for (int idx : dq) {
            cout << " " << idx << "->" << arr[idx] << " ";
        }
        cout << "]\n";

        // 4. Đủ k phần tử → lấy MIN
        if (i >= k - 1) {
            int current_min = arr[dq.front()];
            ans ^= current_min;
            cout << "   => Cua so da du k. MIN hien tai = " << current_min 
                 << " (Gia tri ans sau khi XOR = " << ans << ")\n";
        }
    }
    cout << "\n--- KET THUC TRACE ---\n";

    //cout << ans;

    /*
================================================================================
                            TRACE MONOTONIC DEQUE
================================================================================

Input:

    n = 8
    k = 5

    arr = [3, 0, 1, 8, 2, 4, 7, 6]

Quy ước:

    dq lưu INDEX, không lưu VALUE.

    dq = [0, 2, 4]

    nghĩa là:

        index :  0  2  4
        value :  3  1  2

    Giá trị trong dq luôn tăng dần.

    dq.front() = index của phần tử nhỏ nhất hiện tại.


-------------------------------------------------------------------------------
i = 0
arr[i] = 3
-------------------------------------------------------------------------------

Cửa sổ tạm thời:

    [3]

1. Kiểm tra phần tử đã ra khỏi cửa sổ:
    dq đang rỗng
    => không làm gì.

2. Loại phần tử lớn hơn arr[i]:
    dq đang rỗng
    => không làm gì.

3. Thêm i:

    dq = [0]

    value:
    dq = [3]

4. i < k - 1
   0 < 4
   => chưa đủ k phần tử, chưa lấy MIN.


-------------------------------------------------------------------------------
i = 1
arr[i] = 0
-------------------------------------------------------------------------------

Cửa sổ tạm thời:

    [3, 0]

1. Phần tử ra khỏi cửa sổ?
    Chưa.

2. Kiểm tra cuối deque:

    arr[dq.back()] = arr[0] = 3
    arr[i]        = arr[1] = 0

    3 > 0
    => 3 không còn cơ hội làm MIN.

    pop_back()

    dq = []

3. Thêm i:

    dq = [1]

    value:
    dq = [0]

4. Chưa đủ k phần tử.


-------------------------------------------------------------------------------
i = 2
arr[i] = 1
-------------------------------------------------------------------------------

Cửa sổ:

    [3, 0, 1]

1. Phần tử ra khỏi cửa sổ?
    Chưa.

2. Kiểm tra cuối deque:

    arr[1] = 0
    arr[2] = 1

    0 > 1 ? FALSE

    => giữ 0.

3. Thêm i:

    dq = [1, 2]

    value:
    dq = [0, 1]

4. Chưa đủ k phần tử.


-------------------------------------------------------------------------------
i = 3
arr[i] = 8
-------------------------------------------------------------------------------

Cửa sổ:

    [3, 0, 1, 8]

1. Phần tử ra khỏi cửa sổ?
    Chưa.

2. Kiểm tra cuối deque:

    arr[2] = 1
    arr[3] = 8

    1 > 8 ? FALSE

    => giữ 1.

3. Thêm i:

    dq = [1, 2, 3]

    value:
    dq = [0, 1, 8]

4. Chưa đủ k phần tử.


-------------------------------------------------------------------------------
i = 4
arr[i] = 2
-------------------------------------------------------------------------------

Cửa sổ:

    [3, 0, 1, 8, 2]

Đây là cửa sổ đầu tiên có đủ k = 5 phần tử.

1. Phần tử ra khỏi cửa sổ?

    i - k + 1
    = 4 - 5 + 1
    = 0

    dq.front() = 1

    1 < 0 ? FALSE

    => chưa có phần tử nào bị đá ra.


2. Loại phần tử lớn hơn 2:

    dq = [1, 2, 3]

    nhìn phần tử cuối:

    arr[3] = 8
    8 > 2
    => pop index 3

    dq = [1, 2]

    tiếp tục:

    arr[2] = 1
    1 > 2 ? FALSE

    => dừng.


3. Thêm i:

    dq = [1, 2, 4]

    value:

    index :  1  2  4
    value :  0  1  2


4. Đủ k phần tử:

    dq.front() = 1

    arr[1] = 0

    MIN = 0

    ans = 0 ^ 0
        = 0


Cửa sổ:

    [3, 0, 1, 8, 2]
     ^
    MIN = 0


-------------------------------------------------------------------------------
i = 5
arr[i] = 4
-------------------------------------------------------------------------------

Cửa sổ:

    [0, 1, 8, 2, 4]

1. Phần tử ra khỏi cửa sổ?

    i - k + 1
    = 5 - 5 + 1
    = 1

    dq.front() = 1

    1 < 1 ? FALSE

    => index 1 vẫn còn trong cửa sổ.


2. Loại phần tử lớn hơn 4:

    arr[dq.back()]
    = arr[4]
    = 2

    2 > 4 ? FALSE

    => không pop.


3. Thêm i:

    dq = [1, 2, 4, 5]

    value:

    [0, 1, 2, 4]


4. MIN:

    dq.front() = 1
    arr[1] = 0

    ans = 0 ^ 0
        = 0


Cửa sổ:

    [0, 1, 8, 2, 4]
     ^
    MIN = 0


-------------------------------------------------------------------------------
i = 6
arr[i] = 7
-------------------------------------------------------------------------------

Cửa sổ:

    [1, 8, 2, 4, 7]

1. Phần tử ra khỏi cửa sổ?

    i - k + 1
    = 6 - 5 + 1
    = 2

    dq.front() = 1

    1 < 2
    => index 1 đã ra khỏi cửa sổ.

    pop_front()

    dq = [2, 4, 5]


2. Loại phần tử lớn hơn 7:

    arr[5] = 4

    4 > 7 ? FALSE

    => không pop.


3. Thêm i:

    dq = [2, 4, 5, 6]

    value:

    [1, 2, 4, 7]


4. MIN:

    dq.front() = 2

    arr[2] = 1

    ans = 0 ^ 1
        = 1


Cửa sổ:

    [1, 8, 2, 4, 7]
     ^
    MIN = 1


-------------------------------------------------------------------------------
i = 7
arr[i] = 6
-------------------------------------------------------------------------------

Cửa sổ:

    [8, 2, 4, 7, 6]

1. Phần tử ra khỏi cửa sổ?

    i - k + 1
    = 7 - 5 + 1
    = 3

    dq.front() = 2

    2 < 3
    => index 2 đã ra khỏi cửa sổ.

    pop_front()

    dq = [4, 5, 6]


2. Loại phần tử lớn hơn 6:

    arr[6] = 7

    7 > 6
    => pop_back()

    dq = [4, 5]

    tiếp tục:

    arr[5] = 4

    4 > 6 ? FALSE

    => dừng.


3. Thêm i:

    dq = [4, 5, 7]

    value:

    [2, 4, 6]


4. MIN:

    dq.front() = 4

    arr[4] = 2

    ans = 1 ^ 2
        = 3


Cửa sổ:

    [8, 2, 4, 7, 6]
        ^
    MIN = 2


================================================================================
                              KẾT QUẢ
================================================================================

Các minimum:

    0
    0
    1
    2

XOR:

    0 ^ 0 ^ 1 ^ 2

  = 0 ^ 1 ^ 2
  = 1 ^ 2
  = 3

=> ans = 3


================================================================================
                         TRACE NGẮN GỌN
================================================================================

i     arr[i]    dq (INDEX)      dq (VALUE)       MIN     ans
----------------------------------------------------------------
0       3       [0]             [3]              -       -
1       0       [1]             [0]              -       -
2       1       [1,2]           [0,1]            -       -
3       8       [1,2,3]         [0,1,8]          -       -
4       2       [1,2,4]         [0,1,2]          0       0
5       4       [1,2,4,5]       [0,1,2,4]        0       0
6       7       [2,4,5,6]       [1,2,4,7]        1       1
7       6       [4,5,7]         [2,4,6]          2       3

================================================================================
                              CHỐT
================================================================================

Deque không giữ toàn bộ cửa sổ.

Nó chỉ giữ các "ứng viên" có khả năng trở thành MIN.

    - Ra khỏi cửa sổ → pop_front()
    - Lớn hơn phần tử mới → pop_back()
    - Phần tử mới → push_back()
    - dq.front() → MIN

Mỗi index chỉ vào deque 1 lần và ra khỏi deque 1 lần.

=> O(n)

================================================================================
*/

    return 0;
}