#include <math.h>

#include <algorithm>
#include <iostream>
using namespace std;

const int N = 1e3 + 5;

void solve() {
    int k, n, x = 0;
    cin >> n >> k;
    long long sum = n * k;
    int a[N], cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    cnt++;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1] + 1)
            cnt++;
        else {
            x = 1;
            while (x) {
                int l = x * (x - 1) / 2 + 1;
                int r = x * (x + 1) / 2;
                if (cnt >= l && cnt <= r)
                    break;
                x++;
            }

            cnt = 1;
            sum += (x - 1) * k;
        }
        if (i == n - 1) {
            x = 1;
            while (x) {
                int l = x * (x - 1) / 2 + 1;
                int r = x * (x + 1) / 2;
                if (cnt >= l && cnt <= r)
                    break;
                x++;
            }

            cnt = 1;
            sum += (x - 1) * k;
        }
    }
    cout << sum << '\n';
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}