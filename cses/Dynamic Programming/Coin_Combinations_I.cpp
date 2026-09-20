/*
Coin Combinations I

Đề:
Cho n loại đồng xu và số tiền x.
Hỏi có bao nhiêu cách dùng các đồng xu để tạo ra đúng x?

Lưu ý:
Thứ tự các đồng xu được xem là khác nhau.

Ví dụ:
coins = {1, 2}

Tạo 3 tiền:

1 + 1 + 1
1 + 2
2 + 1

=> 3 cách.

--------------------------------------------------

Mình hiểu bài này như thế nào?

Muốn tạo ra tổng i thì mình thử nghĩ:

=> Đồng xu cuối cùng có thể là đồng nào?

Nếu đồng xu cuối cùng là coin[j]:

    i
    ↓ bóc coin[j]
    i - coin[j]

Vậy trước khi bỏ đồng xu cuối vào,
mình phải tạo được tổng:

    i - coin[j]

Nếu số cách tạo i - coin[j] là:

    dp[i - coin[j]]

thì sau khi thêm coin[j] vào cuối,
mỗi cách đó tạo ra một cách mới để tạo i.

=> đóng góp:

    dp[i - coin[j]]

Thử tất cả các đồng xu có thể làm đồng cuối
rồi cộng tất cả lại.

--------------------------------------------------

dp[i] là gì?

=> dp[i] = số cách để tạo ra đúng tổng i.

i là gì?

=> i = tổng tiền hiện tại mà mình đang tìm số cách tạo ra.

j là gì?

=> j = vị trí của đồng xu đang được xét
   xem nó có phải đồng xu cuối hay không.

--------------------------------------------------

Khởi tạo:

    vector<int> dp(x + 1, 0);

Ở bài này dùng 0 vì:

    dp[i] = số cách tạo tổng i

Ban đầu chưa xét đồng xu nào,
nên mỗi dp[i] bắt đầu với 0 cách.

Sau đó từng đồng xu sẽ đóng góp thêm:

    dp[i] += dp[i - coin]

--------------------------------------------------

Tại sao dp[0] = 1?

Muốn tạo tổng 0 thì có đúng 1 cách:

=> không chọn đồng xu nào.

Cách này là trạng thái bắt đầu để các trạng thái khác
có thể xây dựng lên.

Ví dụ:

i = 1
coin = 1

dp[1] += dp[0]

=> có 1 cách:

1

--------------------------------------------------

Ví dụ:

coins = {1, 2, 3}
x = 3

Khi i = 3:

Nếu đồng cuối là 1:
    trước đó cần tạo 2
    => có dp[2] cách

Nếu đồng cuối là 2:
    trước đó cần tạo 1
    => có dp[1] cách

Nếu đồng cuối là 3:
    trước đó cần tạo 0
    => có dp[0] = 1 cách

Vậy:

    dp[3] = dp[2] + dp[1] + dp[0]

Các cách tạo 3 là:

    1 + 1 + 1
    1 + 2
    2 + 1
    3

=> 4 cách.

--------------------------------------------------

Khác với Minimizing Coins:

Minimizing Coins:
    mỗi đồng xu là một phương án
    => chọn phương án nhỏ nhất
    => min()

Coin Combinations I:
    mỗi đồng xu cuối đóng góp một nhóm cách khác nhau
    => cộng tất cả các nhóm
    => +

--------------------------------------------------

Công thức mình tự rút ra:

    dp[i] += dp[i - coins[j]]

và vì số cách có thể cực lớn:

    dp[i] = (dp[i] + dp[i - coins[j]]) % 1000000007

--------------------------------------------------

Lỗi / thứ từng quên:

1. Quên modulo 1e9+7
   => số cách tăng rất nhanh.

2. Warning signed / unsigned:

       int j
       coins.size() -> size_t

   => đổi j thành unsigned / size_t để tránh warning.

--------------------------------------------------

Cách mình nhớ bài:

Muốn tạo i
=> nhìn vào đồng xu cuối
=> bóc nó ra
=> còn i - coin
=> lấy tất cả cách tạo phần còn lại
=> thêm đồng cuối vào
=> cộng tất cả các đồng xu cuối lại.

*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];

    vector<int> dp(x + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= x; i++) {
        for (unsigned int j = 0; j < coins.size(); j++) {
            if (i >= coins[j]) 
                dp[i] = (dp[i] + dp[i - coins[j]]) % 1000000007LL;
        }
    }
    
    cout << dp[x];

    return 0;
}