#include <bits/stdc++.h>
using namespace std;

int main() {
   ios::sync_with_stdio(false);
   cin.tie(nullptr);
   int n, x;
   cin >> n >> x;

   vector<int> coins(n);
   for (int i = 0; i < n; i++) {
       cin >> coins[i];
   }

   vector<int> dp(x + 1, x + 1);
   dp[0] = 0;
   
   for (int i = 1; i <= x; i++) {
       for (int j = 0; j < coins.size(); j++) { 
           if (i >= coins[j]) {
               dp[i] = min(dp[i], dp[i - coins[j]] + 1);
           }
       }
   }

   if (dp[x] > x) 
       cout << -1;
   else
       cout << dp[x];
       
   return 0;
}