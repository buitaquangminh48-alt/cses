#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while(n--) {
        int x, y;
        cin >> x >> y;

        long long layer = max(x, y);
        long long result;

        if (x == layer) {
            if (layer % 2 == 0) {
                result = layer * layer - y + 1;
            } else {
                result =  (layer-1) * (layer-1) + y;
            }
        } else {
            if (layer % 2 == 0) {
                result = (layer-1) * (layer-1) + x;
            } else {
                result = layer * layer - x + 1; 
            }
        }

        cout << result << "\n";
    }

    return 0;
}