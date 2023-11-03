/**
 * @author phanttien
 * @email phanttien@outlook.com
 * @create date 2023-06-03 11:39:26
 * @modify date 2023-06-03 11:39:26
 * @desc [queenfight]
 */
#include <bits/stdc++.h>
using namespace std; 

int main() {
    int x1, y1;
    int x2, y2;
    
    char c; 
    cin >> c >> y1;
    x1 = c - 'a';
    cin >> c >> y2;
    x2 = c - 'a';
    
    if (x1 == x2 || y1 == y2 || abs(x1 - x2) == abs(y1 - y2)) {
        cout << "YES\n";
        return 0;
    }
    
    cout << "NO";
    return 0;
}