#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q, a, b;
    cin >> n >> q;
    //cout << n << " " << q << endl;
    vector<int> x(n);
    for (int i = 0; i < n; i++) 
        cin >> x[i];

    //for (int i = 0; i < n; i++) 
    //    cout << x[i] << " ";
    //cout << endl;

    vector<long long> pref(n + 1, 0);

    //pref[0] = 0;

    for (int i = 1; i <= n; i++) {
        cout << "pref[i=" << i << "] = pref[i - 1] + x[i - 1] \n= "
            << "pref[" << i << " - 1] + x[" << i << "- 1] \n= "
            << pref[i - 1] << " + " << x[i - 1] << " \n= ";
        pref[i] = pref[i - 1] + x[i - 1];
        cout << pref[i] << endl << endl;
    }
        
    while (q--) {
        
        cin >> a >> b;
        
        /*int sum = 0;
        for (int i = a-1; i < b; i++) {
            cout << "sum = sum + x[i=" << i << "] \n= "
                << sum << " + " << x[i] << " \n= ";
            sum += x[i];
            cout << sum << endl << endl;
        }*/
       
        //n = x.size() - 1;

        //vector<int> pref(n + 1, 0);

        //pref[0] = 0;

        /*for (int i = 1; i <= n; i++) {
            cout << "pref[i=" << i << "] = pref[i - 1] + x[i - 1] \n= "
                << pref[i - 1] << " + " << x[i - 1] << " \n= ";
            pref[i] = pref[i - 1] + x[i - 1];
            cout << pref[i] << endl << endl;
        }*/

        //long long sum = pref[b] - pref[a - 1];
        cout << pref[b] - pref[a - 1] << endl;
    }

    return 0;
}
