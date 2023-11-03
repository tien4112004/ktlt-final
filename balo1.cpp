/**
 * @author 22120368
 * @email 22120368@student.hcmus.edu.vn
 * @create date 2023-06-02 17:53:35
 * @modify date 2023-06-02 17:53:35
 * @desc BALO1 submission
 */
#include <iostream>
#include <vector>
using namespace std;

vector<int> ans;
int max_value = 0;

void backtrack(int a[], int n, vector<int> track, int pos, int sum, int target) {
    if (sum > target) return;
    if (sum <= target && sum > max_value) {
        max_value = sum;
        ans = track;
    }

    for (int i = pos; i < n; i++) {
        track.push_back(i);
        backtrack(a, n, track, i + 1, sum + a[i], target);
        track.pop_back();
    }
}

int main() {
    int n; cin >> n; 
    int target; cin >> target;  
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> track;
    backtrack(a, n, track, 0, 0, target);

    cout << max_value << '\n';
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' '; 
    }
    return 0;
}