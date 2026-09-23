#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n); 
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end());

    vector<int> b(m);
    for (int i = 0; i < m; i++)
        cin >> b[i];
    
    sort(b.begin(), b.end());

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    for (int i = 0; i < m; i++)
        cout << b[i] << " ";
    cout << endl;

    int cnt = 0;
    int i = 0;
    int j = 0;

    while (i < n && j < m) {
        if (b[j] >= a[i] - k && b[j] <= a[i] + k) {
            cout << "Do can ho thu " << j + 1 
                << " co dien tich b[j=" << j + 1 << "](" << b[j] << ") >= a[i=" << i + 1
                << "] - " << k << " (" << a[i] - k << ") va <= a[i" << i << "] + " << k 
                << " (" << a[i] + k << ") nen:\n";
            cout << "So nguoi co dc can ho thoa man nhu cau tang len: ";
            cnt++;
            cout << cnt << endl;
            cout << "Va ta di qua tiep den nguoi thu ";
            i++;
            cout << i + 1<< " voi can ho thu ";
            j++;
            cout << j + 1<< endl << endl;
        } else if (b[j] < a[i] - k) {
            cout << "Vi can ho thu " << j + 1<< " co dien tich b[j=" << j + 1 << "](" << b[j] << ") < "
                << "a[i=" << i + 1<< "] - " << k << " (" << a[i] - k << ") rat nhieu so vs nhu cau nguoi thue nen ta di qua can ho thu ";
            j++;
            cout << j + 1 << " de so sanh tiep! (vi can ho co the co kha nang co dien tich thoa man nhu cau cua nguoi nay)\n\n";
        } else {
            cout << "Vi can ho thu " << j + 1<< " co dien tich b[j=" << j + 1 << "](" << b[j] << ") > "
                << "a[i=" << i + 1 << "] + " << k << " (" << a[i] + k << ") rat nhieu so vs nhu cau nguoi thue nen ta di qua nguoi thu ";
            i++;
            cout << i + 1 << " de xet tiep luon! (tai neu can ho sau lon hon nhu cau cua nguoi nay roi thi cx thiet su ko con can ho nao thoa man nhu cau nguoi nay nx)\n\n";
        }
    }

    cout << cnt;

    return 0;
}

