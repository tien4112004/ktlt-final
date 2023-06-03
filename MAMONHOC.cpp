/**
 * @author phanttien
 * @email phanttien@outlook.com
 * @create date 2023-06-03 11:41:50
 * @modify date 2023-06-03 11:41:50
 * @desc [MAMONHOC]
 */

#include <bits/stdc++.h>
using namespace std;
/* n: số phần tử muốn nhập */

int main() {
    cin.tie(nullptr) -> sync_with_stdio(false);

    int n; cin >> n;
    cin.ignore();
    set<string> s;
    for(int i = 0; i < n; i++) {
        string str;
        getline(cin, str);
        
        stringstream ss(str);
        string hash;
        string temp;
        int words = 0;
        while (ss >> temp) {
            hash += toupper(temp[0]);
            // temp[0] & (~(1 << 5));
            words++;
        }
        int c = words;
        while (s.find(hash) != s.end()) {
            c--;
            hash.clear();
            ss = stringstream(str);
            for(int i = 0; i < words; i++) {
                ss >> temp;
                hash += toupper(temp[0]);
                if (i >= c) 
                    hash += tolower(temp.back());
            }
        }
        s.insert(hash);
        cout << hash << '\n';
    }

    // cout << "\nTime: " << clock() / (double)1000 << " secs"; // CLOCK
    return 0;
}